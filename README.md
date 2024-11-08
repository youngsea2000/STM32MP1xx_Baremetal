# STM32MP1xx_Baremetal
**[简体中文](#简介)**&nbsp;&nbsp;&nbsp;&nbsp;**[English](#Introduction)**
## Introduction
This project involves bare-metal development on the STM32MP157DAAA1, and in theory, all programs in this repository are compatible with all microcontrollers in the STM32MP15XX series. The purpose of this project is to bypass u-boot and use a more lightweight bootloader for pure bare-metal operation. For this MPU, the bare-metal program can be initiated through the following methods:

1. **Running the bare-metal program as an FSBL**: This method requires the program to run in SYSRAM instead of DDR. For this approach, you can refer to the bootloader project in the FSBLA folder of the repository.
2. **Running the bare-metal program through a bootloader**: Here, the bare-metal program is loaded into DDR, and both the FSBLA and the bare-metal program need to be compiled and burned to the storage medium.

There is virtually no difference between these two methods in terms of programming; only the RCC configuration and the address offsets in the linker script (ld file) need attention. The repository focuses mainly on the second method. The original purpose of creating this repository is for personal projects; therefore, the repository will include the following implementations as example programs:

* **[(Completed) FSBLA_Sdmmc1]()**: Supports loading a bare-metal program from an SD card into DDR3L for execution.
* **[(In Progress) STM32MP157_A7_Multi_Core]()**: Booting the A7 dual cores to run independent programs on each core.
* **[(Planned) STM32MP157_A7_LVGL]()**: Running an LVGL GUI demo on a touchscreen using the A7 core.
* **[(Planned) STM32MP157_A7_USB_Host]()**: Using the A7 core to drive a USB host for a UVC camera.
* **[(Planned) STM32MP157_M4_HelloWorld]()**: Starting the M4 core to run a simple UART demo.
* **[(Planned) STM32MP157_A7_RTOS]()**: Running a multi-threaded application using the A7 core with RTOS.
* **[(Planned) STM32MP157_XX_...]()**: Additional programs might be added as the project progresses.
---
## 简介
该项目采用 STM32MP157DAAA1 进行裸机程序开发，理论上这个仓库中的所有程序适用于 STM32MP15XX 系列的所有单片机。建立本项目的初衷是为了脱离 u-boot 转而采用更精简的引导程序进行纯裸机程序运行，针对于这个 MPU 的启动方式，裸机程序可以通过以下几种条件进行启动：
1. 将裸机程序作为 FSBL 程序运行，这种启动方式要求程序在 SYSRAM 中运行而不是 DDR。采用这种启动方式可以参考仓库中FSBLA文件夹的 bootloader 项目进行程序编写。
2. 通过 bootloader 裸机程序，裸机程序加载至 DDR 中，需要编译FSBLA以及裸机程序并烧录至存储介质中。

二者在程序编写的方法上几乎没有任何区别，只需要注意RCC配置以及链接过程中ld文件地址偏移即可。同时仓库以第二种启动方法为主，同时建立仓库的初衷是为了完成个人项目，因此仓库将陆续实现以下内容作为示例程序：
* **[(已完成)FSBLA_Sdmmc1]()**: 支持从 SD 卡加载裸机程序到 DDR3L 中运行。
* **[(创建中)STM32MP157_A7_Multi_Core]()**：启动A7双核分别运行独立程序。
* **[(待实现)STM32MP157_A7_LVGL]()**：使用A7内核驱动触屏运行 LVGL GUI demo。
* **[(待实现)STM32MP157_A7_USB_Host]()**：使用A7内核驱动 USB 主机驱动 UVC 摄像头。
* **[(待实现)STM32MP157_M4_HelloWorld]()**：启动M4内核，运行简单的串口 demo。
* **[(待实现)STM32MP157_A7_RTOS]()**：使用A7内核以及RTOS进行多线程操作。
* **[(待实现)STM32MP157_XX_...]()**：随着项目推进可能会有更多的程序供参考。
