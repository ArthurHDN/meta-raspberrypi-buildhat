# meta-raspberrypi-buildhat

OpenEmbedded/Yocto layer with support for the
[Raspberry Pi Build HAT](https://www.raspberrypi.com/products/build-hat/),
an add-on board for controlling LEGO Technic motors and SPIKE Portfolio
sensors.

## Contents

| Recipe                                                | Description                                  |
| ----------------------------------------------------- | -------------------------------------------- |
| `recipes-devtools/python/python3-build-hat_0.9.0.bb`  | `buildhat` Python library (PyPI)             |
| `recipes-devtools/python/python3-gpiozero_2.0.1.post3.bb` | `gpiozero`, used to drive the HAT reset/boot pins |

## Dependencies

This layer depends on:

- `openembedded-core` (`meta`)
- `meta-raspberrypi`
- `meta-openembedded/meta-python`

Supported release series: `scarthgap`.

## Usage

Add the layer to `conf/bblayers.conf`:

```sh
bitbake-layers add-layer /path/to/meta-raspberrypi-buildhat
```

Or, with [kas](https://kas.readthedocs.io/):

```yaml
repos:
  meta-raspberrypi-buildhat:
    path: /path/to/meta-raspberrypi-buildhat
```

Install the library in your image:

```
IMAGE_INSTALL:append = " python3-build-hat"
```

## UART configuration

The Build HAT is connected to GPIO14/GPIO15 and communicates over
`/dev/serial0`, so the UART must be enabled and must not be used as the kernel
or login console. The required settings are provided by an opt-in include file;
add this to your `local.conf` or distro configuration:

```
require conf/distro/include/raspberrypi-buildhat.inc
```

With kas:

```yaml
local_conf_header:
  buildhat: |
    require conf/distro/include/raspberrypi-buildhat.inc
```

The include file sets (all weak assignments, overridable in `local.conf`):

```
ENABLE_UART ?= "1"
CMDLINE_SERIAL ?= ""
SERIAL_CONSOLES ?= ""
```

- `ENABLE_UART` adds `enable_uart=1` to `config.txt`.
- `CMDLINE_SERIAL` removes `console=serial0,115200` from `cmdline.txt`
  (see `rpi-cmdline` in `meta-raspberrypi`).
- `SERIAL_CONSOLES` prevents a getty from being spawned on the UART.

## Maintainer

Arthur Nunes

## License

MIT, see [LICENSE](LICENSE).
