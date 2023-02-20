/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    custom_app.c
  * @author  MCD Application Team
  * @brief   Custom Example Application (Server)
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
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "app_common.h"
#include "dbg_trace.h"
#include "ble.h"
#include "custom_app.h"
#include "custom_stm.h"
#include "stm32_seq.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32wbxx_nucleo.h"
#include "app_ble.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef struct
{
  /* IOT_Test */
  uint8_t               Rwn_Notification_Status;
  uint8_t               R_w_nr_Indication_Status;
  /* USER CODE BEGIN CUSTOM_APP_Context_t */

  /* USER CODE END CUSTOM_APP_Context_t */

  uint16_t              ConnectionHandle;
} Custom_App_Context_t;

/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private defines ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
extern uint8_t TimerSendNotification_Id;
extern uint8_t TimerSendIndication_Id;

static void Send_Notification_proc(void);
static void Send_Indication_proc(void);

#define DEFAULT_TS_MEASUREMENT_INTERVAL   (1000000/CFG_TS_TICK_VAL)  /**< 1s */
#define DELAY_1s  (1*DEFAULT_TS_MEASUREMENT_INTERVAL)
#define TIMEUNIT  1

#define BOUNCE_THRESHOLD                20U
#define LONG_PRESS_THRESHOLD            1000U

typedef enum
{
    FLAG_ON,
    FLAG_OFF
} Flag_Id;

Flag_Id notification_flag;
Flag_Id indication_flag;

#define BUTTON_PRESSED GPIO_PIN_RESET

/* USER CODE END PD */

/* Private macros -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/**
 * START of Section BLE_APP_CONTEXT
 */

static Custom_App_Context_t Custom_App_Context;

/**
 * END of Section BLE_APP_CONTEXT
 */

uint8_t UpdateCharData[247];
uint8_t NotifyCharData[247];

/* USER CODE BEGIN PV */
uint8_t Notification[1];
uint8_t Indication[1];

uint8_t IndicateCharData[247];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* IOT_Test */
static void Custom_Rwn_Update_Char(void);
static void Custom_Rwn_Send_Notification(void);
static void Custom_R_w_nr_Update_Char(void);
static void Custom_R_w_nr_Send_Indication(void);

/* USER CODE BEGIN PFP */
static void Appli_UpdateButtonState(int isPressed);
/* USER CODE END PFP */

/* Functions Definition ------------------------------------------------------*/
void Custom_STM_App_Notification(Custom_STM_App_Notification_evt_t *pNotification)
{
  /* USER CODE BEGIN CUSTOM_STM_App_Notification_1 */

  /* USER CODE END CUSTOM_STM_App_Notification_1 */
  switch (pNotification->Custom_Evt_Opcode)
  {
    /* USER CODE BEGIN CUSTOM_STM_App_Notification_Custom_Evt_Opcode */

    /* USER CODE END CUSTOM_STM_App_Notification_Custom_Evt_Opcode */

    /* IOT_Test */
    case CUSTOM_STM_RWN_READ_EVT:
      /* USER CODE BEGIN CUSTOM_STM_RWN_READ_EVT */

      /* USER CODE END CUSTOM_STM_RWN_READ_EVT */
      break;

    case CUSTOM_STM_RWN_WRITE_EVT:
      /* USER CODE BEGIN CUSTOM_STM_RWN_WRITE_EVT */

      /* USER CODE END CUSTOM_STM_RWN_WRITE_EVT */
      break;

    case CUSTOM_STM_RWN_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_RWN_NOTIFY_ENABLED_EVT */
        Custom_App_Context.Rwn_Notification_Status=1;
    	HW_TS_Start(TimerSendNotification_Id, DELAY_1s);
    	BSP_LED_On(LED_BLUE);
      /* USER CODE END CUSTOM_STM_RWN_NOTIFY_ENABLED_EVT */
      break;

    case CUSTOM_STM_RWN_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_RWN_NOTIFY_DISABLED_EVT */
        Custom_App_Context.Rwn_Notification_Status= 0 ;
    	HW_TS_Stop(TimerSendNotification_Id);
    	BSP_LED_Off(LED_BLUE);
        
      /* USER CODE END CUSTOM_STM_RWN_NOTIFY_DISABLED_EVT */
      break;

    case CUSTOM_STM_R_W_NR_READ_EVT:
      /* USER CODE BEGIN CUSTOM_STM_R_W_NR_READ_EVT */

      /* USER CODE END CUSTOM_STM_R_W_NR_READ_EVT */
      break;

    case CUSTOM_STM_R_W_NR_WRITE_NO_RESP_EVT:
      /* USER CODE BEGIN CUSTOM_STM_R_W_NR_WRITE_NO_RESP_EVT */

      /* USER CODE END CUSTOM_STM_R_W_NR_WRITE_NO_RESP_EVT */
      break;

    case CUSTOM_STM_R_W_NR_INDICATE_ENABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_R_W_NR_INDICATE_ENABLED_EVT */
        Custom_App_Context.R_w_nr_Indication_Status = 1 ;
    	HW_TS_Start(TimerSendIndication_Id, DELAY_1s);
    	BSP_LED_On(LED_GREEN);
      /* USER CODE END CUSTOM_STM_R_W_NR_INDICATE_ENABLED_EVT */
      break;

    case CUSTOM_STM_R_W_NR_INDICATE_DISABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_R_W_NR_INDICATE_DISABLED_EVT */
        Custom_App_Context.R_w_nr_Indication_Status = 0 ;
    	HW_TS_Stop(TimerSendIndication_Id);
    	BSP_LED_Off(LED_GREEN);
      /* USER CODE END CUSTOM_STM_R_W_NR_INDICATE_DISABLED_EVT */
      break;

    case CUSTOM_STM_R_W_ENC_READ_EVT:
      /* USER CODE BEGIN CUSTOM_STM_R_W_ENC_READ_EVT */
        Custom_Rwn_Update_Char();
      /* USER CODE END CUSTOM_STM_R_W_ENC_READ_EVT */
      break;

    case CUSTOM_STM_R_W_ENC_WRITE_EVT:
      /* USER CODE BEGIN CUSTOM_STM_R_W_ENC_WRITE_EVT */

      /* USER CODE END CUSTOM_STM_R_W_ENC_WRITE_EVT */
      break;

    default:
      /* USER CODE BEGIN CUSTOM_STM_App_Notification_default */

      /* USER CODE END CUSTOM_STM_App_Notification_default */
      break;
  }
  /* USER CODE BEGIN CUSTOM_STM_App_Notification_2 */

  /* USER CODE END CUSTOM_STM_App_Notification_2 */
  return;
}

void Custom_APP_Notification(Custom_App_ConnHandle_Not_evt_t *pNotification)
{
  /* USER CODE BEGIN CUSTOM_APP_Notification_1 */

  /* USER CODE END CUSTOM_APP_Notification_1 */

  switch (pNotification->Custom_Evt_Opcode)
  {
    /* USER CODE BEGIN CUSTOM_APP_Notification_Custom_Evt_Opcode */

    /* USER CODE END P2PS_CUSTOM_Notification_Custom_Evt_Opcode */
    case CUSTOM_CONN_HANDLE_EVT :
      /* USER CODE BEGIN CUSTOM_CONN_HANDLE_EVT */

      /* USER CODE END CUSTOM_CONN_HANDLE_EVT */
      break;

    case CUSTOM_DISCON_HANDLE_EVT :
      /* USER CODE BEGIN CUSTOM_DISCON_HANDLE_EVT */

      /* USER CODE END CUSTOM_DISCON_HANDLE_EVT */
      break;

    default:
      /* USER CODE BEGIN CUSTOM_APP_Notification_default */

      /* USER CODE END CUSTOM_APP_Notification_default */
      break;
  }

  /* USER CODE BEGIN CUSTOM_APP_Notification_2 */

  /* USER CODE END CUSTOM_APP_Notification_2 */

  return;
}

void Custom_APP_Init(void)
{
  /* USER CODE BEGIN CUSTOM_APP_Init */
	UTIL_SEQ_RegTask( 1<<CFG_TASK_SEND_DATA_NOTIFICATION_ID, UTIL_SEQ_RFU, Custom_Rwn_Send_Notification);
	UTIL_SEQ_RegTask( 1<<CFG_TASK_SEND_DATA_INDICATION_ID, UTIL_SEQ_RFU, Custom_R_w_nr_Send_Indication);

	UTIL_SEQ_RegTask( 1<<CFG_TASK_SLAVE_SECURITY_REQ_ID, UTIL_SEQ_RFU, BLE_SVC_Security_Req);
	UTIL_SEQ_RegTask( 1<<CFG_TASK_CLEAR_SECURITY_DB_ID, UTIL_SEQ_RFU, BLE_SVC_GAP_Clear_DataBase);

	/* Create timer for sending data notification when notification is enabled */
	HW_TS_Create(CFG_TIM_PROC_ID_ISR, &(TimerSendNotification_Id), hw_ts_Repeated, Send_Notification_proc);

	/* Create timer for sending data indication when indication is enabled */
	HW_TS_Create(CFG_TIM_PROC_ID_ISR, &(TimerSendIndication_Id), hw_ts_Repeated, Send_Indication_proc);

	notification_flag = FLAG_ON;
	indication_flag = FLAG_ON;

        Custom_App_Context.Rwn_Notification_Status=0;
        Custom_App_Context.R_w_nr_Indication_Status=0;

	  for (int i=0 ; i<(SizeR_W_Nr-1) ; i++)
	  {
		  NotifyCharData[i] = i+1;
		  IndicateCharData[i] = i+1;
	  }
  /* USER CODE END CUSTOM_APP_Init */
  return;
}

/* USER CODE BEGIN FD */
static void Send_Notification_proc(){

  UTIL_SEQ_SetTask(1 << CFG_TASK_SEND_DATA_NOTIFICATION_ID, CFG_SCH_PRIO_0);
}

static void Send_Indication_proc(){

  UTIL_SEQ_SetTask(1 << CFG_TASK_SEND_DATA_INDICATION_ID, CFG_SCH_PRIO_0);
}
/* USER CODE END FD */

/*************************************************************
 *
 * LOCAL FUNCTIONS
 *
 *************************************************************/

/* IOT_Test */
void Custom_Rwn_Update_Char(void) /* Property Read */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN Rwn_UC_1*/
  if(notification_flag == FLAG_ON)
  {
	  Notification[0] = 0x55;
	  SizeRwn = (uint8_t)1;
	  APP_DBG_MSG("C1 CHAR UPDATE - LENGTH = %d \n", SizeRwn);
	  Custom_STM_App_Update_Char(CUSTOM_STM_RWN, (uint8_t *)Notification);
	  notification_flag = FLAG_OFF;
  }
  else
  {
	  NotifyCharData[0] += 1;
	  SizeRwn = (uint8_t)249;
	  APP_DBG_MSG("C1 CHAR UPDATE - LENGTH = %d \n", SizeRwn);
	  Custom_STM_App_Update_Char(CUSTOM_STM_RWN, (uint8_t *)NotifyCharData);
	  notification_flag = FLAG_ON;
  }
  /* USER CODE END Rwn_UC_1*/

  if (updateflag != 0)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_RWN, (uint8_t *)UpdateCharData);
  }

  /* USER CODE BEGIN Rwn_UC_Last*/

  /* USER CODE END Rwn_UC_Last*/
  return;
}

void Custom_Rwn_Send_Notification(void) /* Property Notification */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN Rwn_NS_1*/
  if(Custom_App_Context.Rwn_Notification_Status)
    {
      //Custom_STM_App_Update_Char(CUSTOM_STM_S1_C1, (uint8_t *)NotifyCharData);
      /* USER CODE BEGIN S1_c1_NS*/
	  Custom_Rwn_Update_Char();
	  APP_DBG_MSG("Custom_Rwn_Send_Notification \n");
      /* USER CODE END S1_c1_NS*/
    }
    else
    {
      APP_DBG_MSG("-- CUSTOM APPLICATION : CAN'T INFORM CLIENT -  NOTIFICATION DISABLED\n ");
    }
  /* USER CODE END Rwn_NS_1*/

  if (updateflag != 0)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_RWN, (uint8_t *)NotifyCharData);
  }

  /* USER CODE BEGIN Rwn_NS_Last*/

  /* USER CODE END Rwn_NS_Last*/

  return;
}

void Custom_R_w_nr_Update_Char(void) /* Property Read */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN R_w_nr_UC_1*/
  if(indication_flag == FLAG_ON)
  {
	  Indication[0] = 0x55;
	  SizeR_W_Nr = (uint8_t)1;
	  APP_DBG_MSG("C2 CHAR UPDATE - LENGTH = %d \n", SizeR_W_Nr);
	  Custom_STM_App_Update_Char(CUSTOM_STM_R_W_NR, (uint8_t *)Indication);
	  indication_flag = FLAG_OFF;
  }
  else
  {
	  IndicateCharData[0] += 1;
	  SizeR_W_Nr = (uint8_t)249;
	  APP_DBG_MSG("C2 CHAR UPDATE - LENGTH = %d \n", SizeR_W_Nr);
	  Custom_STM_App_Update_Char(CUSTOM_STM_R_W_NR, (uint8_t *)IndicateCharData);
	  indication_flag  = FLAG_ON;
  }
  /* USER CODE END R_w_nr_UC_1*/

  if (updateflag != 0)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_R_W_NR, (uint8_t *)UpdateCharData);
  }

  /* USER CODE BEGIN R_w_nr_UC_Last*/

  /* USER CODE END R_w_nr_UC_Last*/
  return;
}

void Custom_R_w_nr_Send_Indication(void) /* Property Indication */
{
  uint8_t updateflag = 0;

  /* USER CODE BEGIN R_w_nr_IS_1*/
  if(Custom_App_Context.R_w_nr_Indication_Status)
  {
    //Custom_STM_App_Update_Char(CUSTOM_STM_S1_C2, (uint8_t *)IndicateCharData);
    /* USER CODE BEGIN S1_c2_IS*/
    Custom_R_w_nr_Update_Char();
    APP_DBG_MSG("Custom_R_w_nr_Send_Indication \n");
    /* USER CODE END S1_c2_IS*/
  }
  else
  {
    APP_DBG_MSG("-- CUSTOM APPLICATION : CAN'T INFORM CLIENT -  INDICATION DISABLED\n ");
  }
  /* USER CODE END R_w_nr_IS_1*/

  if (updateflag != 0)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_R_W_NR, (uint8_t *)IndicateCharData);
  }

  /* USER CODE BEGIN R_w_nr_IS_Last*/

  /* USER CODE END R_w_nr_IS_Last*/

  return;
}

/* USER CODE BEGIN FD_LOCAL_FUNCTIONS*/

static void Appli_UpdateButtonState(int isPressed)
{
  uint32_t t0 = 0,t1 = 1;

  t0 = HAL_GetTick(); /* SW3 press timing */

  while(BSP_PB_GetState(BUTTON_SW3) == BUTTON_PRESSED);
  t1 = HAL_GetTick(); /* SW3 release timing */

  if((t1 - t0) > LONG_PRESS_THRESHOLD)
  {
    /* Button 3 long press action */
    APP_DBG_MSG("clear database \n");
    UTIL_SEQ_SetTask(1 << CFG_TASK_CLEAR_SECURITY_DB_ID, CFG_SCH_PRIO_0);
  }
  else if((t1 - t0) > BOUNCE_THRESHOLD)
  {
    /* Button 3 short press action */
    APP_DBG_MSG("slave security request \n");
    UTIL_SEQ_SetTask(1 << CFG_TASK_SLAVE_SECURITY_REQ_ID, CFG_SCH_PRIO_0);
  }
}

void IOT_App_Button3_Trigger_Received( void )
{
  Appli_UpdateButtonState(BSP_PB_GetState(BUTTON_SW3) == BUTTON_PRESSED);

  return;
}
/* USER CODE END FD_LOCAL_FUNCTIONS*/
