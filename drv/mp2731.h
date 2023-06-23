#ifndef MP2731_H_
#define MP2731_H_

#include <stdint.h>

#define MP2731_ADDR     0x4B

#define REG00           0x00
#define REG01           0x01
#define REG02           0x02
#define REG03           0x03
#define REG04           0x04
#define REG05           0x05
#define REG06           0x06
#define REG07           0x07
#define REG08           0x08
#define REG09           0x09
#define REG0A           0x0A
#define REG0B           0x0B
#define REG0C           0x0C
#define REG0D           0x0D
#define REG0E           0x0E
#define REG0F           0x0F
#define REG10           0x10
#define REG11           0x11
#define REG12           0x12
#define REG13           0x13
#define REG14           0x14
#define REG15           0x15
#define REG16           0x16
#define REG17           0x17

typedef struct
{
    uint8_t vin;
    uint8_t charge;
    uint8_t ntc;
    uint8_t therm;
    uint8_t vsys;
} MP2731Status;

typedef struct
{
    uint8_t watchdog;
    uint8_t otg;
    uint8_t input;
    uint8_t thermal;
    uint8_t battery;
    uint8_t ntc;
} MP2731Fault;

typedef struct
{
    uint16_t vBattery;      //mV
    uint16_t vSystem;       //mV
    uint16_t vNTC;          //mV
    uint16_t vInput;        //mV
    uint16_t iCharge;       //mA
    uint16_t iInput;        //mA
} MP2731ADC;

typedef struct
{
    MP2731Status stat;
    MP2731Fault fault;
    MP2731ADC adc;
} MP2731TypeDef;

void mp2731_detect(void);
void mp2731_readRegisters(void);
uint16_t mp2731_adcBatteryVoltage(void);
uint16_t mp2731_adcSystemVoltage(void);
uint16_t mp2731_adcNTCVoltage(void);
uint16_t mp2731_adcInputVoltage(void);
uint16_t mp2731_adcChargeCurrent(void);
uint16_t mp2731_adcInputCurrent(void);
void mp2731_readStatus(MP2731TypeDef *mp);
void mp2731_readFault(MP2731TypeDef *mp);
void mp2731_readADC(MP2731TypeDef *mp);

#endif /* MP2731_H_ */
