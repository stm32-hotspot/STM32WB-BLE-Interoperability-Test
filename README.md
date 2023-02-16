# **STM32WB Series BLE interoperability test**
***
## Introduction

This application allows to verify behavior of our STM32WB BLE solution against Smart Phones (Android & IOS), by performing basic functional tests such as discovery, connection, GATT procedure.

You can find more information on the [AN5604](https://www.st.com/resource/en/application_note/an5604-stm32wb-series-ble-interoperability-report-stmicroelectronics.pdf).

## Setup
This application is running on a **NUCLEO-WB55RG board**.   

A smartphone is needed to connect to STM32WB device with ST BLE Toolbox application. You can get it from your platform application store.  
After flashing your board you have to unplug jumpers present on JP5 in order to reach best current measurements. These ones connect STM32WB to ST-LINK debugger.  

To measure current consumption of the MCU you can use our X-NUCLEO-LPM01A board and power Nucleo board from JP2 connector.

## Application description
In order to make the program work, you must do the following:
 - Open your toolchain 
 - Rebuild all files and flash the board with the executable file

On the Android/iOS device, enable the Bluetooth communications, and if not done before,
 - Install the ST BLE Toolbox application:
   https://wiki.st.com/stm32mcu/wiki/Connectivity:BLE_smartphone_applications#ST_BLE_Toolbox
 - Enable Bluetooth communications
 - Open ST BLE Toolbox and Start Scanning.
 - Connect to IOT_test application to access all the services and associated characteristics
 - A display terminal can be used to display application messages 

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

## Troubleshooting

**Caution** : Issues and the pull-requests are **not supported** to submit problems or suggestions related to the software delivered in this repository. The STM32WB-BLE-IOT-TEST example is being delivered as-is, and not necessarily supported by ST.

**For any other question** related to the product, the hardware performance or characteristics, the tools, the environment, you can submit it to the **ST Community** on the STM32 MCUs related [page](https://community.st.com/s/topic/0TO0X000000BSqSWAW/stm32-mcus).
