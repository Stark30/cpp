/* USER CODE BEGIN Includes */
#include "string.h"
#include "stdio.h"
/* USER CODE END Includes */

/* USER CODE BEGIN PV */
#define UART_BUFFER_SIZE 256
QueueHandle_t uartQueue;
uint8_t InputBuffer[UART_BUFFER_SIZE];
uint8_t OutputBuffer[UART_BUFFER_SIZE];
/* USER CODE END PV */

/* USER CODE BEGIN PFP */
void UARTReceiveTask(void *argument);
void UARTSendTask(void *argument);
/* USER CODE END PFP */

int main(void)
{
    // ... [Unchanged initialization code]

    /* USER CODE BEGIN 2 */
    uartQueue = xQueueCreate(10, UART_BUFFER_SIZE);
    if (uartQueue == NULL)
    {
        Error_Handler();
    }

    // Defining tasks for UART recieving and transmission
    osThreadDef(uartReceiveTask, UARTReceiveTask, osPriorityNormal, 0, 128);
    osThreadCreate(osThread(uartReceiveTask), NULL);

    osThreadDef(uartSendTask, UARTSendTask, osPriorityNormal, 0, 128);
    osThreadCreate(osThread(uartSendTask), NULL);
    /* USER CODE END 2 */
}

void UARTReceiveTask(void *argument)
{
    for (;;)
    {
        HAL_UART_Receive(&huart2, InputBuffer, UART_BUFFER_SIZE, HAL_MAX_DELAY);

        if (xQueueSend(uartQueue, InputBuffer, portMAX_DELAY) != pdPASS)
        {
        }
    }
}

void UARTSendTask(void *argument)
{
    uint8_t buffer[UART_BUFFER_SIZE];

    for (;;)
    {
        if (xQueueReceive(uartQueue, buffer, portMAX_DELAY) == pdPASS)
        {
            HAL_UART_Transmit(&huart2, buffer, strlen((char *)buffer), HAL_MAX_DELAY);
            memset(buffer, 0, UART_BUFFER_SIZE);
        }
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART2)
    {
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        xTaskNotifyFromISR(uartQueue, 0, eNoAction, &xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}

/* Error Handler */
void Error_Handler(void)
{
    __disable_irq();
    while (1)
    {
    }
}

/* USER CODE BEGIN 4 */
// Add any additional helper functions here if necessary
/* USER CODE END 4 */
