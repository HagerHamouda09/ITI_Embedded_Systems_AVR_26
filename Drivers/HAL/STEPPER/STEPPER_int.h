/*
 * STEPPER_int.h
 *
 *  Created on: Jul 27, 2026
 *      Author: Hager Adel
 */

#ifndef HAL_STEPPER_STEPPER_INT_H_
#define HAL_STEPPER_STEPPER_INT_H_

#define STEPPER_PORT DIO_PORTA

#define STEPPER_BLUE DIO_PIN0
#define STEPPER_PINK DIO_PIN1
#define STEPPER_ORANGE DIO_PIN2
#define STEPPER_YELLOW DIO_PIN3


void HSTEPPER_vInit();

void HSTEPPER_vRotateCW(f64 A_f64StepDelay);
void HSTEPPER_vRotateCCW(f64 A_f64StepDelay);

void HSTEPPER_vStop();


#endif /* HAL_STEPPER_STEPPER_INT_H_ */
