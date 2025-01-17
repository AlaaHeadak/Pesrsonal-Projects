#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"


#include "RCC_interface.h"
#include "RCC_private.h"
#include "RCC_configuration.h"

void MRCC_voidInit(void)
{
#if CLK_SOURCE == HSI
	/*
	 * 1- Turn on HSI Clock
	 * 2- Check HSI is Ready
	 * 3- Switch to HSI
	 * 4- Turn off PLL
	 * 5- Turn off HSE
	 */

	// 1- Turn on HSI Clock
	SET_BIT(RCC->CR, CR_HSI_ON_BIT);
	// 2- Check HSI is Ready
	while (GET_BIT(RCC->CR, CR_HSI_RDY_BIT) == 0)
		;
	// 3- Switch to HSI
	CLR_BIT(RCC->CFGR, CFGR_SW_BIT0);
	CLR_BIT(RCC->CFGR, CFGR_SW_BIT1);
	// 4- Turn off PLL
	CLR_BIT(RCC->CR, CR_PLL_ON_BIT);
	// 5- Turn off HSE
	CLR_BIT(RCC->CR, CR_HSE_ON_BIT);

#elif CLK_SOURCE == HSE
	/*
	 * 1- Turn on HSE Clock
	 * 2- Check HSe is Ready
	 * 3- Switch to HSE
	 * 4- Turn off PLL
	 * 5- Turn off HSI
	 */

	// 1- Turn on HSE Clock
	SET_BIT(RCC->CR, CR_HSE_ON_BIT);
	// 2- Check HSI is Ready
	while (GET_BIT(RCC->CR, CR_HSE_RDY_BIT) == 0)
		;
	// 3- Switch to HSE
	SET_BIT(RCC->CFGR, CFGR_SW_BIT0);
	CLR_BIT(RCC->CFGR, CFGR_SW_BIT1);
	// 4- Turn off PLL
	CLR_BIT(RCC->CR, CR_PLL_ON_BIT);
	// 5- Turn off HSI
	CLR_BIT(RCC->CR, CR_HSI_ON_BIT);
#elif CLK_SOURCE == PLL

#if PLL_SOURCE == HSI
	// 1- Turn on HSI Clock
	SET_BIT(RCC->CR, CR_HSI_ON_BIT);
	// 2- Check HSI is Ready
	while (GET_BIT(RCC->CR, CR_HSI_RDY_BIT) == 0)
		;
	// 3- Set PLL Source to HSI
	CLR_BIT(RCC->PLLCFGR, PLLCFGR_PLL_SOURCE_BIT);
	// 4- Set PLLM Values
	RCC->PLLCFGR &= ~PLLM_MASK;
	RCC->PLLCFGR |= PLLM_VALUE;
	// 5- Set PLLN Values
	RCC->PLLCFGR &= ~PLLN_MASK;
	RCC->PLLCFGR |= (PLLN_VALUE << 6);
	// 6- Set PLLP Values
	RCC->PLLCFGR &= ~PLLP_MASK;
	RCC->PLLCFGR |= (PLLP_VALUE << 16);
	// 7- Set AHB Prescaler
	RCC->CFGR &= ~AHB_PRESCALER_MASK;
	RCC->CFGR |= AHB_PRESCALER << 4;

	// 8- Set APB1 Prescaler
	RCC->CFGR &= ~APB1_PRESCALER_MASK;
	RCC->CFGR |= APB1_PRESCALER << 10;

	// 9- Set APB2 Prescaler
	RCC->CFGR &= ~APB2_PRESCALER_MASK;
	RCC->CFGR |= APB2_PRESCALER << 13;

	// 10- Turn on PLL Clock
	SET_BIT(RCC->CR, CR_PLL_ON_BIT);

	// 11- Check HSI is Ready
	while (GET_BIT(RCC->CR, CR_PLL_RDY_BIT) == 0)
		;

	// 12- Switch to PLL
	CLR_BIT(RCC->CFGR, CFGR_SW_BIT0);
	SET_BIT(RCC->CFGR, CFGR_SW_BIT1);
#elif PLL_SOURCE == HSE
	// 1- Turn on HSE Clock
	SET_BIT(RCC->CR, CR_HSE_ON_BIT);
	// 2- Check HSE is Ready
	while (GET_BIT(RCC->CR, CR_HSE_RDY_BIT) == 0)
		;
	// 3- Set PLL Source to HSE
	SET_BIT(RCC->PLLCFGR, PLLCFGR_PLL_SOURCE_BIT);
	// 4- Set PLLM Values
	RCC->PLLCFGR &= ~PLLM_MASK;
	RCC->PLLCFGR |= PLLM_VALUE;
	// 5- Set PLLN Values
	RCC->PLLCFGR &= ~PLLN_MASK;
	RCC->PLLCFGR |= (PLLN_VALUE << 6);
	// 6- Set PLLP Values
	RCC->PLLCFGR &= ~PLLP_MASK;
	RCC->PLLCFGR |= (PLLP_VALUE << 16);
	// 7- Set AHB Prescaler
	RCC->CFGR &= ~AHB_PRESCALER_MASK;
	RCC->CFGR |= AHB_PRESCALER << 4;

	// 8- Set APB1 Prescaler
	RCC->CFGR &= ~APB1_PRESCALER_MASK;
	RCC->CFGR |= APB1_PRESCALER << 10;

	// 9- Set APB2 Prescaler
	RCC->CFGR &= ~APB2_PRESCALER_MASK;
	RCC->CFGR |= APB2_PRESCALER << 13;

	// 10- Turn on PLL Clock
	SET_BIT(RCC->CR, CR_PLL_ON_BIT);

	// 11- Check HSI is Ready
	while (GET_BIT(RCC->CR, CR_PLL_RDY_BIT) == 0)
		;

	// 12- Switch to PLL
	CLR_BIT(RCC->CFGR, CFGR_SW_BIT0);
	SET_BIT(RCC->CFGR, CFGR_SW_BIT1);
#else
#error Wrong Clock Configuration
#endif
#else
#error Wrong Clock Configuration
#endif
}

void MRCC_voidPeripheralEnable(u8 copy_u8Bus, u8 copy_u8Peripheral)
{
	if (copy_u8Bus > APB2 || copy_u8Peripheral > 31)
	{
	}
	else
	{
		switch (copy_u8Bus)
		{
		case AHB1:
			SET_BIT(RCC->AHB1ENR, copy_u8Peripheral);
			break;
		case AHB2:
			SET_BIT(RCC->AHB2ENR, copy_u8Peripheral);
			break;
		case APB1:
			SET_BIT(RCC->APB1ENR, copy_u8Peripheral);
			break;
		case APB2:
			SET_BIT(RCC->APB2ENR, copy_u8Peripheral);
			break;
		}
	}
}

void MRCC_voidPeripheralDisable(u8 copy_u8Bus, u8 copy_u8Peripheral)
{
	if (copy_u8Bus > APB2 || copy_u8Peripheral > 31)
	{
	}
	else
	{
		switch (copy_u8Bus)
		{
		case AHB1:
			CLR_BIT(RCC->AHB1ENR, copy_u8Peripheral);
			break;
		case AHB2:
			CLR_BIT(RCC->AHB2ENR, copy_u8Peripheral);
			break;
		case APB1:
			CLR_BIT(RCC->APB1ENR, copy_u8Peripheral);
			break;
		case APB2:
			CLR_BIT(RCC->APB2ENR, copy_u8Peripheral);
			break;
		}
	}
}

/* Set input as a system clock */
void MRCC_voidSetClkSource(u8 copy_u8ClkSource)
{
	switch (copy_u8ClkSource)
	{
	case HSI:
		CLR_BIT(RCC->CFGR, CFGR_SW_BIT0);
		CLR_BIT(RCC->CFGR, CFGR_SW_BIT1);
		break;
	case HSE:
		SET_BIT(RCC->CFGR, CFGR_SW_BIT0);
		CLR_BIT(RCC->CFGR, CFGR_SW_BIT1);
		break;
	case PLL:
		CLR_BIT(RCC->CFGR, CFGR_SW_BIT0);
		SET_BIT(RCC->CFGR, CFGR_SW_BIT1);
		break;
	default:
		break;
	}
}
#define ON 1
#define OFF 0
/* Turn on and off clock source */
void MRCC_voidSetClkStatus(u8 copy_u8ClkSource, u8 copy_u8Status)
{
	switch (copy_u8ClkSource)
	{
	case HSI:
		switch (copy_u8Status)
		{
		case ON:
			SET_BIT(RCC->CR, CR_HSI_ON_BIT);
			break;
		case OFF:
			CLR_BIT(RCC->CR, CR_HSI_ON_BIT);
			break;
		}
		break;
	case HSE:
		switch (copy_u8Status)
		{
		case ON:
			SET_BIT(RCC->CR, CR_HSE_ON_BIT);
			break;
		case OFF:
			CLR_BIT(RCC->CR, CR_HSE_ON_BIT);
			break;
		}
		break;
	case PLL:
		switch (copy_u8Status)
		{
		case ON:
			SET_BIT(RCC->CR, CR_PLL_ON_BIT);
			break;
		case OFF:
			CLR_BIT(RCC->CR, CR_PLL_ON_BIT);
			break;
		}
		break;
	default:
		break;
	}
}
/* Set AHB1 and APB1 and APB2 Prescalers */
void MRCC_voidSetBusesPrescaler(u8 copy_u8AHB, u8 copy_u8APB1, u8 copy_u8APB2)
{
	// 1- Set AHB Prescaler
	RCC->CFGR &= ~AHB_PRESCALER_MASK;
	RCC->CFGR |= copy_u8AHB << 4;

	// 2- Set APB1 Prescaler
	RCC->CFGR &= ~APB1_PRESCALER_MASK;
	RCC->CFGR |= copy_u8APB1 << 10;

	// 3- Set APB2 Prescaler
	RCC->CFGR &= ~APB2_PRESCALER_MASK;
	RCC->CFGR |= copy_u8APB2 << 13;
}
/* Set PLL Factors */
void MRCC_voidSetPLLFactors(u8 copy_u8PLLM, u8 copy_u8PLLN, u8 copy_u8PLLP, u8 copy_u8PLLQ)
{
	// 1- Set PLLM Values
	RCC->PLLCFGR &= ~PLLM_MASK;
	RCC->PLLCFGR |= copy_u8PLLM;
	// 2- Set PLLN Values
	RCC->PLLCFGR &= ~PLLN_MASK;
	RCC->PLLCFGR |= (copy_u8PLLN << 6);
	// 3- Set PLLP Values
	RCC->PLLCFGR &= ~PLLP_MASK;
	RCC->PLLCFGR |= (copy_u8PLLP << 16);
	// 4- Set PLLQ Values
	RCC->PLLCFGR &= ~PLLQ_MASK;
	RCC->PLLCFGR |= (copy_u8PLLQ << 24);
}

u8 MRCC_u8CheckClockReady(u8 copy_u8ClkSource)
{
	u8 local_u8Flag = NotRdy;
	u16 local_u16Counter = 0;
	switch (copy_u8ClkSource)
	{
	case HSI:
		while (local_u8Flag == NotRdy && local_u16Counter < 50000)
		{
			local_u16Counter++;
			local_u8Flag = GET_BIT(RCC->CR, CR_HSI_RDY_BIT);
		}
		break;
	case HSE:
		while (local_u8Flag == NotRdy && local_u16Counter < 50000)
		{
			local_u16Counter++;
			local_u8Flag = GET_BIT(RCC->CR, CR_HSE_RDY_BIT);
		}
		break;
	case PLL:
		while (local_u8Flag == NotRdy && local_u16Counter < 50000)
		{
			local_u16Counter++;
			local_u8Flag = GET_BIT(RCC->CR, CR_PLL_RDY_BIT);
		}
		break;
	default:
		local_u8Flag = OutOfRange;
		break;
	}
	return local_u8Flag;
}
