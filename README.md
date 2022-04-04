# LVGL Test App for Apache NuttX RTOS

See https://github.com/lupyuen/pinedio-stack-nuttx

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
