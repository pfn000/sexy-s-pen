# Microsoft Surface Pen Family Compatibility

Sexy S-Pen should support the full Microsoft Surface Pen family through runtime capability detection. Microsoft’s compatibility guide groups pens by feature families rather than promising identical behavior for every generation [1]. The backend should identify the connected device where possible and expose only the controls that the device, kernel, libinput, compositor, and Bluetooth stack actually report.

| Microsoft pen family | Pressure / inking | Bluetooth | Tilt | Magnet attach | Sexy S-Pen policy |
|---|---:|---:|---:|---:|---|
| Surface Slim Pen / Slim Pen 2 | 4096 pressure points | Yes | Yes | Supported on compatible Surface devices | Full artist profile, pairing, battery attempt, tilt/hover when Linux exposes them |
| Surface Slim Pen, 1st generation | 4096 pressure points | Yes | Yes | Device-dependent | Same progressive-enhancement path as Slim Pen 2 |
| Surface Pen with no clip | 1024 or 4096 depending on model | Yes | Model-dependent | Model-dependent | Pressure, buttons, pairing, battery, and tilt only when detected |
| Surface Pen with one button on flat edge | 1024 or 4096 depending on model | Yes | Model-dependent | No | Support the single side-action layout and runtime-map button capabilities |
| Surface Pen with two side buttons | 1024 or 4096 depending on model | Yes | Model-dependent | No | Support separate side-button mappings and eraser/tool events when exposed |
| Microsoft Classroom Pen | 1024 or 4096 depending on model | No | No | No | Support writing/pressure and button behavior available through the input device; omit Bluetooth UI |
| Microsoft Classroom Pen 2 / Microsoft Business Pen | 1024 or 4096 depending on model | No | No | No | Same non-Bluetooth progressive-enhancement path |
| Surface Pro Pen | 1024 pressure points | No | No | No | Support pressure and inking; do not show pairing, battery, tilt, or hover unless the OS reports them independently |
| Surface Hub Pen | 4096 pressure points | Yes | Yes | Device-dependent | Support pressure, tilt, Bluetooth/battery attempt, and dual-tool capability where Linux exposes it |

## Runtime policy

The application must not infer features solely from a marketing name. It should probe for Bluetooth presence, battery data, stylus pressure, tilt axes, proximity, tip/eraser state, and tool-button events. For example, a Bluetooth-enabled pen can still report no battery percentage, and a pen advertised with tilt support may not expose tilt through a particular Linux kernel/compositor path.

## Reference

[1]: https://support.microsoft.com/en-us/surface/pen/surface-pen-compatibility-and-features "Microsoft Surface Pen compatibility and features"
