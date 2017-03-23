#include <stm32f10x.h>


void delay(uint32_t time){
	while(time!=0){
		time--;
	}
}

void EXTI0_IRQHandler(){
	if(EXTI->PR & EXTI_PR_PR0){
		GPIOA->BSRR |= GPIO_BSRR_BS1;
		GPIOC->BSRR |= GPIO_BSRR_BS8;
		delay(1000000);
		GPIOA->BRR |= GPIO_BRR_BR1;
		GPIOC->BRR |= GPIO_BRR_BR8;
		delay(1000000);
	}
	EXTI->PR |= EXTI_PR_PR0;
}




int main(){
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	GPIOC->CRH &=~ GPIO_CRH_CNF8_0 | GPIO_CRH_CNF8_1;
	GPIOC->CRH |= GPIO_CRH_MODE8_0 | GPIO_CRH_MODE8_1;
	GPIOA->CRL &=~ (GPIO_CRL_CNF0 | GPIO_CRL_MODE0);
	GPIOA->CRL = 0x38;
	//GPIOA->CRL &=~ GPIO_CRL_MODE0 | GPIO_CRL_CNF0_0;
	//GPIOA->CRL |= GPIO_CRL_CNF0_1;
	GPIOA->BSRR &=~ GPIO_BSRR_BS1;
	AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI0_PA;
	EXTI->FTSR |= EXTI_FTSR_TR0;
	EXTI->IMR |= EXTI_IMR_MR0;
	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_SetPriority(EXTI0_IRQn, 0);
	while(1==1){/*
		GPIOA->BSRR |= GPIO_BSRR_BS1;
		GPIOC->BSRR |= GPIO_BSRR_BS8;
		delay(2000000);
		GPIOA->BRR |= GPIO_BRR_BR1;
		GPIOC->BRR |= GPIO_BRR_BR8;
		delay(2000000);*/
	}
}