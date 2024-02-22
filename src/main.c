/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
/* STEP 3 - Include the header file of the I2C API */
#include <zephyr/drivers/i2c.h>

/* STEP 4.1 - Include the header file of printk() */
#include <zephyr/sys/printk.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

/* STEP 8 - Define the I2C slave device address and the addresses of relevant registers */
#define STTS751_TEMP_HIGH_REG            0x00
#define STTS751_TEMP_LOW_REG             0x02
#define STTS751_CONFIG_REG               0x03
#define STTS751_CONV_REG                 0x04
#define STTS751_STATUS_REG               0x01

#define PRIORITY 7

#define STACKSIZE 1024

/* STEP 6 - Get the node identifier of the sensor */
#define I2C0_NODE DT_NODELABEL(mysensor)

static const struct i2c_dt_spec dev_i2c = I2C_DT_SPEC_GET(I2C0_NODE);



void temp_data(void);
float tem_sensor_read(void);
void temp_sensor_init(void);
void thread0(void);

float value;


void temp_data(void)
{
		
			
		
		int ret;

/* STEP 7 - Retrieve the API-specific device structure and make sure that the device is ready to use  */
// static const struct i2c_dt_spec dev_i2c = I2C_DT_SPEC_GET(I2C0_NODE);
if (!device_is_ready(dev_i2c.bus)) {
	printk("I2C bus %s is not ready!\n\r",dev_i2c.bus->name);
	return;
}


/* STEP 9 - Setup the sensor by writing the value 0x8C to the Configuration register */
uint8_t config[2] = {STTS751_CONFIG_REG,0x8C};
	ret = i2c_write_dt(&dev_i2c, config, sizeof(config));
	if(ret != 0){
		printk("Failed to write to I2C device address %x at Reg. %x \n", dev_i2c.addr,config[0]);
		return;
	}

while(true)
{

/* STEP 10 - Read the temperature from the sensor */
uint8_t temp_reading[2]= {0};
uint8_t sensor_regs[2] ={STTS751_TEMP_LOW_REG,STTS751_TEMP_HIGH_REG};
ret = i2c_write_read_dt(&dev_i2c,&sensor_regs[0],1,&temp_reading[0],1);
if(ret != 0){
	printk("Failed to write/read I2C device address %x at Reg. %x \r\n", dev_i2c.addr,sensor_regs[0]);
}
ret = i2c_write_read_dt(&dev_i2c,&sensor_regs[1],1,&temp_reading[1],1);
if(ret != 0){
	printk("Failed to write/read I2C device address %x at Reg. %x \r\n", dev_i2c.addr,sensor_regs[1]);
}


/* STEP 11 - Convert the two bytes to a 12-bits */
int temp = ((int)temp_reading[1] * 256 + ((int)temp_reading[0] & 0xF0)) / 16;
if(temp > 2047)
{
	temp -= 4096;
}

// Convert to engineering units 
double cTemp = temp * 0.0625;
double fTemp = cTemp * 1.8 + 32;

value=cTemp;

//Print reading to console  
printk("Temperature in Celsius : %.2f C \n", value);
printk("Temperature in Fahrenheit : %.2f F \n", fTemp);

		k_msleep(SLEEP_TIME_MS);
 }
	}




void temp_sensor_init(void)
{
// #define SLEEP_TIME_MS   1000

/* STEP 8 - Define the I2C slave device address and the addresses of relevant registers */


/* STEP 6 - Get the node identifier of the sensor */

	int ret=0;

uint8_t temp_status_reading=0;
uint8_t status_reg[1]={STTS751_STATUS_REG};

/* STEP 7 - Retrieve the API-specific device structure and make sure that the device is ready to use  */

if (!device_is_ready(dev_i2c.bus)) {
	// printk("I2C bus %s is not ready!\n\r",dev_i2c.bus->name);
	return;
}


/* STEP 9 - Setup the sensor by writing the value 0x8C to the Configuration register */
uint8_t config1[2] = {STTS751_CONFIG_REG,0x8C};
	ret = i2c_write_dt(&dev_i2c, config1, sizeof(config1));
	if(ret != 0){
		// printk("Failed to write to I2C device address %x at Reg. %x \n", dev_i2c.addr,config[0]);
		return;
	}


	uint8_t config2[2] = {STTS751_CONV_REG,0x08};
	ret = i2c_write_dt(&dev_i2c, config2, sizeof(config2));
	if(ret != 0){
		// printk("Failed to write to I2C device address %x at Reg. %x \n", dev_i2c.addr,config[0]);
		return;
	}




}



float tem_sensor_read(void)
{

	float val;
    int ret;

		// while(1)

{
/* STEP 10 - Read the temperature from the sensor */
uint8_t temp_reading[2]= {0};
uint8_t sensor_regs[2] ={STTS751_TEMP_LOW_REG,STTS751_TEMP_HIGH_REG};
ret = i2c_write_read_dt(&dev_i2c,&sensor_regs[0],1,&temp_reading[0],1);
if(ret != 0){
	// printk("Failed to write/read I2C device address %x at Reg. %x \r\n", dev_i2c.addr,sensor_regs[0]);
}
ret = i2c_write_read_dt(&dev_i2c,&sensor_regs[1],1,&temp_reading[1],1);
if(ret != 0){
	// printk("Failed to write/read I2C device address %x at Reg. %x \r\n", dev_i2c.addr,sensor_regs[1]);
}


/* STEP 11 - Convert the two bytes to a 12-bits */
int temp = ((int)temp_reading[1] * 256 + ((int)temp_reading[0] & 0xF0))/16;
if(temp > 2047)
{
	temp -= 4096;
}

// Convert to engineering units 
float cTemp = temp * 0.0625;
float fTemp = cTemp * 1.8 + 32;

//Print reading to console  
// printk("04:Temperature in Celsius : %d C \n", temp);
// printk("Temperature in Fahrenheit : %d F \n", temp_reading[1]);
     k_msleep(SLEEP_TIME_MS);
	 value=cTemp;
	
printk("thread says fix this boy\n");
printk("t: is %f:\n",cTemp);
// k_msleep(SLEEP_TIME_MS);

 return cTemp;



}
}














void thread0(void)
{
	float val;
	temp_sensor_init();
	while (1) {
		    //   val=tem_sensor_read();
		  /* STEP 3 - Call printk() to display a simple string "Hello, I am thread0" */
		  printk("Hello, I am thread0\n");
		 printk("hm temp_sensor: is %f:\n",tem_sensor_read());
		  /* STEP 6 - Make the thread yield */
          //k_yield();
		  /* STEP 10 - Put the thread to sleep */
		  k_msleep(1000);
		  /* Remember to comment out the line from STEP 6 */
	}
}	


// void main(void)
// {


// while(1)

// {

// //    temp_data();


// }





// }

 K_THREAD_DEFINE(send_humidity_thread_id, STACKSIZE, temp_data, NULL,  NULL,
		NULL, PRIORITY, 0, 1000); 







