#ifndef __SPI2C_H
#define __SPI2C_H

#include <stdint.h>

#define ACK     0
#define NACK    1

typedef struct {
    void (*init)(void);
    void (*scl_out)(uint8_t state);
    void (*sda_out)(uint8_t state);
    uint8_t (*sda_in)(void);
    void (*delay_us)(uint32_t us);
} i2c_t;

typedef struct
{
    void (*init)(void);
    void (*nss_out)(uint8_t state);
    void (*clk_out)(uint8_t state);
    void (*mosi_out)(uint8_t state);
    uint8_t (*miso_in)(void);
}spi_t;


void i2c_init(i2c_t *obj);
void i2c_start(i2c_t *obj);
void i2c_stop(i2c_t *obj);
void i2c_write(i2c_t *obj,uint8_t data);
uint8_t i2c_read(i2c_t *obj,uint8_t ack);
void i2c_ack(i2c_t *obj,uint8_t ack);
uint8_t i2c_wait_ack(i2c_t *obj);

void spi_init(spi_t *obj);
void spi_start(spi_t *obj);
void spi_stop(spi_t *obj);
uint8_t spi_swap(spi_t *obj,uint8_t data);


#endif // __SPI2C_H