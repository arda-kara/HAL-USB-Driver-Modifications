/*
 * usb_driver.c
 *
 * Created on: Jul 12, 2024
 * Author: Arda
 */

#include "usb_driver.h"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_cdc.h"
#include "usbd_cdc_if.h"

/* USB Device Core handle declaration */
USBD_HandleTypeDef hUsbDeviceFS;

/* USB RX and TX buffers */
uint8_t UserRxBufferFS[USB_RX_BUFFER_SIZE];
uint8_t UserTxBufferFS[USB_TX_BUFFER_SIZE];

/**
 * @brief Initialize the USB device.
 *
 * This function initializes the USB device, configures the CDC class,
 * and starts the USB device.
 */
void USB_Init(void)
{
    /* Initialize the USB Device Library, add the CDC class, and start the library */
    USBD_Init(&hUsbDeviceFS, &FS_Desc, DEVICE_FS);
    USBD_RegisterClass(&hUsbDeviceFS, &USBD_CDC);
    USBD_CDC_RegisterInterface(&hUsbDeviceFS, &USBD_Interface_fops_FS);
    USBD_Start(&hUsbDeviceFS);
}

/**
 * @brief Transmit data over USB.
 *
 * This function transmits data over the USB CDC interface.
 *
 * @param Buf Pointer to the data buffer to be transmitted.
 * @param Len Length of the data to be transmitted.
 * @return HAL status indicating success or failure.
 */
HAL_StatusTypeDef USB_Transmit(uint8_t* Buf, uint16_t Len)
{
    USBD_CDC_HandleTypeDef *hcdc = (USBD_CDC_HandleTypeDef*)hUsbDeviceFS.pClassData;
    if (hcdc->TxState != 0)
    {
        return USBD_BUSY;
    }
    USBD_CDC_SetTxBuffer(&hUsbDeviceFS, Buf, Len);
    return USBD_CDC_TransmitPacket(&hUsbDeviceFS);
}

/**
 * @brief Prepare the USB device to receive data.
 *
 * This function sets up the buffer for receiving data over the USB CDC interface.
 *
 * @param Buf Pointer to the buffer where received data will be stored.
 * @return HAL status indicating success or failure.
 */
HAL_StatusTypeDef USB_Receive(uint8_t* Buf)
{
    /* This function is typically handled via the callback CDC_Receive_FS */
    USBD_CDC_SetRxBuffer(&hUsbDeviceFS, Buf);
    return USBD_CDC_ReceivePacket(&hUsbDeviceFS);
}

/**
 * @brief Reset the USB device.
 *
 * This function deinitializes the USB device, effectively resetting it.
 *
 * @return HAL status indicating success or failure.
 */
HAL_StatusTypeDef USB_Reset(void)
{
    return USBD_DeInit(&hUsbDeviceFS);
}

/**
 * @brief Suspend the USB device.
 *
 * This function suspends the USB device.
 *
 * @return HAL status indicating success or failure.
 */
HAL_StatusTypeDef USB_Suspend(void)
{
    return USBD_Suspend(&hUsbDeviceFS);
}

/**
 * @brief Resume the USB device from suspension.
 *
 * This function resumes the USB device from suspension.
 *
 * @return HAL status indicating success or failure.
 */
HAL_StatusTypeDef USB_Resume(void)
{
    return USBD_Resume(&hUsbDeviceFS);
}

/**
 * @brief Callback function to handle data reception.
 *
 * This function is called by the USB library when data is received.
 * It processes the received data and prepares the USB device for the next reception.
 *
 * @param Buf Pointer to the received data buffer.
 * @param Len Pointer to a variable containing the length of the received data.
 * @return USBD status indicating success or failure.
 */
static int8_t CDC_Receive_FS(uint8_t* Buf, uint32_t *Len)
{
    /* Process received data here */
    USBD_CDC_SetRxBuffer(&hUsbDeviceFS, &Buf[0]);
    USBD_CDC_ReceivePacket(&hUsbDeviceFS);

    // The actual length of received data is managed by the USB library and can be processed here
    // Example: printf("Received %lu bytes\n", *Len);

    return (USBD_OK);
}

/* CDC Interface callback structure */
USBD_CDC_ItfTypeDef USBD_Interface_fops_FS = {
    CDC_Init_FS,
    CDC_DeInit_FS,
    CDC_Control_FS,
    CDC_Receive_FS
};

/**
 * @brief Initialize the CDC interface.
 *
 * This function sets up the application buffers for the CDC interface.
 *
 * @return USBD status indicating success or failure.
 */
static int8_t CDC_Init_FS(void)
{
    /* Set Application Buffers */
    USBD_CDC_SetTxBuffer(&hUsbDeviceFS, UserTxBufferFS, 0);
    USBD_CDC_SetRxBuffer(&hUsbDeviceFS, UserRxBufferFS);
    return (USBD_OK);
}

/**
 * @brief Deinitialize the CDC interface.
 *
 * This function deinitializes the CDC interface.
 *
 * @return USBD status indicating success or failure.
 */
static int8_t CDC_DeInit_FS(void)
{
    return (USBD_OK);
}

/**
 * @brief Handle CDC control requests.
 *
 * This function handles control requests from the USB host.
 *
 * @param cmd Command code.
 * @param pbuf Pointer to the data buffer.
 * @param length Length of the data.
 * @return USBD status indicating success or failure.
 */
static int8_t CDC_Control_FS(uint8_t cmd, uint8_t* pbuf, uint16_t length)
{
    switch(cmd)
    {
        case CDC_SEND_ENCAPSULATED_COMMAND:
            break;
        case CDC_GET_ENCAPSULATED_RESPONSE:
            break;
        case CDC_SET_COMM_FEATURE:
            break;
        case CDC_GET_COMM_FEATURE:
            break;
        case CDC_CLEAR_COMM_FEATURE:
            break;
        case CDC_SET_LINE_CODING:
            break;
        case CDC_GET_LINE_CODING:
            break;
        case CDC_SET_CONTROL_LINE_STATE:
            break;
        case CDC_SEND_BREAK:
            break;
        default:
            break;
    }
    return (USBD_OK);
}
