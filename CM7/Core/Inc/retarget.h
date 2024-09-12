/*
 * @brief	IO redirection support
 *
 * This file adds re-direction support to the library for various
 * projects. It can be configured in one of 3 ways - no redirection,
 * redirection via a UART, or redirection via semihosting. If NDEBUG
 * not defined, all printf statements will do nothing with the
 * output being throw away. If NDEBUG is not defined, then the choice of
 * output is selected by the DEBUG_SEMIHOSTING define. If the
 * DEBUG_SEMIHOSTING is not defined, then output is redirected via
 * the UART. If DEBUG_SEMIHOSTING is defined, then output will be
 * attempted to be redirected via semihosting. If the UART method
 * is used, then the Board_UARTPutChar and Board_UARTGetChar
 * functions must be defined to be used by this driver and the UART
 * must already be initialized to the correct settings.
 *
 */
#pragma once

#include "stm32h7xx_hal.h"

extern UART_HandleTypeDef huart3;

#define PUTCHAR_PROTOTYPE inline int __io_putchar(int ch)

PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART1 and Loop until the end of transmission */
  HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 0xFFFF);

  return ch;
}
