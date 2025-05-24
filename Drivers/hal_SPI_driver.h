#ifndef HAL_SPI_DRIVER_H_
#define HAL_SPI_DRIVER_H_

#include <stdint.h>
#include <stm32f49xx.h>

/*************************SPI_CR1 register ******************************/

#define SPI_CR1_BIDIMODE                      ((uint32_t) 1 << 15)
#define SPI_ENABLE_2_LINE_UNI_DIR             0 /* 2-line unidirectional data mode selected */
#define SPI_ENABLE_1_LINE_BIDIR               1 /* 1-line bidirectional data mode selected */

#define SPI_CR1_BIDIOE                        ((uint32_t) 1 << 14)
#define SPI_OUTPUT_DISABLE                    0 /* Recieve-only mode */
#define SPI_OUTPUT_ENABLE                     1 /* Transmit-only mode */

#define SPI_CR1_DFF                           ((uint32_t) 1 << 11)
#define SPI_8Bit_DF_ENABLE                    0
#define SPI_16Bit_DF_ENABLE                   1

#define SPI_CR1_RXONLY                        ((uint32_t) 1 << 10)
#define SPI_FULL_DUPLEX                       0
#define SPI_RECIEVE_ONLY                      1

#define SPI_CR1_SSM                           ((uint32_t) 1 << 9) /* Software slave management */
#define SPI_SSM_ENABLE                        1
#define SPI_SSM_DISABLE                       0

#define SPI_CR1_SSI                          ((uint32_t) 1 << 8) /* Internal slave select */

#define SPI_CR1_LSBFIRST                      ((uint32_t) 1 << 7)
#define SPI_TX_MSB_FIRST                      0
#define SPI_TX_LSB_FIRST                      1


#define SPI_CR1_SPE                           ((uint32_t) 1 << 6) /* SPI enable */
#define SPI_PERIPHERAL_ENABLE                  1
#define SPI_PERIPHERAL_DISABLE                 0



#define SPI_CR1_BR_PCLK_DIV_2                 ((uint32_t) 0 << 3)
#define SPI_CR1_BR_PCLK_DIV_4                 ((uint32_t) 1 << 3)
#define SPI_CR1_BR_PCLK_DIV_8                 ((uint32_t) 2 << 3)
#define SPI_CR1_BR_PCLK_DIV_16                ((uint32_t) 3 << 3)
#define SPI_CR1_BR_PCLK_DIV_32                ((uint32_t) 4 << 3)
#define SPI_CR1_BR_PCLK_DIV_64                ((uint32_t) 5 << 3)
#define SPI_CR1_BR_PCLK_DIV_128               ((uint32_t) 6 << 3)
#define SPI_CR1_BR_PCLK_DIV_256               ((uint32_t) 7 << 3)

#define SPI_CR1_MSTR                          ((uint32_t) 1 << 2)
#define SPI_SLAVE_MODE                        0
#define SPI_MASTER_MODE                       1

#define SPI_CR1_CPOL                          ((uint32_t) 1 << 1)
#define SPI_CPOL_LOW                          0
#define SPI_CPOL_HIGH                         1

#define SPI_CR1_CPHA                          ((uint32_t) 1 << 0)
#define SPI_FIRST_CLOCK_TRANS                 0
#define SPI_SECOND_CLOCK_TRANS                1



/*************************SPI_CR2 register ******************************/

#define SPI_CR2_TXEIE_ENABLE                  ((uint32_t) 1 << 7) /* Tx buffer empty interrupt enable */
#define SPI_TXIE_MASKED                       0
#define SPI_TXIE_NOT_MASKED                   1


#define SPI_CR2_RXNEIE_ENABLE                 ((uint32_t) 1 << 6) /* Rx buffer not empty interrupt enable */
#define SPI_RXNEIE_MASKED                     0
#define SPI_RXNEIE_NOT_MASKED                 1


#define SPI_CR2_ERRIE_ENABLE                  ((uint32_t) 1 << 5) /* Error interrupt enable */
#define SPI_ERRIE_ENABELED                    1
#define SPI_ERRIE_MASKED                      0


#define SPI_CR2_FRAME_FORMAT                  ((uint32_t) 1 << 4) /* Frame format */
#define SPI_MOTOROLA_MODE                     0
#define SPI_TI_MODE                           1

#define SPI_CR2_SSOE                          ((uint32_t) 1 << 2)
#define SPI_SS_DISABLE                        0 /* Output is Disabled in master mode and the cell
                                                can work in multimaster configuration */

#define SPI_SS_ENABLE                         1 /* Output is enabled in master mode when the cell
                                                 is enabled, the cell cannot work in a multimaster
                                                 environment */
#define SPI_CR2_TXDMAEN                       ((uint32_t) 1 << 1) /* Tx buffer DMA enable */
#define SPI_TX_DMA_ENABLE                     1
#define SPI_TX_DMA_DISABLE                    0


#define SPI_CR2_RXDMAEN                       ((uint32_t) 1 << 0) /* Rx buffer DMA enable */
#define SPI_RX_DMA_ENABLE                     1
#define SPI_RX_DMA_DISABL                     0


/*************************SPI_SR register ******************************/

#define SPI_SR_FRE_FLAG                       ((uint32_t) 1 << 8) /* Frame format error */
#define SPI_FRE_ERROR                         1
#define SPI_FRE_NO_ERROR                      0


#define SPI_SR_BUSY_FLAG                      ((uint32_t) 1 << 7)
#define SPI_IS_BUSY                           1
#define SPI_IS_NOT_BUSY                       0


#define SPI_SR_TXE_FLAG                       ((uint32_t) 1 << 1) /* Transmit buffer empty */
#define SPI_TX_NOT_EMPTY                      0
#define SPI_TX_EMPTY                          1


#define SPI_SR_RXNE_FLAG                      ((uint32_t) 1 << 0) /* Recieve buffer empty */
#define SPI_RX_NOT_EMPTY                      1
#define SPI_RX_EMPTY                          0


#define SPI_1                                 SPI1
#define SPI_2                                 SPI2
#define SPI_3                                 SPI3
#define SPI_4                                 SPI4
#define SPI_5                                 SPI4
#define SPI_6                                 SPI6


#define _HAL_RCC_SPI1_CLK_ENABLE()            ((RCC->APB2ENR |= (1 << 12))
#define _HAL_RCC_SPI2_CLK_ENABLE()            ((RCC->APB2ENR |= (1 << 14))
#define _HAL_RCC_SPI3_CLK_ENABLE()            ((RCC->APB2ENR |= (1 << 15))
#define _HAL_RCC_SPI4_CLK_ENABLE()            ((RCC->APB2ENR |= (1 << 12))
#define _HAL_RCC_SPI5_CLK_ENABLE()            ((RCC->APB2ENR |= (1 << 20))
#define _HAL_RCC_SPI6_CLK_ENABLE()            ((RCC->APB2ENR |= (1 << 21))

#define RESET                                 0
#define SET                                   !RESET



/*************************SPI Data Structure ******************************/

// SPI State structure:
typedef enum {

	HAL_SPI_STATE_RESET              = 0x00,    // SPI not yet initialized or disabled
	HAL_SPI_STATE_READY              = 0x01,    // SPI initialized and ready for use
	HAL_SPI_STATE_BUSY               = 0x02,    // SPI process is ongoing
	HAL_SPI_STATE_BUSY_TX            = 0x12,    // DATA Transmission process is ongoing
	HAL_SPI_STATE_BUSY_RX            = 0x22,    // DATA Reception process is ongoing
	HAL_SPI_STATE_BUSY_TX_RX         = 0x32,    // DATA Transmission and Reception process is ongoing
	HAL_SPI_STATE_ERROR              = 0x03,    // SPI error state

}HAL_SPI_STATE_T;




// SPI Configuration Structure:
typedef struct {

	uint32_t Mode;                         /* Specifies the SPI operating mode Master or Slave */

	uint32_t Direcion;                     /* Specifies the SPI Directional mode state , unidirectional or bidirectional */

	uint32_t DataSize;                     /* Specifies the SPI data size */

	uint32_t CLKPolarity;                  /* Specifies the clock steady state */

	uint32_t CLKPhase;                     /* Specifies the clock active edge for the bit capture */

	uint32_t NSS;                          /*Specifies whether the NSS signal is managed by hardware or
	                                          by software using the SSI bit */
	uint32_t BaudRatePrescaler;            /* Specifies the baud rate prescaler value which will be used
	                                          to configure the transmit and receive SCK clock */
    uint32_t FirstBit;                     /* Specifies whether data transfers start from MSB or LSB bit */

}SPI_Init_t;


// SPI Handle Structure:
typedef struct {

	SPI_TypeDef     *Instance;              /* SPI registers base address */
	SPI_Init_t      *Init;                  /* SPI Communication parameters */
	uint8_t         *pTxBuffer;             /* Pointer to SPI TX buffer */
	uint16_t        TxTranferSize;          /* SPI Tx transfer size */
	uint16_t        TxTransferCount;        /* SPI Tx transfer count */
	uint8_t         *pRxBuffer;             /* Pointer to SPI RX buffer */
	uint16_t        RxTranferSize;          /* SPI Rx transfer size */
	uint16_t        RxTransferCount;        /* SPI Rx transfer count */
	HAL_SPI_STATE_T State;                  /* SPI Communication state */

}SPI_Handle_t;



/*************************SPI Driver exposed APIs ******************************/

//API used to do initialize the given SPI device:
void HAL_SPI_Init(SPI_Handle_t *SPI_Handle);



//API used to do master data transmission:
void HAL_SPI_MASTER_TX(SPI_Handle_t *SPI_Handle, uint8_t *TxBuffer, uint32_t len);
        /* len is length of tx data
         * *TxBuffer : pointer to the tx buffer
         */

//API used to do slave data reception:
void HAL_SPI_SLAVE_RX(SPI_Handle_t *SPI_Handle, uint8_t *RxBuffer, uint32_t len);
      /* len is length of the Rx buffer
       * *RxBuffer pointer to the RX bufer
       */

//API is used to do master data reception:
void HAL_SPI_MASTER_RX(SPI_Handle_t *SPI_Handle, uint8_t *RxBuffer, uint32_t len);
      /* len is length of the Rx buffer
       * *RxBuffer pointer to the Rx Buffer
       */

//API is used to do slave data transmission:
void HAL_SPI_SLAVE_TX(SPI_Handle_t *SPI_Handle, uint8_t *TxBuffer, uint32_t len);
      /* len is length of the Tx buffer
       * *TxBuffer pointer to the Tx Buffer
       */

//This function handles SPI interrupt request:
void HAL_I2C_SPI_IRQ_HANDLER(SPI_Handle_t *hspi);
      /* hspi pointer to a SPI_Handle_t structure that contains the
       * configuration information for spi  madule
       */



#endif /* HAL_SPI_DRIVER_H_ */
