/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main0.c
  * @brief          : Core0 Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
__IO uint8_t log_lock = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
HAL_StatusTypeDef start_cpu1(void);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
  // uint16_t cnt = 0;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  /* USER CODE BEGIN 2 */
  BSP_LED_Init(LED_GREEN);
  BSP_LED_Init(LED_RED);
  BSP_PB_Init(BUTTON_WAKEUP, BUTTON_MODE_GPIO);
  BSP_PB_Init(BUTTON_KEY0  , BUTTON_MODE_GPIO);
  BSP_PB_Init(BUTTON_KEY1  , BUTTON_MODE_GPIO);

  COM_InitTypeDef COM_Init[COMn]={
    [COM1]={115200, 8, COM_STOPBITS_1, COM_PARITY_NONE, COM_HWCONTROL_NONE},
  };
  BSP_COM_Init(COM1, &COM_Init[COM1]);

  if(wait_lock(&log_lock))
  {
    set_lock(&log_lock);
    printf("\r\nHello from core0!\r\n");
    printf("MPU_CLK: %ldMHz\r\n", HAL_RCC_GetMPUSSFreq());
    printf("AXI_CLK: %ldMHz\r\n", HAL_RCC_GetAXISSFreq());
    printf("MCU_CLK: %ldMHz\r\n", HAL_RCC_GetMCUSSFreq());
    printf("Start up core1\r\n");
    if(start_cpu1()!=HAL_OK)
    {
      printf("fail start core1\r\n");
    } else {
      printf("success start core1\r\n");
    }
    clr_lock(&log_lock);
  }
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    HAL_Delay(1000);
    BSP_LED_Toggle(LED_RED);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  // RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  // RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  // RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_MPU | RCC_CLOCKTYPE_ACLK | RCC_CLOCKTYPE_HCLK /* <-- MCU Clock */ |
  //      RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 | RCC_CLOCKTYPE_PCLK3 | RCC_CLOCKTYPE_PCLK4 |
  //      RCC_CLOCKTYPE_PCLK5;
  // RCC_ClkInitStruct.MPUInit.MPU_Clock = RCC_MPUSOURCE_HSI;
  // RCC_ClkInitStruct.MPUInit.MPU_Div = RCC_MPU_DIV2;
  // RCC_ClkInitStruct.AXISSInit.AXI_Clock = RCC_AXISSOURCE_HSI;
  // RCC_ClkInitStruct.AXISSInit.AXI_Div = RCC_AXI_DIV1;
  // RCC_ClkInitStruct.MCUInit.MCU_Clock = RCC_MCUSSOURCE_HSI;
  // RCC_ClkInitStruct.MCUInit.MCU_Div = RCC_MCU_DIV1;
  // RCC_ClkInitStruct.APB4_Div = RCC_APB4_DIV2;
  // RCC_ClkInitStruct.APB5_Div = RCC_APB5_DIV4;
  // RCC_ClkInitStruct.APB1_Div = RCC_APB1_DIV2;
  // RCC_ClkInitStruct.APB2_Div = RCC_APB2_DIV2;
  // RCC_ClkInitStruct.APB3_Div = RCC_APB3_DIV2;
  // if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct) != HAL_OK)
  // {
  //   Error_Handler();
  // }

  // /** Configure LSE Drive Capability
  // */
  // HAL_PWR_EnableBkUpAccess();
  // __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_MEDIUMHIGH);

  // /** Initializes the RCC Oscillators according to the specified parameters
  // * in the RCC_OscInitTypeDef structure.
  // */
  // RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
  // RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  // RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  // RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  // RCC_OscInitStruct.PLL.PLLSource = RCC_PLL12SOURCE_HSE;
  // RCC_OscInitStruct.PLL.PLLM = 3;
  // RCC_OscInitStruct.PLL.PLLN = 100;
  // RCC_OscInitStruct.PLL.PLLP = 1;
  // RCC_OscInitStruct.PLL.PLLQ = 2;
  // RCC_OscInitStruct.PLL.PLLR = 2;
  // RCC_OscInitStruct.PLL.PLLFRACV = 0;
  // RCC_OscInitStruct.PLL.PLLMODE = RCC_PLL_INTEGER;
  // RCC_OscInitStruct.PLL2.PLLState = RCC_PLL_NONE;
  // RCC_OscInitStruct.PLL2.PLLSource = RCC_PLL12SOURCE_HSE;
  // RCC_OscInitStruct.PLL2.PLLM = 3;
  // RCC_OscInitStruct.PLL2.PLLN = 66;
  // RCC_OscInitStruct.PLL2.PLLP = 2;
  // RCC_OscInitStruct.PLL2.PLLQ = 1;
  // RCC_OscInitStruct.PLL2.PLLR = 1;
  // RCC_OscInitStruct.PLL2.PLLFRACV = 5120;
  // RCC_OscInitStruct.PLL2.PLLMODE = RCC_PLL_FRACTIONAL;
  // RCC_OscInitStruct.PLL3.PLLState = RCC_PLL_ON;
  // RCC_OscInitStruct.PLL3.PLLSource = RCC_PLL3SOURCE_HSE;
  // RCC_OscInitStruct.PLL3.PLLM = 2;
  // RCC_OscInitStruct.PLL3.PLLN = 52;
  // RCC_OscInitStruct.PLL3.PLLP = 3;
  // RCC_OscInitStruct.PLL3.PLLQ = 17;
  // RCC_OscInitStruct.PLL3.PLLR = 37;
  // RCC_OscInitStruct.PLL3.PLLRGE = RCC_PLL3IFRANGE_1;
  // RCC_OscInitStruct.PLL3.PLLFRACV = 2048;
  // RCC_OscInitStruct.PLL3.PLLMODE = RCC_PLL_FRACTIONAL;
  // RCC_OscInitStruct.PLL4.PLLState = RCC_PLL_ON;
  // RCC_OscInitStruct.PLL4.PLLSource = RCC_PLL4SOURCE_HSE;
  // RCC_OscInitStruct.PLL4.PLLM = 4;
  // RCC_OscInitStruct.PLL4.PLLN = 9;
  // RCC_OscInitStruct.PLL4.PLLP = 6;
  // RCC_OscInitStruct.PLL4.PLLQ = 8;
  // RCC_OscInitStruct.PLL4.PLLR = 8;
  // RCC_OscInitStruct.PLL4.PLLRGE = RCC_PLL4IFRANGE_0;
  // RCC_OscInitStruct.PLL4.PLLFRACV = 0x1000;
  // RCC_OscInitStruct.PLL4.PLLMODE = RCC_PLL_INTEGER;
  // if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  // {
  //   Error_Handler();
  // }

  // /** Set the HSE division factor for RTC clock
  // */
  // __HAL_RCC_RTC_HSEDIV(1);

  // RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_MPU | RCC_CLOCKTYPE_ACLK | RCC_CLOCKTYPE_HCLK /* <-- MCU Clock */ |
  //      RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 | RCC_CLOCKTYPE_PCLK3 | RCC_CLOCKTYPE_PCLK4 |
  //      RCC_CLOCKTYPE_PCLK5;
  // RCC_ClkInitStruct.MPUInit.MPU_Clock = RCC_MPUSOURCE_PLL1;
  // RCC_ClkInitStruct.AXISSInit.AXI_Clock = RCC_AXISSOURCE_PLL2;
  // RCC_ClkInitStruct.MCUInit.MCU_Clock = RCC_MCUSSOURCE_PLL3;
  // if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct) != HAL_OK)
  // {
  //   Error_Handler();
  // }
}

/* USER CODE BEGIN 4 */
void set_lock(__IO uint8_t *lock)
{
  *lock = 1;
}
void clr_lock(__IO uint8_t *lock)
{
  *lock = 0;
}
uint8_t wait_lock(__IO uint8_t *lock)
{
  uint32_t tickstart;
  tickstart = HAL_GetTick();
  while (*lock == 1) {
    if ((HAL_GetTick() - tickstart) > 1000)
    {
      return 1;
    }
  }
  return 0;
}

/**
  * @brief Provides a tick value in millisecond.
  * @note This function is declared as __weak to be overwritten in case of other
  *       implementations in user file.
  * @retval tick value
  */
uint32_t HAL_GetTick(void)
{
#if defined (CORE_CA7)

#if defined (USE_ST_CASIS)
  return ( Gen_Timer_Get_PhysicalCount() / (HSI_VALUE/1000));
#elif defined (USE_PL1_SecurePhysicalTimer_IRQ)
  /* tick is incremented in SecurePhysicalTimer_IRQ handler */
  return uwTick;
#else
  /* tick value directly got from 64bits CA7 register*/
  if ((RCC->STGENCKSELR & RCC_STGENCKSELR_STGENSRC) == RCC_STGENCLKSOURCE_HSE)
  {
    return ( PL1_GetCurrentPhysicalValue() / (HSE_VALUE/1000UL));
  }
  else
  {
    return ( PL1_GetCurrentPhysicalValue() / (HSI_VALUE/1000));
  }
#endif

#endif /* CORE_CA7 */


#if defined (CORE_CM4)
  /* tick is incremented in systick handler */
  return uwTick;
#endif /* CORE_CM4 */

}

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
