/*
 * GPIO_init.h
 *
 *  Created on: Oct 19, 2022
 *      Author: LENOVO
 */

#ifndef ARM_MCAL_GPIO_GPIO_INTERFACE_H_
#define ARM_MCAL_GPIO_GPIO_INTERFACE_H_

#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7
#define PIN8 8
#define PIN9 9
#define PIN10 10
#define PIN11 11
#define PIN12 12
#define PIN13 13
#define PIN14 14
#define PIN15 15

#define GPIOA_PORT 0
#define GPIOB_PORT 1
#define GPIOC_PORT 2

#define LOW_SPEED 0
#define MEDIUM_SPEED 1
#define HIGH_SPEED 2
#define VERY_HIGH_SPEED 3



#define GPIO_MODE_INPUT                0b00
#define GPIO_MODE_OUTPUT               0b01
#define GPIO_MODE_Alternate_function   0b10
#define GPIO_MODE_Analog               0b11


#define GPIO_NO_PULL_UP_DOWN              0b00
#define GPIO_PULL_UP                      0b01
#define GPIO_PULL_DOWN                    0b10






#define INPUT_FLOATING 1
#define INPUT_PULL_UP 2
#define INPUT_PULL_DOWN 3
#define INPUT_ANALOG 4

#define OUTPUT_PUSH_PULL 5
#define OUTPUT_PUSH_PULL_PULL_UP 6
#define OUTPUT_PUSH_PULL_PULL_DOWN 7

#define OUTPUT_OPEN_DRAIN 8
#define OUTPUT_PUSH_OPEN_DRAIN_UP 9
#define OUTPUT_PUSH_OPEN_DRAIN_DOWN 10

#define AF_PUSH_PULL 11
#define AF_PUSH_PULL_PULL_UP 12
#define AF_PUSH_PULL_PULL_DOWN 13

#define AF_OPEN_DRAIN 14
#define AF_PUSH_OPEN_DRAIN_UP 15
#define AF_PUSH_OPEN_DRAIN_DOWN 16

#define GPIO_OPENDRAIN 1
#define GPIO_PUSHPULL 0

#define HIGH 1
#define LOW 0


void MGPIO_vSetPinMode(u8 A_u8PortId,u8 A_u8PinNo ,u8 A_u8Mode);

void MGPIO_vSetPinOutputType(u8 A_u8PortId,u8 A_u8PinNo ,u8 A_u8OutType);

void MGPIO_vSetPinOutputSpeed(u8 A_u8PortId,u8 A_u8PinNo ,u8 A_u8OutSpeed);

void MGPIO_vSetPinInputPull(u8 A_u8PortId,u8 A_u8PinNo ,u8 A_u8PullType);

u8   MGPIO_u8GetPinValue(u8 A_u8PortId,u8 A_u8PinNo);

void MGPIO_vSetPinVal(u8 A_u8PortId,u8 A_u8PinNo,u8 A_u8PinVal);

void MGPIO_vSetPinVal_fast(u8 A_u8PortId,u8 A_u8PinNo,u8 A_u8PinVal);




#endif /* ARM_MCAL_GPIO_GPIO_INTERFACE_H_ */
