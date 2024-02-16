#include "usb_lib.h"
#include "usb_conf.h"
#include "usb_pwr.h"
#include "hw_config.h"

__IO uint32_t bDeviceState = UNCONNECTED; /* USB device status */

