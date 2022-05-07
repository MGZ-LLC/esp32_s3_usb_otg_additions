/* 
    Changes for the ESP32-S3-USB-OTG Development Board
    More information can be found at the bottom of this file.
*/
#include "driver/gpio.h"

static const char *USB_ADDITIONS_TAG = "ESP32-S3-USB-ADDITIONS";

#define DEV_VBUS_EN GPIO_NUM_12     // DEV_VBUS_EN: High level to enable DEV_VBUS power supply. (power the board from the device port by connecting to a computer)
#define BOOST_EN GPIO_NUM_13        // BOOST_EN: High level to enable Boost boost circuit. Low to enable USB_DEV as the power source
#define IDEV_LIMIT_EN GPIO_NUM_17   // LIMIT_EN: Enable current limiting IC, high level enable.
#define USB_SEL GPIO_NUM_18         // USB_SEL: Used to switch the USB interface. When high level, the USB_HOST interface is enabled. When low level, the USB_DEV interface is enabled.

#define GPIO_OUTPUT_PIN_SEL  ((1ULL<<DEV_VBUS_EN) | (1ULL<<BOOST_EN)| (1ULL<<IDEV_LIMIT_EN) | (1ULL<<USB_SEL))

void usb_host_power_init(){   
    gpio_config_t io_conf = {
        io_conf.intr_type = GPIO_INTR_DISABLE,      //disable interrupt
        io_conf.mode = GPIO_MODE_OUTPUT,            //set as output mode
        io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL, //bit mask of the pins to set,e.g.GPIO12/18
        io_conf.pull_down_en = 0,                   //disable pull-down mode
        io_conf.pull_up_en = 0                      //disable pull-up mode
    };
    
    gpio_config(&io_conf);              //configure GPIO with the given settings
    gpio_set_level(DEV_VBUS_EN, 1);     // Purpose: Powers USB_HOST (USB-A socket/receptacle) with power from the USB_DEV port (USB-A plug) as opposed to the battery [Therefore we should set the battery switch to OFF when using this mode]
    ESP_LOGI(USB_ADDITIONS_TAG, "   DEV_VBUS_EN (GPIO_NUM_12) configured as HIGH.");
    gpio_set_level(BOOST_EN, 0);        // Purpose: Avoids undefined behavior. Disable when using USB power, as we do not need the boost functionality. The boost IC can raise the battery voltage from 3.5 to 5 when enabled.
    ESP_LOGI(USB_ADDITIONS_TAG, "      BOOST_EN (GPIO_NUM_13) configured as LOW.");
    gpio_set_level(IDEV_LIMIT_EN, 1);   // Purpose: Enables voltage to leave the current limiting IC (Vout)
    ESP_LOGI(USB_ADDITIONS_TAG, " IDEV_LIMIT_EN (GPIO_NUM_17) configured as HIGH.");
    gpio_set_level(USB_SEL, 1);         // Purpose: Determines whether signals are routed to either the USB_HOST or the USB_DEV
    ESP_LOGI(USB_ADDITIONS_TAG, "           USB_SEL (GPIO 18) configured as HIGH.");
}

/* Changes for the ESP32-S3-USB-OTG Development Board
source: https://docs.espressif.com/projects/espressif-esp-dev-kits/en/latest/esp32s3/esp32-s3-usb-otg/user_guide.html
- #usb-host-interface-power-options
USB HOST interface power supply selection:

BOOST_EN | DEV_VBUS_EN | Power Source
       0 |           1 | USB_DEV
       1 |           0 | Battery
       0 |           0 | No output
       1 |           1 | Undefined

- #pin-layout
No.      | ESP32-S3-MINI-1 Pin | Description
       1 |       GPIO18        | USB_SEL: Used to switch the USB interface. When high level, the USB_HOST interface is enabled. When low level, the USB_DEV interface is enabled.
      25 |       GPIO12        | DEV_VBUS_EN: High level to enable DEV_VBUS power supply.
      23 |       GPIO17        | LIMIT_EN: Enable current limiting IC, high level enable.
      26 |       GPIO13        | BOOST_EN: High level to enable Boost boost circuit.
*/