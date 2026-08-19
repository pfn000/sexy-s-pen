---
layout: default
title: Installation and Usage
---

# Installation and Usage

## Arch and CachyOS

Install the build dependencies, clone the public repository, and run the transparent installer:

```bash
sudo pacman -S --needed base-devel cmake ninja qt6-base qt6-declarative
git clone https://github.com/pfn000/sexy-s-pen.git
cd sexy-s-pen
./scripts/install-sexy-s-pen.sh build
```

The installer builds from the checked-out source and uses `sudo` only for the final installation step. It does not download and execute an unknown script as root.

To build the Arch package directly:

```bash
cd packaging
makepkg -si
```

The command `sudo pacman -S sexy-s-pen` becomes available only after the package is published in a configured repository or AUR. It is not valid for a new GitHub repository automatically.

## Flatpak

The repository includes a Flatpak manifest. Install the required tools and run:

```bash
sudo pacman -S --needed flatpak flatpak-builder
./scripts/install-sexy-s-pen.sh flatpak
```

Flatpak permissions are deliberately scoped. Bluetooth access and desktop integration may work differently from a native package, and applying protected `/etc/iptsd.conf` settings should eventually use a narrowly scoped host helper rather than unrestricted filesystem access.

## First launch

Open **Sexy S-Pen** from the KDE application launcher or run:

```bash
sexy-s-pen
```

Start with the **Balanced** profile. Choose **Writing** for stronger palm rejection and more forgiving handwriting feel. Choose **Drawing** for lighter smoothing and faster expressive strokes. Choose **Touch-first** when you want the display to behave primarily as a touch device.

Use **Pair / reconnect pen** to hand off pairing to KDE’s Bluetooth settings. Put the pen into pairing mode according to its model’s instructions. Sexy S-Pen does not attempt to replace the desktop Bluetooth security flow.

## What the controls mean

| Control | Meaning |
|---|---|
| Reject touch near pen | Maps conceptually to IPTSD `DisableOnStylus` when system integration is available |
| Reject palm contacts | Maps conceptually to IPTSD `DisableOnPalm` when system integration is available |
| Grace period | Keeps writing-oriented touch policy active briefly after the pen leaves proximity |
| Tip threshold | Adjusts the preferred minimum pressure before a stroke is considered active |
| Pressure curve | A user preference for soft, linear, or firm artist feel |
| Brush smoothing | A user preference for reducing erratic speed samples without erasing subtle motion |
| Button mappings | Logical actions such as undo, eraser, redo, or shortcut-ready actions |
| Battery | Shows live percentage only when the Bluetooth stack reports it |

## Calibration

KDE Plasma and KWin provide tablet calibration support on compatible devices. Use the calibration guidance in Sexy S-Pen to find the native Plasma calibration flow rather than applying random X11-only commands in a Wayland session. Calibrate only when the pen cursor is consistently offset or parallax is visibly wrong.

## Configuration storage

The current application stores user preferences under:

```text
~/.config/sexy-s-pen.ini
```

The GUI intentionally does not silently overwrite `/etc/iptsd.conf`, run arbitrary root commands, or restart system services without an explicit future integration path.
