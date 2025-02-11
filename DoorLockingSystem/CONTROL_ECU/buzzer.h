 /******************************************************************************
 *
 * Module: Buzzer driver
 *
 * File Name: buzzer.h
 *
 * Description: header file for the buzzer driver
 *
 * Author: nada
 *
 *******************************************************************************/

#ifndef BUZZER_H_
#define BUZZER_H_
#include"gpio.h"
#include"std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define BUZZER_PORT_ID          PORTD_ID
#define BUZZER_PIN_ID           PIN4_ID
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Setup the direction for the buzzer pin as output pin through the GPIO driver.
 *Turn off the buzzer through the GPIO.
 */
void Buzzer_init(void);

/*
 * Description :
 * Function to enable the Buzzer through the GPIO.
 */
void Buzzer_on(void);

/*
 * Description :
 * Function to disable the Buzzer through the GPIO.
 */
void Buzzer_off(void);


#endif /* BUZZER_H_ */
