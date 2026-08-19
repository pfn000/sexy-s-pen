## Sexy S-Pen v0.3.0

This release expands Sexy S-Pen from a Surface Pro-focused prototype into a broader Microsoft Surface Pen-family control centre with a polished public project presentation.

### Highlights

- Added a redesigned GitHub README with a visual pen gallery using the supplied Microsoft Surface Pen and Surface Slim Pen 2 reference images.
- Added a compatibility matrix covering Surface Slim Pen, Slim Pen 2, first-generation Slim Pen, Surface Pen variants, Microsoft Classroom Pen, Microsoft Business Pen, Surface Pro Pen, and Surface Hub Pen.
- Documented runtime capability detection for pressure, tilt, hover/proximity, eraser, tool buttons, Bluetooth connection, and BlueZ battery reporting.
- Bumped the application and Arch package version to 0.3.0.
- Added image-source attribution and redistribution guidance.
- Kept the progressive-enhancement model: unsupported hardware or compositor features are shown as unavailable rather than simulated.

### Installation

Arch users can build the package with `makepkg -si` from `packaging/`, or use the source installer documented in the README. Flatpak packaging remains available through `packaging/io.github.sexyspen.SexySPen.yml`.

### Important compatibility note

Microsoft’s hardware feature matrix does not imply that every Surface Pen exposes the same controls. Linux support also depends on the kernel, linux-surface/IPTSD, libinput, Wayland compositor, and Bluetooth stack. The application therefore detects capabilities at runtime.
