/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_PWR_H
#define __USB_PWR_H
/* Includes ------------------------------------------------------------------*/
#include "usb_core.h"
#include "usb_type.h"

typedef enum _DEVICE_STATE
{
  UNCONNECTED,
  ATTACHED,
  POWERED,
  SUSPENDED,
  ADDRESSED,
  CONFIGURED
} DEVICE_STATE;

/* External variables --------------------------------------------------------*/
extern  __IO uint32_t bDeviceState; /* USB device status */

#endif  /*__USB_PWR_H*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
