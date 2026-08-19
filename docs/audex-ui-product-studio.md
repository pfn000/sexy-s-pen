# NCOM AudeX UI/Product Studio Specification

## Product concept

AudeX should grow from a painting application into an **artist-first UI and product studio**. The central idea is that an artist can paint, vectorize, compose, prototype, and ship a working interface without switching between a painting app, a design tool, and a code editor. The studio must remain original in its interface and implementation while combining the strongest workflows documented across professional design and painting tools.

AudeX UI/Product Studio has three connected modes:

| Mode | Purpose |
|---|---|
| **Canvas** | Paint raster and vector artwork with pressure, tilt, gestures, layers, brushes, masks, and animation. |
| **Studio** | Build responsive screens, components, artboards, tokens, assets, and interactive prototypes. |
| **Ship** | Inspect designs, validate accessibility, export assets, and generate runnable application projects with source, presets, and build instructions. |

The same document should support all three modes. A painted button icon can remain editable as a source layer, become an asset in a component, appear in a prototype, and be emitted into a generated application package.

## Core design-system model

AudeX should use a typed scene graph rather than a flat list of pixels. The graph contains pages, artboards, frames, groups, components, instances, vector shapes, text, raster assets, paint layers, prototype nodes, and annotations. Each object has a stable identifier, human-readable name, constraints, accessibility metadata, and optional code-generation hints.

Components should support variants and typed properties. A **Window Chrome** component can expose `cornerRadius = 24`, `theme = dark/light`, `density`, `titleBar`, `shadow`, and `blurPolicy`. A **Button** component can expose `size`, `state`, `tone`, `leadingIcon`, `trailingIcon`, and `enabled`. Users can create their own component sets and publish them to a local library.

Variables should implement design tokens. Token collections should cover color, number, string, boolean, typography, spacing, radius, elevation, motion, and asset references. Modes should support light, dark, high contrast, low power, left-handed layout, and brand variants. A token can be used simultaneously by a painted composition, vector shape, component property, prototype condition, and generated source file.

## Responsive layout and interaction

The Studio canvas should support artboards for desktop, tablet, mobile, and custom sizes. Frames should provide constraints, anchors, auto-layout, wrapping, gap, padding, min/max sizes, alignment, content hugging, and scroll regions. Layout warnings should identify overflow, clipped text, unsatisfied constraints, and inaccessible contrast.

The prototype engine should be a state graph. A node represents a screen or overlay; an edge contains a trigger, optional condition, variable changes, transition, duration, easing, and target. Triggers should include click/tap, pen tip, pen button, hover, touch gesture, key press, drag, scroll, timer, and startup. Prototype actions should include navigate, overlay, replace, scroll, open URL, set variable, conditional branch, play animation, and invoke a command. All generated interactions must remain inspectable and editable.

## Code export

AudeX should export complete projects, not only isolated snippets. The exporter should begin with a target profile:

| Target | Output |
|---|---|
| Qt/QML | `.qml` components, token file, assets, project file, and build instructions for KDE/Linux. |
| GTK/Libadwaita | Blueprint or XML/UI files, CSS, assets, and a matching application skeleton. |
| Web | TypeScript/React or vanilla HTML/CSS/JS, responsive assets, token CSS, and a runnable package. |
| Flutter | Dart widgets, theme tokens, assets, and a minimal runnable project. |
| Android Compose | Kotlin composables, theme tokens, resources, and a Gradle project. |
| SVG/Canvas | Self-contained SVG, raster fallback, and optional interaction metadata. |

The generated project should contain a `README`, `LICENSE` placeholder or selected license, `assets/`, `tokens/`, `components/`, `screens/`, `routes/`, `tests/`, and `audeX-export.json` manifest. Each generated component should include source mapping back to the AudeX object ID. The exporter should run a validation pass and report missing fonts, unsupported effects, unresolved tokens, inaccessible labels, unsupported blend modes, and assets that require conversion.

Generated code should be deterministic and readable. It should not silently embed proprietary code or remote dependencies. AudeX can provide an optional local template registry for project scaffolds, but generated output must remain usable without an AudeX runtime unless the user explicitly chooses a runtime-backed export.

## Asset and preset pipeline

The asset library should accept raster images, vectors, fonts, brush presets, animation clips, colors, gradients, components, code templates, and export presets. Every asset must have a name, tags, preview, source path, license note, version, and content hash. Presets should include the 24 px rounded-window family as a built-in original design system:

| Preset family | Examples |
|---|---|
| Window | 24 px radius, light glass, dark glass, low-power opaque, high-contrast opaque. |
| Navigation | Side rail, top rail, command palette, tab bar, breadcrumb. |
| Controls | Buttons, toggles, sliders, segmented controls, menus, dialogs, tooltips. |
| Content | Cards, lists, tables, forms, empty states, notifications, media frames. |
| Artist | Brush inspector, layer stack, color wheel, canvas HUD, timeline, pen-status bubble. |

A painted asset should preserve its source layer relationship when inserted into a component. Export should allow a flattened image, editable SVG where possible, or a linked source asset package.

## File import and export contract

AudeX should provide a format matrix with three statuses: **native**, **supported conversion**, and **best effort**. Native formats preserve the complete scene graph. Conversion formats preserve the main visual content and selected semantics. Best-effort formats show a conversion report before import or export.

| Format | Import | Export | Fidelity target |
|---|---|---|---|
| `.audex` | Native | Native | Full scene graph, strokes, layers, components, prototypes, tokens, and code metadata. |
| PNG | Native | Native | Raster pixels, alpha, and selected metadata. |
| JPG/JPEG | Native | Native | Raster pixels; transparency and layer semantics are lost. |
| TIFF | Native conversion | Native | Raster, alpha, and selected color-profile metadata; layers depend on implementation. |
| WEBP | Native conversion | Native | Raster and alpha where supported. |
| SVG | Native conversion | Native | Vector geometry, paths, fills, strokes, text policy, and selected metadata. |
| PDF | Conversion | Native export | Pages, text glyphs, vectors, and raster content; interactive semantics are not guaranteed. |
| OpenRaster | Native conversion | Native | Raster layers and basic blend/layer structure. |
| PSD | Best effort | Planned best effort | Raster layers, groups, masks, and text where parsable; unsupported effects are reported. |
| GIF/APNG/video | Conversion | Native for animation milestones | Frames and timing; editability depends on imported structure. |
| Figma `.fig` | Not promised without an authorized interchange route | Not applicable | Use SVG, PDF, PNG, or documented exchange paths rather than claiming closed-format round-tripping. |
| Procreate `.procreate` | Not promised as a closed-format importer | Not applicable | Use PSD, PNG, TIFF, PDF, or OpenRaster exchange and report lost semantics. |

The user’s requirement for “everything” should be implemented as broad, transparent coverage rather than a misleading promise of perfect closed-format compatibility. The import dialog should show exactly what will survive conversion.

## 24 px window and visual system

The Studio itself should use a 24 px client-side corner radius, layered translucent surfaces, editable theme tokens, light/dark modes, reduced motion, and an opaque low-power mode. The same radius should be available as a token and component preset for exported applications. Generated code should express the radius as a token, not as repeated magic numbers.

## Roadmap

| Release | UI/Product Studio scope |
|---|---|
| 0.1 | Artboards, scene graph, 24 px window preset, vector primitives, text, raster placement, PNG/JPG/SVG/PDF export, and basic component instances. |
| 0.2 | Auto-layout, constraints, component properties, variants, tokens, light/dark modes, asset library, and OpenRaster/TIFF/WEBP workflows. |
| 0.3 | Prototype state graph, gestures, pen/touch triggers, overlays, transitions, annotations, accessibility checks, and interactive preview. |
| 0.4 | Qt/QML and web code export, export manifest, token sync, generated tests, and project validation. |
| 0.5 | GTK, Flutter, and Android Compose exporters, PSD best-effort conversion, animation assets, and plugin/template registry. |
| 1.0 | Stable `.audex` format, complete documentation, reliable export reports, reproducible generated projects, and long-term compatibility guarantees. |

## References

[1]: https://help.figma.com/hc/en-us/articles/15023124644247-Guide-to-Dev-Mode "Figma — Guide to Dev Mode"
[2]: https://help.figma.com/hc/en-us/articles/15339657135383-Guide-to-variables-in-Figma "Figma — Guide to variables"
[3]: https://help.figma.com/hc/en-us/articles/360056440594-Create-and-use-variants "Figma — Create and use variants"
[4]: https://help.figma.com/hc/en-us/articles/13402894554519-Export-formats-and-settings-for-static-designs "Figma — Export formats and settings"
[5]: https://help.figma.com/hc/en-us/articles/360041003114-Import-files-to-the-file-browser "Figma — Import files"
[6]: https://help.procreate.com/procreate/handbook/introduction "Procreate Handbook"
[7]: https://help.procreate.com/procreate/handbook/gallery/gallery-file-types "Procreate — File types"
[8]: https://help.procreate.com/procreate/handbook/brushes/brush-studio "Procreate — Brush Studio"
[9]: https://help.procreate.com/procreate/handbook/interface-gestures/gestures "Procreate — Gestures"
