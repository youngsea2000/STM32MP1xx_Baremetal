/**
  * STM32MP157D DDR3 4Gb configuration
  * 1x DDR3L 4Gb, 16-bit, 533MHz.
  * Reference used MT41K256M16TW-107 P from Micron
  *
  * DDR type / Platform	DDR3/3L
  * freq		533MHz
  * width	16
  * datasheet	1
  * DDR density	4
  * timing mode	optimized
  * Scheduling/QoS options : type = 6
  * address mapping : RBC
  * Tc > + 85C : N
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
#ifndef STM32MP1XX_DDR3_4GBIT_H
#define STM32MP1XX_DDR3_4GBIT_H

#define DDR_MEM_NAME "DDR3-1066 bin F 1x4Gb 533MHz v1.53"
#define DDR_MEM_SPEED 533000U
#define DDR_MEM_SIZE 0x20000000U

#define DDR_MSTR 0x00040401U
#define DDR_MRCTRL0 0x00000010U
#define DDR_MRCTRL1 0x00000000U
#define DDR_DERATEEN 0x00000000U
#define DDR_DERATEINT 0x00800000U
#define DDR_PWRCTL 0x00000000U
#define DDR_PWRTMG 0x00400010U
#define DDR_HWLPCTL 0x00000000U
#define DDR_RFSHCTL0 0x00210000U
#define DDR_RFSHCTL3 0x00000000U
#define DDR_RFSHTMG 0x0081008BU
#define DDR_CRCPARCTL0 0x00000000U
#define DDR_DRAMTMG0 0x121B2414U
#define DDR_DRAMTMG1 0x000A041BU
#define DDR_DRAMTMG2 0x0607080FU
#define DDR_DRAMTMG3 0x0050400CU
#define DDR_DRAMTMG4 0x07040607U
#define DDR_DRAMTMG5 0x06060403U
#define DDR_DRAMTMG6 0x02020002U
#define DDR_DRAMTMG7 0x00000202U
#define DDR_DRAMTMG8 0x00001005U
#define DDR_DRAMTMG14 0x000000A0U
#define DDR_ZQCTL0 0xC2000040U
#define DDR_DFITMG0 0x02050105U
#define DDR_DFITMG1 0x00000202U
#define DDR_DFILPCFG0 0x07000000U
#define DDR_DFIUPD0 0xC0400003U
#define DDR_DFIUPD1 0x00000000U
#define DDR_DFIUPD2 0x00000000U
#define DDR_DFIPHYMSTR 0x00000000U
#define DDR_ADDRMAP1 0x00080808U
#define DDR_ADDRMAP2 0x00000000U
#define DDR_ADDRMAP3 0x00000000U
#define DDR_ADDRMAP4 0x00001F1FU
#define DDR_ADDRMAP5 0x07070707U
#define DDR_ADDRMAP6 0x0F070707U
#define DDR_ADDRMAP9 0x00000000U
#define DDR_ADDRMAP10 0x00000000U
#define DDR_ADDRMAP11 0x00000000U
#define DDR_ODTCFG 0x06000600U
#define DDR_ODTMAP 0x00000001U
#define DDR_SCHED 0x00000F01U
#define DDR_SCHED1 0x00000000U
#define DDR_PERFHPR1 0x00000001U
#define DDR_PERFLPR1 0x04000200U
#define DDR_PERFWR1 0x08000400U
#define DDR_DBG0 0x00000000U
#define DDR_DBG1 0x00000000U
#define DDR_DBGCMD 0x00000000U
#define DDR_POISONCFG 0x00000000U
#define DDR_PCCFG 0x00000010U
#define DDR_PCFGR_0 0x00000000U
#define DDR_PCFGW_0 0x00000000U
#define DDR_PCFGQOS0_0 0x00100009U
#define DDR_PCFGQOS1_0 0x00000020U
#define DDR_PCFGWQOS0_0 0x01100B03U
#define DDR_PCFGWQOS1_0 0x01000200U
#define DDR_PGCR 0x01442E02U
#define DDR_PTR0 0x0022AA5BU
#define DDR_PTR1 0x04841104U
#define DDR_PTR2 0x042DA068U
#define DDR_ACIOCR 0x10400812U
#define DDR_DXCCR 0x00000C40U
#define DDR_DSGCR 0xF200011FU
#define DDR_DCR 0x0000000BU
#define DDR_DTPR0 0x36D477D0U
#define DDR_DTPR1 0x098B00D8U
#define DDR_DTPR2 0x10023600U
#define DDR_MR0 0x00000830U
#define DDR_MR1 0x00000000U
#define DDR_MR2 0x00000208U
#define DDR_MR3 0x00000000U
#define DDR_ODTCR 0x00010000U
#define DDR_ZQ0CR1 0x00000038U
#define DDR_DX0GCR 0x0000CE81U
#define DDR_DX1GCR 0x0000CE81U

#endif /*STM32MP1XX_DDR3_4GBIT_H*/