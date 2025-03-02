#include "spi2c.h"

void i2c_init(i2c_t *obj)
{
    obj->init();
}

void i2c_start(i2c_t *obj)
{
    obj->sda_out(1);
    obj->scl_out(1);
    obj->delay_us(5);
    obj->sda_out(0);
    obj->delay_us(6);
    obj->scl_out(0);
}


void i2c_stop(i2c_t *obj)
{
    obj->scl_out(0);
    obj->sda_out(0);
    obj->scl_out(1);
    obj->delay_us(6);
    obj->sda_out(1);
    obj->delay_us(6);
}


void i2c_ack(i2c_t *obj,uint8_t ack)
{
    obj->scl_out(0);
    obj->sda_out(ack);
    obj->delay_us(2);
    obj->scl_out(1);
    obj->delay_us(5);
    obj->scl_out(0);
}

uint8_t i2c_wait_ack(i2c_t *obj)
{
    uint8_t tempTime=0;

    obj->sda_out(1);
    obj->delay_us(1);
    obj->scl_out(1);
    obj->delay_us(1);
    while(obj->sda_in())
    {
        tempTime++;
        if(tempTime>250)
        {
            i2c_stop(obj);
            return 1;
        }
    }
    obj->scl_out(0);
    return 0;
}

void i2c_write(i2c_t *obj,uint8_t data)
{
    uint8_t i;
    obj->scl_out(0);
    for(i=0;i<8;i++)
    {
        if((data & (0x80 >> i))>0) 
		{
            obj->sda_out(1);
		}
		else
		{
			obj->sda_out(0);
        }  	 
        obj->delay_us(2);
        obj->scl_out(1);
		obj->delay_us(2);
		obj->scl_out(0);
		obj->delay_us(2);
    }
}


uint8_t i2c_read(i2c_t *obj,uint8_t ack)
{
    uint8_t i,receive=0;
    for(i=0;i<8;i++ )
    {
        obj->scl_out(0); 
        obj->delay_us(2);
        obj->scl_out(1);
        receive<<=1;
        if(obj->sda_in()) receive++;   
        obj->delay_us(1); 
    }
    if(!ack)
    {
        i2c_ack(obj,NACK);
    }
    else
    {
        i2c_ack(obj,ACK); 
    }
    return receive;
}


void spi_init(spi_t *obj)
{
    obj->init();
}


void spi_start(spi_t *obj)
{
    obj->nss_out(0);
}


void spi_stop(spi_t *obj)
{
    obj->nss_out(1);
}


uint8_t spi_swap(spi_t *obj,uint8_t data)
{
    uint8_t i,temp=0;
    for(i = 0;i < 8;i++)
    {
        if(data & (0x80 >> i))
        {
            obj->mosi_out(1);
        }
        else
        {
            obj->mosi_out(0);
        }
        obj->clk_out(1);
        if(obj->miso_in())
        {
            temp |= (0x80 >> i);
        }
        obj->clk_out(0);
    }
    return temp;
}

