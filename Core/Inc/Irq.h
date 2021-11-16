#pragma once

#include <stdint.h>

namespace core
{

enum Irq : int32_t
{
/******  Cortex-M4 Processor Exceptions Numbers ****************************************************************/
  NonMaskableInt_IRQ_Number         = -14,    /*!< 2 Non Maskable Interrupt                                          */
  MemoryManagement_IRQ_Number       = -12,    /*!< 4 Cortex-M4 Memory Management Interrupt                           */
  BusFault_IRQ_Number               = -11,    /*!< 5 Cortex-M4 Bus Fault Interrupt                                   */
  UsageFault_IRQ_Number             = -10,    /*!< 6 Cortex-M4 Usage Fault Interrupt                                 */
  SVCall_IRQ_Number                 = -5,     /*!< 11 Cortex-M4 SV Call Interrupt                                    */
  DebugMonitor_IRQ_Number           = -4,     /*!< 12 Cortex-M4 Debug Monitor Interrupt                              */
  PendSV_IRQ_Number                 = -2,     /*!< 14 Cortex-M4 Pend SV Interrupt                                    */
  SysTick_IRQ_Number                = -1,     /*!< 15 Cortex-M4 System Tick Interrupt                                */
/******  STM32 specific Interrupt Numbers **********************************************************************/
  WWDG_IRQ_Number                   = 0,      /*!< Window WatchDog Interrupt                                         */
  PVD_IRQ_Number                    = 1,      /*!< PVD through EXTI Line detection Interrupt                         */
  TAMP_STAMP_IRQ_Number             = 2,      /*!< Tamper and TimeStamp interrupts through the EXTI line             */
  RTC_WKUP_IRQ_Number               = 3,      /*!< RTC Wakeup interrupt through the EXTI line                        */
  FLASH_IRQ_Number                  = 4,      /*!< FLASH global Interrupt                                            */
  RCC_IRQ_Number                    = 5,      /*!< RCC global Interrupt                                              */
  EXTI0_IRQ_Number                  = 6,      /*!< EXTI Line0 Interrupt                                              */
  EXTI1_IRQ_Number                  = 7,      /*!< EXTI Line1 Interrupt                                              */
  EXTI2_IRQ_Number                  = 8,      /*!< EXTI Line2 Interrupt                                              */
  EXTI3_IRQ_Number                  = 9,      /*!< EXTI Line3 Interrupt                                              */
  EXTI4_IRQ_Number                  = 10,     /*!< EXTI Line4 Interrupt                                              */
  DMA1_Stream0_IRQ_Number           = 11,     /*!< DMA1 Stream 0 global Interrupt                                    */
  DMA1_Stream1_IRQ_Number           = 12,     /*!< DMA1 Stream 1 global Interrupt                                    */
  DMA1_Stream2_IRQ_Number           = 13,     /*!< DMA1 Stream 2 global Interrupt                                    */
  DMA1_Stream3_IRQ_Number           = 14,     /*!< DMA1 Stream 3 global Interrupt                                    */
  DMA1_Stream4_IRQ_Number           = 15,     /*!< DMA1 Stream 4 global Interrupt                                    */
  DMA1_Stream5_IRQ_Number           = 16,     /*!< DMA1 Stream 5 global Interrupt                                    */
  DMA1_Stream6_IRQ_Number           = 17,     /*!< DMA1 Stream 6 global Interrupt                                    */
  ADC_IRQ_Number                    = 18,     /*!< ADC1, ADC2 and ADC3 global Interrupts                             */
  CAN1_TX_IRQ_Number                = 19,     /*!< CAN1 TX Interrupt                                                 */
  CAN1_RX0_IRQ_Number               = 20,     /*!< CAN1 RX0 Interrupt                                                */
  CAN1_RX1_IRQ_Number               = 21,     /*!< CAN1 RX1 Interrupt                                                */
  CAN1_SCE_IRQ_Number               = 22,     /*!< CAN1 SCE Interrupt                                                */
  EXTI9_5_IRQ_Number                = 23,     /*!< External Line[9:5] Interrupts                                     */
  TIM1_BRK_TIM9_IRQ_Number          = 24,     /*!< TIM1 Break interrupt and TIM9 global interrupt                    */
  TIM1_UP_TIM10_IRQ_Number          = 25,     /*!< TIM1 Update Interrupt and TIM10 global interrupt                  */
  TIM1_TRG_COM_TIM11_IRQ_Number     = 26,     /*!< TIM1 Trigger and Commutation Interrupt and TIM11 global interrupt */
  TIM1_CC_IRQ_Number                = 27,     /*!< TIM1 Capture Compare Interrupt                                    */
  TIM2_IRQ_Number                   = 28,     /*!< TIM2 global Interrupt                                             */
  TIM3_IRQ_Number                   = 29,     /*!< TIM3 global Interrupt                                             */
  TIM4_IRQ_Number                   = 30,     /*!< TIM4 global Interrupt                                             */
  I2C1_EV_IRQ_Number                = 31,     /*!< I2C1 Event Interrupt                                              */
  I2C1_ER_IRQ_Number                = 32,     /*!< I2C1 Error Interrupt                                              */
  I2C2_EV_IRQ_Number                = 33,     /*!< I2C2 Event Interrupt                                              */
  I2C2_ER_IRQ_Number                = 34,     /*!< I2C2 Error Interrupt                                              */
  SPI1_IRQ_Number                   = 35,     /*!< SPI1 global Interrupt                                             */
  SPI2_IRQ_Number                   = 36,     /*!< SPI2 global Interrupt                                             */
  USART1_IRQ_Number                 = 37,     /*!< USART1 global Interrupt                                           */
  USART2_IRQ_Number                 = 38,     /*!< USART2 global Interrupt                                           */
  USART3_IRQ_Number                 = 39,     /*!< USART3 global Interrupt                                           */
  EXTI15_10_IRQ_Number              = 40,     /*!< External Line[15:10] Interrupts                                   */
  RTC_Alarm_IRQ_Number              = 41,     /*!< RTC Alarm (A and B) through EXTI Line Interrupt                   */
  OTG_FS_WKUP_IRQ_Number            = 42,     /*!< USB OTG FS Wakeup through EXTI line interrupt                     */
  TIM8_BRK_TIM12_IRQ_Number         = 43,     /*!< TIM8 Break Interrupt and TIM12 global interrupt                   */
  TIM8_UP_TIM13_IRQ_Number          = 44,     /*!< TIM8 Update Interrupt and TIM13 global interrupt                  */
  TIM8_TRG_COM_TIM14_IRQ_Number     = 45,     /*!< TIM8 Trigger and Commutation Interrupt and TIM14 global interrupt */
  TIM8_CC_IRQ_Number                = 46,     /*!< TIM8 Capture Compare global interrupt                             */
  DMA1_Stream7_IRQ_Number           = 47,     /*!< DMA1 Stream7 Interrupt                                            */
  SDIO_IRQ_Number                   = 49,     /*!< SDIO global Interrupt                                             */
  TIM5_IRQ_Number                   = 50,     /*!< TIM5 global Interrupt                                             */
  SPI3_IRQ_Number                   = 51,     /*!< SPI3 global Interrupt                                             */
  TIM6_IRQ_Number                   = 54,     /*!< TIM6 global interrupt                                             */
  TIM7_IRQ_Number                   = 55,     /*!< TIM7 global interrupt                                             */
  DMA2_Stream0_IRQ_Number           = 56,     /*!< DMA2 Stream 0 global Interrupt                                    */
  DMA2_Stream1_IRQ_Number           = 57,     /*!< DMA2 Stream 1 global Interrupt                                    */
  DMA2_Stream2_IRQ_Number           = 58,     /*!< DMA2 Stream 2 global Interrupt                                    */
  DMA2_Stream3_IRQ_Number           = 59,     /*!< DMA2 Stream 3 global Interrupt                                    */
  DMA2_Stream4_IRQ_Number           = 60,     /*!< DMA2 Stream 4 global Interrupt                                    */
  DFSDM1_FLT0_IRQ_Number            = 61,     /*!< DFSDM1 Filter 0 global Interrupt                                  */
  DFSDM1_FLT1_IRQ_Number            = 62,     /*!< DFSDM1 Filter 1 global Interrupt                                  */
  CAN2_TX_IRQ_Number                = 63,     /*!< CAN2 TX Interrupt                                                 */
  CAN2_RX0_IRQ_Number               = 64,     /*!< CAN2 RX0 Interrupt                                                */
  CAN2_RX1_IRQ_Number               = 65,     /*!< CAN2 RX1 Interrupt                                                */
  CAN2_SCE_IRQ_Number               = 66,     /*!< CAN2 SCE Interrupt                                                */
  OTG_FS_IRQ_Number                 = 67,     /*!< USB OTG FS global Interrupt                                       */
  DMA2_Stream5_IRQ_Number           = 68,     /*!< DMA2 Stream 5 global interrupt                                    */
  DMA2_Stream6_IRQ_Number           = 69,     /*!< DMA2 Stream 6 global interrupt                                    */
  DMA2_Stream7_IRQ_Number           = 70,     /*!< DMA2 Stream 7 global interrupt                                    */
  USART6_IRQ_Number                 = 71,     /*!< USART6 global interrupt                                           */
  I2C3_EV_IRQ_Number                = 72,     /*!< I2C3 event interrupt                                              */
  I2C3_ER_IRQ_Number                = 73,     /*!< I2C3 error interrupt                                              */
  RNG_IRQ_Number                    = 80,     /*!< RNG global Interrupt                                              */
  FPU_IRQ_Number                    = 81,     /*!< FPU global interrupt                                              */
  SPI4_IRQ_Number                   = 84,     /*!< SPI4 global Interrupt                                             */
  SPI5_IRQ_Number                   = 85,     /*!< SPI5 global Interrupt                                             */
  QUADSPI_IRQ_Number                = 92,     /*!< QuadSPI global Interrupt                                          */ 
  FMPI2C1_EV_IRQ_Number             = 95,     /*!< FMPI2C1 Event Interrupt                                           */
  FMPI2C1_ER_IRQ_Number             = 96      /*!< FMPI2C1 Error Interrupt                                           */
};

}
