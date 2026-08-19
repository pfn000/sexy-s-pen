# NCOM AudeX Research Notes

## Official Procreate Handbook

Source: https://help.procreate.com/procreate/handbook/introduction

The official handbook organizes Procreate around interface and gestures, accessibility, Apple Pencil input, keyboard shortcuts, QuickMenu, widgets, gallery organization, colors and palettes, color profiles, brush libraries, Brush Studio, dual brushes, layers, blend modes, masks, text and fonts, drawing guides, symmetry, Drawing Assist, QuickShape, animation, page organization, 3D painting, actions, selections, transforms, adjustments, Liquify, clone, blur, noise, bloom, halftone, and export/share workflows. These categories are useful product requirements, but NCOM AudeX must use original names, layouts, icons, and implementations.

## Official HiPaint manual

Source: https://www.aige-hipaint.com/support/manual/en-us

The official HiPaint manual lists a simple, accessible workflow with picture album/gallery management, interface and gestures, color, brushes, layers, external image import, auxiliary tools, 3D model support, text, Liquify, transform, selection, curve tools, canvas adjustment, animation, work playback, painting settings, device connection, and filters. HiPaint’s structure reinforces that mobile-friendly artists want a compact canvas-first UI with a quick path to layers, brushes, transforms, auxiliary tools, and animation.

## Official Krita feature documentation

Sources: https://krita.org/en/features/ and https://docs.krita.org/en/reference_manual/brushes/brush_engines/mypaint_engine.html

Krita documents a customizable interface with dockers, saved workspaces, dark and light themes, brush stabilizers, vector and text tools, multiple brush engines, wrap-around mode for seamless textures, resource/brush pack management, 2D animation with timelines, onion skinning, tweening, playback, audio support, assistants, layer and mask management, selections and transforms, full color management, GPU-enhanced canvas rendering, PSD support, HDR painting, and Python scripting.

The MyPaint brush engine documentation describes dynamic inputs beyond pressure: fine speed, gross speed, random, stroke progress, direction, declination/tilt elevation, ascension/tilt direction, and custom input. It also documents brush radius, hardness, eraser state, anti-aliasing, elliptical dab angle and ratio, direction filtering, color shifts, speed response, dab density, opacity, tracking, smudge, stroke timing, and custom input smoothing.

## NCOM AudeX design implication

The strongest shared artist requirements are a fast canvas-first workflow, pressure/tilt-aware brushes, a compact but powerful brush editor, layers and masks, selection and transform tools, color management, stabilizers, symmetry and perspective aids, animation/timeline support, resource import/export, keyboard and pen-button shortcuts, and reliable autosave/history. AudeX should implement these as an original Linux-native experience using Vulkan or OpenGL for canvas compositing and standard Linux tablet events through libinput/Wayland, with Sexy S-Pen providing optional profile and capability metadata.

## Legal and product boundary

NCOM AudeX may be inspired by professional painting workflows, but it must not copy Procreate or HiPaint proprietary code, exact interface artwork, icons, names, text, screenshots, or brand identity. Feature descriptions in this note are research input, not source code or assets.

## Focused Procreate workflows

Sources: https://help.procreate.com/procreate/handbook/brushes/brush-studio, https://help.procreate.com/procreate/handbook/interface-gestures/gestures, and https://help.procreate.com/procreate/handbook/animation

The Procreate Brush Studio model is a useful requirements reference: it separates editable brush attributes, settings, and a live drawing pad. The official page describes fourteen adjustable aspects spanning shape, grain, stroke path, rendering, dynamics, wet-mix behavior, Apple Pencil response, brush properties, and author metadata. AudeX should use a live brush laboratory with a preview stroke and explicit sensor mapping rather than copying the Brush Studio layout.

The gesture documentation emphasizes canvas-first interaction: touch-to-paint/smudge/erase, pinch zoom, pinch-twist rotation, quick pinch to fit, two-finger undo, and customizable gesture controls. On Linux, AudeX should translate this idea into configurable touch gestures plus pen-button, keyboard, and modifier shortcuts, while making palm rejection explicit.

The Animation Assist page confirms the value of a simple timeline, onion skinning, instant playback, frame editing, animation settings, and export. AudeX should treat animation as a later milestone built on a frame/layer model rather than bolting it onto a single raster surface.

## Procreate gesture and accessibility findings

Sources: https://help.procreate.com/procreate/handbook/interface-gestures/gestures, https://help.procreate.com/procreate/handbook/interface-gestures/quickmenu, https://help.procreate.com/procreate/handbook/interface-gestures/widgets, and https://help.procreate.com/procreate/handbook/interface-gestures/accessibility

The official Procreate gesture documentation describes touch-to-paint, smudge, and erase; pinch zoom; pinch-twist rotation; quick pinch to fit the canvas; two-finger tap undo; and additional touch shortcuts for canvas and editing actions. Its QuickMenu is a customizable six-button radial menu that can be invoked by a configurable shortcut and selected by touch-drag for fast muscle-memory actions. Widgets provide a shortcut back to the last artwork, while the accessibility documentation describes a single-touch companion for undo, redo, zoom, move, rotate, and fit-to-canvas, plus screen-reader support through the operating system.

AudeX should implement the equivalent workflows through a gesture engine with configurable touch bindings, a radial command palette, pen-button and keyboard fallbacks, a single-touch companion mode, reduced-motion support, and accessible labels. iPad-only widgets become KDE desktop recent-document or taskbar shortcuts rather than copied mobile widgets. Apple Pencil squeeze and hover-specific behaviors should become optional Surface Pen capability mappings only when the actual Linux input stack reports a corresponding event.
