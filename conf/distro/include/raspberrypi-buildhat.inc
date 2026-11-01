# Configuration required to use the Raspberry Pi Build HAT.
#
# This file is opt-in: include it from your distro configuration or local.conf:
#
#     require conf/distro/include/raspberrypi-buildhat.inc
#
# The Build HAT is connected to GPIO14/GPIO15 and is accessed through
# /dev/serial0, so the UART must be enabled and must not be used as a
# console by the kernel or by a getty.

# Enable the UART in config.txt (enable_uart=1)
ENABLE_UART ?= "1"

# Do not add console=serial0,115200 to cmdline.txt
CMDLINE_SERIAL ?= ""

# Do not spawn a getty on the UART
SERIAL_CONSOLES ?= ""

IMAGE_INSTALL:append = " \
    python3-build-hat \
    rpi-gpio \
    udev-rules-rpi \
"
