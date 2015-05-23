#include "stm32f10x.h"

#include "stm32f10x_conf.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#include "ST7735.h"
#include "ade7880.h"

//#include "stm32f10x_spi.h"
//#include "spi.h"
//#include "main.h"
//#include <stdint.h>

/***************************************************************************//**
 * Declare function prototypes
 ******************************************************************************/
void RCC_Configuration(void);
//void GPIO_Configuration(void);
//void NVIC_Configuration(void);

#define  USE_FULL_ASSERT 0;

//void SPI_Exp(void);






int main(void)
{


//	SPI_Exp();
//	ST7735_init();


	RCC_Configuration();	//Enables clock for all used peripherials


	GPIO_InitTypeDef GPIO_InitStructure;		//LED blue
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);


//	spiInit(SPI2);
//	spiReadWrite(SPILCD, 0, data, 1, LCDSPEED);

//	SPI_I2S_SendData(SPI2, data);

	ADE_SPIInit();
//	ST7735_init();
	ADE_SPISel();


	while(1)
    {

		//spiReadWrite(SPILCD, 0, data, 1, LCDSPEED);
/*
		Delay(200000);
		data += 10;
		if (data >= 1000) data==0;
		SPI_I2S_SendData(SPI2, data);
*/


		Delay(4000000);
		GPIO_SetBits(GPIOC, GPIO_Pin_8 );

		Delay(4000000);
		GPIO_ResetBits(GPIOC, GPIO_Pin_8 );


    }
}


void RCC_Configuration(void)
{
	ErrorStatus HSEStartUpStatus;

    /* RCC system reset(for debug purpose) */
    RCC_DeInit();

    /* Enable HSE */
    RCC_HSEConfig(RCC_HSE_ON);

    /* Wait till HSE is ready */
    HSEStartUpStatus = RCC_WaitForHSEStartUp();

    if (HSEStartUpStatus == SUCCESS)
    {
        /* HCLK = SYSCLK */
        RCC_HCLKConfig(RCC_SYSCLK_Div1);

        /* PCLK2 = HCLK/2 */
        RCC_PCLK2Config(RCC_HCLK_Div1);

        /* PCLK1 = HCLK/2 */
        RCC_PCLK1Config(RCC_HCLK_Div2);

        /* PLLCLK = 8MHz * 3 = 24 MHz */
        RCC_PLLConfig(0x00010000, RCC_PLLMul_3);

        /* Enable PLL */
        RCC_PLLCmd(ENABLE);

        /* Wait till PLL is ready */
        while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) {}

        /* Select PLL as system clock source */
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

        /* Wait till PLL is used as system clock source */
        while (RCC_GetSYSCLKSource() != 0x08) {}
    }

    /* Enable peripheral clocks ----------------------------------------------*/
    /* GPIOA, GPIOB and SPI1 clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_SPI1, ENABLE);
    /* SPI2 Peripheral clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
}
