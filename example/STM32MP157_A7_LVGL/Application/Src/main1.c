/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main1.c
  * @brief          : Core1 Main program body
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

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
void Reset_Handler_cpu1(void);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main_cpu1(void)
{

  /* USER CODE BEGIN 1 */
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */

  /* USER CODE BEGIN Init */
  
  /* USER CODE END Init */

  /* Configure the system clock */

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  /* USER CODE BEGIN 2 */
  if(wait_lock(&log_lock))
  {
    set_lock(&log_lock);
    printf("\r\nHello from Core1!\r\n");
    clr_lock(&log_lock);
  }

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    HAL_Delay(1000);
    BSP_LED_Toggle(LED_GREEN);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */
#ifdef USE_SECOND_A7_CORE
HAL_StatusTypeDef start_cpu1(void)
{
  uint32_t tickstart;
  HAL_StatusTypeDef ret = HAL_OK;      /* Intermediate status */

  /* Enable corresponding interrupt */
  IRQ_Enable(SGI0_IRQn);
  
  /* Enable write access to Backup domain */
  SET_BIT(PWR->CR1, PWR_CR1_DBP);

  /* Wait for Backup domain Write protection disable */
  tickstart = HAL_GetTick();

  while ((PWR->CR1 & PWR_CR1_DBP) == RESET)
  {
    if ((HAL_GetTick() - tickstart) > DBP_TIMEOUT_VALUE)
    {
      ret = HAL_TIMEOUT;
    }
  }

  if (ret == HAL_OK)
  {
    WRITE_REG(TAMP->SMCR, TAMP_SMCR_TAMPDPROT);
    WRITE_REG(TAMP->BKP5R, (uint32_t)(&Reset_Handler_cpu1));
    WRITE_REG(TAMP->BKP4R, 0xCA7FACE1);
    GIC_SendSGI(SGI0_IRQn, 2, 0);
  }

  return ret;
}


#endif