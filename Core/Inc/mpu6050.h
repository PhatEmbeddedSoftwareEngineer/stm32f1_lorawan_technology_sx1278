/*
 * mpu6050.h
 *
 *  Created on: Feb 12, 2024
 *      Author: phat
 */
#include "main.h"
#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_
/*
 *
 * tat ca nhung dia chi nam , nam trong trang 6 datasheet*/
#define   SMPLRT_DIV      0x19   //0x07(125Hz) trang 6 datasheet
#define   CONFIG         0x1A   //0x06(5Hz) trang 6 datasheet
#define   GYRO_CONFIG      0x1B // trang 6 datasheet
#define   ACCEL_CONFIG   0x1C
#define   ACCEL_XOUT_H   0x3B
#define   ACCEL_XOUT_L   0x3C
#define   ACCEL_YOUT_H   0x3D
#define   ACCEL_YOUT_L   0x3E
#define   ACCEL_ZOUT_H   0x3F
#define   ACCEL_ZOUT_L   0x40
#define   TEMP_OUT_H      0x41
#define   TEMP_OUT_L      0x42
#define   GYRO_XOUT_H      0x43
#define   GYRO_XOUT_L      0x44
#define   GYRO_YOUT_H      0x45
#define   GYRO_YOUT_L      0x46
#define   GYRO_ZOUT_H      0x47
#define   GYRO_ZOUT_L      0x48
#define   PWR_MGMT_1      0x6B   //
#define   WHO_AM_I         0x75   //

///////////////////////////////////////////
/*
 *
 * phan nay gan nhu khong thay su dung trong chuong trinh */
//#define mpu6050 0xD0  //dia chi cua cam bien mpu6050
#define DATA_REGISTER_EMPTY (1<<UDRE)
#define RX_COMPLETE (1<<RXC)
#define FRAMING_ERROR (1<<FE)
#define PARITY_ERROR (1<<UPE)
#define DATA_OVERRUN (1<<DOR)

///////////////////////////////////////////

int16_t mpu6050_g[3];// tao bien mpu6050_g[3] co 3 phan tu
float mpu6050_gf[3]; // tao bien float mpu6050_gf co 3 phan tu
int16_t mpu6050_a[3]; // tao bien int16_t co 3 phan tu mpu6050_a[3]
float mpu6050_af[3]; // tao bien float mpu6050_af[3] co 3 phan tu
uint8_t mpu6050_tbuff[6]; // tao bien uint8_t mpu6050_tbuff[6] co 6 phan tu
uint8_t mpu6050_rbuff[6]; // tao bien uint8_t mpu6050_rbuff[6] co 6 phan tu

extern I2C_HandleTypeDef hi2c1; // extern bien hi2c1

/*
 * tao chuong trinh mpu6050_read gom hai doi so ky tu khong am char add, va ky tu khong am char n
 * */

void mpu6050_read(unsigned char add, unsigned char n)     //doc n byte bt dau tu dia chi add, luu vao rbuff
{
	/*gan gia tri cua add vao ky tu dau tien cua mang mpu6050_tbuff la gia tri mpu6050_tbuff[0]*/

	*mpu6050_tbuff=add;
//    HAL_I2C_Master_Transmit(&hi2c1,0xD0,mpu6050_tbuff,1,1);
 //   HAL_I2C_Master_Receive(&hi2c1,0xD0,mpu6050_rbuff,n,1);
	/*
	 * ham nay dung de doc ky tu duoc dua vao tu bien add va kich thuoc la n
	 * */
		HAL_I2C_Mem_Read(&hi2c1, 0xD0, add,I2C_MEMADD_SIZE_8BIT, mpu6050_rbuff, n, 1000);
}
void mpu6050_getgyro()					 //doc du lieu gyro 16bit, ghi vao rbuff
{
	// lay du lieu gia toc goc
	/*
	 * 0x43 la bit cua gyro_xout_h trang 7
	 * */
    mpu6050_read(0x43,6);
    /*
     * gia tri dau tien
     * */
    *mpu6050_g=((*mpu6050_rbuff)<<8)+*(mpu6050_rbuff+1);
    *(mpu6050_g+1)=(*(mpu6050_rbuff+2)<<8)+*(mpu6050_rbuff+3);
    *(mpu6050_g+2)=(*(mpu6050_rbuff+4)<<8)+*(mpu6050_rbuff+5);
}
void mpu6050_getgyrodata()				//doc du lieu gyro, don vi: rad/giay, ghi vao mang mpu6050_gf
	{	//3.2768
		mpu6050_getgyro();
		*mpu6050_gf=*mpu6050_g/939.650784f;
		*(mpu6050_gf+1)=*(mpu6050_g+1)/939.650784f;
		*(mpu6050_gf+2)=*(mpu6050_g+2)/939.650784f;

	}
void mpu6050_getaccel()					//doc du lieu accel 16bit, ghi vao mang mpu6050_a
{
	/*
	 * 0x3b la gia tri accel_xout_h
	 * */
    mpu6050_read(0x3b,6);
    *mpu6050_a=((*mpu6050_rbuff)<<8)+*(mpu6050_rbuff+1)-260;
    *(mpu6050_a+1)=(*(mpu6050_rbuff+2)<<8)+*(mpu6050_rbuff+3);
    *(mpu6050_a+2)=(*(mpu6050_rbuff+4)<<8)+*(mpu6050_rbuff+5);
}
void mpu6050_getacceldata()				//doc du lieu accel, don vi:g, ghi vao mang mpu6050_af
	{//409.60
		mpu6050_getaccel();
		*mpu6050_af=*mpu6050_a/8192.0f;
		*(mpu6050_af+1)=*(mpu6050_a+1)/8192.0f;
		*(mpu6050_af+2)=*(mpu6050_a+2)/8192.0f;
	}
void mpu6050_write(unsigned char add,unsigned char data)	//ham ghi 1 byte vao dia chi add
{
	*mpu6050_tbuff=add;
	*(mpu6050_tbuff+1)=data;
	HAL_I2C_Master_Transmit(&hi2c1,0xD0,mpu6050_tbuff,2,1);
//	HAL_I2C_Mem_Write(&hi2c1, 0x68, address, I2C_MEMADD_SIZE_8BIT, &data, 1, 1);
}
int mpu6050_getdata(unsigned char add)			//doc 2 byte tu dia chi add
{
   mpu6050_read(add, 2);

   return ((*mpu6050_rbuff)<<8)+*(mpu6050_rbuff+1);
}
void mpu6050_init(void)
{
   mpu6050_write(PWR_MGMT_1, 0x00);  // internal 20MHz, disabled SLEEP mode, disable CYCLE mode
   mpu6050_write(SMPLRT_DIV, 0x03);	 //sample rate: 4MHZ
   mpu6050_write(CONFIG, 0x06);		 //DLPF enable gia toc ke bandwidth 5hz, Delay 19ms,con quay hoi chuyen bandwidth 5hz - delay 18.6ms - Fs=1khz
   mpu6050_write(GYRO_CONFIG, 0x10);  //full scale range mode 2 +-1000do/s - 32.8 LSB/do/s
   mpu6050_write(ACCEL_CONFIG, 0x10); //full scale range mode 2 +-8g 4096 LSB/g
}


#endif /* INC_MPU6050_H_ */
