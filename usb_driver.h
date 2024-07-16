/*
 * usb_driver.h
 *
 * Created on: Jul 12, 2024
 * Author: Arda
 */

#ifndef USB_DRIVER_H_
#define USB_DRIVER_H_

#include "stm32f1xx_hal.h"

/* Define buffer sizes */
#define USB_RX_BUFFER_SIZE  2048
#define USB_TX_BUFFER_SIZE  2048

/**
 * @brief Initialize the USB device.
 *
 * This function initializes the USB device, configures the CDC class,
 * and starts the USB device.
 */
void USB_Init(void);

/**
 * @brief Transmit data over USB.
 *
 * @param Buf Pointer to the data buffer to be transmitted.
 * @param Len Length of the data to be transmitted.
 * @return HAL status indicating success or failure.
 */
HAL_StatusTypeDef USB_Transmit(uint8_t* Buf, uint16_t Len);

/**
 * @brief Prepare the USB device to receive data.
 *
 * @param Buf Pointer to the buffer where received data will be stored.
 * @return HAL status indicating success or failure.
 */
HAL_StatusTypeDef USB_Receive(uint8_t* Buf);

/**
 * @brief Reset the USB device.
 *
 * @return HAL status indicating success or failure.
 */
HAL_StatusTypeDef USB_Reset(void);

/**
 * @brief Suspend the USB device.
 *
 * @return HAL status indicating success or failure.
 */
HAL_StatusTypeDef USB_Suspend(void);

/**
 * @brief Resume the USB device from suspension.
 *
 * @return HAL status indicating success or failure.
 */
HAL_StatusTypeDef USB_Resume(void);

#endif /* USB_DRIVER_H_ */
