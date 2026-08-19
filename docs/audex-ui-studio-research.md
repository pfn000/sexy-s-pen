# NCOM AudeX UI/Product Studio Research Notes

## Figma capabilities reviewed

Sources: [Figma Dev Mode](https://help.figma.com/hc/en-us/articles/15023124644247-Guide-to-Dev-Mode), [Figma Variables](https://help.figma.com/hc/en-us/articles/15339657135383-Guide-to-variables-in-Figma), [Figma Variants](https://help.figma.com/hc/en-us/articles/360056440594-Create-and-use-variants), [Figma export formats](https://help.figma.com/hc/en-us/articles/13402894554519-Export-formats-and-settings-for-static-designs), and [Figma import files](https://help.figma.com/hc/en-us/articles/360041003114-Import-files-to-the-file-browser).

Figma Dev Mode is a design-to-development handoff mode. The official guide describes ready-for-development status, frame and layer navigation, version comparison, annotations and measurements, external resource links, component metadata, a component playground, variables, downloadable assets, code snippets, and export settings. Figma can present code or list properties for selected layers and can support custom code snippets through code-generation integrations. Its documented static export formats include PNG, JPG, SVG, and PDF.

Figma Variables provide reusable values for design tokens and can be applied to design properties and prototype actions. Figma documents color, number, string, and boolean values, variable collections, modes for light/dark or other contexts, expressions, conditional logic, and multiple actions. Variables can drive responsive layouts, localization previews, and interactive prototype state.

Figma Variants group related components into component sets. Variant properties and values represent dimensions such as size, state, color, or icon presence. Component properties, naming conventions, descriptions, documentation links, and published libraries are core design-system workflows. Components and instances are intended to be reusable and inspectable rather than repeatedly redrawn.

Figma’s official static export guide documents PNG with alpha, JPG, SVG, and PDF, plus scale, suffix, color profile, resampling, text outlining, SVG IDs, and overlap controls. Figma’s file-browser import documentation also identifies image, GIF, and video import paths. AudeX should support these formats where practical, but it should not claim that every proprietary Figma file structure or plugin behavior can be imported without loss.

## Procreate capabilities relevant to UI/Product Studio

Sources: [Procreate Handbook](https://help.procreate.com/procreate/handbook/introduction), [Procreate file types](https://help.procreate.com/procreate/handbook/gallery/gallery-file-types), [Procreate Brush Studio](https://help.procreate.com/procreate/handbook/brushes/brush-studio), [Procreate gestures](https://help.procreate.com/procreate/handbook/interface-gestures/gestures), and [Procreate animation](https://help.procreate.com/procreate/handbook/animation).

Procreate contributes the artist-first side of AudeX: canvas-first navigation, pressure and tilt-aware brushes, layer and mask workflows, selections, transforms, drawing guides, symmetry, animation, page organization, color profiles, time-lapse/export, and fast gesture-driven editing. Procreate’s file documentation includes layered and animation-related exports, while its brush system provides a useful model for editable presets with live previews.

The UI/Product Studio should keep these artist strengths intact. A user should be able to paint an icon, texture, illustration, or visual asset directly on the canvas, then place that asset into a component, prototype, design token, or generated application without leaving the AudeX workspace.

## What AudeX should implement

| Research capability | Original AudeX interpretation |
|---|---|
| Frames and layout | Artboards with responsive constraints, auto-layout, grids, guides, safe areas, and device presets. |
| Components and variants | Reusable AudeX Components with typed properties, states, slots, variants, and 24 px window presets. |
| Variables and modes | Design-token collections for colors, typography, spacing, radii, shadows, motion, and light/dark/accessibility modes. |
| Prototyping | A state-machine prototype canvas with triggers, transitions, conditions, variables, overlays, scroll regions, and keyboard/pen/touch events. |
| Dev handoff | Inspect panel, annotations, measurements, token names, asset download, generated code, and export manifest. |
| Code export | Generate complete runnable starter projects, not only snippets, with assets, tokens, component files, routes/screens, and build instructions. |
| Artist workflow | Paint directly into assets, use pressure/tilt for illustrations, create brush presets, and preserve editable source layers. |
| File pipeline | Import/export with explicit fidelity levels and warnings when formats cannot preserve all semantics. |
| Asset library | Searchable local library for vectors, raster images, brush presets, fonts, components, motion presets, and code templates. |
| Collaboration | Local-first documents with optional Git-based collaboration, comments, version history, and conflict-aware merges. |
| Accessibility | Keyboard navigation, screen-reader metadata, reduced motion, high contrast, large controls, and exported accessibility annotations. |

## Fidelity boundary

AudeX should natively preserve its own `.audex` document model, raster layers, vector shapes, components, tokens, prototypes, and code-export metadata. PNG, JPG, TIFF, WEBP, SVG, PDF, OpenRaster, and selected PSD workflows can be handled through specialized import/export paths. Figma `.fig` files, proprietary plugin data, application-specific brush formats, and complex prototype semantics require either an official interchange route or a best-effort importer with a conversion report. “Import everything Figma and Procreate can” should therefore mean broad format coverage with transparent loss reporting, not a promise of perfect round-tripping for closed formats.

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
[10]: https://help.procreate.com/procreate/handbook/animation "Procreate — Animation"
