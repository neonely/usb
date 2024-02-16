#include "hw_config.h"
#include "my_inits.h"
#include "usb_lib.h"
#include "usb_pwr.h"
#include <stdlib.h>
#include <stdio.h>

#define SWO_OUTPUT

#ifdef SWO_OUTPUT
int _write(int file, char *ptr, int len)
{
	while(len--) ITM_SendChar(*ptr++);	
	return 0;
}
#endif

uint8_t bulk_buffer[64];
unsigned char str[] = "Hello from USB device STM32!!!\nHello from USB device STM32!!!!\n";

int main(void)
{
    init_my_clock();
    init_my_gpio();

    init_usb_clock();
    USB_Interrupts_Config();
    USB_Init();

    while (bDeviceState != CONFIGURED)
    {

    }
	UserToPMABufferCopy(str, ENDP2_TXADDR, sizeof(str));
    SetEPTxCount(ENDP2, 64);
	SetEPTxStatus(ENDP2, EP_TX_VALID);

    #ifdef SWO_OUTPUT
            printf("MAIN\n");
    #endif

    while(1) 
    {
        // loop
    }
}
