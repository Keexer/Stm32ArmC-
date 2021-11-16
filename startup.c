#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __weak
    #define __weak  __attribute__((weak))
#endif

extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _estack;

extern void __libc_init_array();
extern int main();

void Reset_Handler()
{
    for (uint32_t* bss_ptr = &_sbss; bss_ptr < &_ebss;)
    {
        *bss_ptr++ = 0;
    }

    const uint32_t* init_values_ptr = &_sidata;
    uint32_t* data_ptr = &_sdata;
    if (init_values_ptr != data_ptr)
    {
        for (; data_ptr < &_edata;)
        {
            *data_ptr++ = *init_values_ptr++;
        }
    }

    //SystemInit();
    volatile uint32_t* const CPACR = (volatile uint32_t*)0xE000ED88;
    *CPACR = (3 << 20) | (3 << 22);
    __libc_init_array();
    main();
    
    while (1);
}

void Default_Handler()
{
    while (1);
}

// Weak definitions
__weak void NMI_Handler(void)           { Default_Handler(); }
__weak void HardFault_Handler(void)     { Default_Handler(); }
__weak void MemManage_Handler(void)     { Default_Handler(); }
__weak void BusFault_Handler(void)      { Default_Handler(); }
__weak void UsageFault_Handler(void)    { Default_Handler(); }
__weak void SVC_Handler(void)           { Default_Handler(); }
__weak void DebugMon_Handler(void)      { Default_Handler(); }
__weak void PendSV_Handler(void)        { Default_Handler(); }
__weak void SysTick_Handler(void)       { Default_Handler(); }

/* External Interrupts */
__weak void WWDG_IRQHandler(void)                { Default_Handler(); }   /* Window WatchDog                             */
__weak void PVD_IRQHandler(void)                 { Default_Handler(); }   /* PVD through EXTI Line detection             */
__weak void TAMP_STAMP_IRQHandler(void)          { Default_Handler(); }   /* Tamper and TimeStamps through the EXTI line */
__weak void RTC_WKUP_IRQHandler(void)            { Default_Handler(); }   /* RTC Wakeup through the EXTI line            */
__weak void FLASH_IRQHandler(void)               { Default_Handler(); }   /* FLASH                                       */
__weak void RCC_IRQHandler(void)                 { Default_Handler(); }   /* RCC                                         */
__weak void EXTI0_IRQHandler(void)               { Default_Handler(); }   /* EXTI Line0                                  */
__weak void EXTI1_IRQHandler(void)               { Default_Handler(); }   /* EXTI Line1                                  */
__weak void EXTI2_IRQHandler(void)               { Default_Handler(); }   /* EXTI Line2                                  */
__weak void EXTI3_IRQHandler(void)               { Default_Handler(); }   /* EXTI Line3                                  */
__weak void EXTI4_IRQHandler(void)               { Default_Handler(); }   /* EXTI Line4                                  */
__weak void DMA1_Stream0_IRQHandler(void)        { Default_Handler(); }   /* DMA1 Stream 0                               */
__weak void DMA1_Stream1_IRQHandler(void)        { Default_Handler(); }   /* DMA1 Stream 1                               */
__weak void DMA1_Stream2_IRQHandler(void)        { Default_Handler(); }   /* DMA1 Stream 2                               */
__weak void DMA1_Stream3_IRQHandler(void)        { Default_Handler(); }   /* DMA1 Stream 3                               */
__weak void DMA1_Stream4_IRQHandler(void)        { Default_Handler(); }   /* DMA1 Stream 4                               */
__weak void DMA1_Stream5_IRQHandler(void)        { Default_Handler(); }   /* DMA1 Stream 5                               */
__weak void DMA1_Stream6_IRQHandler(void)        { Default_Handler(); }   /* DMA1 Stream 6                               */
__weak void ADC_IRQHandler(void)                 { Default_Handler(); }   /* ADC1, ADC2 and ADC3s                        */
__weak void CAN1_TX_IRQHandler(void)             { Default_Handler(); }   /* CAN1 TX                                     */
__weak void CAN1_RX1_IRQHandler(void)            { Default_Handler(); }   /* CAN1 RX1                                    */
__weak void CAN1_SCE_IRQHandler(void)            { Default_Handler(); }   /* CAN1 SCE                                    */
__weak void CAN1_RX0_IRQHandler(void)            { Default_Handler(); }   /* CAN1 RX0                                    */
__weak void EXTI9_5_IRQHandler(void)             { Default_Handler(); }   /* External Line[9:5]s                         */
__weak void TIM1_BRK_TIM9_IRQHandler(void)       { Default_Handler(); }   /* TIM1 Break and TIM9                         */
__weak void TIM1_UP_TIM10_IRQHandler(void)       { Default_Handler(); }   /* TIM1 Update and TIM10                       */
__weak void TIM1_TRG_COM_TIM11_IRQHandler(void)  { Default_Handler(); }   /* TIM1 Trigger and Commutation and TIM11      */
__weak void TIM1_CC_IRQHandler(void)             { Default_Handler(); }   /* TIM1 Capture Compare                        */
__weak void TIM2_IRQHandler(void)                { Default_Handler(); }   /* TIM2                                        */
__weak void TIM3_IRQHandler(void)                { Default_Handler(); }   /* TIM3                                        */
__weak void TIM4_IRQHandler(void)                { Default_Handler(); }   /* TIM4                                        */
__weak void I2C1_EV_IRQHandler(void)             { Default_Handler(); }   /* I2C1 Event                                  */
__weak void I2C1_ER_IRQHandler(void)             { Default_Handler(); }   /* I2C1 Error                                  */
__weak void I2C2_EV_IRQHandler(void)             { Default_Handler(); }   /* I2C2 Event                                  */
__weak void I2C2_ER_IRQHandler(void)             { Default_Handler(); }   /* I2C2 Error                                  */
__weak void SPI1_IRQHandler(void)                { Default_Handler(); }   /* SPI1                                        */
__weak void SPI2_IRQHandler(void)                { Default_Handler(); }   /* SPI2                                        */
__weak void USART1_IRQHandler(void)              { Default_Handler(); }   /* USART1                                      */
__weak void USART2_IRQHandler(void)              { Default_Handler(); }   /* USART2                                      */
__weak void USART3_IRQHandler(void)              { Default_Handler(); }   /* USART3                                      */
__weak void EXTI15_10_IRQHandler(void)           { Default_Handler(); }   /* External Line[15:10]s                       */
__weak void RTC_Alarm_IRQHandler(void)           { Default_Handler(); }   /* RTC Alarm (A and B) through EXTI Line       */
__weak void OTG_FS_WKUP_IRQHandler(void)         { Default_Handler(); }   /* USB OTG FS Wakeup through EXTI line         */
__weak void TIM8_BRK_TIM12_IRQHandler(void)      { Default_Handler(); }   /* TIM8 Break and TIM12                        */
__weak void TIM8_UP_TIM13_IRQHandler(void)       { Default_Handler(); }   /* TIM8 Update and TIM13                       */
__weak void TIM8_TRG_COM_TIM14_IRQHandler(void)  { Default_Handler(); }   /* TIM8 Trigger and Commutation and TIM14      */
__weak void TIM8_CC_IRQHandler(void)             { Default_Handler(); }   /* TIM8 Capture Compare                        */
__weak void DMA1_Stream7_IRQHandler(void)        { Default_Handler(); }   /* DMA1 Stream7                                */
__weak void SDIO_IRQHandler(void)                { Default_Handler(); }   /* SDIO                                        */
__weak void TIM5_IRQHandler(void)                { Default_Handler(); }   /* TIM5                                        */
__weak void SPI3_IRQHandler(void)                { Default_Handler(); }   /* SPI3                                        */
__weak void TIM6_IRQHandler(void)                { Default_Handler(); }   /* TIM6                                        */
__weak void TIM7_IRQHandler(void)                { Default_Handler(); }   /* TIM7                                        */
__weak void DMA2_Stream0_IRQHandler(void)        { Default_Handler(); }   /* DMA2 Stream 0                               */
__weak void DMA2_Stream1_IRQHandler(void)        { Default_Handler(); }   /* DMA2 Stream 1                               */
__weak void DMA2_Stream2_IRQHandler(void)        { Default_Handler(); }   /* DMA2 Stream 2                               */
__weak void DMA2_Stream3_IRQHandler(void)        { Default_Handler(); }   /* DMA2 Stream 3                               */
__weak void DMA2_Stream4_IRQHandler(void)        { Default_Handler(); }   /* DMA2 Stream 4                               */
__weak void DFSDM1_FLT0_IRQHandler(void)         { Default_Handler(); }   /* DFSDM1 Filter0                              */
__weak void DFSDM1_FLT1_IRQHandler(void)         { Default_Handler(); }   /* DFSDM1 Filter1                              */
__weak void CAN2_TX_IRQHandler(void)             { Default_Handler(); }   /* CAN2 TX                                     */
__weak void CAN2_RX0_IRQHandler(void)            { Default_Handler(); }   /* CAN2 RX0                                    */
__weak void CAN2_RX1_IRQHandler(void)            { Default_Handler(); }   /* CAN2 RX1                                    */
__weak void CAN2_SCE_IRQHandler(void)            { Default_Handler(); }   /* CAN2 SCE                                    */
__weak void OTG_FS_IRQHandler(void)              { Default_Handler(); }   /* USB OTG FS                                  */
__weak void DMA2_Stream5_IRQHandler(void)        { Default_Handler(); }   /* DMA2 Stream 5                               */
__weak void DMA2_Stream6_IRQHandler(void)        { Default_Handler(); }   /* DMA2 Stream 6                               */
__weak void DMA2_Stream7_IRQHandler(void)        { Default_Handler(); }   /* DMA2 Stream 7                               */
__weak void USART6_IRQHandler(void)              { Default_Handler(); }   /* USART6                                      */
__weak void I2C3_EV_IRQHandler(void)             { Default_Handler(); }   /* I2C3 event                                  */
__weak void I2C3_ER_IRQHandler(void)             { Default_Handler(); }   /* I2C3 error                                  */
__weak void RNG_IRQHandler(void)                 { Default_Handler(); }   /* RNG                                         */
__weak void FPU_IRQHandler(void)                 { Default_Handler(); }   /* FPU                                         */
__weak void SPI4_IRQHandler(void)                { Default_Handler(); }   /* SPI4                                        */
__weak void SPI5_IRQHandler(void)                { Default_Handler(); }   /* SPI5                                        */
__weak void QUADSPI_IRQHandler(void)             { Default_Handler(); }   /* QuadSPI                                     */
__weak void FMPI2C1_EV_IRQHandler(void)          { Default_Handler(); }   /* FMPI2C1 Event                               */
__weak void FMPI2C1_ER_IRQHandler(void)          { Default_Handler(); }   /* FMPI2C1 Error                               */

// Interrupt vector table
__attribute__((section(".isr_vector")))
void (* VectorTable[])(void) =
{
    (void (*)(void)) &_estack,
    Reset_Handler,
    NMI_Handler,
    HardFault_Handler,
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    0,
    0,
    0,
    0,
    SVC_Handler,
    DebugMon_Handler,
    0,
    PendSV_Handler,
    SysTick_Handler,
    WWDG_IRQHandler,                   /* Window WatchDog                             */
    PVD_IRQHandler,                    /* PVD through EXTI Line detection             */
    TAMP_STAMP_IRQHandler,             /* Tamper and TimeStamps through the EXTI line */
    RTC_WKUP_IRQHandler,               /* RTC Wakeup through the EXTI line            */
    FLASH_IRQHandler,                  /* FLASH                                       */
    RCC_IRQHandler,                    /* RCC                                         */
    EXTI0_IRQHandler,                  /* EXTI Line0                                  */
    EXTI1_IRQHandler,                  /* EXTI Line1                                  */
    EXTI2_IRQHandler,                  /* EXTI Line2                                  */
    EXTI3_IRQHandler,                  /* EXTI Line3                                  */
    EXTI4_IRQHandler,                  /* EXTI Line4                                  */
    DMA1_Stream0_IRQHandler,           /* DMA1 Stream 0                               */
    DMA1_Stream1_IRQHandler,           /* DMA1 Stream 1                               */
    DMA1_Stream2_IRQHandler,           /* DMA1 Stream 2                               */
    DMA1_Stream3_IRQHandler,           /* DMA1 Stream 3                               */
    DMA1_Stream4_IRQHandler,           /* DMA1 Stream 4                               */
    DMA1_Stream5_IRQHandler,           /* DMA1 Stream 5                               */
    DMA1_Stream6_IRQHandler,           /* DMA1 Stream 6                               */
    ADC_IRQHandler,                    /* ADC1, ADC2 and ADC3s                        */
    CAN1_TX_IRQHandler,                /* CAN1 TX                                     */
    CAN1_RX0_IRQHandler,               /* CAN1 RX0                                    */
    CAN1_RX1_IRQHandler,               /* CAN1 RX1                                    */
    CAN1_SCE_IRQHandler,               /* CAN1 SCE                                    */
    EXTI9_5_IRQHandler,                /* External Line[9:5]s                         */
    TIM1_BRK_TIM9_IRQHandler,          /* TIM1 Break and TIM9                         */
    TIM1_UP_TIM10_IRQHandler,          /* TIM1 Update and TIM10                       */
    TIM1_TRG_COM_TIM11_IRQHandler,     /* TIM1 Trigger and Commutation and TIM11      */
    TIM1_CC_IRQHandler,                /* TIM1 Capture Compare                        */
    TIM2_IRQHandler,                   /* TIM2                                        */
    TIM3_IRQHandler,                   /* TIM3                                        */
    TIM4_IRQHandler,                   /* TIM4                                        */
    I2C1_EV_IRQHandler,                /* I2C1 Event                                  */
    I2C1_ER_IRQHandler,                /* I2C1 Error                                  */
    I2C2_EV_IRQHandler,                /* I2C2 Event                                  */
    I2C2_ER_IRQHandler,                /* I2C2 Error                                  */
    SPI1_IRQHandler,                   /* SPI1                                        */
    SPI2_IRQHandler,                   /* SPI2                                        */
    USART1_IRQHandler,                 /* USART1                                      */
    USART2_IRQHandler,                 /* USART2                                      */
    USART3_IRQHandler,                 /* USART3                                      */
    EXTI15_10_IRQHandler,              /* External Line[15:10]s                       */
    RTC_Alarm_IRQHandler,              /* RTC Alarm (A and B) through EXTI Line       */
    OTG_FS_WKUP_IRQHandler,            /* USB OTG FS Wakeup through EXTI line         */
    TIM8_BRK_TIM12_IRQHandler,         /* TIM8 Break and TIM12                        */
    TIM8_UP_TIM13_IRQHandler,          /* TIM8 Update and TIM13                       */
    TIM8_TRG_COM_TIM14_IRQHandler,     /* TIM8 Trigger and Commutation and TIM14      */
    TIM8_CC_IRQHandler,                /* TIM8 Capture Compare                        */
    DMA1_Stream7_IRQHandler,           /* DMA1 Stream7                                */
    0,                                 /* Reserved                                    */
    SDIO_IRQHandler,                   /* SDIO                                        */
    TIM5_IRQHandler,                   /* TIM5                                        */
    SPI3_IRQHandler,                   /* SPI3                                        */
    0,                                 /* Reserved                                    */
    0,                                 /* Reserved                                    */
    TIM6_IRQHandler,                   /* TIM6                                        */
    TIM7_IRQHandler,                   /* TIM7                                        */
    DMA2_Stream0_IRQHandler,           /* DMA2 Stream 0                               */
    DMA2_Stream1_IRQHandler,           /* DMA2 Stream 1                               */
    DMA2_Stream2_IRQHandler,           /* DMA2 Stream 2                               */
    DMA2_Stream3_IRQHandler,           /* DMA2 Stream 3                               */
    DMA2_Stream4_IRQHandler,           /* DMA2 Stream 4                               */
    DFSDM1_FLT0_IRQHandler,            /* DFSDM1 Filter0                              */
    DFSDM1_FLT1_IRQHandler,            /* DFSDM1 Filter1                              */
    CAN2_TX_IRQHandler,                /* CAN2 TX                                     */
    CAN2_RX0_IRQHandler,               /* CAN2 RX0                                    */
    CAN2_RX1_IRQHandler,               /* CAN2 RX1                                    */
    CAN2_SCE_IRQHandler,               /* CAN2 SCE                                    */
    OTG_FS_IRQHandler,                 /* USB OTG FS                                  */
    DMA2_Stream5_IRQHandler,           /* DMA2 Stream 5                               */
    DMA2_Stream6_IRQHandler,           /* DMA2 Stream 6                               */
    DMA2_Stream7_IRQHandler,           /* DMA2 Stream 7                               */
    USART6_IRQHandler,                 /* USART6                                      */
    I2C3_EV_IRQHandler,                /* I2C3 event                                  */
    I2C3_ER_IRQHandler,                /* I2C3 error                                  */
    0,                                 /* Reserved                                    */
    0,                                 /* Reserved                                    */
    0,                                 /* Reserved                                    */
    0,                                 /* Reserved                                    */
    0,                                 /* Reserved                                    */
    0,                                 /* Reserved                                    */
    RNG_IRQHandler,                    /* RNG                                         */
    FPU_IRQHandler,                    /* FPU                                         */
    0,                                 /* Reserved                                    */
    0,                                 /* Reserved                                    */
    SPI4_IRQHandler,                   /* SPI4                                        */
    SPI5_IRQHandler,                   /* SPI5                                        */
    0,                                 /* Reserved                                    */
    0,                                 /* Reserved                                    */
    0,                                 /* Reserved                                    */
    0,                                 /* Reserved                                    */
    0,                                 /* Reserved                                    */
    0,                                 /* Reserved                                    */
    QUADSPI_IRQHandler,                /* QuadSPI                                     */
    0,                                 /* Reserved                                    */
    0,                                 /* Reserved                                    */
    FMPI2C1_EV_IRQHandler,             /* FMPI2C1 Event                               */
    FMPI2C1_ER_IRQHandler              /* FMPI2C1 Error                               */
};

#ifdef __cplusplus
}
#endif
