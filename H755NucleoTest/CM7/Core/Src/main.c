/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#ifndef HSEM_ID_0
#define HSEM_ID_0 (0U) /* HW semaphore 0*/
#endif

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

COM_InitTypeDef BspCOMInit;

I2C_HandleTypeDef hi2c4;

SPI_HandleTypeDef hspi3;

/* USER CODE BEGIN PV */
uint8_t rx_buffer[4];
uint8_t RX_Buffer[3];
uint8_t tx_buffer[] = {100, 200, 35, 100};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C4_Init(void);
static void MX_SPI3_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

// I2C event callback
//void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef *hi2c)
//{
//    HAL_I2C_EnableListen_IT(hi2c);  // Re-enable listening mode
//}
//
//void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode)
//{
//    if(TransferDirection == I2C_DIRECTION_TRANSMIT)  // Master is writing to slave
//    {
//        HAL_I2C_Slave_Receive_IT(hi2c, rx_buffer, sizeof(rx_buffer));
//    }
//    else  // Master is reading from slave
//    {
//        HAL_I2C_Slave_Transmit_IT(hi2c, tx_buffer, sizeof(tx_buffer));
//    }
//}
//
//void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c)
//{
//	HAL_I2C_EnableListen_IT(hi2c);
//}
//
//void HAL_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef *hi2c)
//{
//    HAL_I2C_EnableListen_IT(hi2c);  // Only re-enable listening mode
//}
//
//void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c)
//{
//    HAL_I2C_EnableListen_IT(hi2c);  // Only re-enable listening mode
//}

//void HAL_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef *hi2c)
//{
//    if (hi2c->Instance == I2C4)
//    {
//        HAL_I2C_Slave_Transmit_IT(&hi2c4, tx_buffer, sizeof(tx_buffer)); // Restart transmission
//    }
//
//    HAL_I2C_EnableListen_IT(hi2c);  // Re-enable listening mode
//}
//
//void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c)
//{
//    if (hi2c->Instance == I2C4)
//    {
//        HAL_I2C_Slave_Receive_IT(&hi2c4, tx_buffer, sizeof(tx_buffer)); // Restart transmission
//    }
//
//    HAL_I2C_EnableListen_IT(hi2c);  // Re-enable listening mode
////
////    printf("received\n");
////    uint8_t i;
////
////    for (i = 0; i < 6; ++i) {
////    	printf("%d", rx_buffer[i]);
////    }
////
////    printf("\n");
//
//
//}



void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef *hi2c)
{
    printf("Listen Complete\n");
    HAL_I2C_EnableListen_IT(hi2c);  // Re-enable listening mode
}

void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c,
                          uint8_t TransferDirection,
                          uint16_t AddrMatchCode)
{
    if (hi2c->Instance == I2C4) // or match your slave address
    {
        if (TransferDirection == I2C_DIRECTION_TRANSMIT)
        {
            // Master is writing data to us
            // Prepare to receive. E.g.:
            HAL_I2C_Slave_Seq_Receive_IT(hi2c, rx_buffer, 4,
                                         I2C_NEXT_FRAME);
        }
        else // I2C_DIRECTION_RECEIVE
        {
            // Master is reading from us
            // Prepare to transmit. E.g.:
            HAL_I2C_Slave_Seq_Transmit_IT(hi2c, tx_buffer, 4,
                                          I2C_NEXT_FRAME);
        }
//    	if(TransferDirection == I2C_DIRECTION_TRANSMIT)  // Master is writing to slave
//    	    {
//    	        HAL_I2C_Slave_Receive_IT(hi2c, rx_buffer, sizeof(rx_buffer));
//    	    }
//    	    else  // Master is reading from slave
//    	    {
//    	        HAL_I2C_Slave_Transmit_IT(hi2c, tx_buffer, sizeof(tx_buffer));
//    	    }
    }
}
void HAL_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    printf("Tx Complete\n");
    HAL_I2C_EnableListen_IT(hi2c);
}

void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    printf("Rx Complete\n");

    for (int i = 0; i < 4; ++i) {
        	printf("%d, ", rx_buffer[i]);
        }

        printf("\n");

    HAL_I2C_EnableListen_IT(hi2c);

}

// Also handle error:
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c)
{
//    printf("error\n");
    // Optionally inspect hi2c->ErrorCode for details
	  printf("I2C ErrorCallback: ErrorCode = 0x%lX\r\n", hi2c->ErrorCode);
	// Clear errors or re-init as needed
    HAL_I2C_EnableListen_IT(hi2c);
}
/* USER CODE END 0 */

//void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
//{
//    if (hspi->Instance == SPI3)  // Replace with your SPI instance
//    {
//        // Process the received data in spiRxBuf.
//        printf("SPI half-duplex RX complete. Received bytes:\r\n");
//        for (int i = 0; i < 3; i++) {
//            printf("  0x%02X\r\n", rx_buffer[i]);
//        }
//
//        // Re-arm the reception for the next transaction.
//        HAL_SPIEx_HalfDuplex_Receive_IT(hspi, rx_buffer, 3);
//    }
//}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
    if (hspi->Instance == SPI3)
    {
        // After receiving, send back data
        HAL_SPI_Transmit_IT(hspi, tx_buffer, sizeof(tx_buffer));
        HAL_SPI_Receive_IT(&hspi3, rx_buffer, sizeof(rx_buffer));
    }
}



void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
    if (hspi->Instance == SPI3)
    {
        printf("SPI TX complete.\r\n");
        // If you need to send new data on the next transaction, update spiTxBuf here.
        // For continuous full-duplex transactions, you may call:

//        HAL_SPI_TransmitReceive_IT(hspi, spiTxBuf, spiRxBuf, SPI_RX_BUF_SIZE);
    }
}

void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi)
{
    if (hspi->Instance == SPI2)
    {
        printf("SPI Error occurred. Error Code: 0x%lX\r\n", hspi->ErrorCode);
        // Optionally, abort the current operation and re-start:
        HAL_SPI_Receive_IT(hspi, rx_buffer, 3);
    }
}


/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
/* USER CODE BEGIN Boot_Mode_Sequence_0 */
  int32_t timeout;
/* USER CODE END Boot_Mode_Sequence_0 */

/* USER CODE BEGIN Boot_Mode_Sequence_1 */
  /* Wait until CPU2 boots and enters in stop mode or timeout*/
//  timeout = 0xFFFF;
//  while((__HAL_RCC_GET_FLAG(RCC_FLAG_D2CKRDY) != RESET) && (timeout-- > 0));
//  if ( timeout < 0 )
//  {
//  Error_Handler();
//  }
/* USER CODE END Boot_Mode_Sequence_1 */
  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();
/* USER CODE BEGIN Boot_Mode_Sequence_2 */
/* When system initialization is finished, Cortex-M7 will release Cortex-M4 by means of
HSEM notification */
/*HW semaphore Clock enable*/
__HAL_RCC_HSEM_CLK_ENABLE();
/*Take HSEM */
HAL_HSEM_FastTake(HSEM_ID_0);
/*Release HSEM in order to notify the CPU2(CM4)*/
HAL_HSEM_Release(HSEM_ID_0,0);
/* wait until CPU2 wakes up from stop mode */
timeout = 0xFFFF;
while((__HAL_RCC_GET_FLAG(RCC_FLAG_D2CKRDY) == RESET) && (timeout-- > 0));
if ( timeout < 0 )
{
Error_Handler();
}
/* USER CODE END Boot_Mode_Sequence_2 */

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C4_Init();
  MX_SPI3_Init();
  /* USER CODE BEGIN 2 */
//  HAL_I2C_Slave_Receive_IT(&hi2c4 ,(uint8_t *)RX_Buffer, 1); //Receiving in Interrupt mode
  /* USER CODE END 2 */

  /* Initialize leds */
  BSP_LED_Init(LED_GREEN);
  BSP_LED_Init(LED_YELLOW);
  BSP_LED_Init(LED_RED);

  /* Initialize USER push-button, will be used to trigger an interrupt each time it's pressed.*/
  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_EXTI);

  /* Initialize COM1 port (115200, 8 bits (7-bit data + 1 stop bit), no parity */
  BspCOMInit.BaudRate   = 115200;
  BspCOMInit.WordLength = COM_WORDLENGTH_8B;
  BspCOMInit.StopBits   = COM_STOPBITS_1;
  BspCOMInit.Parity     = COM_PARITY_NONE;
  BspCOMInit.HwFlowCtl  = COM_HWCONTROL_NONE;
  if (BSP_COM_Init(COM1, &BspCOMInit) != BSP_ERROR_NONE)
  {
    Error_Handler();
  }

  HAL_I2C_EnableListen_IT(&hi2c4);
  // Initialize SPI2 as a half-duplex slave via CubeMX or your initialization code.
//  HAL_SPIEx_HalfDuplex_Receive_IT(&hspi3, rx_buffer, 3);

  HAL_SPI_Receive_IT(&hspi3, rx_buffer, sizeof(rx_buffer));
  printf("testing code \n");
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

    /* USER CODE END WHILE */
//	  HAL_SPI_Receive_IT(&hspi3, RX_Buffer, 1); //Receiving in Interrupt mode
//	  printf("testing\n");
//	  HAL_Delay(500);

//	  if (HAL_SPI_Receive(&hspi3, rx_buffer, sizeof(rx_buffer), HAL_MAX_DELAY) == HAL_OK)
//	      {
////	          HAL_UART_Transmit(&huart2, rx_buffer, sizeof(rx_buffer), 1000);  // Print received data via UART
////	          Send_SPI_Response(); // Send confirmation after receiving
////		  SET_BIT(hspi3.Instance->CR1, SPI_CR1_BIDIOE); // Set Data Line to Output (TX)
//		  HAL_SPI_Transmit(&hspi3, tx_buffer, sizeof(tx_buffer), HAL_MAX_DELAY);
//		  BSP_LED_Toggle(LED_RED);
////		  HAL_Delay(1000);
////		  BSP_COM_Transmit(COM1, (uint8_t *)rx_buffer, strlen(rx_buffer), HAL_MAX_DELAY);
//		  for (int i = 0; i < 6; ++i) {
//			  printf("%d\n", rx_buffer[i]);
//		  }
////		  printf("%x\n", rx_buffer[0]);
////		  printf("%x\n", rx_buffer[1]);
////		  printf("%x\n", rx_buffer[2]);
//		  if (rx_buffer[0] == 0x5) {
//
//				  BSP_LED_Toggle(LED_GREEN);
//		  	  }
//
//	      }
//	  HAL_I2C_Slave_Receive_IT(&hi2c4 ,(uint8_t *)RX_Buffer, 1); //Receiving in Interrupt mode
	  BSP_LED_Toggle(LED_GREEN);
//	  HAL_Delay(100);
//	  printf("Main loop\n");
//	          static uint32_t lastTime = 0;
//	          uint32_t currentTime = HAL_GetTick();
//
//	          // Every 5 seconds, try to re-enable listen mode
//	          if(currentTime - lastTime > 5000)
//	          {
//	              printf("Re-enabling listen mode\n");
//	              HAL_I2C_EnableListen_IT(&hi2c4);
//	              lastTime = currentTime;
//	          }
	          HAL_Delay(1000);

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_DIRECT_SMPS_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOMEDIUM;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV1;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C4_Init(void)
{

  /* USER CODE BEGIN I2C4_Init 0 */

  /* USER CODE END I2C4_Init 0 */

  /* USER CODE BEGIN I2C4_Init 1 */

  /* USER CODE END I2C4_Init 1 */
  hi2c4.Instance = I2C4;
  hi2c4.Init.Timing = 0x00300F38;
  hi2c4.Init.OwnAddress1 = 64;
  hi2c4.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c4.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c4.Init.OwnAddress2 = 0;
  hi2c4.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c4.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c4.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c4) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c4, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c4, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C4_Init 2 */

  /* USER CODE END I2C4_Init 2 */

}

/**
  * @brief SPI3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI3_Init(void)
{

  /* USER CODE BEGIN SPI3_Init 0 */

  /* USER CODE END SPI3_Init 0 */

  /* USER CODE BEGIN SPI3_Init 1 */

  /* USER CODE END SPI3_Init 1 */
  /* SPI3 parameter configuration*/
  hspi3.Instance = SPI3;
  hspi3.Init.Mode = SPI_MODE_SLAVE;
  hspi3.Init.Direction = SPI_DIRECTION_1LINE;
  hspi3.Init.DataSize = SPI_DATASIZE_4BIT;
  hspi3.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi3.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi3.Init.NSS = SPI_NSS_SOFT;
  hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi3.Init.CRCPolynomial = 0x0;
  hspi3.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  hspi3.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
  hspi3.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
  hspi3.Init.TxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
  hspi3.Init.RxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
  hspi3.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
  hspi3.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
  hspi3.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
  hspi3.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_DISABLE;
  hspi3.Init.IOSwap = SPI_IO_SWAP_DISABLE;
  if (HAL_SPI_Init(&hspi3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI3_Init 2 */

  /* USER CODE END SPI3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pins : PC1 PC4 PC5 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA1 PA2 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PB13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PA8 PA11 PA12 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG1_FS;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PG11 PG13 */
  GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
