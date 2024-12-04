#include "main.h"
#include "string.h"

UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart2_tx;
DMA_HandleTypeDef hdma_usart2_rx;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART2_UART_Init(void);

char tx_data[] = "Hello this is shruti\r\n";
char rx_data[512];  

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_DMA_Init();
    MX_USART2_UART_Init();
    
    while (1) {
        HAL_UART_Transmit_DMA(&huart2, (uint8_t *)tx_data, strlen(tx_data));
        
        HAL_Delay(100);
        
        HAL_UART_Receive_DMA(&huart2, (uint8_t *)rx_data, sizeof(rx_data));
        
        HAL_Delay(1000);  
    }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    HAL_UART_Transmit_DMA(&huart2, (uint8_t *)rx_data, strlen(rx_data)); // Echo received data back
}

void SystemClock_Config(void) {
}

static void MX_USART2_UART_Init(void) {
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 115200;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart2) != HAL_OK) {
        Error_Handler();
    }
}

static void MX_DMA_Init(void) {
    __HAL_RCC_DMA1_CLK_ENABLE();
    HAL_DMA_Init(&hdma_usart2_tx);
    HAL_DMA_Init(&hdma_usart2_rx);

    __HAL_LINKDMA(&huart2, hdmatx, hdma_usart2_tx);
    __HAL_LINKDMA(&huart2, hdmarx, hdma_usart2_rx);
}

static void MX_GPIO_Init(void) {
}

void Error_Handler(void) {
    while (1) { }
}
