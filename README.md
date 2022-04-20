![LVGL Test App on Pine64 PineDio Stack BL604 RISC-V Board](https://lupyuen.github.io/images/pinedio2-title.jpg)

# LVGL Test App for Apache NuttX RTOS

Read the articles...

-   ["PineDio Stack BL604 runs Apache NuttX RTOS"](https://lupyuen.github.io/articles/pinedio2)

-   ["NuttX Touch Panel Driver for PineDio Stack BL604"](https://lupyuen.github.io/articles/touch)

This NuttX App is a simplified version of the LVGL Demo App for NuttX...

-   [incubator-nuttx-apps/examples/lvgldemo](https://github.com/lupyuen/incubator-nuttx-apps/tree/pinedio/examples/lvgldemo)

# Install App

To add this repo to your NuttX project...

```bash
## TODO: Change this to the path of our "incubator-nuttx-apps/examples" folder
pushd nuttx/apps/examples
git submodule add https://github.com/lupyuen/lvgltest-nuttx lvgltest
popd
```

Then update the NuttX Build Config...

```bash
## TODO: Change this to the path of our "incubator-nuttx" folder
cd nuttx/nuttx

## Preserve the Build Config
cp .config ../config

## Erase the Build Config and Kconfig files
make distclean

## For PineDio Stack BL604: Configure the build for PineDio Stack BL604
./tools/configure.sh bl602evb:pinedio

## For BL602 / BL604: Configure the build for BL602 / BL604
./tools/configure.sh bl602evb:nsh

## For ESP32: Configure the build for ESP32.
## TODO: Change "esp32-devkitc" to our ESP32 board.
./tools/configure.sh esp32-devkitc:nsh

## Restore the Build Config
cp ../config .config

## Edit the Build Config
make menuconfig 
```

In menuconfig, enable the LVGL Test App under "Application Configuration" → "Examples".

To run the app, enter this in the NuttX Shell...

```bash
lvgltest
```
