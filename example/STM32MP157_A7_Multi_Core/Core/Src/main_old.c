/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
// #include <stdio.h>
#include <stdbool.h>
#include "usb_otg.h"
#include "usart.h"
#include "usbh_core.h"
#include "usbh_video.h"
#include "usbh_video_desc_parsing.h"
#include "usbh_video_stream_parsing.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define SRAM_FREE_ADDR 0xE0000000
#define UVC_FRAMEBUFFER0        (SRAM_FREE_ADDR)
#define UVC_FRAMEBUFFER1        (UVC_FRAMEBUFFER0 + UVC_MAX_FRAME_SIZE)

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
HCD_HandleTypeDef  hhcd;
extern ApplicationTypeDef appstate;
const char *global_constant_string = "And hi to you too!\r\n";

//uint32_t frame_cnt = 0;//Drawn frames counter
//uint32_t prev_frame_cnt = 0;
//uint32_t timestamp_1sec = 0;
//uint8_t last_fps = 0;
//uint8_t frame_received_flag = 0;
//// extern uint32_t uvc_frame_cnt;
//extern uint8_t uvc_parsing_new_frame_ready;
//extern uint8_t* uvc_ready_framebuffer_ptr;
//// extern uint32_t uvc_ready_frame_length;
//// extern USBH_VIDEO_TargetFormat_t USBH_VIDEO_Target_Format;
//
//volatile uint32_t decode_time = 0;//debug only

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USBH_HS1_USB_Init(void);
static bool MX_USB_OTG_HS_USB_Init(void);
/* USER CODE BEGIN PFP */
static void USBH_User_Callback  (USBH_HandleTypeDef *phost, uint8_t id);

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
  // SystemCoreClockUpdate();
  HAL_Init();

  /* USER CODE BEGIN Init */
  
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USBH_HS1_USB_Init();
  MX_UART4_Init();
  /* USER CODE BEGIN 2 */
  printf("\r\nHello from HAL Driver!\r\n");
  printf("MPU_CLK: %ldMHz\r\n", HAL_RCC_GetMPUSSFreq());
  printf("AXI_CLK: %ldMHz\r\n", HAL_RCC_GetAXISSFreq());
  printf("MCU_CLK: %ldMHz\r\n", HAL_RCC_GetMCUSSFreq());
  if (!MX_USB_OTG_HS_USB_Init()) {
    printf("USB Host failed to initialize!\n");
  }

  video_stream_init_buffers((uint8_t*)UVC_FRAMEBUFFER0, (uint8_t*)UVC_FRAMEBUFFER1);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
//    USBH_Process(&usbhost);
//    if (uvc_parsing_new_frame_ready)
//    {
//      uvc_parsing_new_frame_ready = 0;
//
//      // if (frame_received_flag == 0)
//      // {
//      //   //First frame from camera - switch to LCD dual buffer mode
//      //   frame_received_flag = 1;
//      //   HAL_Delay(1000);
//
//      //   lcd_clear(LCD_COLOR_WHITE);//clear buffer0
//      //   lcd_switch_buffer();
//      //   lcd_switch_buffer();//make shadow buffer = buffer1
//      //   lcd_clear(LCD_COLOR_WHITE);//clear buffer1
//      // }
//
//      uint32_t start_decode_time = HAL_GetTick();
//      //Draw captured image
//      // if (USBH_VIDEO_Target_Format == USBH_VIDEO_YUY2)
//      // {
//      //   lcd_draw_yuyv_picture((uint8_t*)uvc_ready_framebuffer_ptr);
//      // }
//      // else
//      // {
//      //   mjpeg_decompression_and_draw((uint8_t*)uvc_ready_framebuffer_ptr, uvc_ready_frame_length);
//      // }
//      decode_time = HAL_GetTick() - start_decode_time;//debug only
//
//      //Draw FPS
//      uint8_t tmp_str[32];
//      sprintf((char*)tmp_str, "FPS: %d   \n", last_fps);
//      printf("%s",tmp_str);
//      // LCD_DisplayStringLine(LCD_PIXEL_HEIGHT - 20, tmp_str);
//
//      // lcd_switch_buffer();
//
//      video_stream_ready_update();
//      frame_cnt++;
//      HAL_GPIO_TogglePin(GPIOI,GPIO_PIN_0);//Blink LED
//    }
//
//    //Calculate FPS
//    if ((HAL_GetTick() - timestamp_1sec) > 1000)// 1000ms
//    {
//      timestamp_1sec = HAL_GetTick();
//      last_fps = frame_cnt - prev_frame_cnt;
//      prev_frame_cnt = frame_cnt;
//    }
    HAL_Delay(1000);
    HAL_GPIO_TogglePin(GPIOI,GPIO_PIN_0);
    HAL_GPIO_TogglePin(GPIOF,GPIO_PIN_3);

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
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_MPU | RCC_CLOCKTYPE_ACLK | RCC_CLOCKTYPE_HCLK /* <-- MCU Clock */ |
       RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 | RCC_CLOCKTYPE_PCLK3 | RCC_CLOCKTYPE_PCLK4 |
       RCC_CLOCKTYPE_PCLK5;
  RCC_ClkInitStruct.MPUInit.MPU_Clock = RCC_MPUSOURCE_HSI;
  RCC_ClkInitStruct.MPUInit.MPU_Div = RCC_MPU_DIV2;
  RCC_ClkInitStruct.AXISSInit.AXI_Clock = RCC_AXISSOURCE_HSI;
  RCC_ClkInitStruct.AXISSInit.AXI_Div = RCC_AXI_DIV1;
  RCC_ClkInitStruct.MCUInit.MCU_Clock = RCC_MCUSSOURCE_HSI;
  RCC_ClkInitStruct.MCUInit.MCU_Div = RCC_MCU_DIV1;
  RCC_ClkInitStruct.APB4_Div = RCC_APB4_DIV2;
  RCC_ClkInitStruct.APB5_Div = RCC_APB5_DIV4;
  RCC_ClkInitStruct.APB1_Div = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2_Div = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB3_Div = RCC_APB3_DIV2;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_MEDIUMHIGH);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLL12SOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 3;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = 1;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLFRACV = 0;
  RCC_OscInitStruct.PLL.PLLMODE = RCC_PLL_INTEGER;
  RCC_OscInitStruct.PLL2.PLLState = RCC_PLL_NONE;
  RCC_OscInitStruct.PLL2.PLLSource = RCC_PLL12SOURCE_HSE;
  RCC_OscInitStruct.PLL2.PLLM = 3;
  RCC_OscInitStruct.PLL2.PLLN = 66;
  RCC_OscInitStruct.PLL2.PLLP = 2;
  RCC_OscInitStruct.PLL2.PLLQ = 1;
  RCC_OscInitStruct.PLL2.PLLR = 1;
  RCC_OscInitStruct.PLL2.PLLFRACV = 5120;
  RCC_OscInitStruct.PLL2.PLLMODE = RCC_PLL_FRACTIONAL;
  RCC_OscInitStruct.PLL3.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL3.PLLSource = RCC_PLL3SOURCE_HSE;
  RCC_OscInitStruct.PLL3.PLLM = 2;
  RCC_OscInitStruct.PLL3.PLLN = 52;
  RCC_OscInitStruct.PLL3.PLLP = 3;
  RCC_OscInitStruct.PLL3.PLLQ = 17;
  RCC_OscInitStruct.PLL3.PLLR = 37;
  RCC_OscInitStruct.PLL3.PLLRGE = RCC_PLL3IFRANGE_1;
  RCC_OscInitStruct.PLL3.PLLFRACV = 2048;
  RCC_OscInitStruct.PLL3.PLLMODE = RCC_PLL_FRACTIONAL;
  RCC_OscInitStruct.PLL4.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL4.PLLSource = RCC_PLL4SOURCE_HSE;
  RCC_OscInitStruct.PLL4.PLLM = 4;
  RCC_OscInitStruct.PLL4.PLLN = 9;
  RCC_OscInitStruct.PLL4.PLLP = 6;
  RCC_OscInitStruct.PLL4.PLLQ = 8;
  RCC_OscInitStruct.PLL4.PLLR = 8;
  RCC_OscInitStruct.PLL4.PLLRGE = RCC_PLL4IFRANGE_0;
  RCC_OscInitStruct.PLL4.PLLFRACV = 0x1000;
  RCC_OscInitStruct.PLL4.PLLMODE = RCC_PLL_INTEGER;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Set the HSE division factor for RTC clock
  */
  __HAL_RCC_RTC_HSEDIV(1);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_MPU | RCC_CLOCKTYPE_ACLK | RCC_CLOCKTYPE_HCLK /* <-- MCU Clock */ |
       RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 | RCC_CLOCKTYPE_PCLK3 | RCC_CLOCKTYPE_PCLK4 |
       RCC_CLOCKTYPE_PCLK5;
  RCC_ClkInitStruct.MPUInit.MPU_Clock = RCC_MPUSOURCE_PLL1;
  RCC_ClkInitStruct.AXISSInit.AXI_Clock = RCC_AXISSOURCE_PLL2;
  RCC_ClkInitStruct.MCUInit.MCU_Clock = RCC_MCUSSOURCE_PLL3;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USBH_HS1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USBH_HS1_USB_Init(void)
{

  /* USER CODE BEGIN USBH_HS1_Init 0 */

  /* USER CODE END USBH_HS1_Init 0 */

  /* USER CODE BEGIN USBH_HS1_Init 1 */

  /* USER CODE END USBH_HS1_Init 1 */
  /* USER CODE BEGIN USBH_HS1_Init 2 */

  /* USER CODE END USBH_HS1_Init 2 */

}

/**
  * @brief USB_OTG_HS Initialization Function
  * @param None
  * @retval None
  */
static bool MX_USB_OTG_HS_USB_Init(void)
{
  USBH_StatusTypeDef status;
  memset(&hhcd, 0, sizeof(HCD_HandleTypeDef));

  /* USER CODE BEGIN USB_OTG_HS_Init 0 */
  hhcd.Instance = USB_OTG_HS;
  hhcd.Init.Host_channels = 16;
  hhcd.Init.speed = HCD_SPEED_HIGH;
  hhcd.Init.dma_enable = DISABLE;
  hhcd.Init.phy_itface = USB_OTG_HS_EMBEDDED_PHY;
  hhcd.Init.Sof_enable = DISABLE;
  hhcd.Init.battery_charging_enable = ENABLE;
  hhcd.Init.lpm_enable = ENABLE;
  hhcd.Init.use_external_vbus = ENABLE;	 // Might only be used for ULPI?
  hhcd.Init.vbus_sensing_enable = DISABLE; // Doesn't seem to be used for hosts?
  hhcd.Init.low_power_enable = DISABLE;	 // Doesn't seem to be used?
  hhcd.Init.dev_endpoints = 0;			 // Not used for hosts?
  hhcd.Init.ep0_mps = EP_MPS_64;			 // Max packet size. Doesnt seem to be used?
  hhcd.Init.use_dedicated_ep1 = DISABLE;
  // Link The driver to the stack
  hhcd.pData = &usbhost;
  usbhost.pData = &hhcd;
  
  /* USER CODE END USB_OTG_HS_Init 0 */
  status = USBH_Init(&usbhost, USBH_User_Callback, HOST_HS);
  if (status != USBH_OK)
    return false;

  /* USER CODE BEGIN USB_OTG_HS_Init 1 */
  IRQ_Disable(OTG_IRQn);
  IRQ_SetPriority(OTG_IRQn, (0<<5)|(0<<3));
  IRQ_SetMode(OTG_IRQn, IRQ_MODE_TRIG_LEVEL|IRQ_MODE_CPU_0);
  IRQ_ClearPending(OTG_IRQn);
  IRQ_Enable(OTG_IRQn);
  /* USER CODE END USB_OTG_HS_Init 1 */
  USBH_RegisterClass(&usbhost, USBH_VIDEO_CLASS);
  USBH_Start(&usbhost);
  /* USER CODE BEGIN USB_OTG_HS_Init 2 */
  return true;
  /* USER CODE END USB_OTG_HS_Init 2 */
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOI_CLK_ENABLE();
  __HAL_RCC_GPIOZ_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF,GPIO_PIN_3,GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOI,GPIO_PIN_0,GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOZ,GPIO_PIN_6,GPIO_PIN_RESET);

  /*Configure GPIO pin : PF3 */
  GPIO_InitStruct.Pin = GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pin : PI0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

  /*Configure GPIO pin : PZ6 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOZ, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
static void USBH_User_Callback  (USBH_HandleTypeDef *phost, uint8_t id)
{
  switch(id)
  {
    case HOST_USER_CLASS_SELECTED:
			printf("Class selected\n");
    {
      USBH_StatusTypeDef status;
      status = USBH_VS_SetCur(phost, VS_PROBE_CONTROL << 8);
      status = USBH_VS_GetCur(phost, VS_PROBE_CONTROL << 8);
      if (status == USBH_OK)
      {
        USBH_VS_SetCur(phost, VS_COMMIT_CONTROL << 8);
        //USBH_VS_GetCur(phost, VS_COMMIT_CONTROL << 8);// not necessary
      }
    }
    break;
    
    case HOST_USER_SELECT_CONFIGURATION:
			printf("Select config\n");
    break;
    
    case HOST_USER_DISCONNECTION:
			printf("Disconnected\n");
      appstate = APPLICATION_DISCONNECT;
    break;
    
    case HOST_USER_CLASS_ACTIVE:
      printf("Class active\n");
      appstate = APPLICATION_READY;
    break;
    
    case HOST_USER_CONNECTION:
			printf("Connected\n");
      appstate = APPLICATION_START;
    break;
    
    case HOST_USER_UNRECOVERED_ERROR:
      printf("Error\n");
    break;

    default:
    break;
  }
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
