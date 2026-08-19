---
layout: default
title: Architecture and Support Boundaries
---

# Architecture and Support Boundaries

Sexy S-Pen is a control panel, not a replacement for the Surface Linux kernel stack. The UI is written in Qt/QML and the controller stores user preferences, probes system state, hands pairing to KDE, and reports capabilities.

## Input path

```text
Surface touchscreen and pen hardware
        ↓
Surface Linux kernel and IPTSD
        ↓
uinput / libinput
        ↓
KDE Plasma + KWin Wayland compositor
        ↓
Sexy S-Pen capability and profile UI
```

IPTSD processes raw Surface touchscreen and stylus measurements and creates standard input events. Its configuration includes touchscreen palm and stylus-proximity policies. libinput and KWin determine which pressure, tilt, proximity, eraser, button, and calibration features are available to applications.

## Bluetooth and battery path

```text
Surface Pen Bluetooth radio
        ↓
BlueZ D-Bus
        ↓
Desktop Bluetooth state
        ↓
Sexy S-Pen connection and battery card
```

BlueZ can expose a battery percentage through `org.bluez.Battery1`, but the pen must actually report a compatible battery service or HID battery report. Connection and battery availability are separate states.

## Why this is progressive enhancement

Different Microsoft Surface Pens have different hardware. Some have two side buttons, some have one, some have an eraser, some have Bluetooth, some have tilt, and some have no Bluetooth at all. Even when a pen has a feature, the Linux kernel or compositor might not expose it through the current device path.

Sexy S-Pen therefore follows three rules:

1. Detect capabilities when possible.
2. Show unavailable features clearly.
3. Never claim to create hardware signals that the pen or operating system does not provide.

## Privilege boundary

The current application stores preferences in the user’s configuration directory and does not silently overwrite `/etc/iptsd.conf`, restart system services, or execute arbitrary root commands. A future system integration should use a narrowly scoped polkit helper or dedicated service accepting only validated settings.

This boundary is intentional. A beautiful pen UI is not worth turning a user’s input settings panel into an unrestricted root command launcher.

## Research references

- [linux-surface/iptsd](https://github.com/linux-surface/iptsd)
- [iptsd default configuration](https://raw.githubusercontent.com/linux-surface/iptsd/master/etc/iptsd.conf)
- [libinput tablet support](https://wayland.freedesktop.org/libinput/doc/latest/tablet-support.html)
- [BlueZ Battery1 interface](https://github.com/bluez/bluez/blob/master/doc/org.bluez.Battery.rst)
- [Microsoft Surface Pen compatibility](https://support.microsoft.com/en-us/surface/pen/surface-pen-compatibility-and-features)
