# Sexy S-Pen Capability Matrix

Sexy S-Pen is designed around progressive enhancement. The interface should remain useful with a basic Surface Pen and unlock richer controls only when the running kernel, BlueZ, libinput, compositor, and desktop environment expose them.

| Feature family | Sexy S-Pen behavior | Dependency | Support status |
|---|---|---|---|
| Palm rejection | Writing, Drawing, Balanced, and Touch-first profiles; stylus-proximity rejection; palm rejection; grace period | linux-surface/iptsd and touchscreen device | Strongly supportable on Surface IPTS |
| Pressure | Live pressure meter; tip threshold; curve presets; per-app profile | Stylus pressure axis via kernel/libinput | Supportable when axis is reported |
| Tilt | Live X/Y tilt display; orientation-aware brush guidance; per-app toggle | Stylus tilt axes from device/kernel/compositor | Hardware- and compositor-dependent |
| Hover | Hover card, cursor preview, optional tool palette | Stylus proximity/motion events | Supportable only if proximity events are exposed |
| Buttons | Double-tap timing, side-button actions, eraser action, keyboard shortcuts, app profiles | Tool button events and compositor/portal/helper | Keyboard actions are safest on Wayland |
| Calibration | Four-point calibration flow or launcher to Plasma calibration | KWin/libinput calibration support | Integrate with native Plasma where available |
| Battery | Live percentage, last-known/stale state, charging/unknown states | BlueZ `org.bluez.Battery1` D-Bus interface | Supportable only when the pen reports battery data |
| Pairing | System Bluetooth pairing handoff plus animated connection state | BlueZ D-Bus and desktop portal/UI | Supportable; avoid custom unsafe pairing protocol |
| Artist workflow | Pressure curve, smoothing, speed sample tuning, canvas shortcuts, app profiles | Global preferences plus optional Krita/Xournal++ adapters | Strongly supportable as profiles |
| Apple Pencil analogues | Tool palette, hover preview, double-tap, animation, haptics if present | Existing button/proximity/hardware APIs | Software analogues supportable; squeeze/barrel roll/haptics may not be |
| Updates | Release check, signed/verifiable assets, Flatpak/pacman-native updates | GitHub Releases, Flatpak remotes, Arch packaging | Supportable without self-replacing binaries |

## Architecture

The application remains a small Qt 6/QML desktop program. A `CapabilityProbe` backend observes BlueZ, libinput-visible device metadata, and IPTSD presence. A `ProfileStore` persists per-user profiles. A `SystemIntegration` boundary exposes only validated operations, such as generating an IPTSD configuration diff or launching the desktop’s Bluetooth and tablet settings. A future polkit helper can apply narrowly scoped IPTSD changes without granting the GUI arbitrary root access.

The updater checks release metadata and delegates installation to Flatpak, pacman/AUR, or a verified release asset. It never downloads and executes an unverified script. The shell installer is an explicit bootstrapper that prints the source, verifies the downloaded package or repository, and asks before installing.
