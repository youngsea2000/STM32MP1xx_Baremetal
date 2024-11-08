/**
  ******************************************************************************
  * @file    usbh_conf.c
  * @author  MCD Application Team
  * @brief   This file implements the board support package for the USB host library
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2015 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usbh_core.h"
#include "main.h"

/**
  * @brief  USBH_LL_Init
  *         Initialize the Low Level portion of the Host driver.
  * @param  phost: Host handle
  * @retval USBH Status
  */
USBH_StatusTypeDef USBH_LL_Init(USBH_HandleTypeDef *phost)
{
  /* Init USB_IP */
  // if (phost->id == HOST_FS) {
  // /* Link The driver to the stack */
  // hhcd_USB_OTG_FS.pData = phost;
  // phost->pData = &hhcd_USB_OTG_FS;

  // hhcd_USB_OTG_FS.Instance = USB_OTG_FS;
  // hhcd_USB_OTG_FS.Init.Host_channels = 8;
  // hhcd_USB_OTG_FS.Init.speed = HCD_SPEED_FULL;
  // hhcd_USB_OTG_FS.Init.dma_enable = DISABLE;
  // hhcd_USB_OTG_FS.Init.phy_itface = HCD_PHY_EMBEDDED;
  // hhcd_USB_OTG_FS.Init.Sof_enable = DISABLE;
//  if (HAL_HCD_Init((HCD_HandleTypeDef *)phost->pData) != HAL_OK)
//  {
//    Error_Handler();
//    return USBH_FAIL;
//  }

  USBH_LL_SetTimer(phost, HAL_HCD_GetCurrentFrame((HCD_HandleTypeDef *) phost->pData));
  // }
  return USBH_OK;
}

/**
  * @brief  USBH_LL_DeInit
  *         De-Initialize the Low Level portion of the Host driver.
  * @param  phost: Host handle
  * @retval USBH Status
  */
USBH_StatusTypeDef USBH_LL_DeInit(USBH_HandleTypeDef *phost)
{
  HAL_StatusTypeDef hal_status = HAL_OK;
  USBH_StatusTypeDef usb_status = USBH_OK;
 
  hal_status = HAL_HCD_DeInit(phost->pData);
  
  switch (hal_status)
  {
    case HAL_OK :
      usb_status = USBH_OK;
      break;
    case HAL_ERROR :
      usb_status = USBH_FAIL;
      break;
    case HAL_BUSY :
      usb_status = USBH_BUSY;
      break;
    case HAL_TIMEOUT :
      usb_status = USBH_FAIL;
      break;
    default :
      usb_status = USBH_FAIL;
      break;
  }
  return usb_status;
}

/**
  * @brief  USBH_LL_Start
  *         Start the Low Level portion of the Host driver.
  * @param  phost: Host handle
  * @retval USBH Status
  */
USBH_StatusTypeDef USBH_LL_Start(USBH_HandleTypeDef *phost)
{
  HAL_StatusTypeDef hal_status = HAL_OK;
  USBH_StatusTypeDef usb_status = USBH_OK;
 
  hal_status = HAL_HCD_Start((HCD_HandleTypeDef *) phost->pData);
  
  switch (hal_status)
  {
    case HAL_OK :
      usb_status = USBH_OK;
      break;
    case HAL_ERROR :
      usb_status = USBH_FAIL;
      break;
    case HAL_BUSY :
      usb_status = USBH_BUSY;
      break;
    case HAL_TIMEOUT :
      usb_status = USBH_FAIL;
      break;
    default :
      usb_status = USBH_FAIL;
      break;
  }
  return usb_status;
}

/**
  * @brief  USBH_LL_Stop
  *         Stop the Low Level portion of the Host driver.
  * @param  phost: Host handle
  * @retval USBH Status
  */
USBH_StatusTypeDef USBH_LL_Stop(USBH_HandleTypeDef *phost)
{
  HAL_StatusTypeDef hal_status = HAL_OK;
  USBH_StatusTypeDef usb_status = USBH_OK;

  hal_status = HAL_HCD_Stop((HCD_HandleTypeDef *) phost->pData);
  
  switch (hal_status)
  {
    case HAL_OK :
      usb_status = USBH_OK;
      break;
    case HAL_ERROR :
      usb_status = USBH_FAIL;
      break;
    case HAL_BUSY :
      usb_status = USBH_BUSY;
      break;
    case HAL_TIMEOUT :
      usb_status = USBH_FAIL;
      break;
    default :
      usb_status = USBH_FAIL;
      break;
  }
  return usb_status; 
}

/**
  * @brief  USBH_LL_GetSpeed
  *         Return the USB Host Speed from the Low Level Driver.
  * @param  phost: Host handle
  * @retval USBH Speeds
  */
USBH_SpeedTypeDef USBH_LL_GetSpeed(USBH_HandleTypeDef *phost)
{
  USBH_SpeedTypeDef speed = USBH_SPEED_FULL;

  switch (HAL_HCD_GetCurrentSpeed((HCD_HandleTypeDef *) phost->pData))
  {
    case 0 :
      speed = USBH_SPEED_HIGH;
      break;

    case 1 :
      speed = USBH_SPEED_FULL;
      break;

    case 2 :
      speed = USBH_SPEED_LOW;
      break;

    default :
      speed = USBH_SPEED_FULL;
      break;
  }
  return  speed;
}

/**
  * @brief  USBH_LL_ResetPort
  *         Reset the Host Port of the Low Level Driver.
  * @param  phost: Host handle
  * @retval USBH Status
  */
USBH_StatusTypeDef USBH_LL_ResetPort(USBH_HandleTypeDef *phost)
{
  HAL_StatusTypeDef hal_status = HAL_OK;
  USBH_StatusTypeDef usb_status = USBH_OK;
 
  hal_status = HAL_HCD_ResetPort(phost->pData);
  switch (hal_status)
  {
    case HAL_OK :
      usb_status = USBH_OK;
      break;
    case HAL_ERROR :
      usb_status = USBH_FAIL;
      break;
    case HAL_BUSY :
      usb_status = USBH_BUSY;
      break;
    case HAL_TIMEOUT :
      usb_status = USBH_FAIL;
      break;
    default :
      usb_status = USBH_FAIL;
      break;
  }
  return usb_status;
}

/**
  * @brief  USBH_LL_GetLastXferSize
  *         Return the last transferred packet size.
  * @param  phost: Host handle
  * @param  pipe: Pipe index
  * @retval Packet Size
  */
uint32_t USBH_LL_GetLastXferSize(USBH_HandleTypeDef *phost, uint8_t pipe)
{
  return HAL_HCD_HC_GetXferCount( (HCD_HandleTypeDef *) phost->pData, pipe);
}

/**
  * @brief  USBH_LL_OpenPipe
  *         Open a pipe of the Low Level Driver.
  * @param  phost: Host handle
  * @param  pipe_num: Pipe index
  * @param  epnum: Endpoint Number
  * @param  dev_address: Device USB address
  * @param  speed: Device Speed
  * @param  ep_type: Endpoint Type
  * @param  mps: Endpoint Max Packet Size
  * @retval USBH Status
  */
USBH_StatusTypeDef USBH_LL_OpenPipe(USBH_HandleTypeDef *phost,
                                    uint8_t pipe_num,
                                    uint8_t epnum,
                                    uint8_t dev_address,
                                    uint8_t speed,
                                    uint8_t ep_type,
                                    uint16_t mps)
{
  HAL_StatusTypeDef hal_status = HAL_OK;
  USBH_StatusTypeDef usb_status = USBH_OK;

  hal_status = HAL_HCD_HC_Init(
    (HCD_HandleTypeDef *) phost->pData,
                          pipe_num,
                          epnum,
                          dev_address,
                          speed,
                          ep_type,
                          mps);
  switch (hal_status)
  {
    case HAL_OK :
      usb_status = USBH_OK;
      break;
    case HAL_ERROR :
      usb_status = USBH_FAIL;
      break;
    case HAL_BUSY :
      usb_status = USBH_BUSY;
      break;
    case HAL_TIMEOUT :
      usb_status = USBH_FAIL;
      break;
    default :
      usb_status = USBH_FAIL;
      break;
  }
  return usb_status;
}

/**
  * @brief  USBH_LL_ClosePipe
  *         Close a pipe of the Low Level Driver.
  * @param  phost: Host handle
  * @param  pipe_num: Pipe index
  * @retval USBH Status
  */
USBH_StatusTypeDef USBH_LL_ClosePipe(USBH_HandleTypeDef *phost, uint8_t pipe)
{
  HAL_StatusTypeDef hal_status = HAL_OK;
  USBH_StatusTypeDef usb_status = USBH_OK;

  hal_status = HAL_HCD_HC_Halt((HCD_HandleTypeDef *) phost->pData, pipe);
  switch (hal_status)
  {
    case HAL_OK :
      usb_status = USBH_OK;
      break;
    case HAL_ERROR :
      usb_status = USBH_FAIL;
      break;
    case HAL_BUSY :
      usb_status = USBH_BUSY;
      break;
    case HAL_TIMEOUT :
      usb_status = USBH_FAIL;
      break;
    default :
      usb_status = USBH_FAIL;
      break;
  }
  return usb_status;  
}

/**
  * @brief  USBH_LL_SubmitURB
  *         Submit a new URB to the low level driver.
  * @param  phost: Host handle
  * @param  pipe: Pipe index
  *         This parameter can be a value from 1 to 15
  * @param  direction : Channel number
  *          This parameter can be one of the these values:
  *           0 : Output
  *           1 : Input
  * @param  ep_type : Endpoint Type
  *          This parameter can be one of the these values:
  *            @arg EP_TYPE_CTRL: Control type
  *            @arg EP_TYPE_ISOC: Isochronous type
  *            @arg EP_TYPE_BULK: Bulk type
  *            @arg EP_TYPE_INTR: Interrupt type
  * @param  token : Endpoint Type
  *          This parameter can be one of the these values:
  *            @arg 0: PID_SETUP
  *            @arg 1: PID_DATA
  * @param  pbuff : pointer to URB data
  * @param  length : Length of URB data
  * @param  do_ping : activate do ping protocol (for high speed only)
  *          This parameter can be one of the these values:
  *           0 : do ping inactive
  *           1 : do ping active
  * @retval Status
  */
USBH_StatusTypeDef USBH_LL_SubmitURB(USBH_HandleTypeDef *phost,
                                     uint8_t pipe,
                                     uint8_t direction,
                                     uint8_t ep_type,
                                     uint8_t token,
                                     uint8_t *pbuff,
                                     uint16_t length,
                                     uint8_t do_ping)
{
  HAL_StatusTypeDef hal_status = HAL_OK;
  USBH_StatusTypeDef usb_status = USBH_OK;

  hal_status = HAL_HCD_HC_SubmitRequest(
    (HCD_HandleTypeDef *) phost->pData,
                          pipe,
                          direction,
                          ep_type,
                          token,
                          pbuff,
                          length,
                          do_ping);
  switch (hal_status)
  {
    case HAL_OK :
      usb_status = USBH_OK;
      break;
    case HAL_ERROR :
      usb_status = USBH_FAIL;
      break;
    case HAL_BUSY :
      usb_status = USBH_BUSY;
      break;
    case HAL_TIMEOUT :
      usb_status = USBH_FAIL;
      break;
    default :
      usb_status = USBH_FAIL;
      break;
  }
  return usb_status;  
}

/**
  * @brief  USBH_LL_GetURBState
  *         Get a URB state from the low level driver.
  * @param  phost: Host handle
  * @param  pipe: Pipe index
  *         This parameter can be a value from 1 to 15
  * @retval URB state
  *          This parameter can be one of the these values:
  *            @arg URB_IDLE
  *            @arg URB_DONE
  *            @arg URB_NOTREADY
  *            @arg URB_NYET
  *            @arg URB_ERROR
  *            @arg URB_STALL
  */
USBH_URBStateTypeDef USBH_LL_GetURBState(USBH_HandleTypeDef *phost, uint8_t pipe)
{
  return HAL_HCD_HC_GetURBState((HCD_HandleTypeDef *) phost->pData, pipe);
}

/**
  * @brief  USBH_LL_DriverVBUS
  *         Drive VBUS.
  * @param  phost: Host handle
  * @param  state : VBUS state
  *          This parameter can be one of the these values:
  *           0 : VBUS Inactive
  *           1 : VBUS Active
  * @retval Status
  */
USBH_StatusTypeDef USBH_LL_DriverVBUS(USBH_HandleTypeDef *phost, uint8_t state)
{
  if (state == 0)
  {
    HAL_GPIO_WritePin(GPIOZ,GPIO_PIN_6,GPIO_PIN_RESET);
  }
  else
  {
    HAL_GPIO_WritePin(GPIOZ,GPIO_PIN_6,GPIO_PIN_SET);
  }
  HAL_Delay(200);
  return USBH_OK;
}

/**
  * @brief  USBH_LL_SetToggle
  *         Set toggle for a pipe.
  * @param  phost: Host handle
  * @param  pipe: Pipe index
  * @param  pipe_num: Pipe index
  * @param  toggle: toggle (0/1)
  * @retval Status
  */
USBH_StatusTypeDef USBH_LL_SetToggle(USBH_HandleTypeDef *phost, uint8_t pipe, uint8_t toggle)
{
  HCD_HandleTypeDef *hhcd = (HCD_HandleTypeDef *) phost->pData;
  if(hhcd->hc[pipe].ep_is_in)
  {
    hhcd->hc[pipe].toggle_in = toggle;
  }
  else
  {
    hhcd->hc[pipe].toggle_out = toggle;
  }
  return USBH_OK;
}

/**
  * @brief  USBH_LL_GetToggle
  *         Return the current toggle of a pipe.
  * @param  phost: Host handle
  * @param  pipe: Pipe index
  * @retval toggle (0/1)
  */
uint8_t USBH_LL_GetToggle(USBH_HandleTypeDef *phost, uint8_t pipe)
{
  HCD_HandleTypeDef *hhcd = (HCD_HandleTypeDef *) phost->pData;
  uint8_t toggle = 0U;
  
  if(hhcd->hc[pipe].ep_is_in)
  {
    toggle = hhcd->hc[pipe].toggle_in;
  }
  else
  {
    toggle = hhcd->hc[pipe].toggle_out;
  }
  return toggle;
}

/**
  * @brief  USBH_Delay
  *         Delay routine for the USB Host Library
  * @param  Delay: Delay in ms
  * @retval None
  */
void USBH_Delay(uint32_t Delay)
{
  HAL_Delay(Delay);
}
