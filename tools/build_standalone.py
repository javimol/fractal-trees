#!/usr/bin/env python3
"""Build a single-file web viewer with the trees and bark texture embedded.

    python3 tools/build_standalone.py [--fragment] [-o dist/fractal-trees.html]

The result opens directly from disk (no web server needed). --fragment drops the
<html>/<head>/<body> wrapper, for hosts that add their own page skeleton.
"""
import argparse, base64, glob, io, json, os, re, struct, zlib

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def bmp_to_png_data_uri(path):
    """Convert an uncompressed 24-bit BMP to a PNG data URI (no dependencies)."""
    data = open(path, "rb").read()
    offset, = struct.unpack_from("<I", data, 10)
    width, height = struct.unpack_from("<ii", data, 18)
    bpp, = struct.unpack_from("<H", data, 28)
    if bpp != 24:
        raise SystemExit(f"{path}: only 24-bit BMPs are supported")
    row_size = (width * 3 + 3) & ~3
    rows = []
    for y in range(abs(height)):
        src = y if height < 0 else abs(height) - 1 - y  # PNG is top-down
        row = data[offset + src * row_size: offset + src * row_size + width * 3]
        rgb = bytearray(row)
        rgb[0::3], rgb[2::3] = row[2::3], row[0::3]  # BGR -> RGB
        rows.append(b"\x00" + bytes(rgb))

    def chunk(tag, body):
        return struct.pack(">I", len(body)) + tag + body + struct.pack(">I", zlib.crc32(tag + body) & 0xFFFFFFFF)

    png = b"\x89PNG\r\n\x1a\n" + chunk(b"IHDR", struct.pack(">IIBBBBB", width, abs(height), 8, 2, 0, 0, 0)) \
        + chunk(b"IDAT", zlib.compress(b"".join(rows), 9)) + chunk(b"IEND", b"")
    return "data:image/png;base64," + base64.b64encode(png).decode()


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("-o", "--output", default=os.path.join(ROOT, "dist", "fractal-trees.html"))
    ap.add_argument("--data", default=os.path.join(ROOT, "data", "chopos"))
    ap.add_argument("--fragment", action="store_true")
    args = ap.parse_args()

    files = sorted(glob.glob(os.path.join(args.data, "*.fra")),
                   key=lambda p: [int(t) if t.isdigit() else t for t in re.split(r"(\d+)", p)])
    payload = {"trees": [{"name": os.path.basename(f), "text": open(f).read()} for f in files]}
    bark = os.path.join(args.data, "bark.bmp")
    if not os.path.exists(bark):  # fall back to the first *.bmp, like the C viewer
        bmps = sorted(glob.glob(os.path.join(args.data, "*.bmp")))
        bark = bmps[0] if bmps else bark
    if os.path.exists(bark):
        payload["bark"] = bmp_to_png_data_uri(bark)

    html = open(os.path.join(ROOT, "web", "index.html"), encoding="utf-8").read()
    blob = json.dumps(payload, separators=(",", ":")).replace("</", "<\\/")
    html = html.replace("<!--EMBEDDED-DATA-->",
                        f'<script type="application/json" id="fra-data">{blob}</script>')
    if args.fragment:
        html = re.sub(r"<!doctype html>\s*|</?html[^>]*>\s*|</?head>\s*|</?body>\s*|<meta [^>]*>\s*", "", html, flags=re.I)

    os.makedirs(os.path.dirname(os.path.abspath(args.output)), exist_ok=True)
    open(args.output, "w", encoding="utf-8").write(html)
    print(f"Wrote {args.output} ({len(html) // 1024} KB, {len(files)} trees)")


if __name__ == "__main__":
    main()
