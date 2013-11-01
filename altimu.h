#ifndef ALTIMU_H
#define ALTIMU_H

#define LSM303DLHC_A_adress     0x19
#define LSM303DLHC_A_CTRL_REG1  0x20
#define LSM303DLHC_A_CTRL_REG4  0x23
#define LSM303DLHC_A_OUT_X_L    0x28
#define LSM303DLHC_A_OUT_X_H    0x29
#define LSM303DLHC_A_OUT_Y_L    0x2A
#define LSM303DLHC_A_OUT_Y_H    0x2B
#define LSM303DLHC_A_OUT_Z_L    0x2C
#define LSM303DLHC_A_OUT_Z_H    0x2D

#define LSM303DLHC_M_adress      0x1e
#define LSM303DLHC_M_MR_REG      0x02
#define LSM303DLHC_M_OUT_X_H     0x03
#define LSM303DLHC_M_OUT_X_L     0x04
#define LSM303DLHC_M_OUT_Y_H     0x07 
#define LSM303DLHC_M_OUT_Y_L     0x08
#define LSM303DLHC_M_OUT_Z_H     0x05 
#define LSM303DLHC_M_OUT_Z_L     0x06

#define L3GD20_adress     0x6b
#define L3GD20_CTRL_REG1  0x20
#define L3GD20_OUT_X_L    0x28
#define L3GD20_OUT_X_H    0x29
#define L3GD20_OUT_Y_L    0x2A
#define L3GD20_OUT_Y_H    0x2B
#define L3GD20_OUT_Z_L    0x2C
#define L3GD20_OUT_Z_H    0x2D

#define LPS331AP_adress        0x5d
#define LPS331AP_CTRL_REG1     0x20
#define LPS331AP_TEMP_OUT_L    0x2B
#define LPS331AP_TEMP_OUT_H    0x2C
#define LPS331AP_PRESS_OUT_XL  0x28
#define LPS331AP_PRESS_OUT_L   0x29
#define LPS331AP_PRESS_OUT_H   0x2A

#include <inttypes.h>

struct XYZ
{
    int16_t x;
    int16_t y;
    int16_t z;
} acc, gyro, mag;

int16_t twosComplementToDec16bit(uint16_t);
int32_t twosComplementToDec32bit(uint32_t);
int I2C_init(void);
void LSM303DLHC_A_init(void);
void LSM303DLHC_A_read(void);
void LSM303DLHC_M_init(void);
void LSM303DLHC_M_read(void);
void L3GD20_init(void);
void L3GD20_read(void);
void LPS331AP_init(void);
float LPS331AP_readTempC(void);
float LPS331AP_readPerssureMbar(void);

#endif
