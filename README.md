# Sexy S-Pen

**Sexy S-Pen** is a lightweight Qt 6/QML artist control centre for Microsoft Surface Pen devices running Surface Linux, Arch-based distributions, KDE Plasma, and Wayland.

Repository: [github.com/pfn000/sexy-s-pen](https://github.com/pfn000/sexy-s-pen)

The application brings together palm-rejection profiles, pressure and smoothing preferences, hover and tilt capability reporting, button mappings, Bluetooth pairing handoff, battery-state monitoring, Plasma calibration guidance, Flatpak packaging, an Arch `PKGBUILD`, and a transparent shell installer.

## What it can support

Sexy S-Pen follows a progressive-enhancement model. IPTSD can expose Surface touchscreen and stylus data, including configuration switches such as `DisableOnPalm`, `DisableOnStylus`, and stylus tip-distance compensation [1] [2]. libinput and the Wayland compositor determine whether pressure, tilt, proximity, eraser, and button events are available [3]. BlueZ can expose a read-only battery percentage through its `org.bluez.Battery1` D-Bus interface when the pen reports it [4].

| Capability | Behavior in Sexy S-Pen | Reality check |
|---|---|---|
| Palm rejection | Writing, Drawing, Balanced, and Touch-first profiles; proximity rejection; grace period | Strongly supportable through IPTSD on supported Surface devices |
| Pressure and artist feel | Tip threshold, soft/linear/firm curves, smoothing, profile presets | Requires a pressure axis from the running input stack |
| Tilt and hover | Capability chips and future live meters | Depends on kernel, device, compositor, and application support |
| Buttons | Undo, eraser, mouse-style, redo, and custom-action concepts | Wayland keyboard actions are safer; click injection may need a helper |
| Pairing | Opens KDE Bluetooth settings with an animated in-app transition | The user still puts the pen into pairing mode |
| Battery | Polls `bluetoothctl` and handles percentage, unknown, disconnected, and stale states | Only works when BlueZ receives battery data from the pen |
| Calibration | Opens a guided Plasma-calibration status path | Plasma/KWin owns the actual calibration matrix |
| iPad-inspired UX | Animated connection bubble, tool-profile flow, hover concept, double-action-ready architecture | Apple-only squeeze, barrel roll, haptics, magnetic charging, and Find My cannot be fabricated on Surface hardware |

## Install from the public repository

On CachyOS or Arch Linux, install the build dependencies and build locally:

```bash
sudo pacman -S --needed base-devel cmake ninja qt6-base qt6-declarative
git clone https://github.com/pfn000/sexy-s-pen.git
cd sexy-s-pen
./scripts/install-sexy-s-pen.sh build
```

The installer builds from the checked-out source and asks for `sudo` only for the final installation step. It does not download and execute an unverified remote script.

The requested `sudo pacman -S sexy-s-pen` command becomes valid only after `sexy-s-pen` is published in an official repository or a configured custom repository. The immediate Arch-native path is the included `PKGBUILD`:

```bash
cd packaging
makepkg -si
```

For the AUR, the package should be reviewed and submitted under the name `sexy-s-pen`. AUR packages are user-produced PKGBUILDs, so users should inspect them before building [5].

## Flatpak

The repository includes `packaging/io.github.sexyspen.SexySPen.yml`. Flatpak isolates applications and requires explicit permissions for resources such as Wayland, graphics, and Bluetooth D-Bus access [6]. Build locally with:

```bash
sudo pacman -S --needed flatpak flatpak-builder
git clone https://github.com/pfn000/sexy-s-pen.git
cd sexy-s-pen
./scripts/install-sexy-s-pen.sh flatpak
```

A future Flathub submission should keep permissions narrow and should use a separate, carefully scoped host integration mechanism if applying IPTSD system configuration becomes necessary. The GUI must not receive unrestricted host filesystem access merely to edit `/etc/iptsd.conf`.

## Updates and community support

The project is prepared for GitHub Releases and native package updates. GitHub’s public Releases API exposes release tags, assets, download URLs, and asset digests [7]. The intended update flow is to direct users to a verified release asset, `flatpak update`, or `pacman -Syu`; Sexy S-Pen should not silently replace its own executable.

If Sexy S-Pen helps your workflow, visit the project at [github.com/pfn000/sexy-s-pen](https://github.com/pfn000/sexy-s-pen), share it, open issues, and contribute improvements. A Liberapay button is included in the interface and currently points to `https://liberapay.com/pfn000/`; replace that URL if the project uses a different Liberapay account.

## Development

```bash
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/sexy-s-pen
```

The sandbox used to prepare this repository did not have the Qt development toolchain installed, so compilation should be performed on the CachyOS Surface system or in CI. GitHub Actions is configured in `.github/workflows/build.yml` to install Qt and build the project on pushes and pull requests.

## References

[1]: https://github.com/linux-surface/iptsd "linux-surface/iptsd"
[2]: https://raw.githubusercontent.com/linux-surface/iptsd/master/etc/iptsd.conf "iptsd default configuration"
[3]: https://wayland.freedesktop.org/libinput/doc/latest/tablet-support.html "libinput tablet support documentation"
[4]: https://github.com/bluez/bluez/blob/master/doc/org.bluez.Battery.rst "BlueZ Battery1 D-Bus interface"
[5]: https://wiki.archlinux.org/title/Arch_User_Repository "ArchWiki — Arch User Repository"
[6]: https://docs.flatpak.org/en/latest/flatpak-command-reference.html "Flatpak command reference"
[7]: https://docs.github.com/en/rest/releases/releases "GitHub Releases REST API"
