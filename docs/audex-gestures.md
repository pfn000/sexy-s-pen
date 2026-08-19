# NCOM AudeX Gesture Specification

NCOM AudeX should provide the speed and physicality artists expect from a touch-first painting application while remaining native to KDE Wayland and usable with a Surface Pen. The goal is **workflow equivalence**, not a copied interface or copied gesture implementation.

## Gesture matrix

| Artist action | Primary touch gesture | Surface Pen / button fallback | Keyboard fallback | Notes |
|---|---|---|---|---|
| Paint | One-finger/stylus stroke | Tip contact | B / current brush | Touch paints only when touch-paint mode is enabled and palm policy allows it. |
| Smudge | Select Smudge, then stroke | Button-mapped temporary smudge or tool selection | S | Separate tool state avoids accidental mode changes. |
| Erase | Select Erase, then stroke | Eraser end or button-mapped temporary eraser | E | Eraser capability is shown only when exposed; the shortcut remains available. |
| Zoom | Two-finger pinch | Ctrl/Meta + pen drag or button + drag | Ctrl + `+` / `-` | Zoom centers around the gesture centroid. |
| Rotate canvas | Two-finger twist | Shift + pen drag or button + drag | Shift + `[` / `]` | Rotation snaps to configured increments when snapping is enabled. |
| Fit canvas | Quick pinch inward/outward | Double-click canvas or mapped button | `2` | A single-touch companion provides an alternative. |
| Pan canvas | Two-finger drag | Space + pen drag | Space + drag | Pan must not create a stroke. |
| Undo | Two-finger tap | Top button or mapped side button | Ctrl/Cmd + Z | An unobtrusive toast reports the affected action. |
| Redo | Three-finger tap or configured gesture | Bottom button or mapped side button | Ctrl/Cmd + Shift + Z | Users can disable three-finger recognition if it conflicts with touch hardware. |
| Clear current layer | Three-finger scrub or QuickMenu action | Long-press button then tap | Delete / Backspace | Always requires an undoable command; destructive confirmation is optional. |
| Copy | Three-finger pinch in | QuickMenu or keyboard | Ctrl/Cmd + C | Selection-aware. |
| Cut | Three-finger pinch in after selection | QuickMenu or keyboard | Ctrl/Cmd + X | Selection-aware. |
| Paste | Three-finger pinch out | QuickMenu or keyboard | Ctrl/Cmd + V | Creates a new layer by default. |
| QuickMenu | One-finger tap in companion mode, long press, or configurable touch gesture | Hold a pen button | Tab or custom shortcut | Six or eight radial actions, fully configurable. |
| Brush size | Horizontal two-finger swipe or dedicated HUD slider | Side button + vertical drag | Shift + drag or `[` / `]` | HUD shows size and pressure response without blocking the canvas. |
| Brush opacity | Vertical two-finger swipe or HUD slider | Side button + horizontal drag | `I` / `O` or custom mapping | Must be distinguishable from brush-size adjustment. |
| Color picker | Hold touch modifier while tapping canvas | Bottom button + tip contact | Ctrl/Alt while clicking | Samples merged, current layer, or visible composite according to preference. |
| Straight line | Draw then hold briefly | Tip stroke then hold | V modifier | Uses a visible preview before commit. |
| Quick shape | Draw closed shape then hold | Tip stroke then hold | Shift modifier | Converts line, ellipse, rectangle, polygon, or arc according to detected shape. |
| Symmetry | Toggle from guide HUD or QuickMenu | Button mapping | M | Supports vertical, horizontal, radial, and mirrored modes. |
| Selection | Lasso/rectangle/ellipse tool | Button or tool rail | R / custom shortcut | Selection tools remain available without touch gestures. |
| Transform | Two-finger move/scale/rotate on selection | Modifier + pen drag | Ctrl/Cmd + T | Transform previews use GPU compositing and commit to a history action. |
| Layer opacity | Gesture on layer row or layer HUD | QuickMenu action | Numeric shortcut or custom | Must not conflict with canvas gestures. |
| Show/hide UI | Four-finger tap or edge swipe | QuickMenu | Tab | Canvas-only mode leaves a discoverable exit affordance. |
| Toggle reference/guide overlay | Three-finger hold or QuickMenu | Button mapping | G | Separate from guide editing. |
| Open brush library | Long press brush button or edge swipe | Side button + tap | F6 | Opens a non-modal glass panel with search and favorites. |
| Open layers | Edge swipe from right or QuickMenu | Button mapping | F7 | Users can pin the panel for non-touch workflows. |

## Gesture engine rules

The gesture engine must classify input only after a short movement and time threshold. A contact that begins with a stylus in proximity has priority over touch. When Sexy S-Pen or the input adapter reports stylus proximity, new palm contacts should be routed to the configured palm-rejection policy rather than interpreted as canvas gestures.

A gesture may be cancelled when the movement becomes ambiguous, when a pen tip goes down, or when the user lifts all contacts before the minimum recognition threshold. The engine should prefer a safe no-op over an accidental clear, transform, or destructive action. Every editing gesture must create one undoable command, even if it changes multiple tiles or layers.

Users need a gesture editor that shows a human-readable action, the current binding, conflicts, and an alternate binding. Conflict detection must prevent the same gesture from simultaneously changing brush size and rotating the canvas. A “safe defaults” button should restore the recommended artist layout.

## Surface Pen mappings

The default Surface Pen mapping should treat the eraser end as Erase when the kernel reports the eraser tool. The first side button should open QuickMenu or temporarily invoke the color picker, depending on the selected profile. The second side button should default to Undo or temporary Eraser. Users can map buttons to any non-destructive command, tool switch, modifier, or custom shortcut. A pen model with one button simply hides the second-button row.

Squeeze, barrel roll, haptics, and Apple Pencil-specific interactions must not appear as active controls unless the hardware and Linux input stack expose an equivalent event. The settings panel may show them under **Future or unavailable capabilities**, but it must not simulate support.

## Accessibility and fallback design

Every gesture must have a non-gesture path. AudeX should include a single-touch companion mode for undo, redo, zoom, pan, rotate, and fit-to-canvas; a command palette searchable by keyboard; visible toolbar buttons; configurable shortcuts; left-handed layouts; large controls; high contrast; reduced motion; and screen-reader labels. A user who cannot perform multi-touch gestures should still be able to complete the entire painting workflow.

## References

[1]: https://help.procreate.com/procreate/handbook/interface-gestures/gestures "Procreate Handbook — Gestures"
[2]: https://help.procreate.com/procreate/handbook/interface-gestures/quickmenu "Procreate Handbook — QuickMenu"
[3]: https://help.procreate.com/procreate/handbook/interface-gestures/widgets "Procreate Handbook — Widgets"
[4]: https://help.procreate.com/procreate/handbook/interface-gestures/accessibility "Procreate Handbook — Accessibility"
[5]: https://wayland.freedesktop.org/libinput/doc/latest/tablet-support.html "libinput — Tablet support"
