#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"


#include "../RCC/RCC_Interface.h"
#include "../RCC/RCC_private.h"
#include "../RCC/RCC_configuration.h"

#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_configuration.h"

#include "../GPIO/GPIO_interface.h"
#include "../GPIO/GPIO_private.h"
#include "../GPIO/GPIO_configurations.h"

void (*EXTI0_CallBack)(void);

/******************************************************************************************/
/*Function: MEXTI_voidConfig	                         						          */
/*I/P Parameters: Port - Line Number - Sense mode         			  			          */
/*Returns:it returns no thing	                            				  			  */
/*Desc:This Function Configures the EXTI 							          			  */
/******************************************************************************************/
/*
 * Options for copy_u8EXTILine:- EXTI0 ... EXTI15
 * Options for copy_u8PORT :- GPIOA_PORT - GPIOB_PORT - GPIOC_PORT
 * Options for copy_u8SenseMode:- FALLING_EDGE - RISING_EDGE - ON_CHANGE_EDGE
/******************************************************************************************/
void MEXTI_voidConfig(u8 copy_u8EXTILine, u8 copy_u8PORT, u8 copy_u8SenseMode)
{
    switch (copy_u8PORT)
    {
    case GPIOA_PORT:
        switch (copy_u8EXTILine)
        {
        case EXTI0:
        case EXTI1:
        case EXTI2:
        case EXTI3:
            SYSCFG->EXTICR1 |= (0 << (copy_u8EXTILine * 4));
            break;
        case EXTI4:
        case EXTI5:
        case EXTI6:
        case EXTI7:
            SYSCFG->EXTICR2 |= (0 << ((copy_u8EXTILine - 4) * 4));
            break;
        case EXTI8:
        case EXTI9:
        case EXTI10:
        case EXTI11:
            SYSCFG->EXTICR3 |= (0 << ((copy_u8EXTILine - 8) * 4));
            break;
        case EXTI12:
        case EXTI13:
        case EXTI14:
        case EXTI15:
            SYSCFG->EXTICR4 |= (0 << ((copy_u8EXTILine - 12) * 4));
            break;
        }
        break;
    case GPIOB_PORT:
        switch (copy_u8EXTILine)
        {
        case EXTI0:
        case EXTI1:
        case EXTI2:
        case EXTI3:
            SYSCFG->EXTICR1 |= (1 << (copy_u8EXTILine * 4));
            break;
        case EXTI4:
        case EXTI5:
        case EXTI6:
        case EXTI7:
            SYSCFG->EXTICR2 |= (1 << ((copy_u8EXTILine - 4) * 4));
            break;
        case EXTI8:
        case EXTI9:
        case EXTI10:
        case EXTI11:
            SYSCFG->EXTICR3 |= (1 << ((copy_u8EXTILine - 8) * 4));
            break;
        case EXTI12:
        case EXTI13:
        case EXTI14:
        case EXTI15:
            SYSCFG->EXTICR4 |= (1 << ((copy_u8EXTILine - 12) * 4));
            break;
        }
        break;
    default:
        break;
    }

    switch (copy_u8SenseMode)
    {
    case FALLING_EDGE:
        SET_BIT(EXTI->FTSR, copy_u8EXTILine);
        CLR_BIT(EXTI->RTSR, copy_u8EXTILine);
        break;
    case RISING_EDGE:
        CLR_BIT(EXTI->FTSR, copy_u8EXTILine);
        SET_BIT(EXTI->RTSR, copy_u8EXTILine);
        break;
    case ON_CHANGE_EDGE:
        SET_BIT(EXTI->FTSR, copy_u8EXTILine);
        SET_BIT(EXTI->RTSR, copy_u8EXTILine);
        break;
    default:
        break;
    }
    SET_BIT(EXTI->IMR, copy_u8EXTILine); // Enable EXTI Line
}

/******************************************************************************************/
/*Function: MEXTI_voidDisable	                         						          */
/*I/P Parameters: Line Number                           			  			          */
/*Returns:it returns no thing	                            				  			  */
/*Desc:This Function Disables the EXTI 							             			  */
/******************************************************************************************/
/*
 * Options for copy_u8EXTILine:- EXTI0 ... EXTI15
/******************************************************************************************/
void MEXTI_voidDisable(u8 copy_u8EXTILine)
{
    CLR_BIT(EXTI->IMR, copy_u8EXTILine); // Disable EXTI Line
}

void EXTI0_VidSetCallBack(void (*ptr)(void))
{

    EXTI0_CallBack = ptr;
}
void EXTI0_IRQHandler(void)
{

    EXTI0_CallBack();
    SET_BIT(EXTI->PR, 0);
}
