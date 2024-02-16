#ifndef USB_PROP_H
#define USB_PROP_H

#include "hw_config.h"
#include "usb_lib.h"
#include "usb_desc.h"
#include "usb_conf.h"
#include "stm32f10x_gpio.h"

#define Device_Status_In 		    NOP_Process 
#define Device_Status_Out		    NOP_Process 

#define Device_GetConfiguration		NOP_Process
//#define Device_SetConfiguration	NOP_Process
#define Device_GetInterface			NOP_Process
#define Device_SetInterface			NOP_Process
#define Device_GetStatus			NOP_Process
#define Device_ClearFeature			NOP_Process
#define Device_SetEndPointFeature	NOP_Process
#define Device_SetDeviceFeature		NOP_Process
//#define Device_SetDeviceAddress	NOP_Process 

void Device_init(void);
void Device_Reset(void);
RESULT Device_Data_Setup(uint8_t RequestNo);
RESULT Device_NoData_Setup(uint8_t RequestNo);
RESULT Device_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting);
uint8_t *Device_GetDeviceDescriptor(uint16_t Length);
uint8_t *Device_GetConfigDescriptor(uint16_t Length);
uint8_t *Device_GetStringDescriptor(uint16_t Length);
uint8_t *My_Request(uint16_t Length);
void Device_SetConfiguration(void);
void Device_SetDeviceAddress (void);

typedef struct _CHIPCMD
{
    uint8_t cbw;
    uint16_t capacity;
    uint16_t address;
    uint16_t count;
    uint8_t spi_edi;
    uint8_t www;
}CHIPCMD;

#endif
