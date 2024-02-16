#ifndef USB_CONF_H
#define USB_CONF_H

// 3 EPs, 0 CONTROL, 1 OUT, 2 IN
#define EP_NUM			    (0x03)

#define BTABLE_ADDRESS      (0x00)

/* EP0 */
/* rx/tx buffer base address */
#define ENDP0_RXADDR        (0x40)
#define ENDP0_TXADDR        (0x80)

/* EP1 */
/* rx buffer base address */
#define ENDP1_RXADDR        (0xC0)

/* EP2*/
/* tx buffer base address */
#define ENDP2_TXADDR        (0x100)

/* IMR_MSK */
/* mask defining which events has to be handled */
/* by the device application software */
#define IMR_MSK (CNTR_CTRM  | CNTR_RESETM )//| CNTR_SOFM )

//#define SOF_CALLBACK

#endif
