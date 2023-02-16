/**
  @page BLE_IOT_TEST Application

  @verbatim
  ******************************************************************************
  * @file    BLE/BLE_IOT_TEST/readme.txt
  * @author  MCD Application Team
  * @brief   Description of the BLE_IOT_TEST application
  ******************************************************************************
  *
  * Copyright (c) 2019-2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  @endverbatim

@par Application Description


@note This application is to demonstrate that a BLE_IOT_TEST application can be created using CubeMX.
      This application allows to verify behavior of our STM32WB BLE solution against Smart Phones (Android & IOS).
@note A display terminal can be used to display application messages.
	  This application perform basic functional tests such as discovery, connection, GATT procedure.

@par Keywords

Connectivity, BLE, IPCC, HSEM, RTC, UART, PWR, BLE protocol, BLE pairing, BLE profile, Dual core

@par Directory contents

  - BLE/BLE_IOT_TEST/Core/Inc/app_common.h                  Header for all modules with common definition
  - BLE/BLE_IOT_TEST/Core/Inc/app_conf.h                    Parameters configuration file of the application
  - BLE/BLE_IOT_TEST/Core/Inc/app_debug.h                   Header for app_debug.c module
  - BLE/BLE_IOT_TEST/Core/Inc/app_entry.h                   Parameters configuration file of the application
  - BLE/BLE_IOT_TEST/Core/Inc/hw_conf.h                     Configuration file of the HW
  - BLE/BLE_IOT_TEST/Core/Inc/hw_if.h                       Hardware Interface header file
  - BLE/BLE_IOT_TEST/Core/Inc/main.h                        Header for main.c module
  - BLE/BLE_IOT_TEST/Core/Inc/stm32_lpm_if.h                Header for stm32_lpm_if.c module  
  - BLE/BLE_IOT_TEST/Core/Inc/stm32wbxx_hal_conf.h          HAL configuration file
  - BLE/BLE_IOT_TEST/Core/Inc/stm32wbxx_it.h                Interrupt handlers header file
  - BLE/BLE_IOT_TEST/Core/Inc/utilities_conf.h              Configuration file of the utilities
  - BLE/BLE_IOT_TEST/STM32_WPAN/App/app_ble.h               Header for app_ble.c module
  - BLE/BLE_IOT_TEST/STM32_WPAN/App/ble_conf.h              BLE Services configuration
  - BLE/BLE_IOT_TEST/STM32_WPAN/App/ble_dbg_conf.h          BLE Traces configuration of the BLE services
  - BLE/BLE_IOT_TEST/STM32_WPAN/App/custom_app.h            Header for custom_app.c module
  - BLE/BLE_IOT_TEST/STM32_WPAN/App/custom_stm.h            Header for custom_stm.c module
  - BLE/BLE_IOT_TEST/STM32_WPAN/App/tl_dbg_conf.h        	Debug configuration file for stm32wpan transport layer interface
  - BLE/BLE_IOT_TEST/Core/Src/app_debug.c                   Debug utilities
  - BLE/BLE_IOT_TEST/Core/Src/app_entry.c                   Initialization of the application
  - BLE/BLE_IOT_TEST/Core/Src/hw_timerserver.c              Timer Server based on RTC
  - BLE/BLE_IOT_TEST/Core/Src/hw_uart.c                     UART Driver
  - BLE/BLE_IOT_TEST/Core/Src/main.c                        Main program
  - BLE/BLE_IOT_TEST/Core/Src/stm32_lpm_if.c                Low Power Manager Interface
  - BLE/BLE_IOT_TEST/Core/Src/stm32wbxx_hal_msp.c           MSP Initialization Module
  - BLE/BLE_IOT_TEST/Core/Src/stm32wbxx_it.c                Interrupt handlers
  - BLE/BLE_IOT_TEST/Core/Src/system_stm32wbxx.c            stm32wbxx system source file
  - BLE/BLE_IOT_TEST/STM32_WPAN/App/app_ble.c               BLE Profile implementation
  - BLE/BLE_IOT_TEST/STM32_WPAN/App/custom_app.c            Custom example application
  - BLE/BLE_IOT_TEST/STM32_WPAN/App/custom_stm.c            Custom example services definition

@par Hardware and Software environment

     - This application runs on STM32WB55xx device, Nucleo board (MB1355C).

     - Nucleo board (MB1355C) Set-up
       - Connect the Nucleo Board to your PC with a USB cable type A to mini-B to ST-LINK connector (USB_STLINK).
       - Please ensure that the ST-LINK connectors and jumpers are fitted.

@par How to use it?

This application requires having the stm32wb5x_BLE_Stack_full_fw.bin binary flashed on the Wireless Coprocessor.
If it is not the case, you need to use STM32CubeProgrammer to load the appropriate binary.
All available binaries are located under /Projects/STM32_Copro_Wireless_Binaries directory.
Refer to /Projects/STM32_Copro_Wireless_Binaries/ReleaseNote.html for the detailed procedure to change the
Wireless Coprocessor binary or see following wiki for Hardware setup:
https://wiki.st.com/stm32mcu/wiki/Connectivity:STM32WB_BLE_Hardware_Setup

In order to make the program work, you must do the following:
 - Open your toolchain 
 - Rebuild all files and flash the board with the executable file

On the android/ios device, enable the Bluetooth communications, and if not done before,
 - Install the ST BLE Toolbox application:
   https://wiki.st.com/stm32mcu/wiki/Connectivity:BLE_smartphone_applications#ST_BLE_Toolbox
 - Enable Bluetooth communications
 - Open ST BLE Toolbox and Start Scanning.
 - Connect to IOT_test application to access all the services and associated characteristics

STM32WB is configured as a GATT server and supports :
 - Advertising, restart advertising when disconnection occurs
 - Security (Legacy Pairing and Secure Connection)
 - Clear security database
 - Pairing request initiated by the Slave (STM32WB)
 - Change request of connection interval, slave latency by L2CAP Update Request
 - SW1 Connection interval change request
 - SW2 Slave latency and connection interval change request
 - SW3 (short push) Slave security request 
 - SW3 (long push >1s) Delete Security Database
 - SW4 Reset

For more details refer to the Application Note:
  AN5604 - STM32WB Series BLE interoperability report
 
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
