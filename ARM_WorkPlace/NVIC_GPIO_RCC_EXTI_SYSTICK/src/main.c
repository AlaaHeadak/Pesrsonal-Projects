#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

#include "ARM_MCAL/RCC/RCC_interface.h"
#include "ARM_MCAL/RCC/RCC_private.h"
#include "ARM_MCAL/RCC/RCC_configuration.h"

#include "ARM_MCAL/GPIO/GPIO_interface.h"
#include "ARM_MCAL/GPIO/GPIO_private.h"
#include "ARM_MCAL/GPIO/GPIO_configurations.h"

#include "ARM_MCAL/NVIC/NVIC_interface.h"

#include "ARM_MCAL/EXTI/EXTI_interface.h"
#include "ARM_MCAL/EXTI/EXTI_private.h"
#include "ARM_MCAL/EXTI/EXTI_configuration.h"

int main(void)
{

	/* controlling LED using DIP switch Turn(ON/OFF)*/
	MRCC_voidInit();
	MRCC_voidPeripheralEnable(AHB1,GPIOAEN);
	MRCC_voidPeripheralEnable(APB2,SYSCFGEN);

	MGPIO_voidSetPinDirection(GPIOA_PORT,PIN1,OUTPUT_PUSH_PULL,MEDIUM_SPEED);
	MGPIO_voidSetPinValue(GPIOA_PORT,PIN1,HIGH);

	MGPIO_voidSetPinDirection(GPIOA_PORT,PIN0,INPUT_PULL_UP,MEDIUM_SPEED);
	MGPIO_voidSetPinValue(GPIOA_PORT,PIN0,HIGH);


	MNVIC_VoidEnablePeripheral(ETI0);

	MEXTI_voidConfig(EXTI0,GPIOA_PORT,FALLING_EDGE);

	while(1)
	{

	}

}
