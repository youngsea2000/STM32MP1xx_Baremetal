/**
  ******************************************************************************
  * @file    stm32mp1xx_hal_callback.c
  * @author  Callback Application Team
  * @brief   HAL Callback module.
  *          This file template is located in the HAL folder and should be copied 
  *          to the user folder.
  *         
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  @verbatim
 ===============================================================================
                     ##### How to use this driver #####
 ===============================================================================
    [..]

  @endverbatim
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32mp1xx_hal.h"
#include "usbh_core.h"

/** @addtogroup STM32MP1xx_HAL_Driver
  * @{
  */

/** @defgroup HAL_Callback HAL Callback module driver
  * @brief HAL Callback module.
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup HAL_Callback_Private_Functions HAL Callback Private Functions
  * @{
  */

/**
  * @brief  SOF callback.
  * @param  hhcd HCD handle
  * @retval None
  */
void HAL_HCD_SOF_Callback(HCD_HandleTypeDef *hhcd)
{
  USBH_LL_IncTimer((USBH_HandleTypeDef *) hhcd->pData);
}

/**
 * @brief  Connect callback.
 * @param  hhcd: HCD handle
 * @retval None
 */
void HAL_HCD_Connect_Callback(HCD_HandleTypeDef *hhcd)
{
  USBH_LL_Connect((USBH_HandleTypeDef *) hhcd->pData);
}

/**
 * @brief  Disconnect callback.
 * @param  hhcd: HCD handle
 * @retval None
 */
void HAL_HCD_Disconnect_Callback(HCD_HandleTypeDef *hhcd)
{
  USBH_LL_Disconnect((USBH_HandleTypeDef *) hhcd->pData);
}

/**
 * @brief  Port Port Enabled callback.
 * @param  hhcd: HCD handle
 * @retval None
 */
void HAL_HCD_PortEnabled_Callback(HCD_HandleTypeDef *hhcd)
{
  USBH_LL_PortEnabled((USBH_HandleTypeDef *) hhcd->pData);
}

/**
 * @brief  Port Port Disabled callback.
 * @param  hhcd: HCD handle
 * @retval None
 */
void HAL_HCD_PortDisabled_Callback(HCD_HandleTypeDef *hhcd)
{
  USBH_LL_PortDisabled((USBH_HandleTypeDef *) hhcd->pData);
}

/**
 * @brief  Notify URB state change callback.
 * @param  hhcd: HCD handle
 * @param  chnum: Channel number
 * @param  urb_state: URB State
 * @retval None
 */
void HAL_HCD_HC_NotifyURBChange_Callback(HCD_HandleTypeDef *hhcd, uint8_t chnum, HCD_URBStateTypeDef urb_state)
{
	/* To be used with OS to sync URB state with the global state machine */
#if (USBH_USE_OS == 1)   
	USBH_LL_NotifyURBChange(hhcd->phost);
#endif 
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
