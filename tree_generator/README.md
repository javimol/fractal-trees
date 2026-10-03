# Tree generator

Command-line program that grows random trees from about twenty parameters and writes them as `.fra` files for the [visualizer](../visualizer/), or as VRML 2.0 scenes. It's the cleaned-up version of the 2006 Windows program ("Parameter Trees", MFC) that made the trees in `data/chopos/`.

![Seven trees from the poplar preset](../docs/generated-forest.png)

## Build

It needs only a C99 compiler and `make`:

```sh
cd tree_generator
make
```

## Run

```sh
./tree-generator > tree.fra                        # one poplar
./tree-generator -n 7 -o forest                    # forest/tree0.fra ... tree6.fra
./tree-generator -n 7 -o forest -s 2026            # the forest in the picture above
./tree-generator -p presets/poplar.txt -D generations=4 -D deviousness=0 > tall.fra
./tree-generator -f vrml -t bark.jpg -o tree.wrl   # VRML scene
./tree-generator --print-params                    # the parameters in effect
./tree-generator --help
```

To look at the result:

```sh
../visualizer/fractal-trees -t ../data/chopos/bark.bmp forest
```

The seed is printed to stderr on every run. The same seed and parameters always give the same trees.

## Parameters

Without `-p`, the generator uses the parameters behind `data/chopos/`, taken from the 2006 slides. [presets/poplar.txt](presets/poplar.txt) contains the same values, so you can copy it and edit it. In a parameter file each line is `key = value`, and `#` starts a comment. `-D key=value` overrides a single parameter. Percentages go from 0 to 100, and angles are in degrees.

| Key | 2006 dialog label | Poplar | Meaning |
|---|---|---|---|
| `max_height` | Max. Height | 900 | Height cap |
| `growth_rate` | Pace Growth | 25 | Height gained per year |
| `age` | Age | 100 | Age in months. The target height is `min(age / 12 × growth_rate, max_height)` |
| `trunk_ratio` | Ratio Top/Trunk | 30 | % of the height taken by the first trunk segment |
| `segment_ratio` | Ratio Branch/Branch | 80 | % length of each segment relative to the one before it on the same axis |
| `base_ratio` | Ratio Base/Height | 5 | % base diameter relative to the height |
| `taper` | Ratio Diameter | 5 | % diameter lost along each segment |
| `branch_ratio` | Ratio Trunk/Branch | 60 | % branch length relative to the segment it grows from |
| `branch_diameter_ratio` | Ratio Diameter Trunk/Branch | 35 | % branch base diameter relative to the parent's tip diameter |
| `cone` | Tree Cone | 50 | Angle from the vertical of first-level branches |
| `cone_increment` | Var. Tree Cone | 15 | Branches at level *n* open further: `cone + cone_increment × (1/2 + … + 1/(n+1))` |
| `min_azimuth`, `max_azimuth` | Min. / Max. Angle | 0, 360 | Range of directions around the vertical where branches grow |
| `generations` | Generation | 3 | Branching levels. It's also the maximum number of segments in one axis |
| `frondage` | Frondage | 25 | Splits the azimuth range into `100 / frondage` sections. Each section holds a branch with a `100 − frondage` % chance |
| `stop_probability` | Probability Trunk | 25 | % chance that an axis stops instead of growing another segment |
| `deviousness` | Deviousness | 50 | % chance that a segment is crooked. A crooked segment is drawn as `1 + 100 / (100 − deviousness)` straight pieces |
| `bend_angle` | Deviousness Angle | 60 | Maximum angle from the vertical of each crooked piece |
| `bend_arc` | Deviousness Arch | 45 | Maximum turn around the vertical between pieces, split half each way |
| `variability` | Variability | 35 | % chance, and maximum size, of random changes to heights, lengths, angles and diameters |

The slides call the frondage "branch scarcity" and give 75 for the poplars, which is 100 − 25. The 2006 dialog took the value 25.

## How a tree grows

A tree is made of tapered segments. Each **axis** (the trunk or a branch) is a chain of segments, and each segment can sprout branches that start new axes one level up. Growth runs in steps. A segment that's born in one step is alive in the next one, when it grows:

- **a successor** on the same axis: shorter by `segment_ratio`, thinner by `taper`, and pointing in about the same direction. This doesn't happen once the axis is `generations` segments long or when it stops at random (`stop_probability`). A trunk segment that ends above the target height is dropped.
- **branches**: the azimuth range is split into sections, starting at a random angle, and each section may hold one branch. The branch leans a random fraction of the cone for its level, and it starts at the tip of its parent or, with probability `variability`, part way along it.

After that step the segment is dead. Growth ends when no segment is alive. Then each axis tip that has branches is narrowed to the widest branch starting there, so the joints match.

Any segment may turn out crooked (`deviousness`). It's then cut at random points into straight pieces. Each piece after the first leans at a random angle up to `bend_angle` and turns up to `bend_arc / 2` either way. Most lengths, angles and diameters are randomly changed with probability `variability`, and then nudged by ±10%.

Every straight piece becomes one line of the `.fra` file. Twigs at the last level end in a point, with a tip diameter of 0.

## Source layout

```
src/main.c          command line
src/params.c/h      parameters: defaults, file parsing, per-tree height and diameter
src/generator.c/h   the growth algorithm (Segment)
src/output.c/h      .fra and VRML writers
src/rng.c/h         seeded random numbers, drawn as percentages like the original
presets/poplar.txt  the data/chopos parameters
```

## Changes from the 2006 version

The algorithm and its random decisions are the same as in the 2006 program. The trees it makes match `data/chopos/` in branch count, height, diameters and branch angles. The tree shapes are statistically the same, but no file can be reproduced exactly, because the original used `rand()` seeded from the clock.

- The program is a portable command line tool instead of a Windows MFC dialog. Parameters come from a file or options, and the random seed can be set, so runs are reproducible.
- Each tree varies its height, trunk and diameter from the given parameters. The dialog applied those changes again on every *Generate*, so they built up from one tree to the next.
- Variations no longer give the trunk a negative length, which made trees grow downwards.
- Branches that start part way along a crooked segment are now placed on it. The original walked the pieces wrongly, and could crash.
- Crooked segments are cut at distinct points. The original intended this, but its duplicate check never ran, so it could produce zero-length pieces.
- Fixed a crash (null pointer) when a trunk segment above the target height was removed.
- VRML: crooked segments with a successor get a joint sphere and no tip cone, the axes gizmo is gone, and the texture is optional.
- Dead code (an unused Gaussian generator and transformation matrix) is removed, and identifiers and comments are in English.
