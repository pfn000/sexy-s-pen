# NCOM AudeX Architecture and Roadmap

## Product position

NCOM AudeX is a Linux-native, free and open-source painting application for artists who want a focused canvas, expressive stylus input, and professional tools without a subscription. It is a companion product to Sexy S-Pen, not a replacement for the Surface input stack. Sexy S-Pen owns device discovery, capability display, user profiles, and system-facing palm-rejection preferences. AudeX owns artwork, brushes, layers, rendering, and creative workflow.

The design is inspired by the needs documented across professional painting applications, but its interface, terminology, assets, code, and interaction design must remain original.

## Visual direction

The following images are visual references for the product direction. The Sexy S-Pen image reflects the current control-panel design language. The AudeX image is a concept preview of the future painting workspace, not a claim that the full painting engine already exists.

![Sexy S-Pen liquid-glass dashboard preview](assets/sexy-s-pen-dashboard-preview.png)

![NCOM AudeX Vulkan painting workspace concept](assets/audex-workspace-concept.png)

## Target machine

The first performance target is the developer’s Surface Pro 7 running CachyOS Linux with KDE Plasma on Wayland, an Intel Core i3-1005G1, Intel UHD Graphics, and 4 GiB RAM. This target requires bounded memory use, incremental rendering, low-copy input handling, and graceful reduction of visual effects. The app should offer a **Low-power Intel profile** that reduces background previews, caps undo memory, and disables expensive filters until requested.

| Target | Initial design response |
|---|---|
| 4 GiB RAM | Tiled canvas storage, compressed undo snapshots, lazy thumbnails, bounded caches, and autosave checkpoints. |
| Intel UHD Graphics | Native Vulkan renderer first, OpenGL fallback, and CPU fallback for unsupported paths. |
| KDE Wayland | Qt 6/QML shell with a dedicated canvas surface and input adapters that consume tablet events without global hooks. |
| Surface Pen | Pressure, tip, eraser, buttons, hover, tilt, and battery are capability states. AudeX never assumes all are present. |
| 24 px rounded window | Client-side rounded content with a 24 px radius, translucent glass layers, and compositor-aware decoration requests. |

## Rendering model

Every mark should be represented as a **stroke object** first and rasterized into tiles second. A stroke object contains time-ordered samples with x/y, pressure, tilt-x, tilt-y, distance, tool type, button state, and timestamp. The object also stores the brush preset ID, color, blend mode, transform, and a deterministic random seed for texture. This permits replay, undo, pressure re-editing where supported, and future animation or vectorization features.

The renderer should build a dab stream from those samples. Each dab is a small sprite or instanced quad carrying position, rotation, scale, opacity, color, texture index, and blend parameters. Dabs are batched by brush texture and blend mode, then composited into a tiled canvas.

**Native Vulkan is the primary AudeX graphics backend.** The Vulkan renderer should own device selection, swapchain creation, descriptor and pipeline management, staging uploads, tile-composite passes, brush-texture arrays, synchronization, and optional compute passes for filters or liquify. It should prefer the integrated Intel GPU when it offers a stable Vulkan device, expose a renderer diagnostic panel, and log the selected API/device/driver without requiring users to understand Vulkan internals. The GPU path should use persistent staging buffers, timeline or fence-based synchronization, and double-buffered command submission so the input thread does not block on rendering. When Vulkan is unavailable or unstable, the same dab stream must remain usable through an OpenGL fallback and a CPU raster fallback. AudeX should never make the canvas unusable merely because the preferred renderer is missing.

A 4,096 × 4,096 document should not require a full uncompressed RGBA buffer for every history state. Tiles should be loaded and rendered on demand. The canvas manager should maintain a visible-tile cache, a nearby-tile cache, and a compressed history store. A stroke commit should invalidate only affected tiles rather than rebuilding the entire image.

## Input pipeline

The input pipeline has four layers. The first is a native Wayland/libinput adapter for tablet tool events. The second is a normalization layer that maps raw coordinates and logical pressure/distance ranges into the AudeX canvas space. The third is a sensor router that maps pressure, speed, direction, tilt, distance, and custom expressions into brush parameters. The fourth is the gesture and shortcut layer that resolves pen buttons, touch gestures, keyboard modifiers, and eraser state.

AudeX should expose a tablet inspector modeled as a diagnostic tool rather than a hidden debug log. It should show the last event timestamp, tool type, x/y, pressure, distance, tilt-x, tilt-y, tip state, eraser state, and button state. It should make unavailable axes visibly unavailable. This follows libinput’s documented separation of tool events, pad events, touch events, pressure thresholds, distance, and tilt axes [1].

Sexy S-Pen can publish an optional local profile such as `Writing`, `Drawing`, or `Touch-first`, but AudeX must remain usable if Sexy S-Pen is not installed. The shared boundary should be a versioned user-level settings file or an optional D-Bus service, never an undocumented direct dependency on privileged system files.

## Brush system

AudeX should ship with a small, high-quality starter library instead of an enormous slow catalog. Each preset should declare a texture, dab model, spacing, hardness, opacity, blend behavior, and sensor mapping. The first Brush Lab should provide a live preview pad and grouped controls for shape, grain, stroke path, dynamics, wet behavior, texture, and pressure response. These categories reflect documented artist workflows without copying another product’s naming or screen layout [2] [3].

The sensor mapping graph should allow a user to connect inputs such as pressure, fine speed, gross speed, stroke progress, direction, tilt elevation, tilt direction, distance, randomness, and custom expressions to size, opacity, flow, rotation, color, texture, and smudge amount. Krita’s documentation provides a useful reference for this breadth of dynamic inputs [3].

## Document model

A native `.audex` document should be a versioned package containing a manifest, tiled layer data, stroke objects, brush references, color profile metadata, thumbnails, and optional animation tracks. The app should autosave a recovery copy and write changes transactionally so a crash does not corrupt the main document.

The layer system should support paint layers, groups, clipping groups, alpha lock, transparency masks, filter masks, vector layers, text layers, and frame layers. The first milestone can implement paint layers, groups, alpha lock, masks, and blend modes; later milestones can add vector, text, and animation layers.

## Original liquid-glass workspace

The application should use a canvas-first layout with a slim top command rail, contextual brush controls, collapsible layer and color sidebars, and a command palette. The shell should use an original liquid-glass-inspired language: translucent surfaces, 24 px corner radii, restrained blur where available, thin highlight strokes, clear focus rings, and motion limited to transform and opacity. It should never use Apple logos, Apple Pencil artwork, Procreate icons, or copied interface geometry.

The window should offer dark and light modes, left-handed layout, high-contrast mode, reduced motion, large controls, and keyboard-only navigation. Low-power mode should reduce background animations and glass effects without hiding information.

## Packaging and release architecture

The repository should contain:

| Artifact | Purpose |
|---|---|
| `packaging/io.github.ncomsystems.AudeX.yml` | Flatpak manifest with Qt runtime, graphics permissions, desktop integration, and reproducible sources. |
| `packaging/PKGBUILD` | Arch package recipe producing `audex`. |
| `scripts/install-audex.sh` | Transparent installer for local builds and verified GitHub Release assets. |
| `.github/workflows/build.yml` | Build and static validation on pushes and pull requests. |
| `.github/workflows/pages.yml` | Documentation deployment through GitHub Pages Actions. |
| GitHub Releases | Versioned source archives, checksums, release notes, and future Flatpak/Arch artifacts. |

The project must describe `sudo pacman -S audex` accurately. That command works only after an Arch repository containing the package is configured. Until then, the supported paths are `makepkg -si`, a configured AUR helper, a custom repository, Flatpak, or a GitHub Release installer.

## Roadmap

| Milestone | Scope |
|---|---|
| AudeX 0.1 | Native window shell, Vulkan device/renderer diagnostics, canvas viewport, pen event inspector, one pressure-aware sprite brush, undo/redo, PNG export, 24 px rounded glass UI, and low-power profile. |
| AudeX 0.2 | Tiled raster document, brush presets, three stabilizers, layers/groups, color picker, autosave, Sexy S-Pen profile import, and Flatpak/Arch packaging. |
| AudeX 0.3 | Brush Lab, masks, clipping groups, selections, transforms, symmetry, guides, palette management, OpenRaster, and PSD investigation. |
| AudeX 0.4 | Non-destructive filters, text/vector layers, resource packs, workspace customization, command palette, and accessibility expansion. |
| AudeX 0.5 | Timeline foundation, frame layers, onion skinning, playback, export, and audio markers. |
| AudeX 1.0 | Stable document format, plugin API, robust import/export, profiling on low-memory Intel hardware, and a mature release/update channel. |

## References

[1]: https://wayland.freedesktop.org/libinput/doc/latest/tablet-support.html "libinput tablet support and tablet tool axes"
[2]: https://help.procreate.com/procreate/handbook/brushes/brush-studio "Procreate Brush Studio documentation"
[3]: https://docs.krita.org/en/reference_manual/brushes/brush_engines/mypaint_engine.html "Krita MyPaint brush engine dynamic inputs"
