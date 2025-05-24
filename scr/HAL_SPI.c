#include <stdint.h>
#include "hal_SPI_driver.h"



// ENABLE THE SPI DEVICE:
static void HAL_SPI_ENABLE(SPI_TypeDef *SPIx)
{
	if(!(SPIx->CR1 & SPI_CR1_SPE))
		SPIx->CR1 |= SPI_CR1_SPEL;
}



//Disable the SPI device:
static void HAL_SPI_DISABLE(SPI_TypeDef *SPIx)
{
	SPIx->CR1 &= ~SPI_CR1_SPEL;
}



//Enables the Tx buffer empty interrupt:
static void HAL_SPI_TX_INTERRUPT_ENABLE(SPI_TypeDef *SPIx)
{
	SPIx->CR2 |= SPI_CR2_TXEIE_ENABLE;
}



//Disables the Tx buffer empty interrupt:
static void HAL_SPI_TX_INTERRUPT_DISABLE(SPI_TypeDef *SPIx)
{
	SPIx->CR2 &= ~SPI_CR2_TXEIE_ENABLE;
}



//Enables the Rx buffer not empty interrupt:
static void HAL_SPI_RXNE_INTERRUPT_ENABLE(SPI_TypeDef *SPIx)
{
	SPIx->CR2 |= SPI_CR2_RXNEIE_ENABLE;
}




//Disables the Rx buffer not empty interrupt:
static void HAL_SPI_RXNE_INTERRUPT_DISABLE(SPI_TypeDef *SPIx)
{
	SPIx->CR2 &= ~SPI_CR2_RXNEIE_ENABLE;
}




//configures SPI clk phase and polarity:
void HAL_SPI_CLK_PHASE_AND_POLARITY(SPI_TypeDef *SPIx, uint32_t phase_vaalue, uint32_t polarity_value)
{
	if(phase_value)
		SPIx->CR1 |= SPI_CR1_CPHA; // make CPHASE = 1
	else
		SPIx->CR1 &= ~SPI_CR1_CPHA; // make CPHASE = 0

	if(polarity_value)
		SPIx->CR1 |= SPI_CR1_CPOL;
	else
		SPIx->CR1 &= ~ SPI_CR1_CPOL;

}




//Configures master and slave mode:
void HAL_SPI_DEVICE_MODE(SPI_TypeDef *SPIx, uint32_t master)
{
	if(master)
		SPIx->CR1 |= SPI_CR1_MSTR;
	else
		SPIx->CR1 &= ~SPI_CR1_MSTR;

}



//Configures SPI datasize:
void HAL_SPI_DATASIZE(SPI_TypeDef *SPIx, uint32_t datasize_16, uint32_t lsbFirst)
{
    if(datasize_16)
    	SPIx->CR1 |= SPI_CR1_DFF;
    else
    	SPIx->CR1 &= ~SPI_CR1_DFF;

    if(lsbFirst)
    	SPIx->CR1 |= SPI_CR1_LSBFIRST;
    else
    	SPIx->CR1 &= ~SPI_CR1_LSBFIRST;


}


//Configures the NSS pin of the master:
void HAL_SPI_NSS_MASTER(SPI_TypeDef *SPIx, uint32_t ssm_enable)
{
	if(ssm_enable)
	{
		SPIx->CR1 |= SPI_CR1_SSM;
		SPIx->CR1 |= SPI_CR1_SSI;
	}
	else
		SPIx->CR1 &= ~SPI_CR1_SSM;

}



//configures the NSS pin for the slave:
void HAL_SPI_NSS_SLAVE(SPI_TypeDef *SPIx, uint32_t ssm_enable)
{
	if(ssm_enable)
		SPIx->CR1 |= SPI_CR1_SSM;
	else
		SPIx->CR1 &= ~SPI_CR1_SSM;
}




void HAL_SPI_Init(SPI_Handle_t *SPI_Handle)
{

}

void HAL_SPI_MASTER_TX(SPI_Handle_t *SPI_Handle, uint8_t *TxBuffer, uint32_t len)
{
	  /* populate the TxBuffer pointer address along with the size in the SPI_Handle */
	SPI_Handle->pTxBuffer = TxBuffer;
	SPI_Handle->TxTransferCount = len;
	SPI_Handle->TxTranferSize = len;

	  /* Driver is Busy in TXing data */
	SPI_Handle->State = HAL_SPI_STATE_BUSY_TX;

	  /* Enable the peripherals if its not enable */
	HAL_SPI_ENABLE(SPI_Handle->Instance);

	    /* enable TXE interrupt so the master can transmits data */
	HAL_SPI_TX_INTERRUPT_ENABLE(SPI_Handle->Instance);
}



void HAL_SPI_SLAVE_RX(SPI_Handle_t *SPI_Handle, uint8_t *RxBuffer, uint32_t len)
{

	/* populate the TxBuffer pointer address along with the size in the SPI_Handle */
	SPI_Handle->pRxBuffer = RxBuffer;
	SPI_Handle->RxTransferCount = len;
	SPI_Handle->RxTranferSize = len;

	  /* Driver is Busy in recieving data */
	SPI_Handle->State = HAL_SPI_STATE_BUSY_TX;

	HAL_SPI_ENABLE(SPI_Handle->Instance);

	  /* the slave need to recieve data , so enabling the RXNE Interrupt */
	HAL_SPI_RXNE_INTERRUPT_ENABLE(SPI_Handle->Instance);
}



void HAL_SPI_MASTER_RX(SPI_Handle_t *SPI_Handle, uint8_t *RxBuffer, uint32_t len)
{
	uint32_t val;

	   /* place some data in the Tx Buffer so the master can produce a clock */
	SPI_Handle->pTxBuffer = RxBuffer;
	SPI_Handle->TxTranferSize = len;
	SPI_Handle->TxTransferCount = len;

	   /* put data in the RxBuffer */
	SPI_Handle->pRxBuffer = RxBuffer;
	SPI_Handle->RxTranferSize = len;
	SPI_Handle->RxTransferCount = len;

	  /* Driver is Busy in recieving data */
	SPI_Handle->State = HAL_SPI_STATE_BUSY_RX;

	HAL_SPI_ENABLE(SPI_Handle->Instance);

	/* read data register once before enabling the RXNE INTERRUPT */
	      /* to make sure data register is empty */
	 val = SPI_Handle->Instance->DR;

	/* Enabling both TXE AND RXNE interrupt */
	 HAL_SPI_RXNE_INTERRUPT_ENABLE(SPI_Handle->Instance);
	 HAL_SPI_TX_INTERRUPT_ENABLE(SPI_Handle->Instance);
}




void HAL_SPI_SLAVE_TX(SPI_Handle_t *SPI_Handle, uint8_t *TxBuffer, uint32_t len)
{

      /* place the data in the Tx Buffer for the slave */
	SPI_Handle->pTxBuffer = TxBuffer;
	SPI_Handle->TxTranferSize = len;
	SPI_Handle->TxTransferCount = len;


	SPI_Handle->pRxBuffer = TxBuffer;
	SPI_Handle->RxTranferSize = len;
	SPI_Handle->RxTransferCount = len;

	  /* Driver is busy doing TX */
	SPI_Handle->State = HAL_SPI_STATE_BUSY_TX;

	HAL_SPI_ENABLE(SPI_Handle->Instance);

	/* Enabling both TXE AND RXNE interrupt */
	HAL_SPI_RXNE_INTERRUPT_ENABLE(SPI_Handle->Instance);
	HAL_SPI_TX_INTERRUPT_ENABLE(SPI_Handle->Instance);

}




void HAL_I2C_SPI_IRQ_HANDLER(SPI_Handle_t *hspi)
{
	uint32_t tmp1 = 0, tmp2 = 0;

	 /* check to see if RXNE is set in the status regeister */
	tmp1 = (hspi->Instance->SR & SPI_SR_RXNE_FLAG);
	 /* check whether RXNEIE bit is enabled in the control regester */
	tmp2 = (hspi->Instance->CR2 & SPI_CR2_RXNEIE_ENABLE);

	if((tmp1 != RESET) && (tmp2 != RESET))
	{
		/* RXNE flag is set
		 * handle the RX of data bytes
		 */
		HAL_SPI_RXNE_INTERRUPT_ENABLE(hspi);
		return;
	}

	 /* check to see if TXE is set in the status regeister */
	tmp1 = (hspi->Instance->SR & SPI_SR_TXE_FLAGXE_FLAG);
	tmp2 = (hspi->Instance->CR2 & SPI_CR2_TXEIE_ENABLEE_ENABLE);

	if((tmp1 != RESET) && (tmp2 != RESET))
	{
		/* RXNE flag is set
		 * handle the TX of data bytes
		 */
		HAL_SPI_TX_INTERRUPT_ENABLE(hspi);
		return;
	}

}



//Close TX transfer:
void HAL_SPI_TX_CLOSE_INTERRUPT(SPI_Handle_t *hspi)
{

	  /* Disable TXE interupt */
	HAL_SPI_TX_INTERRUPT_DISABLE(hspi->Instance);

	 /* if master and driver state is not in Busy RX state , then make state READY */
	if(hspi->Init->Mode && (hspi->State != HAL_SPI_STATE_BUSY_RX))
		hspi->State = HAL_SPI_STATE_READY;
}




//Handle TX interrupt:
void HAL_SPI_HANDLE_TX_INTERRUPT(SPI_Handle_t *hspi)
{
	   /* transmit data in 8 Bit mode*/
	if(hspi->Init->DataSize == SPI_8Bit_DF_ENABLE)
	{
		hspi->Instance->DR == (*hspi->pTxBuffer++);
		hspi->TxTransferCount--; // sent one byte
	}
	else
	{
		hspi->Instance->DR = *((uint16_t*)hspi->pTxBuffer);
		hspi->pTxBuffer+=2;
		hspi->TxTransferCount-=2; // sent 2 bytes in one go
	}

	if(hspi->TxTransferCount == 0)
	{
		  /* reached the end of transmission , so close the TXE interrupt */
		HAL_SPI_TX_CLOSE_INTERRUPT(hspi);
	}
}






//Close TX transfer:
void HAL_SPI_RX_CLOSE_INTERRUPT(SPI_Handle_t *hspi)
{
	while(HAL_SPI_IS_BUS_BUSY(hspi->Instance));

	  /* Disable TXE interupt */
	HAL_SPI_RXNE_INTERRUPT_DISABLE(hspi->Instance);
    hspi->State = HAL_SPI_STATE_READY;

}


//Handle RXNE interrupt:
void HAL_SPI_HANDLE_RX_INTERRUPT(SPI_Handle_t *hspi)
{
	   /* transmit data in 8 Bit mode*/
	if(hspi->Init->DataSize == SPI_8Bit_DF_ENABLE)
	{
		//NULL check
		if(hspi->pRxBuffer++)
		   *hspi->pRxBuffer++ = hspi->Instance->DR;
		hspi->xTransferCount--; // sent one byte
	}
	else
	{
		*((uint16_t*)hspi->pRxBuffer) = hspi->Instance->DR;
		hspi->pRxBuffer+=2;
		hspi->RxTransferCount-=2;
	}

	if(hspi->RxTransferCount == 0)
		HAL_SPI_RX_CLOSE_INTERRUPT(hspi);
}
