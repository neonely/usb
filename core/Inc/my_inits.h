#ifndef MY_CLOCK_H
#define MY_CLOCK_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_i2c.h"
#include "stm32f10x_flash.h"

void init_my_clock(void);
void init_usb_clock(void);
void init_my_gpio(void);

#endif
