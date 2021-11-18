#include "main.h"
#include "Irq.h"
#include "Registers.h"
#include "Interrupts.h"
#include "Tick.h"
#include <cassert>

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart3;

PCD_HandleTypeDef hpcd_USB_OTG_FS;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_USB_OTG_FS_PCD_Init(void);

static constexpr uint32_t PORT_B_BASE = 0x40020400UL;

static inline void initLeds()
{
  // Enable peripheral clock for Port B
  constexpr uint32_t RCC_BASE_TEMP = 0x40023800;
  volatile uint32_t* const RCC_AHB1 = (volatile uint32_t*) (RCC_BASE_TEMP + 0x30UL);
  *RCC_AHB1 |= (1 << 1); // Enable clock to Port B

  volatile uint32_t* const MODERB = (volatile uint32_t*) (PORT_B_BASE);
  volatile uint32_t* const OTYPERB = (volatile uint32_t*) (PORT_B_BASE + 0x04UL);
  volatile uint32_t* const OSPEEDRB = (volatile uint32_t*) (PORT_B_BASE + 0x08UL);
  volatile uint32_t* const PUPDRB = (volatile uint32_t*) (PORT_B_BASE + 0x0C);
  *MODERB &= ~((0b11 << 28) | (0b11 << 14) | 0b11); // Clear
  *MODERB |= (0b01 << 28) | (0b01 << 14) | 0b01;  // Set I/O as output
  *OTYPERB &= ~((1 << 14) | (1 << 7) | 1);   // Clear -> Pull-Push
  *OSPEEDRB &= ~((0b11 << 28) | (0b11 << 14) | 0b11); // Clear -> Low speed
  *PUPDRB &= ~((0b11 << 28) | (0b11 << 14) | 0b11); // Clear -> No pull up/down
}

static volatile uint32_t* ODR_B = (volatile uint32_t*) (PORT_B_BASE + 0x14UL);

static inline void setLeds()
{
  *ODR_B |= (1 << 14) | (1 << 7) | 1;
}

static inline void clearLeds()
{
  *ODR_B &= ~((1 << 14) | (1 << 7) | 1);
}

static inline void enableDataInstructionCachePrefetch()
{
  volatile uint32_t* const FLASH_ACR = (volatile uint32_t*) 0x40023C00UL;
  static constexpr uint32_t ICEN = 1 << 9; // Enable instruction cache
  static constexpr uint32_t DCEN = 1 << 10; // Enable data cache
  static constexpr uint32_t PRFTEN = 1 << 8; // Enable prefetch
  *FLASH_ACR |= ICEN | DCEN | PRFTEN;
}

static void updateTick(uint32_t clockspeed)
{
  constexpr uint32_t TICK_FREQ = 1; // 1 KHz
  uint32_t ticks = clockspeed / (1000U / TICK_FREQ);
    /* Configure the SysTick to have interrupt in 1ms time basis*/
  if ((ticks - 1UL) > 0xFFFFFFUL)
  {
    return;                                                   /* Reload value impossible */
  }

  static constexpr uint32_t SySTick_Base = 0xE000E010;
  volatile uint32_t* const LOAD = (volatile uint32_t*)(0xE000E010 + 0x4);
  volatile uint32_t* const VAL = (volatile uint32_t*)(SySTick_Base + 0x8);
  *LOAD  = (uint32_t)(ticks - 1UL);                         /* set reload register */
  *VAL   = 0UL;                                             /* Load the SysTick Counter Value (Jacob: Clear any previous value)*/
}

static void initTick(uint32_t clockspeed, uint32_t hz)
{
  uint32_t ticks = clockspeed / hz;
  assert((ticks - 1UL) < 0xFFFFFFUL);
  REMOVE_MACRO(SysTick)->RVR = (uint32_t)(ticks - 1UL); /* set reload value register */
  REMOVE_MACRO(SysTick)->CVR = 0UL; /* Clear current count, any value writte will clear the register. Use 0 for readability */
  REMOVE_MACRO(SysTick)->CSR = (1UL << 2U) | (1UL << 1U) | 1UL; /* Clock source = Processor clock | Enable SysTick exception request (Interrupt) | Enable counter */

  core::configIrqPriority(core::SysTick_IRQ_Number, 0U, 0U);
}

volatile uint32_t msTick = 0;

void delay(uint32_t ms)
{
  uint32_t start = msTick;
  while (msTick - start < ms);
}

extern "C" void SysTick_Handler(void)
{
  msTick++;
}

int main(void)
{
  enableDataInstructionCachePrefetch();
  core::configInterruptGroupPriority<4U, 0U>();
  initTick(16000000, 1000);
  /* USER CODE BEGIN 1 */
  //HAL_InitTick(0);
  /* USER CODE END 1 */

  // This enables the system configuration controller (SCC) registers on the APB2
  // The SCC gives the possibility to enable external interrupt and memory remapping, what ever it is?
  // The SCC is mapped to the APB2
  //__HAL_RCC_SYSCFG_CLK_ENABLE();
  // This enable the power controller registers on APB1.
  //__HAL_RCC_PWR_CLK_ENABLE();

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  //HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();
  updateTick(96000000);
  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  //MX_GPIO_Init();
  MX_USART3_UART_Init();
  //MX_USB_OTG_FS_PCD_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  initLeds();

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    uint8_t text[] = {'H', 'e', 'l', 'l', 'o', '\n', '\r'};
    HAL_UART_Transmit(&huart3, text, 7, 100);
    setLeds();
    //HAL_Delay(100);
    delay(500);
    clearLeds();
    //HAL_Delay(100);
    delay(500);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

// static void initLeds()
// {
//   // Enable peripheral clock for Port B
//   const uint32_t RCC_BASE_TEMP = 0x40023800;
//   volatile uint32_t* const RCC_AHB1 = (volatile uint32_t*) (RCC_BASE_TEMP + 0x30UL);
//   *RCC_AHB1 |= (1 << 1); // Enable clock to Port B

//   volatile uint32_t* const MODERB = (volatile uint32_t*) (PORT_B_BASE);
//   volatile uint32_t* const OTYPERB = (volatile uint32_t*) (PORT_B_BASE + 0x04UL);
//   volatile uint32_t* const OSPEEDRB = (volatile uint32_t*) (PORT_B_BASE + 0x08UL);
//   volatile uint32_t* const PUPDRB = (volatile uint32_t*) (PORT_B_BASE + 0x0C);
//   *MODERB &= ~((0b11 << 28) | (0b11 << 14) | 0b11); // Clear
//   *MODERB |= (0b01 << 28) | (0b01 << 14) | 0b01;  // Set I/O as output
//   *OTYPERB &= ~((1 << 14) | (1 << 7) | 1);   // Clear -> Pull-Push
//   *OSPEEDRB &= ~((0b11 << 28) | (0b11 << 14) | 0b11); // Clear -> Low speed
//   *PUPDRB &= ~((0b11 << 28) | (0b11 << 14) | 0b11); // Clear -> No pull up/down
// }

// static volatile uint32_t* ODR_B = (volatile uint32_t*) (PORT_B_BASE + 0x14UL);

// static void setLeds()
// {
//   *ODR_B |= (1 << 14) | (1 << 7) | 1;
// }

// static void clearLeds()
// {
//   *ODR_B &= ~((1 << 14) | (1 << 7) | 1);
// }

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 384;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 8;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief USB_OTG_FS Initialization Function
  * @param None
  * @retval None
  */
static void MX_USB_OTG_FS_PCD_Init(void)
{

  /* USER CODE BEGIN USB_OTG_FS_Init 0 */

  /* USER CODE END USB_OTG_FS_Init 0 */

  /* USER CODE BEGIN USB_OTG_FS_Init 1 */

  /* USER CODE END USB_OTG_FS_Init 1 */
  hpcd_USB_OTG_FS.Instance = USB_OTG_FS;
  hpcd_USB_OTG_FS.Init.dev_endpoints = 6;
  hpcd_USB_OTG_FS.Init.speed = PCD_SPEED_FULL;
  hpcd_USB_OTG_FS.Init.dma_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
  hpcd_USB_OTG_FS.Init.Sof_enable = ENABLE;
  hpcd_USB_OTG_FS.Init.low_power_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.lpm_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.battery_charging_enable = ENABLE;
  hpcd_USB_OTG_FS.Init.vbus_sensing_enable = ENABLE;
  hpcd_USB_OTG_FS.Init.use_dedicated_ep1 = DISABLE;
  if (HAL_PCD_Init(&hpcd_USB_OTG_FS) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_OTG_FS_Init 2 */

  /* USER CODE END USB_OTG_FS_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LD1_Pin|LD3_Pin|LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(USB_PowerSwitchOn_GPIO_Port, USB_PowerSwitchOn_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : USER_Btn_Pin */
  GPIO_InitStruct.Pin = USER_Btn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USER_Btn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD1_Pin LD3_Pin LD2_Pin */
  GPIO_InitStruct.Pin = LD1_Pin|LD3_Pin|LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_PowerSwitchOn_Pin */
  GPIO_InitStruct.Pin = USB_PowerSwitchOn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(USB_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_OverCurrent_Pin */
  GPIO_InitStruct.Pin = USB_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USB_OverCurrent_GPIO_Port, &GPIO_InitStruct);

}

#include <cassert>

void __assert_func (const char *, int, const char *, const char *)
{
  __disable_irq();
  while (true);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
