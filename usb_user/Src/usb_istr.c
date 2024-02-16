#include "usb_istr.h"


__IO uint16_t wIstr;            /* ISTR register last read value */
__IO uint8_t bIntPackSOF = 0;  /* SOFs received between 2 consecutive packets */

void USB_HP_CAN1_TX_IRQHandler(void)
{
    CTR_HP();
}

void USB_LP_CAN1_RX0_IRQHandler(void)
{
    wIstr = _GetISTR();
#if(IMR_MSK & ISTR_CTR)
    if(wIstr & ISTR_CTR & wInterrupt_Mask) 
    {
        CTR_LP();
    }
#endif

#if(IMR_MSK & ISTR_RESET)
    if(wIstr & ISTR_RESET & wInterrupt_Mask) 
    {
        _SetISTR((uint16_t)CLR_RESET);
        Device_Property.Reset();
    }
#endif

#if(IMR_MSK & ISTR_SOF)
    if(wIstr & ISTR_SOF & wInterrupt_Mask) 
    {
        _SetISTR((uint16_t)CLR_SOF);
        bIntPackSOF++;

#ifdef SOF_CALLBACK
        SOF_Callback();
#endif
    }
#endif
}

void (*pEpInt_IN[7])(void) =
{
	NOP_Process,
	EP2_IN_Callback,
    NOP_Process,
    NOP_Process,
    NOP_Process,
    NOP_Process,
    NOP_Process,
};

void (*pEpInt_OUT[7])(void) =
{
    EP1_OUT_Callback,
    NOP_Process,
    NOP_Process,
    NOP_Process,
    NOP_Process,
    NOP_Process,
    NOP_Process,
};
