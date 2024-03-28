#ifndef __MPU6050_H
#define __MPU6050_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes */
#include "stm32f4xx_hal.h"
#include <main.h>
#include <IIRFirstOrderFilter.h>
/* Definitions */
#define devAddress 0xD0

#define FS_GYRO_CONFIG_500  8
#define REG_GYRO_CONFIG     27

#define FS_ACC_CONFIG_2G    0
#define FS_ACC_CONFIG_4G    8
#define FS_ACC_CONFIG_8G    16
#define FS_ACC_CONFIG_16G   24
#define REG_ACC_CONFIG      28

#define WHO_AM_I_REG        117
#define REG_PWR_MGMT_1      107

#define ACCEL_XOUT_H_REG   0x3B
#define GYRO_XOUT_H_REG      67

#define ACC_FS_4G_SCALE 9.81/8192

typedef struct
{
    int16_t raw_xaccel;
    int16_t raw_yaccel;
    int16_t raw_zaccel;
    double Ax;
    double Ay;
    double Az;

    double Ax_iir;
    double Ay_iir;
    double Az_iir;

    int16_t raw_xgyro;
    int16_t raw_ygyro;
    int16_t raw_zgyro;
    double Gx;
    double Gy;
    double Gz;
} MPU6050_t;

HAL_StatusTypeDef checkMPU6050Connection(I2C_HandleTypeDef * hi2c1);
void mpu6050_init(I2C_HandleTypeDef * hi2c1, IIRFilter * iir_x, IIRFilter * iir_y, IIRFilter * iir_z);
void mpu6050_readData(I2C_HandleTypeDef * hi2c1, MPU6050_t * mpuVar, IIRFilter * iir_x, IIRFilter * iir_y, IIRFilter * iir_z);

#ifdef __cplusplus
}
#endif

#endif /* __MPU6050 */