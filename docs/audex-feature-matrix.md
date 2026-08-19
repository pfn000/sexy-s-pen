# NCOM AudeX Feature Matrix

NCOM AudeX is an original free and open-source Linux painting application planned as a companion to Sexy S-Pen. This matrix translates documented professional-art workflows into an implementation plan without copying proprietary code, artwork, exact interface layouts, or brand identity.

## Priority model

| Priority | Meaning | Delivery intent |
|---|---|---|
| P0 | Core painting loop | Required for the first usable release. |
| P1 | Professional daily workflow | Required for a credible artist beta. |
| P2 | Expansion and parity-oriented capability | Planned after the core is stable. |
| Hardware-dependent | Enabled only when Linux and the pen expose the required data | Must be shown as a capability state, never implied. |

## Cross-product workflow matrix

| Capability area | Documented workflow signal | NCOM AudeX design | Priority | Linux/Surface note |
|---|---|---|---|---|
| Canvas navigation | Procreate documents pinch zoom, pinch-twist rotation, quick fit, and two-finger undo [1] | Canvas-first navigation with touch gestures, pen buttons, keyboard modifiers, zoom, pan, rotate, fit, and configurable gesture controls | P0 | Touch and pen behavior must be separated by palm-rejection state |
| Brush engine | Procreate Brush Studio exposes many brush attributes and a live drawing pad [2]; Krita documents pressure, speed, direction, tilt, stroke, and custom inputs [3] | Original Brush Lab with live preview, dab shape, grain, spacing, opacity, size, hardness, smudge, scatter, jitter, pressure, speed, tilt, direction, and custom sensor routing | P0/P1 | Pressure and tilt are hardware/compositor dependent; libinput normalizes axes to logical ranges [4] |
| Pressure response | Krita documents global pressure curves and tablet testing [5] | Per-device and per-brush pressure curve, tip threshold, minimum/maximum range, smoothing, and raw-event test panel | P0 | Sexy S-Pen can supply preferences; painting app must consume real tablet events |
| Tilt and direction | Krita/MyPaint expose tilt elevation, tilt direction, and direction inputs [3] | Tilt-aware brush rotation, elliptical dabs, shading brushes, calligraphic nibs, and tilt calibration | P1 | Surface Pen tilt may not be exposed on every kernel/compositor path |
| Palm rejection | Professional tablet workflows require stable separation of touch and stylus input | Shared Sexy S-Pen profile API plus AudeX local safety fallback, proximity-aware touch suppression, grace period, and emergency touch toggle | P0 | IPTSD and compositor policy remain privileged/system boundaries |
| Layers and masks | Procreate and Krita document layers, blend modes, masks, groups, and organization [1] [6] | Non-destructive layer stack with groups, alpha lock, clipping groups, masks, blend modes, filters, and layer history | P0/P1 | Use tiled backing storage to stay usable on 4 GiB RAM |
| Selections and transform | Procreate documents automatic/freehand/shape selections and uniform/freeform/distort/warp transforms [1] | Original selection tools, transform handles, warp mesh, snapping, feather, invert, and selection masks | P1 | GPU compositing should keep previews responsive |
| Stabilization | Krita documents multiple stabilizers and dynamic brush smoothing [7] | Three modes: responsive, weighted, and rope stabilizer; per-brush smoothing and latency display | P0 | Keep latency visible to avoid the “smooth but delayed” feeling |
| Color | Procreate documents disc, classic, harmony, value, palettes, and profiles [1] | Color wheel, square picker, harmony suggestions, swatches, palette import/export, ICC profile selection, soft proof preview | P0/P1 | Color management should use LittleCMS and an explicit working-space model |
| Guides and symmetry | Procreate documents 2D, isometric, perspective, symmetry, Drawing Assist, and QuickShape [1] | Grid, perspective guides, line/ellipse assist, radial symmetry, mirror mode, snapping, and gesture-confirmed shape cleanup | P1 | Render guide overlays separately from raster layers |
| Animation | Procreate documents onion skin, timeline, playback, frame editing, settings, and export [8]; Krita documents layers, audio, timeline, onion skinning, tweening, and export [9] | Frame-aware layer model, timeline, onion skinning, playback, duplicate/hold frames, audio markers, and FFmpeg export | P2 | Build on a stable layer model; do not compromise the first painting release |
| Text and vector | Procreate and Krita document text/vector workflows [1] [9] | Editable text layers, SVG-like vector shapes, speech bubbles, paths, and non-destructive transforms | P1/P2 | Keep vector content separate from raster tiles |
| Liquify and filters | Procreate and HiPaint list Liquify, filters, transforms, and canvas adjustment tools [1] [10] | GPU preview filters, liquify mesh, blur/sharpen/noise, hue/saturation, curves, posterize, and procedural effects | P1/P2 | Use compute/render passes where supported, with CPU fallback |
| 3D and texture painting | Procreate and HiPaint list 3D/model workflows [1] [10] | Optional model import, UV texture paint, environment preview, and material channels | P2 | Separate module; not part of the first Surface Pro 7 target |
| Resource ecosystem | Krita documents brush engines, resource manager, tags, and brush bundle sharing [9] | Signed/importable brush packs, tags, favorites, preview thumbnails, versioned presets, and local-only library | P1 | Do not execute code from brush packs |
| File interchange | Procreate and Krita document import/export and PSD-related workflows [1] [9] | Native `.audex` document, PNG/JPEG/WebP/TIFF, layered PSD where feasible, SVG, OpenRaster, and frame export | P0/P1 | Native format should preserve non-destructive history and metadata |
| Automation | Krita documents Python scripting [9] | Sandboxed plugin API, command palette, macros, export automation, and optional Python bridge after security review | P2 | Plugins must be opt-in and permission-scoped |
| Accessibility | Procreate documents accessibility and customizable gestures [1] | Keyboard navigation, high-contrast theme, reduced motion, screen-reader labels, left-handed layout, and large-control mode | P0/P1 | Test on KDE accessibility stack |
| Workspace | Krita documents movable dockers, saved workspaces, shortcuts, and themes [9] | Canvas-first workspace with collapsible sidebars, saved workspaces, command palette, shortcut editor, and dark/light liquid-glass-inspired themes | P0 | Native Qt window with 24 px rounded corners where compositor decoration permits |
| Distribution | User requirement | Flatpak, Arch `PKGBUILD`, GitHub Releases, and future repository path for `sudo pacman -S audex` | P0 | `pacman -S audex` requires a configured package repository or AUR/helper; it cannot be claimed as official until published |
| Documentation | User requirement | GitHub Pages docs, visual walkthroughs, UI navigation diagram, troubleshooting, release notes, and architecture guide | P0 | Pages should deploy through Actions from `/docs` |

## Recommended first release scope

The first public AudeX milestone should focus on a fast canvas, pressure-aware brush dabs, three stabilizers, brush presets, layers and masks, undo/redo history, selections, transform, color picker and palettes, symmetry, autosave, PNG/OpenRaster export, Surface Pen button mapping, and an event inspector. This is enough to make the app useful rather than presenting a large collection of inactive placeholders.

The second milestone should add the Brush Lab, clipping groups, non-destructive filters, editable text and vector tools, workspace customization, PSD import/export, resource packs, and a timeline foundation. Animation, 3D painting, HDR/scene-referred workflows, scripting, and advanced collaboration should follow only after the memory and latency profile is stable on the 4 GiB Surface Pro 7 target.

## Packaging and release contract

The project should ship an AppStream-aware Flatpak manifest, an Arch `PKGBUILD` that produces a lowercase package named `audex`, GitHub Release archives, checksums, and release notes. The convenient command `sudo pacman -S audex` becomes legitimate only after the package is available in a configured repository; the project documentation must clearly distinguish a custom repository, AUR package, local `makepkg -si`, and official Arch repository status.

The app window should use a 24 px corner radius in its client-side Qt/QML content and request rounded server-side decoration where KDE allows it. It should support light and dark modes, reduced motion, and a low-power rendering profile for Intel UHD graphics and 4 GiB memory.

## References

[1]: https://help.procreate.com/procreate/handbook/introduction "Procreate Handbook — Introduction and feature index"
[2]: https://help.procreate.com/procreate/handbook/brushes/brush-studio "Procreate Handbook — Brush Studio"
[3]: https://docs.krita.org/en/reference_manual/brushes/brush_engines/mypaint_engine.html "Krita Manual — MyPaint Brush Engine and dynamic inputs"
[4]: https://wayland.freedesktop.org/libinput/doc/latest/tablet-support.html "libinput — Tablet support"
[5]: https://docs.krita.org/en/reference_manual/preferences/tablet_settings.html "Krita Manual — Tablet Settings"
[6]: https://help.procreate.com/procreate/handbook/layers "Procreate Handbook — Layers"
[7]: https://krita.org/en/features/ "Krita — Features, stabilizers, resources, animation, and GPU canvas"
[8]: https://help.procreate.com/procreate/handbook/animation "Procreate Handbook — Animation"
[9]: https://krita.org/en/features/ "Krita — Features"
[10]: https://www.aige-hipaint.com/support/manual/en-us "HiPaint — Official User Manual"
