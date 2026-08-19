---
layout: default
title: Sexy S-Pen Documentation
description: A practical guide to the Sexy S-Pen project for Microsoft Surface Pen users on KDE Wayland and Surface Linux.
---

# Sexy S-Pen

> **Make the Surface Pen feel less like a compromise and more like a real creative instrument.**

Sexy S-Pen is an artist-first control centre for Microsoft Surface Pen devices running Surface Linux, KDE Plasma, Wayland, CachyOS, and Arch Linux. It brings palm-rejection profiles, pressure and smoothing controls, button mapping, Bluetooth pairing handoff, battery reporting, calibration guidance, packaging, and troubleshooting into one focused project.

<div class="notice">
<strong>Current project status:</strong> Sexy S-Pen is a solo-built early release. It is useful, opinionated, and still growing. Please be patient, respectful, and specific when reporting problems or requesting features.
</div>

## Why this exists

I was frustrated with the gap between what a modern stylus can feel like on an iPad or professional drawing tablet and what was immediately available on my Linux Surface. At some point I decided: **fuck it, I’ll build the control centre I actually want.** Sexy S-Pen is the result of that decision.

This is not a corporate product built by a large team. It is being built by one person, on real hardware, with real constraints, and with the goal of making Surface Pen use on Linux less frustrating for artists, writers, students, and note-takers.

## Original development system

The original build and design target is:

| Component | Original target |
|---|---|
| Device | Microsoft Surface Pro 7 |
| Distribution | CachyOS Linux, Arch-based |
| Desktop | KDE Plasma 6.7.4 |
| Frameworks | KDE Frameworks 6.29.0 |
| Qt | Qt 6.11.1 |
| Kernel | `6.19.8-arch1-3-surface` |
| Session | Wayland |
| CPU | 4-thread Intel Core i3-1005G1 |
| Memory | 4 GiB RAM, approximately 3.4 GiB usable |
| Graphics | Intel UHD Graphics |
| Input stack | Surface Linux / IPTSD, libinput, KDE Wayland |
| Primary pen | Microsoft Surface Slim-style pen with two buttons, blue/black appearance |

The app is intentionally designed to remain lightweight because the original system has only 4 GiB of memory. A feature that requires a heavy background service, unrestricted root access, or a large runtime needs a strong reason to exist.

## What Sexy S-Pen is trying to provide

| Area | Project goal |
|---|---|
| Palm rejection | Writing, Drawing, Balanced, and Touch-first profiles with IPTSD-aware settings |
| Artist feel | Pressure threshold, pressure curves, smoothing, and future per-application profiles |
| Pen awareness | Connection bubble, battery state, proximity/hover, tilt, eraser, and button capability detection |
| Setup | A simple Arch build path, Flatpak packaging, shell installer, and GitHub releases |
| Documentation | Practical setup, troubleshooting, hardware notes, and honest limitations |
| Community | Respectful forks, attribution, issue reports, and contributions that keep the original project visible |

## Documentation map

Start with the [installation and usage guide](usage.md), then review the [Surface Pen compatibility matrix](surface-pen-compatibility.md) and [troubleshooting guide](troubleshooting.md). The [architecture notes](architecture.md) explain how the UI, Surface Linux, IPTSD, libinput, Wayland, and BlueZ fit together.

The main source repository is [github.com/pfn000/sexy-s-pen](https://github.com/pfn000/sexy-s-pen). The latest packaged release is available on the [GitHub Releases page](https://github.com/pfn000/sexy-s-pen/releases).

## Please be respectful

Sexy S-Pen is being built fully by one person, not a team. Please do not be hostile because a feature is incomplete, a hardware path is unsupported, or a bug needs more time. Good bug reports include your pen model, Surface model, kernel, desktop session, `iptsd` status, and the exact behavior you observed.

Forks and experiments are welcome. Please keep the original project link, GPL license, image attributions, and credit to **pfn000** intact. For private fork coordination, you can contact [@Saidie.10 on Signal](https://signal.me/#eu/ZIWHg_RQMXsICHB_NBchn-W3n2tzj1M7WuZnmGIL7W3nWHugo6sx-MaY_8jJmPYSfc). Read the repository’s [`CONTRIBUTING.md`](https://github.com/pfn000/sexy-s-pen/blob/master/CONTRIBUTING.md) before publishing a substantially renamed derivative.

## Search and discoverability

If Sexy S-Pen helps you, linking to the project from a blog, forum post, Linux hardware guide, or artist workflow article helps other Surface Linux users find it. Please use descriptive phrases such as **Surface Pen on Linux**, **Surface Pro 7 pen Wayland**, **KDE Plasma palm rejection**, **CachyOS Surface Pen**, and **linux-surface IPTSD** when those terms genuinely describe your article. Do not spam search engines or post misleading claims.
