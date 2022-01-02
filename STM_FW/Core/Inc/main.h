/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ARD_D7_GPIO_Pin GPIO_PIN_3
#define ARD_D7_GPIO_GPIO_Port GPIOE
#define LCD_TE_INT_Pin GPIO_PIN_8
#define LCD_TE_INT_GPIO_Port GPIOB
#define WIFI_GPIO_0_Pin GPIO_PIN_14
#define WIFI_GPIO_0_GPIO_Port GPIOG
#define USB_OTG_HS_VBUS_Pin GPIO_PIN_13
#define USB_OTG_HS_VBUS_GPIO_Port GPIOG
#define ARD_D8_GPIO_Pin GPIO_PIN_4
#define ARD_D8_GPIO_GPIO_Port GPIOB
#define SYS_STLINK_JTDO_SWO_Pin GPIO_PIN_3
#define SYS_STLINK_JTDO_SWO_GPIO_Port GPIOB
#define WIFI_RST_Pin GPIO_PIN_12
#define WIFI_RST_GPIO_Port GPIOC
#define CTP_INT_Pin GPIO_PIN_9
#define CTP_INT_GPIO_Port GPIOB
#define SAI2_INT_Pin GPIO_PIN_15
#define SAI2_INT_GPIO_Port GPIOG
#define PMOD_GPIO_0_Pin GPIO_PIN_12
#define PMOD_GPIO_0_GPIO_Port GPIOG
#define PMOD_INT_Pin GPIO_PIN_11
#define PMOD_INT_GPIO_Port GPIOG
#define USB_OTGFS_OVCR_INT_Pin GPIO_PIN_10
#define USB_OTGFS_OVCR_INT_GPIO_Port GPIOG
#define WIFI_GPIO_2_Pin GPIO_PIN_6
#define WIFI_GPIO_2_GPIO_Port GPIOD
#define STMOD_UART4_RXD_s_Pin GPIO_PIN_11
#define STMOD_UART4_RXD_s_GPIO_Port GPIOC
#define PMOD_SPI2_MOSI_Pin GPIO_PIN_3
#define PMOD_SPI2_MOSI_GPIO_Port GPIOI
#define PMOD_SPI2_MISO_Pin GPIO_PIN_2
#define PMOD_SPI2_MISO_GPIO_Port GPIOI
#define WIFI_CH_PD_Pin GPIO_PIN_3
#define WIFI_CH_PD_GPIO_Port GPIOD
#define PMOD_SEL_0_Pin GPIO_PIN_15
#define PMOD_SEL_0_GPIO_Port GPIOH
#define USB_OTG_FS_ID_Pin GPIO_PIN_10
#define USB_OTG_FS_ID_GPIO_Port GPIOA
#define PMOD_GPIO_1_Pin GPIO_PIN_2
#define PMOD_GPIO_1_GPIO_Port GPIOH
#define ARD_D4_GPIO_Pin GPIO_PIN_3
#define ARD_D4_GPIO_GPIO_Port GPIOH
#define USB_OTGFS_PPWR_EN_Pin GPIO_PIN_8
#define USB_OTGFS_PPWR_EN_GPIO_Port GPIOG
#define USB_OTGHS_PPWR_EN_Pin GPIO_PIN_12
#define USB_OTGHS_PPWR_EN_GPIO_Port GPIOH
#define USB_OTGHS_OVCR_INT_Pin GPIO_PIN_10
#define USB_OTGHS_OVCR_INT_GPIO_Port GPIOH
#define CTP_RST_Pin GPIO_PIN_9
#define CTP_RST_GPIO_Port GPIOH
#define SYS_B_User_Pin GPIO_PIN_0
#define SYS_B_User_GPIO_Port GPIOA
#define LCD_RST_Pin GPIO_PIN_7
#define LCD_RST_GPIO_Port GPIOH
#define ARD_D2_GPIO_Pin GPIO_PIN_5
#define ARD_D2_GPIO_GPIO_Port GPIOC
#define USB_OTG_HS_ID_Pin GPIO_PIN_12
#define USB_OTG_HS_ID_GPIO_Port GPIOB
#define SYS_LD_USER1_Pin GPIO_PIN_7
#define SYS_LD_USER1_GPIO_Port GPIOA
#define SYS_LD_USER2_Pin GPIO_PIN_1
#define SYS_LD_USER2_GPIO_Port GPIOB
#define PMOD_RESET_Pin GPIO_PIN_11
#define PMOD_RESET_GPIO_Port GPIOF
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
