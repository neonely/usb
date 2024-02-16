#include "stm32f10x.h"
#include "usb_prop.h"
#include "usb_endp.h"
#include "usb_mem.h"
#include <stdio.h>

#define SWO_OUTPUT

extern uint8_t bulk_buffer[64];
unsigned char str1[] = "Hello from USB device STM32+++\nHello from USB device STM32++++\n";

void Device_IN_Data(void);
void Device_OUT_Data(void);

void EP1_OUT_Callback()
{
	Device_OUT_Data();
}

void EP2_IN_Callback()
{
	Device_IN_Data();
}

/* Запись в девайс */
void Device_OUT_Data()
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);

	uint16_t len = GetEPRxCount(EP1_OUT);
	PMAToUserBufferCopy(bulk_buffer, ENDP1_RXADDR, len);
	SetEPRxStatus(ENDP1, EP_RX_VALID);

	#ifdef SWO_OUTPUT
            printf("WRITE DEVICE\n");
    #endif
	
	GPIO_SetBits(GPIOA, GPIO_Pin_1);
}

/* Чтение девайса */
void Device_IN_Data()
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	
	UserToPMABufferCopy(str1, ENDP2_TXADDR, sizeof(str1));
	SetEPTxCount((ENDP2_TXADDR & 0x7F), 64);
	SetEPTxStatus(ENDP2, EP_TX_VALID);

	#ifdef SWO_OUTPUT
            printf("READ DEVICE\n");
    #endif
	
	GPIO_SetBits(GPIOA, GPIO_Pin_1);
}
