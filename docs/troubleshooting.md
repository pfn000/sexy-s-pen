---
layout: default
title: Troubleshooting
---

# Troubleshooting

## Pen writes but palm rejection is poor

Confirm that the Surface Linux touchscreen daemon is installed and active. Check whether the configuration exists:

```bash
test -f /etc/iptsd.conf && echo "iptsd configuration found" || echo "iptsd configuration missing"
systemctl status 'iptsd*' --no-pager
```

The two most relevant IPTSD settings are `DisableOnStylus` and `DisableOnPalm`. Sexy S-Pen exposes their intended behavior as profiles, but the current safe UI layer does not silently edit protected system configuration. If you edit the system configuration manually, use the current `iptsd-systemd` service tooling for your installation rather than copying commands intended for older releases.

## Pressure is missing

Check whether the stylus is visible to the input stack:

```bash
libinput list-devices
libinput debug-events
```

Move the pen near the display and touch the tip down. If no stylus, pressure, tip, or tool-button events appear, the problem is below Sexy S-Pen in the kernel, IPTSD, HID, libinput, or compositor path.

## Tilt or hover says unavailable

This is not necessarily an application bug. Microsoft’s hardware support matrix differs by pen family, and Linux support additionally depends on the device node, kernel, libinput, and KDE Wayland compositor. A pen can support tilt in another operating system while the current Linux path does not expose tilt axes or hover distance. Sexy S-Pen shows this as unavailable instead of inventing data.

## Buttons do not perform mouse clicks

Wayland intentionally places more control in the compositor and desktop security model than X11. Keyboard shortcuts and application actions are safer and more portable than arbitrary click injection. Test whether the button event appears in `libinput debug-events`; then try a keyboard-action mapping before considering a separately reviewed helper.

## Bluetooth pairing works but battery is unknown

A Bluetooth connection does not guarantee a battery percentage. Check the desktop Bluetooth state and inspect the device information:

```bash
bluetoothctl devices
bluetoothctl info
```

BlueZ may expose a battery percentage only when the pen reports a compatible battery service or HID battery report. The UI intentionally distinguishes **connected** from **battery available**.

## The pen is not found

Make sure the pen has a charged or fresh battery, is awake, and is close to the Surface. Use KDE’s Bluetooth settings to pair Bluetooth-capable pens. Classroom Pen and Surface Pro Pen families may not expose Bluetooth pairing at all; their writing function can still work through the display digitizer.

## The screen creates random touches

First test the Writing profile. If the problem continues, collect the following information before changing several variables at once:

```bash
uname -a
printf 'desktop: '; echo "$XDG_CURRENT_DESKTOP"
printf 'session: '; echo "$XDG_SESSION_TYPE"
iptsd --version 2>/dev/null || true
libinput list-devices
```

Include your exact Surface model, pen family, kernel package, KDE Plasma version, and whether the issue occurs only while the pen is hovering or touching.

## The app opens but does not apply system settings

This is expected for the current safe profile layer. User preferences are stored in `~/.config/sexy-s-pen.ini`; protected system changes require a future narrowly scoped polkit or service integration. Do not grant the GUI unrestricted root access just to make one toggle work.
