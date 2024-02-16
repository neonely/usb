#include "my_inits.h"

ErrorStatus HSEStartUpStatus;

void init_my_gpio()
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    I2C_InitTypeDef I2C_InitStructure;
    
    /* LED usb, Rx Tx */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_SetBits(GPIOA, GPIO_Pin_1);

    /* Configure I2C_EE pins: SCL and SDA */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* I2C configuration */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
    I2C_StructInit(&I2C_InitStructure);
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_OwnAddress1 = 0x15;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_ClockSpeed = 400000;
    I2C_Init(I2C2, &I2C_InitStructure);
    I2C_Cmd(I2C2, ENABLE);
}

void init_my_clock()
{

  RCC_DeInit();
  RCC_HSEConfig(RCC_HSE_ON);
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if (HSEStartUpStatus == SUCCESS)
  {
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
    FLASH_SetLatency(FLASH_Latency_2);
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
    RCC_PCLK2Config(RCC_HCLK_Div1); 
    RCC_PCLK1Config(RCC_HCLK_Div2);

#ifdef STM32F10X_CL	
    RCC_PREDIV2Config(RCC_PREDIV2_Div5);
    RCC_PLL2Config(RCC_PLL2Mul_8);
    RCC_PLL2Cmd(ENABLE);
    while (RCC_GetFlagStatus(RCC_FLAG_PLL2RDY) == RESET)
    {}
    RCC_PREDIV1Config(RCC_PREDIV1_Source_PLL2, RCC_PREDIV1_Div5);
    RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_9);
#else
    // PLLCLK = 8MHz * 9 = 72 MHz
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
#endif

    RCC_PLLCmd(ENABLE);

    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }
  }
  else
  {
    while (1)
    {
    }
  }
}

void init_usb_clock()
{
	RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_1Div5);
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, ENABLE);
}

