# ESP8266 Setup
The followings are notes for setting up (most) ESP8266 boards to work with the Arduino IDE and libraries.

## Installation
Download the Arduino IDE.  Then follow the instructions to get SDK installed in the Arduino environment.

#### Install Arduino core libraries

* [8266 Arduino core libraries installation](https://github.com/esp8266/Arduino) - follow documentation to install CSP8266 packages.
* [8266 Arduino core documentation](https://arduino-esp8266.readthedocs.io/en/latest/) - additional docs about the Arduino core libraries for the ESP board

#### Install USB to UART bridge
The boards come with a UART serial port.  In order to use USB, you must install a USP bridge driver.  If you look under your device, it may have the driver name/version printed.  Let us assume you will need USB-to-UART bridge driver CP2102 from Silicon Labs.

* [Download driver here](https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers) - select driver for your OS
* Follow instructions install your driver


#### Troubleshooting
You may run into issues after installing the driver above. After connecting the device, it may not show up in the port listing in the Arduino IDE.  If that is the case there are several things to consider:

1) **IMPORTANT**  - Use a high quality micro-USB cable that is capable of both data and charging.  This will save you hours of troubleshooting.
2) **MacOS (Sierra/High Sierra or later)** - can run into issues and not start the driver at all. The followings may help:
  - After installing the driver, ensure it is running with the following by grepping for the silab driver:
```shell
$> kextstat | grep labs
  185    0 0xffffff7f846d2000 0x9000     0x9000     com.silabs.driver.CP210xVCPDriver (5.0.4) AB2A33AD-B60D-35F9-A3F5-084252A66E50 <142 23 4 3>
```
  - If the above comomand returns empty, then you will have to start the driver manually using the following:
```shell
$> sudo kextload /Library/Extensions/SiLabsUSBDriver.kext/
```
  - The previous may fail with security policy errors.  If that is the case, under System Preferences, go into *Security and Privacy*. Look for a request to accept/start/allow driver from Silicon Labs. Allow the driver to run.
  - Then validate that the driver is running using the `kextstat` command.  If not, restart it using the `kextload` command (see above).
  - Then as an additional validation step, use the following to make sure the driver is properly running:
```shell
$> sudo kextutil -tn /Library/Extensions/SiLabsUSBDriver.kext
```
  - Lastly, after connecting your ESP8266 device, you can check to make sure the device is recognized as a Silicon Labs device.  Make sure the `/dev/cu.SLAB_USBtoUART` is listed as shown below: 
```shell
$> ls -l /dev/cu.*
crw-rw-rw-  1 root  wheel   21,   1 Apr  5 22:05 /dev/cu.Bluetooth-Incoming-Port
crw-rw-rw-  1 root  wheel   21,  13 Apr  6 12:37 /dev/cu.SLAB_USBtoUART
```
 - Next, start the Arduino IDE, open an example sketch, connect the device, and try to load the example unto the device.

