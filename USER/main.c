#include "stm32f10x.h"
#include "systick.h"
#include "sys.h"
#include "usart.h"
#include "spi2c.h"

extern i2c_t i2c1;
extern spi_t spi1;

int main(void)
{
	SysTick_Init();
	uart_init(115200);
	//i2c_init(&i2c1);
	spi_init(&spi1);
	while(1)
	{
		// i2c_start(&i2c1);
		// i2c_write(&i2c1,0x0F);
		// i2c_ack(&i2c1,NACK);
		// i2c_write(&i2c1,0xF0);
		// i2c_ack(&i2c1,ACK);
		// i2c_stop(&i2c1);
		// delay_ms(100);
		spi_start(&spi1);
		spi_swap(&spi1,0x76);
		spi_swap(&spi1,0xA3);
		spi_stop(&spi1);
		delay_ms(100);
	}
	return 0;
}

