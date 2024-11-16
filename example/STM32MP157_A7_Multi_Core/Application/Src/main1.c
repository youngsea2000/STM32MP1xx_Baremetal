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
#include "gpio.h"
enum { MagicNumberValue = 0xCA7FACE1 };
void Reset_Handler_cpu1(void);

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
  printf("\r\nHello from Core1!\r\n");

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    HAL_Delay(1000);
    // printf("Hello %d\r\n",cnt++);
    // HAL_GPIO_TogglePin(DS0_RED_GPIO_Port,DS0_RED_Pin);
    HAL_GPIO_TogglePin(DS1_GREEN_GPIO_Port,DS1_GREEN_Pin);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */
#ifdef USE_SECOND_A7_CORE
void start_core1(void)
{
  IRQ_Enable(SGI0_IRQn);
  // Turn on the Disable Backup Protection bit, to allow us to write to
  // the TAMP backup registers This is already on if we just booted from
  // U-boot, but if we are debugging and manually reset the code, we'll
  // want to be sure.
  PWR->CR1 = PWR->CR1 | PWR_CR1_DBP;
  while (!(PWR->CR1 & PWR_CR1_DBP)){};
  // Turn off Write protection on backup registers (BOOTROM seems to turn
  // it on for Backup registers 0-4 during MPU1 boot-up)
  TAMP->SMCR = (0 << TAMP_SMCR_BKPRWDPROT_Pos) | (0 << TAMP_SMCR_BKPWDPROT_Pos) | (1 << TAMP_SMCR_TAMPDPROT_Pos);
  uint32_t core1_start_addr = (uint32_t)(&Reset_Handler_cpu1);
  TAMP->BKP5R = core1_start_addr;
  TAMP->BKP4R = MagicNumberValue;
  const uint32_t filter_use_cpu_sel_bits = 0b00;
  const uint32_t cpu1 = 1 << 1;
  GIC_SendSGI(SGI0_IRQn, cpu1, filter_use_cpu_sel_bits);
}
#endif