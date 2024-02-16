#ifndef USB_DESC_H
#define USB_DESC_H

#include "usb_lib.h"

#define SIZ_DEVICE_DESC		0x12
#define SIZ_CONFIG_DESC		0x20
#define SIZ_STRING_LANGID	0x04
#define SIZ_STRING_VENDOR	0x12
#define SIZ_STRING_PRODUCT	0x10
#define SIZ_STRING_SERIAL	0x10

extern const uint8_t USB_ConfigDescriptor[SIZ_CONFIG_DESC];

extern ONE_DESCRIPTOR Device_Descriptor;
extern ONE_DESCRIPTOR Config_Descriptor;
extern ONE_DESCRIPTOR String_Descriptor[4];

#endif
