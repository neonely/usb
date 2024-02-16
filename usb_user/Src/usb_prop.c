#include "usb_prop.h"
#include "usb_pwr.h"

CHIPCMD chipcmd;

DEVICE Device_Table =
{
    EP_NUM,
    1
};

void Device_init()
{
	 DEVICE_INFO *pInfo = &Device_Info;
	 pInfo->Current_Configuration = 0;

	 _SetCNTR(CNTR_FRES);		//Reset USB block
	 _SetCNTR(0);				//Deassert reset signal
	 _SetISTR(0);				//Clear pending interrupts
	 USB_SIL_Init();

     bDeviceState = UNCONNECTED;
}

void Device_Reset()
{
    // Set device as not configured
    pInformation->Current_Configuration = 0;
    pInformation->Current_Interface = 0; // the default Interface
    /* Current Feature initialization */
    pInformation->Current_Feature = USB_ConfigDescriptor[7];

    SetBTABLE(BTABLE_ADDRESS);

    /* Initialize Endpoint 0 */
    SetEPType(ENDP0, EP_CONTROL);
    SetEPTxStatus(ENDP0, EP_TX_STALL);
    SetEPRxAddr(ENDP0, ENDP0_RXADDR);
    SetEPTxAddr(ENDP0, ENDP0_TXADDR);
    Clear_Status_Out(ENDP0);
    SetEPRxCount(ENDP0, Device_Property.MaxPacketSize);
    SetEPRxValid(ENDP0);

    /* инициализация EP1 OUT */
    SetEPType(ENDP1, EP_BULK);
    SetEPRxAddr(ENDP1, ENDP1_RXADDR);
    SetEPRxCount(ENDP1, Device_Property.MaxPacketSize);
    SetEPRxStatus(ENDP1, EP_RX_VALID);
    SetEPTxStatus(ENDP1, EP_TX_DIS);

    /* инициализация EP2 IN */
    SetEPType(ENDP2, EP_BULK);
    SetEPTxAddr(ENDP2, ENDP2_TXADDR);
    SetEPTxStatus(ENDP2, EP_TX_VALID);
    SetEPRxStatus(ENDP2, EP_RX_DIS);
    
    /* Set this device to response on default address */
    SetDeviceAddress(0);
    bDeviceState = ATTACHED;
}

RESULT Device_Data_Setup(uint8_t RequestNo)
{
    uint8_t* (*CopyRoutine)(uint16_t);
    CopyRoutine = NULL;

    if(RequestNo == 0x81) 
        CopyRoutine = My_Request;
    else 
        return USB_UNSUPPORT;

    pInformation->Ctrl_Info.CopyData = CopyRoutine;
    pInformation->Ctrl_Info.Usb_wOffset = 0;
    (*CopyRoutine)(0);
    
    return USB_SUCCESS;
}

uint8_t *My_Request(uint16_t Length)
{
    if(Length == 0) 
    {
        pInformation->Ctrl_Info.Usb_wLength = pInformation->USBwLengths.w;
        return NULL;
    } 
    else 
        return ((uint8_t*)(&chipcmd));
}

RESULT Device_NoData_Setup(uint8_t RequestNo)
{
    return USB_UNSUPPORT;
} 

RESULT Device_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting)
{
    if (AlternateSetting > 0)
    {
        return USB_UNSUPPORT;
    }
    else if (Interface > 0)
    {
        return USB_UNSUPPORT;
    }
    return USB_SUCCESS;
}

uint8_t *Device_GetDeviceDescriptor(uint16_t Length)
{
    return Standard_GetDescriptorData(Length, &Device_Descriptor);
}

uint8_t *Device_GetConfigDescriptor(uint16_t Length)
{
    return Standard_GetDescriptorData(Length, &Config_Descriptor);
}

uint8_t *Device_GetStringDescriptor(uint16_t Length)
{
    uint8_t wValue0 = pInformation->USBwValue0;
    if (wValue0 > 4)
    {
        return NULL;
    }
    else
    {
        return Standard_GetDescriptorData(Length, &String_Descriptor[wValue0]);
    }
}

void Device_SetConfiguration(void)
{
  if (pInformation->Current_Configuration != 0)
  {
    bDeviceState = CONFIGURED;
    ClearDTOG_TX(ENDP2);
    ClearDTOG_RX(ENDP1);
  }
}

void Device_SetDeviceAddress (void)
{
  bDeviceState = ADDRESSED;
}

DEVICE_PROP Device_Property =
{
    Device_init,
    Device_Reset,
    Device_Status_In,
    Device_Status_Out,
    Device_Data_Setup,
    Device_NoData_Setup,
    Device_Get_Interface_Setting,
    Device_GetDeviceDescriptor,
    Device_GetConfigDescriptor,
    Device_GetStringDescriptor,
    0,
    0x40 /*MAX PACKET SIZE*/
};

USER_STANDARD_REQUESTS User_Standard_Requests =
{
    Device_GetConfiguration,
    Device_SetConfiguration,
    Device_GetInterface,
    Device_SetInterface,
    Device_GetStatus,
    Device_ClearFeature,
    Device_SetEndPointFeature,
    Device_SetDeviceFeature,
    Device_SetDeviceAddress
};

