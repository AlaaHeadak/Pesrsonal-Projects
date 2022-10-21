/*
 * NVIC_Program.c
 *
 *  Created on: Oct 21, 2022
 *      Author: LENOVO
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "NVIC_interface.h"
#include "NVIC_Configuration.h"
#include "NVIC_prv.h"




//#include "../include/MCAL/RCC/RCC_interface.h"
//#include "../include/MCAL/RCC/RCC_private.h"
//#include "../include/MCAL/RCC/RCC_configuration.h"




static u32 globalStatic_u32GroupConf;

/******************************************************************************/
/*Function: MNVIC_VoidEnablePeripheral	                         			  */
/*I/P Parameters: Interrupt ID              								  */
/*Returns:it returns no thing	                            				  */
/*Desc:This Function Enables the INT of the peripheral in NVIC		          */
/******************************************************************************/
void MNVIC_VoidEnablePeripheral(u8 Copy_u8INTID)
{
    MNVIC->ISER[Copy_u8INTID / NUMBER_OF_INTERRUPT_PER_REGISTER] = 1 << (Copy_u8INTID % NUMBER_OF_INTERRUPT_PER_REGISTER);
}

/******************************************************************************/
/*Function: MNVIC_VoidDisablePeripheral	                         			  */
/*I/P Parameters: Interrupt ID              								  */
/*Returns:it returns no thing	                            				  */
/*Desc:This Function Disables the INT of the peripheral in NVIC		          */
/******************************************************************************/
void MNVIC_VoidDisablePeripheral(u8 Copy_u8INTID)
{
    MNVIC->ICER[Copy_u8INTID / NUMBER_OF_INTERRUPT_PER_REGISTER] = 1 << (Copy_u8INTID % NUMBER_OF_INTERRUPT_PER_REGISTER);
}

/******************************************************************************/
/*Function: MNVIC_VoidSetPending    	                         			  */
/*I/P Parameters: Interrupt ID              								  */
/*Returns:it returns no thing	                            				  */
/*Desc:This Function Sets pending flag of Peripheral        		          */
/******************************************************************************/
void MNVIC_VoidSetPending(u8 Copy_u8INTID)
{
    MNVIC->ISPR[Copy_u8INTID / NUMBER_OF_INTERRUPT_PER_REGISTER] = 1 << (Copy_u8INTID % NUMBER_OF_INTERRUPT_PER_REGISTER);
}

/******************************************************************************/
/*Function: MNVIC_VoidClearPending    	                         			  */
/*I/P Parameters: Interrupt ID              								  */
/*Returns:it returns no thing	                            				  */
/*Desc:This Function Clears pending flag of Peripheral        		          */
/******************************************************************************/
void MNVIC_VoidClearPending(u8 Copy_u8INTID)
{
    MNVIC->ICPR[Copy_u8INTID / NUMBER_OF_INTERRUPT_PER_REGISTER] = 1 << (Copy_u8INTID % NUMBER_OF_INTERRUPT_PER_REGISTER);
}

/******************************************************************************/
/*Function: MNVIC_u8GetActive       	                         			  */
/*I/P Parameters: Interrupt ID              								  */
/*Returns:it returns no thing	                            				  */
/*Desc:This Function returns state of active flag in NVIC     		          */
/******************************************************************************/
u8 MNVIC_u8GetActive(u8 Copy_u8INTID)
{
    u8 LOC_u8Active = GET_BIT((MNVIC->IAPR[Copy_u8INTID / NUMBER_OF_INTERRUPT_PER_REGISTER]), (Copy_u8INTID % NUMBER_OF_INTERRUPT_PER_REGISTER));
    return LOC_u8Active;
}

/******************************************************************************/
/*Function: MNVIC_voidSetPriorityConfig                         			  */
/*I/P Parameters: Priority option              								  */
/*Returns:it returns no thing	                            				  */
/*Desc:This Function Sets the group and the sub priority configurations       */
/******************************************************************************/
/*
 * Options:- GROUP_4BITS - GROUP_3BITS - GROUP_2BITS - GROUP_1BITS - GROUP_0BITS
/******************************************************************************/
void MNVIC_voidSetPriorityConfig(u8 Copy_u8PriorityOption)
{
	//0x05FA0000 is a password defined by ST to allow writting to this register
	// since this chip offers only 91 interrupt out of 240, ST limited to option to write to the full 8 bits to 4 bits only classified to 4 options(Copy_u8PriorityOption) provided in a table
    globalStatic_u32GroupConf = 0x05FA0000 | (Copy_u8PriorityOption << INTERRUPT_SIZE);
    SCB->AIRCR = globalStatic_u32GroupConf;
}

/******************************************************************************/
/*Function: MNVIC_VoidSetPriority                                			  */
/*I/P Parameters: Interrupt ID              								  */
/*Returns:it returns no thing	                            				  */
/*Desc:This Function Sets the group and the sub priority for required INT     */
/******************************************************************************/
/*
 * Options for Copy_u8GroupPriority:- GROUP_PRIORITY_0 ... GROUP_PRIORITY_15
 * Options for Copy_u8SubPriority  :- SUB_PRIORITY_0   ... SUB_PRIORITY_15
/******************************************************************************/
void MNVIC_VoidSetPriority(s8 Copy_s8INTID, u8 Copy_u8GroupPriority, u8 Copy_u8SubPriority)
{
    u8 local_u8Priority = Copy_u8SubPriority | Copy_u8GroupPriority << ((globalStatic_u32GroupConf - 0x05FA0300) / INTERRUPT_SHIFT_VALUE_BIT);
    // Core Peripheral
    if (Copy_s8INTID < 0)
    {
        if (Copy_s8INTID == MEMORY_MANAGE || Copy_s8INTID == BUS_FAULT || Copy_s8INTID == USAGE_FAULT)
        {
        	Copy_s8INTID += INTERRUPT_RECONFIGURTION_WRITE_SHPR1;
            SCB->SHPR1 = (local_u8Priority) << ((INTERRUPT_SIZE * Copy_s8INTID) + INTERRUPT_RECONFIGURTION_SIZE);
        }
        else if (Copy_s8INTID == SV_CALL)
        {
        	Copy_s8INTID += INTERRUPT_RECONFIGURTION_WRITE_SHPR2;
            SCB->SHPR2 = (local_u8Priority) << ((INTERRUPT_SIZE * Copy_s8INTID) + INTERRUPT_RECONFIGURTION_SIZE);
        }
        else if (Copy_s8INTID == PEND_SV || Copy_s8INTID == SYSTICK)
        {
        	Copy_s8INTID += INTERRUPT_RECONFIGURTION_WRITE_SHPR3;
            SCB->SHPR3 = (local_u8Priority) << ((INTERRUPT_SIZE * Copy_s8INTID) + INTERRUPT_RECONFIGURTION_SIZE);
        }
    }
    // External Peripheral
    else if (Copy_s8INTID >= INTERRUPT_RECONFIGURTION_WRITE_IPR)
    {
        MNVIC->IPR[Copy_s8INTID] = local_u8Priority << INTERRUPT_RECONFIGURTION_SIZE;
    }
}


