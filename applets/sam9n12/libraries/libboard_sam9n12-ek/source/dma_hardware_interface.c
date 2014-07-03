/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support 
 * ----------------------------------------------------------------------------
 * Copyright (c) 2011, Atmel Corporation
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Atmel's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ----------------------------------------------------------------------------
 */

/** \addtogroup dmad_module
 *
 * \section DmaHw Dma Hardware Interface Usage
 * <ul>
 * <li> The DMA controller can handle the transfer between peripherals and memory 
 * and so receives the triggers from the peripherals. The hardware interface number
 * are getting from DMAIF_Get_ChannelNumber().</li>
 
 * <li> DMAIF_IsValidatedPeripherOnDma() helps to check if the given DMAC has associated 
 * peripheral identifier coded by the given  peripheral.</li>
 * 
 * </ul>
*/
/*@{*/
/*@}*/

 /*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/
#include <board.h>

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/
/** Array of DMA Channel definition for SAM9N12 chip*/
static const DmaHardwareInterface dmaHwIf[] = {
    /* dmac, peripheral,  T/R, Channel Number*/
       {0,   ID_HSMCI,    0,   0},
       {0,   ID_HSMCI,    1,   0},
       {0,   ID_SPI0,     0,   1},
       {0,   ID_SPI0,     1,   2},
       {0,   ID_SPI1,     0,   3},
       {0,   ID_SPI1,     1,   4},
       {0,   ID_USART0,   0,   5},
       {0,   ID_USART0,   1,   6},
       {0,   ID_USART1,   0,   7},
       {0,   ID_USART1,   1,   8},
       {0,   ID_USART2,   0,   9},
       {0,   ID_USART2,   1,  10},
       {0,   ID_USART3,   0,  11},
       {0,   ID_USART3,   1,  12},
       {0,   ID_TWI0,     0,  13},
       {0,   ID_TWI0,     1,  14},
       {0,   ID_TWI1,     0,  15},
       {0,   ID_TWI1,     1,  16},
       {0,   ID_UART0,    0,  17},
       {0,   ID_UART0,    1,  18},
       {0,   ID_UART1,    0,  19},
       {0,   ID_UART1,    1,  20},
       {0,   ID_SSC,      0,  21},
       {0,   ID_SSC,      1,  22},
       {0,   ID_ADC,      1,  23},
       {0,   PERI_DBGU,   0,  24},
       {0,   PERI_DBGU,   1,  25}
};

/*----------------------------------------------------------------------------
 *        Consts
 *----------------------------------------------------------------------------*/
 /** Number of recognized peripheral identifier code for DMA0/1. */
#define NUMPERIPHERAL   (sizeof(dmaHwIf) / sizeof (DmaHardwareInterface))

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Get peripheral identifier coded for hardware handshaking interface
 *
 * \param bDmac      DMA Controller number.
 * \param bPeriphID  Peripheral ID.
 * \param bTransfer  Transfer type 0: Tx, 1 :Rx.
 * \return 0-15 peripheral identifier coded.
 *         0xff : no associated peripheral identifier coded.
 */
uint8_t DMAIF_Get_ChannelNumber (uint8_t bDmac,
                                 uint8_t bPeriphID, 
                                 uint8_t bTransfer)
{
    uint8_t i;
    for (i = 0; i < NUMPERIPHERAL; i++)
    {
        if ((dmaHwIf[i].bDmac == bDmac) && (dmaHwIf[i].bPeriphID == bPeriphID) && (dmaHwIf[i].bTransfer == bTransfer))
        {
            return dmaHwIf[i].bIfID;
        }
    }
    return 0xff;
}

/**
 * \brief Check if the given DMAC has associated peripheral identifier coded by 
 * the given  peripheral.
 *
 * \param bDmac      DMA Controller number.
 * \param bPeriphID  Peripheral ID (0xff : memory only).
 * \return 1:  Is a validated peripher. 0: no associated peripheral identifier coded.
 */
uint8_t DMAIF_IsValidatedPeripherOnDma( uint8_t bDmac, uint8_t bPeriphID)
{
    uint8_t i;
    /* It is always validated when transfer to memory */
    if (bPeriphID == 0xFF) {
        return 1;
    }
    for (i = 0; i < NUMPERIPHERAL; i++)
    {
        if ((dmaHwIf[i].bDmac == bDmac) && (dmaHwIf[i].bPeriphID == bPeriphID))
        {
            return 1;
        }
    }
    return 0;
}


