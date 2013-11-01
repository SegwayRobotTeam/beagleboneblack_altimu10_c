#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <inttypes.h>
#include "altimu.h"

int altimu;
char tx[10] = {0};
char rx[10] = {0};

int16_t twosComplementToDec16bit(uint16_t twosComp)
{
    if (twosComp & 0x8000) return(((twosComp ^ 0xffff) + 1) * -1);
    else return twosComp;
}

int32_t twosComplementToDec32bit(uint32_t twosComp)
{
    if (twosComp & 0x80000000) return(((twosComp ^ 0xffffffff) + 1) * -1);
    else return twosComp;
}

int I2C_init()
{
    if ((altimu = open("/dev/i2c-1", O_RDWR)) < 0) return 0;

    return 1;
}

void LSM303DLHC_A_init(void)
{
    ioctl(altimu, I2C_SLAVE, LSM303DLHC_A_adress);
    tx[0] = LSM303DLHC_A_CTRL_REG1;
    tx[1] = 0b00100111; // Normal power mode, all axes enabled
    write(altimu, tx, 2);
    tx[0] = LSM303DLHC_A_CTRL_REG4;
    tx[1] = 0b00001000; // Enable 12-bit resolution
    write(altimu, tx, 2);
}

void LSM303DLHC_A_read(void)
{
    ioctl(altimu, I2C_SLAVE, LSM303DLHC_A_adress);
    tx[0] = LSM303DLHC_A_OUT_X_L | (1 << 7);
    write(altimu, tx, 1);
    read(altimu, rx, 6);
    acc.x = twosComplementToDec16bit((rx[1] << 8 | rx[0])) >> 4;
    acc.y = twosComplementToDec16bit((rx[3] << 8 | rx[2])) >> 4;
    acc.z = twosComplementToDec16bit((rx[5] << 8 | rx[4])) >> 4;
}

void LSM303DLHC_M_init(void)
{
    ioctl(altimu, I2C_SLAVE, LSM303DLHC_M_adress);
    tx[0] = LSM303DLHC_M_MR_REG;
    tx[1] = 0x00; // Continuous conversion mode
    write(altimu, tx, 2);
}

void LSM303DLHC_M_read(void)
{
    ioctl(altimu, I2C_SLAVE, LSM303DLHC_M_adress);
    tx[0] = LSM303DLHC_M_OUT_X_H;
    write(altimu, tx, 1);
    read(altimu, rx, 6);
    mag.x = twosComplementToDec16bit(rx[0] << 12 | rx[1] << 4) >> 4;
    mag.z = twosComplementToDec16bit(rx[2] << 12 | rx[3] << 4) >> 4;
    mag.y = twosComplementToDec16bit(rx[4] << 12 | rx[5] << 4) >> 4;
}

void L3GD20_init(void)
{
    ioctl(altimu, I2C_SLAVE, L3GD20_adress);
    tx[0] = L3GD20_CTRL_REG1;
    tx[1] = 0b00001111; // Normal power mode, all axes enabled
    write(altimu, tx, 2);
}

void L3GD20_read(void)
{
    ioctl(altimu, I2C_SLAVE, L3GD20_adress);
    tx[0] = L3GD20_OUT_X_L | (1 << 7);
    write(altimu, tx, 1);
    read(altimu, rx, 6);
    gyro.x = twosComplementToDec16bit(rx[1] << 8 | rx[0]);
    gyro.y = twosComplementToDec16bit(rx[3] << 8 | rx[2]);
    gyro.z = twosComplementToDec16bit(rx[5] << 8 | rx[4]);
}

void LPS331AP_init(void)
{
    ioctl(altimu, I2C_SLAVE, LPS331AP_adress);
    tx[0] = LPS331AP_CTRL_REG1;
    tx[1] = 0b11100000; // 12.5 Hz
    write(altimu, tx, 2);
}

float LPS331AP_readTempC(void)
{
    ioctl(altimu, I2C_SLAVE, LPS331AP_adress);
    tx[0] = LPS331AP_TEMP_OUT_L | (1 << 7);
    write(altimu, tx, 1);
    read(altimu, rx, 2);
    return(42.5 + twosComplementToDec16bit(rx[1] << 8 | rx[0]) / 480.0);
}

float LPS331AP_readPerssureMbar(void)
{
    ioctl(altimu, I2C_SLAVE, LPS331AP_adress);
    tx[0] = LPS331AP_PRESS_OUT_XL | (1 << 7);
    write(altimu, tx, 1);
    read(altimu, rx, 3);
    return(twosComplementToDec32bit(rx[2] << 16 | rx[1] << 8 | rx[0]) / 4096.0);
}
