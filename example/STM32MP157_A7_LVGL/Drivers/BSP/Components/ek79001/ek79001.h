/**
  ******************************************************************************
  * @file    ek79001.h
  * @author  MCD Application Team
  * @brief   This file contains all the constants parameters for the EK79001
  *          LCD component.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2015-2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __EK79001_H
#define __EK79001_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/  

/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup Components
  * @{
  */ 
  
/** @addtogroup ek79001
  * @{
  */

/** @defgroup EK79001_Exported_Types
  * @{
  */
   
/**
  * @}
  */ 

/** @defgroup EK79001_Exported_Constants
  * @{
  */

/** 
  * @brief  EK79001 Size  
  */     
#define  EK79001_WIDTH    ((uint16_t)1024)          /* LCD PIXEL WIDTH            */
#define  EK79001_HEIGHT   ((uint16_t)600)           /* LCD PIXEL HEIGHT           */

/** 
  * @brief  EK79001 Timing  
  */     
#define  EK79001_HSYNC            ((uint16_t)20)   /* Horizontal synchronization */
#define  EK79001_HBP              ((uint16_t)140)  /* Horizontal back porch      */
#define  EK79001_HFP              ((uint16_t)160)  /* Horizontal front porch     */
#define  EK79001_VSYNC            ((uint16_t)3)    /* Vertical synchronization   */
#define  EK79001_VBP              ((uint16_t)20)   /* Vertical back porch        */
#define  EK79001_VFP              ((uint16_t)12)   /* Vertical front porch       */

/** 
  * @brief  EK79001 frequency divider  
  */    
#define  EK79001_FREQUENCY_DIVIDER    45000000     /* LCD Frequency divider      */
/**
  * @}
  */
  
/** @defgroup EK79001_Exported_Functions
  * @{
  */

/**
  * @}
  */    
#ifdef __cplusplus
}
#endif

#endif /* __EK79001_H */
/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */ 

