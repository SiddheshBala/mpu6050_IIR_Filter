#include <mpu6050.h>
#include <stdio.h>

// extern I2C_HandleTypeDef hi2c1;
HAL_StatusTypeDef checkMPU6050Connection(I2C_HandleTypeDef * hi2c1) {
    HAL_StatusTypeDef ret = HAL_I2C_IsDeviceReady(hi2c1, devAddress, 6, 1000);
    return ret;
}

void mpu6050_init(I2C_HandleTypeDef * hi2c1) {
    HAL_StatusTypeDef mpuReady = checkMPU6050Connection(hi2c1);
    uint8_t check;
    uint8_t Data;

    // check device ID WHO_AM_I
    if (mpuReady == HAL_OK)
    HAL_I2C_Mem_Read(hi2c1, devAddress, WHO_AM_I_REG, 1, &check, 1, 100);
    
    if (check == 0x68) {
        /* Switch on the MPU */
        uint8_t tempData = 0b00000000;
        HAL_StatusTypeDef switchOnFlag = HAL_I2C_Mem_Write(hi2c1, devAddress, REG_PWR_MGMT_1, 1, &tempData, 1, 100);
        /* Data Rate */
        tempData = 0x07;
        HAL_I2C_Mem_Write(hi2c1, devAddress, tempData, 1, &tempData, 1, 100);
        /* Setup Gyroscope */
        tempData = FS_GYRO_CONFIG_500;
        HAL_StatusTypeDef gyroSetupFlag = HAL_I2C_Mem_Write(hi2c1, devAddress, REG_GYRO_CONFIG, 1, &tempData, 1, 100);
        /* Setup Acceleration */
        tempData = FS_ACC_CONFIG_4G;
        HAL_StatusTypeDef accelSetupFlag = HAL_I2C_Mem_Write(hi2c1, devAddress, REG_ACC_CONFIG, 1, &tempData, 1, 100);
        
    }
}



void mpu6050_readData(I2C_HandleTypeDef * hi2c1, MPU6050_t * mpuVar) {
    uint8_t accData[6];
    HAL_StatusTypeDef isItReading = HAL_I2C_Mem_Read(hi2c1, devAddress, ACCEL_XOUT_H_REG, 1, accData, 6, 100);

    mpuVar->raw_xaccel = (int16_t)((accData[0]<<8) | accData[1]);
    mpuVar->raw_yaccel = (int16_t)((accData[2]<<8) | accData[3]);
    mpuVar->raw_zaccel = (int16_t)((accData[4]<<8) | accData[5]);

    mpuVar->Ax = mpuVar->raw_xaccel * ACC_FS_4G_SCALE;
    mpuVar->Ay = mpuVar->raw_yaccel * ACC_FS_4G_SCALE;
    mpuVar->Az = mpuVar->raw_zaccel * ACC_FS_4G_SCALE;

    uint8_t gyroData[6];
    isItReading = HAL_I2C_Mem_Read(hi2c1, devAddress, GYRO_XOUT_H_REG, 1, gyroData, 6, 100);

    mpuVar->raw_xgyro = (int16_t)((gyroData[0]<<8) | gyroData[1]);
    mpuVar->raw_ygyro = (int16_t)((gyroData[2]<<8) | gyroData[3]);
    mpuVar->raw_zgyro = (int16_t)((gyroData[4]<<8) | gyroData[5]);

    mpuVar->Gx = mpuVar->raw_xgyro / 65.5; 
    mpuVar->Gy = mpuVar->raw_ygyro / 65.5;
    mpuVar->Gz = mpuVar->raw_zgyro / 65.5;
}