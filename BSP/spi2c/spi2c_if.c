#include "spi2c.h"
#include "systick.h"
#include "sys.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

//////////实例化一个i2c对象////////////////


void init1(void);
void scl_out1(uint8_t state);
void sda_out1(uint8_t state);
uint8_t sda_in1(void);

//i2c
i2c_t i2c1 = {
    .init = init1,
    .scl_out = scl_out1,
    .sda_out = sda_out1,
    .sda_in = sda_in1,
    .delay_us = delay_us
};

//scl
GPIO_InitTypeDef GPIO_InitStructScl = {
    .GPIO_Mode = GPIO_Mode_Out_PP,
    .GPIO_Pin = GPIO_Pin_5,
    .GPIO_Speed = GPIO_Speed_50MHz
};

//sda
GPIO_InitTypeDef GPIO_InitStructSda = {
    .GPIO_Mode = GPIO_Mode_Out_PP,
    .GPIO_Pin = GPIO_Pin_6,
    .GPIO_Speed = GPIO_Speed_50MHz
};


void init1(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    GPIO_Init(GPIOA,&GPIO_InitStructScl);
    GPIO_Init(GPIOA,&GPIO_InitStructSda);
}


void scl_out1(uint8_t state)
{
    PAout(5) = state;
}

void sda_out1(uint8_t state)
{
    if(GPIO_InitStructSda.GPIO_Mode != GPIO_Mode_Out_PP)
    {
        GPIO_InitStructSda.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_Init(GPIOA,&GPIO_InitStructSda);
    }
    PAout(6) = state;
}


uint8_t sda_in1(void)
{
    if(GPIO_InitStructSda.GPIO_Mode != GPIO_Mode_IPU)
    {
        GPIO_InitStructSda.GPIO_Mode = GPIO_Mode_IPU;
        GPIO_Init(GPIOA,&GPIO_InitStructSda);
    }
    return PAin(6); 
}


//////////实例化一个spi对象////////////////

void init2(void);
void nss_out2(uint8_t state);
void clk_out2(uint8_t state);
void mosi_out2(uint8_t state);
uint8_t miso_in2(void);

spi_t spi1 = {
    .init = init2,
    .nss_out = nss_out2,
    .clk_out = clk_out2,
    .mosi_out = mosi_out2,
    .miso_in = miso_in2
};

//nss
GPIO_InitTypeDef GPIO_InitStructNss = {
    .GPIO_Mode = GPIO_Mode_Out_PP,
    .GPIO_Pin = GPIO_Pin_4,
    .GPIO_Speed = GPIO_Speed_50MHz
};

//clk
GPIO_InitTypeDef GPIO_InitStructClk = {
    .GPIO_Mode = GPIO_Mode_Out_PP,
    .GPIO_Pin = GPIO_Pin_5,
    .GPIO_Speed = GPIO_Speed_50MHz
};

//mosi
GPIO_InitTypeDef GPIO_InitStructMosi = {
    .GPIO_Mode = GPIO_Mode_Out_PP,
    .GPIO_Pin = GPIO_Pin_6,
    .GPIO_Speed = GPIO_Speed_50MHz
};

//miso
GPIO_InitTypeDef GPIO_InitStructMiso = {
    .GPIO_Mode = GPIO_Mode_IN_FLOATING,
    .GPIO_Pin = GPIO_Pin_7,
    .GPIO_Speed = GPIO_Speed_50MHz
};

void init2(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    GPIO_Init(GPIOA,&GPIO_InitStructNss);
    GPIO_Init(GPIOA,&GPIO_InitStructClk);
    GPIO_Init(GPIOA,&GPIO_InitStructMosi);
    GPIO_Init(GPIOA,&GPIO_InitStructMiso);
}


void nss_out2(uint8_t state)
{
    PAout(4) = state;
}
void clk_out2(uint8_t state)
{
    PAout(5) = state;
}
void mosi_out2(uint8_t state)
{
    PAout(6) = state;
}
uint8_t miso_in2(void)
{
    return PAin(7);
}