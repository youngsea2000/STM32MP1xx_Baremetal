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
#include <stdlib.h>

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
uint8_t *LCD_Frame1_Addr;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
HAL_StatusTypeDef start_cpu1(void);
static void LCD_Config(void);

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

  printf("youngsea Ver:0.0.0\r\n");
  printf("\r\nHello from core0!\r\n");
  printf("MPU_CLK: %ldMHz\r\n", HAL_RCC_GetMPUSSFreq());
  printf("AXI_CLK: %ldMHz\r\n", HAL_RCC_GetAXISSFreq());
  printf("MCU_CLK: %ldMHz\r\n", HAL_RCC_GetMCUSSFreq());
  LCD_Config();
  printf("Start up core1\r\n");
  if(start_cpu1()!=HAL_OK)
  {
    printf("fail start core1\r\n");
  } else {
    printf("success start core1\r\n");
  }
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    BSP_LCD_FillRect(0,0,0,EK79001_WIDTH,EK79001_HEIGHT,LCD_COLOR_WHITE);
    BSP_LCD_Reload(0,LCD_RELOAD_IMMEDIATE);
    HAL_Delay(1000);
    BSP_LED_Toggle(LED_RED);
    BSP_LCD_FillRect(0,0,0,EK79001_WIDTH,EK79001_HEIGHT,LCD_COLOR_BLACK);
    BSP_LCD_Reload(0,LCD_RELOAD_IMMEDIATE);
    HAL_Delay(1000);
    BSP_LED_Toggle(LED_RED);
    BSP_LCD_FillRect(0,0,0,EK79001_WIDTH,EK79001_HEIGHT,LCD_COLOR_RED);
    BSP_LCD_Reload(0,LCD_RELOAD_IMMEDIATE);
    HAL_Delay(1000);
    BSP_LED_Toggle(LED_RED);
    BSP_LCD_FillRect(0,0,0,EK79001_WIDTH,EK79001_HEIGHT,LCD_COLOR_GREEN);
    BSP_LCD_Reload(0,LCD_RELOAD_IMMEDIATE);
    HAL_Delay(1000);
    BSP_LED_Toggle(LED_RED);
    BSP_LCD_FillRect(0,0,0,EK79001_WIDTH,EK79001_HEIGHT,LCD_COLOR_BLUE);
    BSP_LCD_Reload(0,LCD_RELOAD_IMMEDIATE);
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
  RCC_PLLInitTypeDef RCC_PLLInitStructure;

  __HAL_RCC_SDMMC1_CLK_DISABLE();

  RCC_PLLInitStructure.PLLState = RCC_PLL_ON;
  RCC_PLLInitStructure.PLLSource = RCC_PLL4SOURCE_HSE;
  RCC_PLLInitStructure.PLLM = 2;
  RCC_PLLInitStructure.PLLN = 50;
  RCC_PLLInitStructure.PLLP = 3;
  RCC_PLLInitStructure.PLLQ = 7;
  RCC_PLLInitStructure.PLLR = 2;
  RCC_PLLInitStructure.PLLRGE = RCC_PLL4IFRANGE_1;
  RCC_PLLInitStructure.PLLFRACV = 0;
  RCC_PLLInitStructure.PLLMODE = RCC_PLL_INTEGER;
  
  if (RCCEx_PLL4_Config(&RCC_PLLInitStructure) != HAL_OK) {
    /* HAL RCC configuration error */
    Error_Handler();
    }

#if !defined(USE_DDR)
  HAL_RCC_DeInit();
  RCC_ClkInitTypeDef RCC_ClkInitStructure;
  RCC_OscInitTypeDef RCC_OscInitStructure;

  /* Enable all available oscillators*/
  RCC_OscInitStructure.OscillatorType = (RCC_OSCILLATORTYPE_HSI |
                                         RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_CSI |
                                         RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_LSE);

  RCC_OscInitStructure.HSIState = RCC_HSI_ON;
  RCC_OscInitStructure.HSEState = RCC_HSE_ON;
  RCC_OscInitStructure.LSEState = RCC_LSE_ON;
  RCC_OscInitStructure.LSIState = RCC_LSI_ON;
  RCC_OscInitStructure.CSIState = RCC_CSI_ON;

  RCC_OscInitStructure.HSICalibrationValue = 0x00; //Default reset value
  RCC_OscInitStructure.CSICalibrationValue = 0x10; //Default reset value
  RCC_OscInitStructure.HSIDivValue = RCC_HSI_DIV1; //Default value

  /* PLL configuration */
  RCC_OscInitStructure.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStructure.PLL.PLLSource = RCC_PLL12SOURCE_HSE;
  RCC_OscInitStructure.PLL.PLLM = 3;
  RCC_OscInitStructure.PLL.PLLN = 100;
  RCC_OscInitStructure.PLL.PLLP = 1;
  RCC_OscInitStructure.PLL.PLLQ = 2;
  RCC_OscInitStructure.PLL.PLLR = 2;
  RCC_OscInitStructure.PLL.PLLFRACV = 0;
  RCC_OscInitStructure.PLL.PLLMODE = RCC_PLL_INTEGER;

  RCC_OscInitStructure.PLL2.PLLState = RCC_PLL_ON;
  RCC_OscInitStructure.PLL2.PLLSource = RCC_PLL12SOURCE_HSE;
  RCC_OscInitStructure.PLL2.PLLM = 3;
  RCC_OscInitStructure.PLL2.PLLN = 66;
  RCC_OscInitStructure.PLL2.PLLP = 2;
  RCC_OscInitStructure.PLL2.PLLQ = 2;
  RCC_OscInitStructure.PLL2.PLLR = 1;
  RCC_OscInitStructure.PLL2.PLLFRACV = 0x1400;
  RCC_OscInitStructure.PLL2.PLLMODE = RCC_PLL_FRACTIONAL;

  RCC_OscInitStructure.PLL3.PLLState = RCC_PLL_ON;
  RCC_OscInitStructure.PLL3.PLLSource = RCC_PLL3SOURCE_HSE;
  RCC_OscInitStructure.PLL3.PLLM = 2;
  RCC_OscInitStructure.PLL3.PLLN = 52;
  RCC_OscInitStructure.PLL3.PLLP = 3;
  RCC_OscInitStructure.PLL3.PLLQ = 2;
  RCC_OscInitStructure.PLL3.PLLR = 2;
  RCC_OscInitStructure.PLL3.PLLRGE = RCC_PLL3IFRANGE_1;
  RCC_OscInitStructure.PLL3.PLLFRACV = 0x0800;
  RCC_OscInitStructure.PLL3.PLLMODE = RCC_PLL_FRACTIONAL;

  RCC_OscInitStructure.PLL4.PLLState = RCC_PLL_ON;
  RCC_OscInitStructure.PLL4.PLLSource = RCC_PLL4SOURCE_HSE;
  RCC_OscInitStructure.PLL4.PLLM = 2;
  RCC_OscInitStructure.PLL4.PLLN = 50;
  RCC_OscInitStructure.PLL4.PLLP = 3;
  RCC_OscInitStructure.PLL4.PLLQ = 1;
  RCC_OscInitStructure.PLL4.PLLR = 1;
  RCC_OscInitStructure.PLL4.PLLRGE = RCC_PLL4IFRANGE_1;
  RCC_OscInitStructure.PLL4.PLLFRACV = 0;
  RCC_OscInitStructure.PLL4.PLLMODE = RCC_PLL_INTEGER;

  /* Enable access to RTC and backup registers */
  SET_BIT(PWR->CR1, PWR_CR1_DBP);
  /* Configure LSEDRIVE value */
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_MEDIUMHIGH);

  if (HAL_RCC_OscConfig(&RCC_OscInitStructure) != HAL_OK) {
    /* HAL RCC configuration error */
    Error_Handler();
    }

  /* Select PLLx as MPU, AXI and MCU clock sources */
  RCC_ClkInitStructure.ClockType = (RCC_CLOCKTYPE_MPU   | RCC_CLOCKTYPE_ACLK  |
                                    RCC_CLOCKTYPE_HCLK  | RCC_CLOCKTYPE_PCLK4 |
                                    RCC_CLOCKTYPE_PCLK5 | RCC_CLOCKTYPE_PCLK1 |
                                    RCC_CLOCKTYPE_PCLK2 | RCC_CLOCKTYPE_PCLK3);

  RCC_ClkInitStructure.MPUInit.MPU_Clock = RCC_MPUSOURCE_PLL1;
  RCC_ClkInitStructure.MPUInit.MPU_Div = RCC_MPU_DIV2;
  RCC_ClkInitStructure.AXISSInit.AXI_Clock = RCC_AXISSOURCE_PLL2;
  RCC_ClkInitStructure.AXISSInit.AXI_Div = RCC_AXI_DIV1;
  RCC_ClkInitStructure.MCUInit.MCU_Clock = RCC_MCUSSOURCE_PLL3;
  RCC_ClkInitStructure.MCUInit.MCU_Div = RCC_MCU_DIV1;
  RCC_ClkInitStructure.APB1_Div = RCC_APB1_DIV2;
  RCC_ClkInitStructure.APB2_Div = RCC_APB2_DIV2;
  RCC_ClkInitStructure.APB3_Div = RCC_APB3_DIV2;
  RCC_ClkInitStructure.APB4_Div = RCC_APB4_DIV2;
  RCC_ClkInitStructure.APB5_Div = RCC_APB5_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStructure) != HAL_OK) {
    /* HAL RCC configuration error */
    Error_Handler();
    }

/*
  Note : The activation of the I/O Compensation Cell is recommended with communication  interfaces
  (GPIO, SPI, FMC, XSPI ...)  when  operating at  high frequencies(please refer to product datasheet)
  The I/O Compensation Cell activation  procedure requires :
  - The activation of the CSI clock
  - The activation of the SYSCFG clock
  - Enabling the I/O Compensation Cell : setting bit[0] of register SYSCFG_CCCSR

  To do this please uncomment the following code
  */

  /*
  __HAL_RCC_CSI_ENABLE() ;

  __HAL_RCC_SYSCFG_CLK_ENABLE() ;

  HAL_EnableCompensationCell();
*/
#endif
}

/* USER CODE BEGIN 4 */

/**
  * @brief  Error callback.
  * @param  hltdc: pointer to a LTDC_HandleTypeDef structure that contains
  *                the configuration information for the LTDC.
  * @retval None
  */
void HAL_LTDC_ErrorCallback(LTDC_HandleTypeDef *hltdc)
{
  Error_Handler();
}

/**
  * @brief  Reload Event callback.
  * @param  hltdc: pointer to a LTDC_HandleTypeDef structure that contains
  *                the configuration information for the LTDC.
  * @retval None
  */
void HAL_LTDC_ReloadEventCallback(LTDC_HandleTypeDef *hltdc)
{
  // ReloadFlag = 1;
}

/**
  * @brief LCD Configuration.
  * @note  This function Configures the LTDC peripheral :
  *        1) DeInit LCD
  *        2) Init LCD
  *        3) Configure the LTDC Layer 1 :
  *           - color RGB888 as pixel format
  *           - The frame buffer is located at DDR memory
  *           - The Layer size configuration : 320x240
  *        4) Configure the LTDC Layer 2 :
  *           - color RGB888 as pixel format
  *           - The frame buffer is located at DDR memory
  *           - The Layer size configuration : 320x240
  *        5) Enable Display On
  * @retval
  *  None
  */
static void LCD_Config(void)
{
  /* LTDC Initialization -------------------------------------------------------*/
  BSP_LCD_DeInit(0);
  if(BSP_LCD_Get_ID(0)==2)
  {
    BSP_LCD_Init(0);
    LCD_Frame1_Addr = malloc(EK79001_WIDTH*EK79001_HEIGHT*3*2);
    printf("start malloc\r\n");
    if(LCD_Frame1_Addr==NULL){
      printf("error of malloc\r\n");
      return;
    }
    // HAL_Delay(1000);
    printf("end malloc\r\n");
    BSP_LCD_LayerDefaultInit(0,LTDC_LAYER_1, (uint32_t)LCD_Frame1_Addr);
    printf("end init\r\n");

  }else{
    printf("LCD Init Fail:%d\r\n",BSP_LCD_Get_ID(0));
    return;
  }

  /* Disable the FIFO underrun interrupt */
  __HAL_LTDC_DISABLE_IT(&hLtdcHandler, LTDC_IT_FU);

  /* Enable Display On */
  BSP_LCD_DisplayOn(0);
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
