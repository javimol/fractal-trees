# Fractal trees

3D models of trees described as lists of branches, a generator that grows new ones from a handful of parameters, and a visualizer to explore them. It started as a 2004–2006 doctoral course project ("Gráficos 3D", Universidad Autónoma de Madrid), originally built with Visual C++ on Windows. This repository is a cleaned-up, portable version of it.

![Forest of seven poplar models](docs/forest.png)

## Contents

```
data/chopos/     seven poplar (chopo) models, Arbol0–6.fra, plus a bark texture
tree_generator/  command-line generator that grows new .fra trees (C, no dependencies)
visualizer/      desktop viewer (C, OpenGL, GLUT) and web viewer (three.js)
docs/            screenshots
```

To see the trees straight away:

```sh
cd visualizer
make            # see visualizer/README.md for dependencies
./fractal-trees
```

Or, without compiling or running anything, clone the repository (or download that single file) and open your local copy of [visualizer/standalone/fractal-trees.html](visualizer/standalone/fractal-trees.html) in a browser. Viewing it on GitHub only shows its source code. It's a single file with all seven trees embedded (it needs an internet connection to load three.js). [visualizer/README.md](visualizer/README.md#web-viewer) has more on the web viewer.

To grow a forest of your own and look at it:

```sh
cd tree_generator
make
./tree-generator -n 7 -o forest
../visualizer/fractal-trees -t ../data/chopos/bark.bmp forest
```

## The generator

[tree_generator/](tree_generator/) grows a tree step by step: each segment can continue its axis with a shorter, thinner one and sprout branches around it inside a cone, and any segment can come out crooked. About twenty parameters (height, growth rate, age, branching cone, frondage, crookedness, variability…) control the shape, and they're read from a simple `key = value` file. The defaults are the ones that made `data/chopos/`, so its trees look like the originals, as in the picture below. [tree_generator/README.md](tree_generator/README.md) describes every parameter and the algorithm.

![Seven trees grown with the poplar parameters](docs/generated-forest.png)

## The tree models

Each `.fra` file describes one tree as plain text, one branch per line. Each branch is a tapered cylinder:

```
# D1      D2        h          Fi         alfa       r0x       r0y         r0z
9.375000  9.093750  107.545624 13.200001  17.599998  0.000000  0.000000    0.000000
9.093750  9.422762  41.813736  15.972001  17.424000  7.425638  104.704155  23.408585
```

| Column | Meaning |
|---|---|
| `D1`, `D2` | Diameter at the base and at the tip |
| `h` | Branch length |
| `Fi` | Angle from the vertical (+Y), in degrees |
| `alfa` | Azimuth around the vertical, in degrees (0 = +Z, 90 = +X) |
| `r0x r0y r0z` | Centre of the branch base |

So a branch runs from `r0` to `r0 + h · (sin Fi · sin alfa, cos Fi, sin Fi · cos alfa)`. Values are whitespace-separated, lines starting with `#` or `//` are comments, and Windows (CRLF) line endings are fine.

The files in `data/chopos/` are the original 2006 files, unchanged. They were made by the 2006 version of the generator and range from 158 to 544 branches per tree.

## History

The first commit holds the original 2006 Windows sources of the visualizer, unchanged except for conversion to UTF-8 and Unix line endings. Later commits port it to Linux and then clean it up; [visualizer/README.md](visualizer/README.md#changes-from-the-2006-version) lists what changed.

The generator was a separate Windows program (MFC, Visual C++) by Víctor Fernández-Carbajales Cañete. `tree_generator/` is a rewrite of it as a portable command-line tool that keeps the same algorithm; [tree_generator/README.md](tree_generator/README.md#changes-from-the-2006-version) lists what changed.

## Credits

Original visualizer by **Víctor Fernández-Carbajales Cañete** and **Javier Molina Vela**, 2004–2006; original generator by **Víctor Fernández-Carbajales Cañete**, 2006. Port and cleanup by Javier Molina Vela, 2026.

## License

[MIT](LICENSE)
