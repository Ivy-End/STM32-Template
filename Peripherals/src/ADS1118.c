#include "ADS1118.h"

volatile uint8_t ReadData_1;
volatile uint8_t ReadData_2;
volatile uint8_t ReadData_3;
volatile uint8_t ReadData_4;
volatile uint32_t ReadData;

void ADS1118_CS_Set(void)
{
    GPIO_SetBits(GPIOA,GPIO_Pin_4);
}

void ADS1118_CS_Reset(void)
{
    GPIO_ResetBits(GPIOA,GPIO_Pin_4);
}

void ADS1118_Init(void)
{
    SPI_InitTypeDef  SPI_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure); 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure); 
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    ADS1118_CS_Set(); 
 
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI1, &SPI_InitStructure);

    SPI_Cmd(SPI1, ENABLE);
}

uint8_t ADS1118_Send(uint8_t Data)
{
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    
    SPI_I2S_SendData(SPI1, Data);	
    
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
    
    return SPI_I2S_ReceiveData(SPI1);
}

void ADS1118_Delay(uint32_t Count)
{
    for(; Count != 0; Count--);
}

uint32_t ADS1118_Read(uint16_t Config)
{
    ADS1118_Delay(10);
    ReadData_1 = ADS1118_Send((uint8_t)(Config >> 8));
    ReadData_2 = ADS1118_Send((uint8_t)Config);
    ReadData_3 = ADS1118_Send((uint8_t)(Config >> 8));
    ReadData_4 = ADS1118_Send((uint8_t)Config);
	ReadData = (((uint32_t)ReadData_1 << 8) | (uint32_t)ReadData_2);
    ADS1118_Delay(1000);
    return ReadData;
}
