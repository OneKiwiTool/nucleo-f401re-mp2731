#include <stdio.h>
#include "mp2731.h"
#include "hal_i2c.h"
#include "main.h"

void mp2731_detect(void)
{
    i2c_detect();
}

void mp2731_readRegisters(void)
{
    uint8_t data = 0;
    for (uint8_t i = 0; i < 0x18; i++)
    {
        i2c_read_register(MP2731_ADDR, i, &data);
        printf("reg 0x%02x: 0x%02x\n", i, data);
    }
}

// mV
uint16_t mp2731_adcBatteryVoltage(void)
{
    uint8_t adc = 0;
    uint16_t data = 0;
    i2c_read_register(MP2731_ADDR, REG0E, &adc);
    data = (uint16_t)(20*data);
    return data;
}

// mV
uint16_t mp2731_adcSystemVoltage(void)
{
    uint8_t adc = 0;
    uint16_t data = 0;
    i2c_read_register(MP2731_ADDR, REG0F, &adc);
    data = (uint16_t)(20*data);
    return data;
}

// %
uint16_t mp2731_adcNTCVoltage(void)
{
    uint8_t adc = 0;
    uint16_t data = 0;
    i2c_read_register(MP2731_ADDR, REG10, &adc);
    data = (uint16_t)(392*data/10);//
    return data;
}

// mV
uint16_t mp2731_adcInputVoltage(void)
{
    uint8_t adc = 0;
    uint16_t data = 0;
    i2c_read_register(MP2731_ADDR, REG11, &adc);
    data = (uint16_t)(60*data);
    return data;
}

// mA
uint16_t mp2731_adcChargeCurrent(void)
{
    uint8_t adc = 0;
    uint16_t data = 0;
    i2c_read_register(MP2731_ADDR, REG12, &adc);
    data = (uint16_t)(175*data/10);
    return data;
}

// mA
uint16_t mp2731_adcInputCurrent(void)
{
    uint8_t adc = 0;
    uint16_t data = 0;
    i2c_read_register(MP2731_ADDR, REG11, &adc);
    data = (uint16_t)(133*data/10);
    return data;
}

void mp2731_readStatus(MP2731TypeDef *mp)
{
    uint8_t data = 0;
    i2c_read_register(MP2731_ADDR, REG0C, &data);
    mp->stat.vin = (data&0xE0)>>5;
    mp->stat.charge = (data&0x18)>>3;
    mp->stat.ntc = (data&0x04)>>2;
    mp->stat.therm = (data&0x02)>>1;
    mp->stat.vsys = data&0x01;
}

void mp2731_readFault(MP2731TypeDef *mp)
{
    uint8_t data = 0;
    i2c_read_register(MP2731_ADDR, REG0D, &data);
    mp->fault.watchdog = (data&0x80)>>7;
    mp->fault.otg = (data&0x40)>>6;
    mp->fault.input = (data&0x20)>>5;
    mp->fault.thermal = (data&0x10)>>4;
    mp->fault.battery = (data&0x08)>>3;
    mp->fault.ntc = data&0x07;
}

void mp2731_readADC(MP2731TypeDef *mp)
{
    mp->adc.vBattery = mp2731_adcBatteryVoltage();
    mp->adc.vSystem = mp2731_adcSystemVoltage();
    mp->adc.vNTC = mp2731_adcNTCVoltage();
    mp->adc.vInput = mp2731_adcInputVoltage();
    mp->adc.iCharge = mp2731_adcChargeCurrent();
    mp->adc.iInput = mp2731_adcInputCurrent();
}

 void mp2731_init(void)
{
    //reg0 = (reg0 &(~REG00_A))|REG00_V; //HIZ is disable  IIN_LIM=MAX  and IIN_LIM is Enable, Iin_lim max value.
    //reg2 = (reg2 &(~REG02_A))|REG02_V; //Auto Input Current Optimize is diabale
    //reg3 = (reg3 &(~REG03_A))|REG03_V; //continuous conversion is enable
    //reg8 = (reg8 &(~REG08_A))|REG08_V; //Termination is Enable  //WTD and safety time is diabale
    //regB = (regB &(~REG0B_A))|REG0B_V; //USB detection is disable
    //IIC_write(REG00,reg0);
    //IIC_write(REG02,reg2);
    //IIC_write(REG03,reg3);
    //IIC_write(REG08,reg8);
    //IIC_write(REG0B,regB);
    //pre_POW=0;
    //f_int=1;

    // EN_HIZ is disable, EN_LIM is Enable, IIN_LIM=3.25A (max value)
    i2c_write_register(MP2731_ADDR, REG00, 0x7F);

    // VIN_MIN = 4.3V
    i2c_write_register(MP2731_ADDR, REG01, 0x06);

    // Default
    i2c_write_register(MP2731_ADDR, REG02, 0xDC);

    // Default
    i2c_write_register(MP2731_ADDR, REG03, 0x10);

    // VSYS_MIN = 3.75V
    i2c_write_register(MP2731_ADDR, REG04, 0x5F);

    // ICC = 4520mA
    i2c_write_register(MP2731_ADDR, REG05, 0xFF);

    // Default
    i2c_write_register(MP2731_ADDR, REG06, 0x22);

    // VBATT_REG = 4.2V
    i2c_write_register(MP2731_ADDR, REG07, 0xA0);

    // Default
    i2c_write_register(MP2731_ADDR, REG08, 0x95);

    // Default
    i2c_write_register(MP2731_ADDR, REG09, 0x00);

    // Default
    i2c_write_register(MP2731_ADDR, REG0A, 0x58);

    // USB detection is disable
    i2c_write_register(MP2731_ADDR, REG0B, 0xC0);
}
