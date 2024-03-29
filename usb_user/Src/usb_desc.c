#include "usb_desc.h"

const uint8_t USB_DeviceDescriptor[SIZ_DEVICE_DESC] = 
{
    0x12,       /* bLength */
    0x01,       /* bDescriptorType */
    0x00, 0x02, /* bcdUSB = 2.00 */
    0xFF,       /* bDeviceClass: Vendor Specific */
    0x00,       /* bDeviceSubClass */
    0x00,       /* bDeviceProtocol */
    0x40,       /* bMaxPacketSize0 64 bytes*/
    0xAD, 0xDE, /* idVendor*/
    0x0D, 0xF0, /* idProduct*/
    0x00, 0x01, /* bcdDevice = 2.00 */
    1,          /* Index of string descriptor describing manufacturer */
    2,          /* Index of string descriptor describing product */
    3,          /* Index of string descriptor describing the device's serial number */
    0x01        /* bNumConfigurations */
};

const uint8_t USB_ConfigDescriptor[SIZ_CONFIG_DESC] = 
{
    /*Configuration Descriptor*/
    0x09,            /* bLength: Configuration Descriptor size */
    0x02,            /* bDescriptorType: Configuration */
    SIZ_CONFIG_DESC, /* wTotalLength:no of returned bytes */
    0x00, 0x01,      /* bNumInterfaces: 1 interface */
    0x01,            /* bConfigurationValue: Configuration value */
    0x00,            /* iConfiguration: Index of string descriptor describing the configuration */
    0xE0,            /* bmAttributes: bus powered */
    0x32,            /* MaxPower 100 mA */

    /*Interface Descriptor*/
    0x09, /* bLength: Interface Descriptor size */
    0x04, /* bDescriptorType: Interface */
    0x00, /* bInterfaceNumber: Number of Interface */
    0x00, /* bAlternateSetting: Alternate setting */
    0x02, /* bNumEndpoints: One endpoints used */
    0xFF, /* bInterfaceClass: Vendor Specific*/
    0x00, /* bInterfaceSubClass*/
    0x00, /* bInterfaceProtocol*/
    0x00, /* iInterface: */

    /*Endpoint 1 Descriptor*/
    0x07,      /* bLength: Endpoint Descriptor size */
    0x05,      /* bDescriptorType: Endpoint */
    0x01,      /* bEndpointAddress: (OUT1) */
    0x02,      /* bmAttributes: Bulk */
    0x40,      /* wMaxPacketSize: */
    0x00, 0x00,/* bInterval: */
    
    /*Endpoint 2 Descriptor*/
    0x07,      /* bLength: Endpoint Descriptor size */
    0x05,      /* bDescriptorType: Endpoint */
    0x82,      /* bEndpointAddress: (IN2) */
    0x02,      /* bmAttributes: Bulk */
    0x40,      /* wMaxPacketSize: */
    0x00, 0x00 /* bInterval: */
};

/* USB String Descriptors */
const uint8_t USB_StringLangID[SIZ_STRING_LANGID] = 
{
    SIZ_STRING_LANGID, /* bLength */
    0x03,              /* String descriptor */
    0x09, 0x04         /* LangID = 0x0409: U.S. English */
};

const uint8_t USB_StringVendor[SIZ_STRING_VENDOR] = 
{ 
    SIZ_STRING_VENDOR, /* Size of Vendor string */
    0x03,                                                                	/* bDescriptorType*/

    /* Manufacturer: "Amon-Ra" */
    'V', 0, 'l', 0, 'a', 0, 'd', 0, 'i', 0, 'm', 0, 'i', 0, 'r', 0 };

const uint8_t USB_StringProduct[SIZ_STRING_PRODUCT] = 
{ 
    SIZ_STRING_PRODUCT, /* bLength */
    0x03,                                                                   /* bDescriptorType */

    /* Product name: "USB LCD" */
    'U', 0, 'S', 0, 'B', 0, ' ', 0, 'X', 0, 'X', 0, 'X', 0 };

uint8_t USB_StringSerial[SIZ_STRING_SERIAL] = 
{ 
    SIZ_STRING_SERIAL, /* bLength */
    0x03,                                                          			/* bDescriptorType */

    'U', 0, 'S', 0, 'B', 0, 'T', 0, 'E', 0, 'S', 0, 'T', 0 };

ONE_DESCRIPTOR Device_Descriptor = 
{ 
    (uint8_t*)USB_DeviceDescriptor, 
    SIZ_DEVICE_DESC 
};

ONE_DESCRIPTOR Config_Descriptor = 
{ 
    (uint8_t*)USB_ConfigDescriptor, 
    SIZ_CONFIG_DESC 
};

ONE_DESCRIPTOR String_Descriptor[4] = 
{ 
    { (uint8_t*)USB_StringLangID,   SIZ_STRING_LANGID },
    { (uint8_t*)USB_StringVendor,   SIZ_STRING_VENDOR }, 
    { (uint8_t*)USB_StringProduct,  SIZ_STRING_PRODUCT },
    { (uint8_t*)USB_StringSerial,   SIZ_STRING_SERIAL } 
};
