/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usb_otg.c
  * @brief   This file provides code for the configuration
  *          of the USB_OTG instances.
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
#include "usb_otg.h"

/* USER CODE BEGIN 0 */
#include "usbh_video.h"

USBH_HandleTypeDef usbhost;

static void USBH_User_Callback  (USBH_HandleTypeDef *phost, uint8_t id);

/* USER CODE END 0 */

HCD_HandleTypeDef hhcd_USB_OTG_HS;
ApplicationTypeDef appstate = APPLICATION_IDLE;

/* USB_OTG_HS init function */

void MX_USB_OTG_HS_HCD_Init(void)
{

  /* USER CODE BEGIN USB_OTG_HS_Init 0 */
//  USBH_StatusTypeDef status;

  /* USER CODE END USB_OTG_HS_Init 0 */

  /* USER CODE BEGIN USB_OTG_HS_Init 1 */
  // memset(&hhcd, 0, sizeof(HCD_HandleTypeDef));

  hhcd_USB_OTG_HS.pData = &usbhost;
  usbhost.pData = &hhcd_USB_OTG_HS;

  hhcd_USB_OTG_HS.Init.battery_charging_enable = ENABLE;
  hhcd_USB_OTG_HS.Init.lpm_enable = ENABLE;
  hhcd_USB_OTG_HS.Init.dev_endpoints = 0;			 // Not used for hosts?
  hhcd_USB_OTG_HS.Init.ep0_mps = EP_MPS_64;			 // Max packet size. Doesnt seem to be used?
  hhcd_USB_OTG_HS.Init.use_dedicated_ep1 = DISABLE;

  /* USER CODE END USB_OTG_HS_Init 1 */
  hhcd_USB_OTG_HS.Instance = USB_OTG_HS;
  hhcd_USB_OTG_HS.Init.Host_channels = 16;
  hhcd_USB_OTG_HS.Init.speed = USB_OTG_SPEED_HIGH;
  hhcd_USB_OTG_HS.Init.dma_enable = DISABLE;
  hhcd_USB_OTG_HS.Init.phy_itface = USB_OTG_HS_EMBEDDED_PHY;
  hhcd_USB_OTG_HS.Init.Sof_enable = DISABLE;
  hhcd_USB_OTG_HS.Init.low_power_enable = DISABLE;
  hhcd_USB_OTG_HS.Init.vbus_sensing_enable = DISABLE;
  hhcd_USB_OTG_HS.Init.use_external_vbus = ENABLE;
  USBH_Init(&usbhost, USBH_User_Callback, HOST_HS);
  if (HAL_HCD_Init(&hhcd_USB_OTG_HS) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_OTG_HS_Init 2 */
  USBH_RegisterClass(&usbhost, USBH_VIDEO_CLASS);
  USBH_Start(&usbhost);

  /* USER CODE END USB_OTG_HS_Init 2 */

}

void HAL_HCD_MspInit(HCD_HandleTypeDef* hcdHandle)
{

  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  if(hcdHandle->Instance==USB_OTG_HS)
  {
  /* USER CODE BEGIN USB_OTG_HS_MspInit 0 */
  IRQ_Disable(OTG_IRQn);
  IRQ_SetMode(OTG_IRQn, IRQ_MODE_TRIG_LEVEL|IRQ_MODE_CPU_0);

  /* USER CODE END USB_OTG_HS_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USBO | RCC_PERIPHCLK_USBPHY;
    PeriphClkInit.UsbphyClockSelection = RCC_USBPHYCLKSOURCE_HSE;
	PeriphClkInit.UsboClockSelection = RCC_USBOCLKSOURCE_PHY;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    /* USB_OTG_HS clock enable */
    __HAL_RCC_USBO_CLK_ENABLE();
    __HAL_RCC_USBPHY_CLK_ENABLE();

    /* USB_OTG_HS interrupt Init */
    /* USER CODE BEGIN YOUNGSEA */
    // SWITHOST 0: Select OTG controller for 2nd PHY port
    USBPHYC->MISC = (USBPHYC->MISC & ~(USBPHYC_MISC_SWITHOST_Msk | USBPHYC_MISC_PPCKDIS_Msk)) |
                    (0 << USBPHYC_MISC_SWITHOST_Pos) | (0 << USBPHYC_MISC_PPCKDIS_Pos);

    // May need this for FS:
    //
    // Set 3.3 volt DETECTOR enable
    // PWR->CR3 |= PWR_CR3_USB33DEN_Msk;
    // while ((PWR->CR3 & PWR_CR3_USB33DEN_Msk) == 0)
    // 	;
    // // Wait 3.3 volt REGULATOR ready
    // while ((PWR->CR3 & PWR_CR3_USB33RDY_Msk) == 0)
    // 	;

    IRQ_ClearPending(OTG_IRQn);
    /* USER CODE END YOUNGSEA */
    IRQ_SetPriority(OTG_IRQn, 0);
    IRQ_Enable(OTG_IRQn);
  /* USER CODE BEGIN USB_OTG_HS_MspInit 1 */

  /* USER CODE END USB_OTG_HS_MspInit 1 */
  }
}

void HAL_HCD_MspDeInit(HCD_HandleTypeDef* hcdHandle)
{

  if(hcdHandle->Instance==USB_OTG_HS)
  {
  /* USER CODE BEGIN USB_OTG_HS_MspDeInit 0 */

  /* USER CODE END USB_OTG_HS_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USBO_CLK_DISABLE();
    __HAL_RCC_USBPHY_CLK_DISABLE();

    /* USB_OTG_HS interrupt Deinit */
    IRQ_Disable(OTG_IRQn);
  /* USER CODE BEGIN USB_OTG_HS_MspDeInit 1 */

  /* USER CODE END USB_OTG_HS_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
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

/* USER CODE END 1 */
