# Surface Pen Control

Surface Pen Control is a lightweight Qt 6/QML control panel intended for KDE Plasma on Wayland. It provides a polished interface for per-user pen preferences, including palm-rejection profiles, grace periods, tip feel, tip-distance compensation, hover feedback, and button mappings.

The application is deliberately designed as a control and profile layer rather than a replacement kernel driver. On Surface devices, `iptsd` reads raw touchscreen and stylus measurements and creates standard input events through `uinput` [1]. Its configuration exposes `DisableOnPalm`, `DisableOnStylus`, touchscreen overshoot, and stylus tip-distance compensation [2]. libinput and the Wayland compositor determine which pressure, tilt, proximity, eraser, and button events are actually available to applications [3].

## Current implementation

| Area | Implemented behavior |
|---|---|
| Palm rejection | Balanced, Writing, Drawing, and Touch-first profiles; `DisableOnStylus`; `DisableOnPalm`; grace-period preference |
| Pen feel | Tip threshold, soft/linear/firm curve preference, tip-distance compensation |
| Pen status | IPTSD configuration detection and an explicit capability/integration message |
| Hover | User preference for a visual hover indicator; capability text avoids claiming unsupported hover distance |
| Buttons | Side-action and rear/eraser action mappings stored per user |
| Appearance | Rounded 24 px cards, elevated dark status panel, KDE-friendly system palette, responsive two-column layout |
| Safety boundary | Settings are saved under the user configuration directory. The GUI does not run arbitrary root commands or overwrite `/etc/iptsd.conf` directly. |

## Build on CachyOS or Arch Linux

Install the Qt 6 development packages, CMake, Ninja, and a compiler using the package manager. The exact package names can vary slightly between Arch derivatives, but the usual command is:

```bash
sudo pacman -S --needed base-devel cmake ninja qt6-base qt6-declarative
```

Then build and install:

```bash
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build
sudo cmake --install build
```

Launch it from the application menu or with:

```bash
surface-pen-control
```

## Integration notes

The first version saves preferences to `~/.config/surface-pen-control.ini`. The interface intentionally does not silently edit `/etc/iptsd.conf`, restart system services, or invoke `sudo`. A production integration should add a narrowly-scoped `polkit` helper or a system service that accepts only validated keys such as `DisableOnPalm`, `DisableOnStylus`, and `TipDistance`, then restarts the correct iptsd unit through the current `iptsd-systemd` mechanism.

The pen's pressure and tilt controls can be displayed and tuned only if the device, kernel, libinput, and compositor expose those axes. The panel cannot manufacture tilt data or guarantee hover-distance events when the underlying stack does not report them. This is consistent with libinput's separation of tablet tool, pad, and integrated touch devices [3].

## Recommended next integration step

After verifying the UI on the user's Surface Pro 7, inspect the actual event devices with `libinput list-devices`, `libinput debug-events`, and, if needed, `evtest`. The next backend milestone is a read-only event monitor that identifies the actual stylus node, reports whether pressure/tilt/proximity/buttons are present, and enables only settings that are confirmed by the running stack.

## References

[1]: https://github.com/linux-surface/iptsd "linux-surface/iptsd — Userspace daemon for Intel Precise Touch & Stylus"
[2]: https://raw.githubusercontent.com/linux-surface/iptsd/master/etc/iptsd.conf "iptsd default configuration"
[3]: https://wayland.freedesktop.org/libinput/doc/latest/tablet-support.html "libinput tablet support documentation"
