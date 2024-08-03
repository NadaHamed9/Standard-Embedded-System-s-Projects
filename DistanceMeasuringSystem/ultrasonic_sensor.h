 /******************************************************************************
 *
 * Module: Ultrasonic Sensor
 *
 * File Name: ultrasonic_sensor.h
 *
 * Description: header file for the ULTRASONIC driver
 *
 * Author: nada
 *
 *******************************************************************************/
#ifndef ULTRASONIC_SENSOR_H_
#define ULTRASONIC_SENSOR_H_

#include"std_types.h"
#include "gpio.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define trigger_PORT_ID    PORTB_ID
#define trigger_PIN_ID     PIN5_ID


extern uint8 g_edgeCount ;
extern uint16  g_timeHigh ;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*Initialize the ICU driver as required.
 *Setup the ICU call back function.
 *Setup the direction for the trigger pin as output pin through the
 *GPIO driver.*/
void Ultrasonic_init(void);

/*Send the Trigger pulse to the ultrasonic .*/
void Ultrasonic_Trigger(void);

/* Send the trigger pulse by using Ultrasonic_Trigger function.
 *Start the measurements by the ICU from this moment.*/
uint16 Ultrasonic_readDistance(void);

/* This is the call back function called by the ICU driver.
 *This is used to calculate the high time (pulse time) generated by
 *the ultrasonic sensor.*/
void Ultrasonic_edgeProcessing(void);

#endif /* ULTRASONIC_SENSOR_H_ */
