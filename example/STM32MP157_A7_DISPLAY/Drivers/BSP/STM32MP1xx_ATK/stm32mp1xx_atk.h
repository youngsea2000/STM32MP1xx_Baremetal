/**
  ******************************************************************************
  * @file    stm32mp1xx_atk.h
  * @author  MCD Application Team
  * @brief   This file contains definitions for STM32MP1xx_ATK LEDs,
  *          push-buttons and COM ports hardware resources.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2020-2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32MP1XX_ATK_H
#define __STM32MP1XX_ATK_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp1xx_hal.h"

#include "stm32mp1xx_atk_conf.h"
#include "stm32mp1xx_atk_errno.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32MP1XX_ATK STM32MP1XX_ATK
  * @{
  */

/** @defgroup STM32MP1XX_ATK_LOW_LEVEL_Exported_Types Exported Types
  * @{
  */

 typedef enum
{
LED0 = 0U,
LED_RED = LED0,
LED1 = 1U,
LED_GREEN = LED1,
LEDn
}Led_TypeDef;


typedef enum
{
  BUTTON_WAKEUP = 0U,
  BUTTON_KEY0 = 1U,
  BUTTON_KEY1 = 2U,
  BUTTONn
}Button_TypeDef;

typedef enum 
{  
  BUTTON_MODE_GPIO = 0U,
  BUTTON_MODE_EXTI = 1U
}ButtonMode_TypeDef;

#if (USE_BSP_COM_FEATURE == 1)
typedef enum
{
  COM1 = 0U,
  COMn
}COM_TypeDef;

#ifdef HAL_UART_MODULE_ENABLED
typedef enum
{
 COM_STOPBITS_1     =   UART_STOPBITS_1,
 COM_STOPBITS_2     =   UART_STOPBITS_2,
}COM_StopBitsTypeDef;

typedef enum
{
 COM_PARITY_NONE     =  UART_PARITY_NONE,
 COM_PARITY_EVEN     =  UART_PARITY_EVEN,
 COM_PARITY_ODD      =  UART_PARITY_ODD,
}COM_ParityTypeDef;


typedef enum
{
 COM_HWCONTROL_NONE    =  UART_HWCONTROL_NONE,
 COM_HWCONTROL_RTS     =  UART_HWCONTROL_RTS,
 COM_HWCONTROL_CTS     =  UART_HWCONTROL_CTS,
 COM_HWCONTROL_RTS_CTS =  UART_HWCONTROL_RTS_CTS,
}COM_HwFlowCtlTypeDef;

typedef struct
{
  uint32_t             BaudRate;
  uint32_t             WordLength;
  COM_StopBitsTypeDef  StopBits;
  COM_ParityTypeDef    Parity;
  COM_HwFlowCtlTypeDef HwFlowCtl;
}COM_InitTypeDef;
#endif

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
typedef struct
{
  pUART_CallbackTypeDef  pMspInitCb;
  pUART_CallbackTypeDef  pMspDeInitCb;
}BSP_COM_Cb_t;
#endif /* (USE_HAL_UART_REGISTER_CALLBACKS == 1) */
#endif /* (USE_BSP_COM_FEATURE == 1) */

/**
  * @}
  */

/** @defgroup STM32MP1XX_ATK_LOW_LEVEL_Exported_Constants Exported Constants
  * @{
  */

/**
  * @brief  Define for STM32MP1XX_ATK board
  */
#if !defined (USE_STM32MP1XX_ATK)
 #define USE_STM32MP1XX_ATK
#endif


/**
  * @}
  */

  /** @addtogroup STM32MP1XX_ATK_LOW_LEVEL_Exported_Constants Exported Constants
  * @{
  */

/** @addtogroup STM32MP1XX_ATK_LOW_LEVEL_Exported_Constants_Group1 LED Constants
  * @{
  */

#define LED0_GPIO_PORT                   GPIOI
#define LED0_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOI_CLK_ENABLE()
#define LED0_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOI_CLK_DISABLE()
#define LED0_PIN                         GPIO_PIN_0

#define LED1_GPIO_PORT                   GPIOF
#define LED1_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOF_CLK_ENABLE()
#define LED1_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOF_CLK_DISABLE()
#define LED1_PIN                         GPIO_PIN_3

/**
  * @}
  */

/** @addtogroup STM32MP1XX_ATK_LOW_LEVEL_Exported_Constants_Group2 BUTTON Constants
  * @{
  */

/* Button state */
#define BUTTON_RELEASED                     1U
#define BUTTON_PRESSED                      0U

/**
  * @brief Wakeup push-button
  */
#define WAKEUP_BUTTON_PIN                   GPIO_PIN_0
#define WAKEUP_BUTTON_GPIO_PORT             GPIOA
#define WAKEUP_BUTTON_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOA_CLK_ENABLE()
#define WAKEUP_BUTTON_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOA_CLK_DISABLE()
#define WAKEUP_BUTTON_EXTI_LINE             EXTI_LINE_0
#define WAKEUP_BUTTON_EXTI_IRQn             EXTI0_IRQn

/**
  * @brief User push-button
  */
#define KEY0_BUTTON_PIN                       GPIO_PIN_3
#define KEY0_BUTTON_GPIO_PORT                 GPIOG
#define KEY0_BUTTON_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOG_CLK_ENABLE()
#define KEY0_BUTTON_GPIO_CLK_DISABLE()        __HAL_RCC_GPIOG_CLK_DISABLE()
#define KEY0_BUTTON_EXTI_LINE                 EXTI_LINE_3
#define KEY0_BUTTON_EXTI_IRQn                 EXTI3_IRQn

/**
  * @brief User2 push-button
  */
#define KEY1_BUTTON_PIN                       GPIO_PIN_7
#define KEY1_BUTTON_GPIO_PORT                 GPIOH
#define KEY1_BUTTON_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOH_CLK_ENABLE()
#define KEY1_BUTTON_GPIO_CLK_DISABLE()        __HAL_RCC_GPIOH_CLK_DISABLE()
#define KEY1_BUTTON_EXTI_LINE                 EXTI_LINE_7
#define KEY1_BUTTON_EXTI_IRQn                 EXTI7_IRQn


/**
  * @}
  */

/** @addtogroup STM32MP1XX_ATK_LOW_LEVEL_Exported_Constants_Group3 COM Constants
  * @{
  */

/**
 * @brief Definition for COM port1, connected to UART4
 */
#if (USE_BSP_COM_FEATURE == 1)
#define COM1_UART                     UART4
#define COM1_CLK_ENABLE()             __HAL_RCC_UART4_CLK_ENABLE()
#define COM1_CLK_DISABLE()            __HAL_RCC_UART4_CLK_DISABLE()

#define COM1_TX_PIN                   GPIO_PIN_11
#define COM1_TX_GPIO_PORT             GPIOG
#define COM1_TX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOG_CLK_ENABLE()
#define COM1_TX_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOG_CLK_DISABLE()
#define COM1_TX_AF                    GPIO_AF6_UART4

#define COM1_RX_PIN                   GPIO_PIN_2
#define COM1_RX_GPIO_PORT             GPIOB
#define COM1_RX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOB_CLK_ENABLE()
#define COM1_RX_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOB_CLK_DISABLE()
#define COM1_RX_AF                    GPIO_AF8_UART4

#define COM1_POLL_TIMEOUT             1000U

#define COM1_IRQn                     UART4_IRQn
#endif /* (USE_BSP_COM_FEATURE == 1) */

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup STM32MP1XX_ATK_LOW_LEVEL_Exported_Functions Exported Functions
  * @{
  */
uint32_t         BSP_GetVersion(void);
void             BSP_Error_Handler(void);

/** @addtogroup STM32MP1XX_ATK_LOW_LEVEL_Exported_Functions_Group1 LED Functions
  * @{
  */
int32_t         BSP_LED_Init(Led_TypeDef Led);
int32_t         BSP_LED_DeInit(Led_TypeDef Led);
int32_t         BSP_LED_On(Led_TypeDef Led);
int32_t         BSP_LED_Off(Led_TypeDef Led);
int32_t         BSP_LED_Toggle(Led_TypeDef Led);
int32_t         BSP_LED_GetState (Led_TypeDef Led);
/**
  * @}
  */

/** @addtogroup STM32MP1XX_ATK_LOW_LEVEL_Exported_Functions_Group2 BUTTON Functions
  * @{
  */
int32_t         BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef ButtonMode);
int32_t         BSP_PB_DeInit(Button_TypeDef Button);
int32_t         BSP_PB_GetState(Button_TypeDef Button);
void            BSP_PB_Callback(Button_TypeDef Button);
void            BSP_PB_IRQHandler(Button_TypeDef Button);
void            BSP_PB_WAKEUP_EXTI_LINE_0_IRQHandler(void);
void            BSP_PB_KEY0_EXTI_LINE_3_IRQHandler(void);
void            BSP_PB_KEY1_EXTI_LINE_7_IRQHandler(void);
/**
  * @}
  */

/** @addtogroup STM32MP1XX_ATK_LOW_LEVEL_Exported_Functions_Group3 COM Functions
  * @{
  */
#if (USE_BSP_COM_FEATURE == 1)
#ifdef HAL_UART_MODULE_ENABLED
int32_t         BSP_COM_Init(COM_TypeDef COM, COM_InitTypeDef *COM_Init);
int32_t         BSP_COM_DeInit(COM_TypeDef COM);
#if( USE_COM_LOG == 1)
int32_t  BSP_COM_SelectLogPort (COM_TypeDef COM);
#endif
HAL_StatusTypeDef MX_UART_Init(UART_HandleTypeDef *huart, COM_InitTypeDef *COM_Init) ;
#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
int32_t BSP_COM_RegisterDefaultMspCallbacks(COM_TypeDef COM);
int32_t BSP_COM_RegisterMspCallbacks(COM_TypeDef COM, BSP_COM_Cb_t *Callback);
#endif /* USE_HAL_UART_REGISTER_CALLBACKS */

#endif
#endif /* (USE_BSP_COM_FEATURE == 1) */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __STM32MP1XX_ATK_H */