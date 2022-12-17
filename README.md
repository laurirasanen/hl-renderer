# A modified OpenGL renderer for [Xash3D FWGS](https://github.com/FWGS/xash3d-fwgs)

## Portable?
No. I'm only testing this on a Linux desktop with `--enable-static-gl`.

- - -

## Installation & Running
0) See Xash3D FWGS instructions: https://github.com/FWGS/xash3d-fwgs
1) Overwrite the default `ref_gl` binary with a precompiled one from [GitHub Releases](https://github.com/laurirasanen/hl-renderer/releases) or build your own
2) Run Xash3D

- - -

## Build instructions
0) See Xash3D FWGS instructions: https://github.com/FWGS/xash3d-fwgs
1) Overwrite Xash3D `ref/gl` source folder with the one in this repository
2) Use `--enable-static-gl` when configuring waf
3) Build Xash3D

- - -

## Features

### Basic color grading

- `gl_cg_red <value>`
- `gl_cg_green <value>`
- `gl_cg_blue <value>`
- `gl_cg_gamma <value>`
- `gl_cg_gain <value>`

![cg comparison image](/img/cg.png)

### Vignette

- `gl_vignette_strength <value>`
- `gl_vignette_distance <value>`
- `gl_vignette_curvature <value>`

![vignette comparison image](/img/vignette.png)
