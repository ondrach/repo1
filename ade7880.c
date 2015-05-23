
#include <stm32f10x.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_spi.h>
#include "ade7880.h"

void ADE_SPIInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

    //SCK
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    //MISO
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    //MOSI
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    //NSS
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

	SPI_InitTypeDef SPI_InitStructure;


	/*Configure SPI1 --------------------------------------------------------------*/
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI1, &SPI_InitStructure);


    SPI_Cmd(SPI1, ENABLE);

//    SPI_SSOutputCmd(SPI2, ENABLE);

    /*POUZE PRO LADENI PAK SMAZAT*/


    uint16_t Data;
    Data = 13;
 //   GPIO_ResetBits(GPIOA, GPIO_Pin_4);
 //   SPI_I2S_SendData( SPI1, Data);
 //   while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
 //   GPIO_SetBits(GPIOA, GPIO_Pin_4);

}


/* Communication interface select */
void ADE_SPISel(void)
{
	//telo fce hyyr
//	SPI_SSOutputCmd(SPI1, ENABLE);

	int i;
	for(i = 0; i<=2; i++){

		GPIO_ResetBits(GPIOA, GPIO_Pin_4);
//		SPI_NSSInternalSoftwareConfig(SPI1, SPI_NSSInternalSoft_Set);

			uint16_t Data;
			Data = i;
			while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
			SPI_I2S_SendData( SPI1, Data);

//			SPI_SSOutputCmd(SPI1, DISABLE);
			while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
 		GPIO_SetBits(GPIOA, GPIO_Pin_4);
	}

	//toggled high to low three times after reset
	//lock the SPI by any write to CONFIG2
}

void ADE_Write( uint8_t TxData[], uint8_t Nr_Bytes)
{


	    //disable intrrupts so the SPI communication is not disturbed
	  	//Cpu_DisableInt();
/*
	  TxData[0] = 1;	//send first the ADE78xx address byte
	  TxData[1] = 2;	//send MS byte of address
	  TxData[2] = 3;	//send LS byte of address
	  TxData[3] = 4;
	  TxData[4] = 5;
*/

//	SPI_I2S_SendData( SPI1, Data);

	    //enable back the interrupts because the communication has finished
	    //Cpu_EnableInt();

	    return;
  }
