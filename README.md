# Setting up ESP32-S3-USB-OTG on Linux & MacOS



This tutorial will explain how to get `usb_host_lib` running on an ESP32-S3-USB-OTG using Linux or MacOS.

Most of this guide is based on the [official getting started webpage](https://docs.espressif.com/projects/espressif-esp-dev-kits/en/latest/esp32s3/esp32-s3-usb-otg/user_guide.html)  for this board. However, there are a number of undocumented issues that one is likely to run into while setting this all up. Here are some supplementary resources:

- ESP Forum: My question [USB Host not working on "ESP32-S3-USB-OTG Development Board"](https://www.esp32.com/viewtopic.php?f=13&t=27050)
- Youtube: [Deep Dive w/Scott: ESP32-S3 and updating the IDF #adafruit](https://www.youtube.com/watch?v=S1-I4R_XJ24&ab_channel=AdafruitIndustries)

#### Begin

The example we are running can be found in ~/esp/esp-idf/examples/peripherals/usb/host/usb_host_lib but we need to ensure that we are on the master branch of the repository.

#### Switch to the master branch

`~/esp/esp-idf: [master branch] $ git checkout master`

```bash
M	examples/peripherals/usb/host/cdc/cdc_acm_host/main/usb-cdc.c
M	examples/peripherals/usb/host/msc/main/msc_example_main.c
M	examples/peripherals/usb/host/usb_host_lib/main/usb_host_lib_main.c
Already on ‘master’
Your branch is behind ‘origin/master’ by 67 commits, and can be fast-forwarded.
  (use “git pull” to update your local branch)
```

#### Confirm that the master branch is active

`~/esp/esp-idf: [master branch] $ git branch -vv`

```bash
* master       36b83fcb98 [origin/master: behind 67] Merge branch 'docs/cpp_function_ref_fixes' into 'master'
  release/v4.4 c29343eb94 [origin/release/v4.4] Merge branch 'feature/update_esptool_v4.4' into 'release/v4.4'
```


`~/esp/esp-idf: [master branch] $ git config --local -l`

```bash
core.repositoryformatversion=0
core.filemode=true
core.bare=false
core.logallrefupdates=true
core.ignorecase=true
core.precomposeunicode=true
submodule.active=.
remote.origin.url=https://github.com/espressif/esp-idf.git
remote.origin.fetch=+refs/heads/*:refs/remotes/origin/*
branch.master.remote=origin
branch.master.merge=refs/heads/master
submodule.components/asio/asio.url=https://github.com/espressif/asio.git
submodule.components/bootloader/subproject/components/micro-ecc/micro-ecc.url=https://github.com/kmackay/micro-ecc.git
submodule.components/bt/controller/lib_esp32.url=https://github.com/espressif/esp32-bt-lib.git
submodule.components/bt/controller/lib_esp32c3_family.url=https://github.com/espressif/esp32c3-bt-lib.git
submodule.components/bt/host/nimble/nimble.url=https://github.com/espressif/esp-nimble.git
submodule.components/cmock/CMock.url=https://github.com/ThrowTheSwitch/CMock.git
submodule.components/coap/libcoap.url=https://github.com/obgm/libcoap.git
submodule.components/esp_phy/lib.url=https://github.com/espressif/esp-phy-lib.git
submodule.components/esp_wifi/lib.url=https://github.com/espressif/esp32-wifi-lib.git
submodule.components/esptool_py/esptool.url=https://github.com/espressif/esptool.git
submodule.components/expat/expat.url=https://github.com/libexpat/libexpat.git
submodule.components/ieee802154/lib.url=https://github.com/espressif/esp-ieee802154-lib.git
submodule.components/json/cJSON.url=https://github.com/DaveGamble/cJSON.git
submodule.components/lwip/lwip.url=https://github.com/espressif/esp-lwip.git
submodule.components/mbedtls/mbedtls.url=https://github.com/espressif/mbedtls.git
submodule.components/mqtt/esp-mqtt.url=https://github.com/espressif/esp-mqtt.git
submodule.components/nghttp/nghttp2.url=https://github.com/nghttp2/nghttp2.git
submodule.components/openthread/lib.url=https://github.com/espressif/esp-thread-lib.git
submodule.components/openthread/openthread.url=https://github.com/espressif/openthread.git
submodule.components/protobuf-c/protobuf-c.url=https://github.com/protobuf-c/protobuf-c.git
submodule.components/spiffs/spiffs.url=https://github.com/pellepl/spiffs.git
submodule.components/tinyusb/tinyusb.url=https://github.com/espressif/tinyusb.git
submodule.components/unity/unity.url=https://github.com/ThrowTheSwitch/Unity.git
submodule.examples/build_system/cmake/import_lib/main/lib/tinyxml2.url=https://github.com/leethomason/tinyxml2.git
submodule.examples/peripherals/secure_element/atecc608_ecdsa/components/esp-cryptoauthlib.url=https://github.com/espressif/esp-cryptoauthlib.git
branch.release/v4.4.remote=origin
branch.release/v4.4.merge=refs/heads/release/v4.4
submodule.components/cbor/tinycbor.url=https://github.com/intel/tinycbor.git
submodule.components/libsodium/libsodium.url=https://github.com/jedisct1/libsodium.git
submodule.components/bt/controller/lib_esp32h2/esp32h2-bt-lib.url=https://github.com/espressif/esp32h2-bt-lib.git
(END)

```

--------------------

#### Check ESP-IDF version 

`idf.py --version`
```bash
ESP-IDF v5.0-dev-2326-g36b83fcb98-dirty
```

--------------------

#### Check submodules and other config

`~/esp/esp-idf: [master branch] $ git config --local -l`

```bash
core.repositoryformatversion=0
core.filemode=true
core.bare=false
core.logallrefupdates=true
core.ignorecase=true
core.precomposeunicode=true
submodule.active=.
remote.origin.url=https://github.com/espressif/esp-idf.git
remote.origin.fetch=+refs/heads/*:refs/remotes/origin/*
branch.master.remote=origin
branch.master.merge=refs/heads/master
submodule.components/asio/asio.url=https://github.com/espressif/asio.git
submodule.components/bootloader/subproject/components/micro-ecc/micro-ecc.url=https://github.com/kmackay/micro-ecc.git
submodule.components/bt/controller/lib_esp32.url=https://github.com/espressif/esp32-bt-lib.git
submodule.components/bt/controller/lib_esp32c3_family.url=https://github.com/espressif/esp32c3-bt-lib.git
submodule.components/bt/host/nimble/nimble.url=https://github.com/espressif/esp-nimble.git
submodule.components/cmock/CMock.url=https://github.com/ThrowTheSwitch/CMock.git
submodule.components/coap/libcoap.url=https://github.com/obgm/libcoap.git
submodule.components/esp_phy/lib.url=https://github.com/espressif/esp-phy-lib.git
submodule.components/esp_wifi/lib.url=https://github.com/espressif/esp32-wifi-lib.git
submodule.components/esptool_py/esptool.url=https://github.com/espressif/esptool.git
submodule.components/expat/expat.url=https://github.com/libexpat/libexpat.git
submodule.components/ieee802154/lib.url=https://github.com/espressif/esp-ieee802154-lib.git
submodule.components/json/cJSON.url=https://github.com/DaveGamble/cJSON.git
submodule.components/lwip/lwip.url=https://github.com/espressif/esp-lwip.git
submodule.components/mbedtls/mbedtls.url=https://github.com/espressif/mbedtls.git
submodule.components/mqtt/esp-mqtt.url=https://github.com/espressif/esp-mqtt.git
submodule.components/nghttp/nghttp2.url=https://github.com/nghttp2/nghttp2.git
submodule.components/openthread/lib.url=https://github.com/espressif/esp-thread-lib.git
submodule.components/openthread/openthread.url=https://github.com/espressif/openthread.git
submodule.components/protobuf-c/protobuf-c.url=https://github.com/protobuf-c/protobuf-c.git
submodule.components/spiffs/spiffs.url=https://github.com/pellepl/spiffs.git
submodule.components/tinyusb/tinyusb.url=https://github.com/espressif/tinyusb.git
submodule.components/unity/unity.url=https://github.com/ThrowTheSwitch/Unity.git
submodule.examples/build_system/cmake/import_lib/main/lib/tinyxml2.url=https://github.com/leethomason/tinyxml2.git
submodule.examples/peripherals/secure_element/atecc608_ecdsa/components/esp-cryptoauthlib.url=https://github.com/espressif/esp-cryptoauthlib.git
branch.release/v4.4.remote=origin
branch.release/v4.4.merge=refs/heads/release/v4.4
submodule.components/cbor/tinycbor.url=https://github.com/intel/tinycbor.git
submodule.components/libsodium/libsodium.url=https://github.com/jedisct1/libsodium.git
submodule.components/bt/controller/lib_esp32h2/esp32h2-bt-lib.url=https://github.com/espressif/esp32h2-bt-lib.git
(END)
```

#### Update git submodules

Note that to synchronise these git submodules you need to run `git submodule update --init --recursive`

-----------

### Add my additions

Include the new file

`#include "esp32_s3_usb_otg_additions.h"`

Call the function

`usb_host_power_init();`


It’s possible that not all four of these need to be set. LIMIT_EN was the one that took me the longest to find as the wording in the documentation made it seem like it was optional.

```bash
No.      | ESP32-S3-MINI-1 Pin | Description
       1 |       GPIO18        | USB_SEL: Used to switch the USB interface. When high level, the USB_HOST interface is enabled. When low level, the USB_DEV interface is enabled.
      25 |       GPIO12        | DEV_VBUS_EN: High level to enable DEV_VBUS power supply.
      23 |       GPIO17        | LIMIT_EN: Enable current limiting IC, high level enable.
      26 |       GPIO13        | BOOST_EN: High level to enable Boost boost circuit.
```

<img src="https://github.com/MGZ-LLC/esp32_s3_usb_otg_additions/blob/main/Documentation_Screenshot_20220404.jpg?raw=true" alt="Screenshot of ESP32-S3-USB-OTG documentation"/>

The text underlined in red is what made it seem that the current limiting IC is something that can be enabled if current limiting is required for the use case.

But the text underlined in green and the schematic show that the IC needs to be enabled to get any output voltage at all.


File hosted on Github:

- [esp32_s3_usb_otg_additions.h](https://github.com/MGZ-LLC/esp32_s3_usb_otg_additions/blob/main/usb_otg_esp32_s3_additions.h)

- [esp32_s3_usb_otg_additions.h [raw]](https://raw.githubusercontent.com/MGZ-LLC/esp32_s3_usb_otg_additions/main/usb_otg_esp32_s3_additions.h)
