# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/gustavo/STM32/LWIP_FREERTOS/CM7"
  "/home/gustavo/STM32/LWIP_FREERTOS/CM7/build"
  "/home/gustavo/STM32/LWIP_FREERTOS/CM7"
  "/home/gustavo/STM32/LWIP_FREERTOS/CM7/tmp"
  "/home/gustavo/STM32/LWIP_FREERTOS/CM7/src/LWIP_FREERTOS_CM7-stamp"
  "/home/gustavo/STM32/LWIP_FREERTOS/CM7/src"
  "/home/gustavo/STM32/LWIP_FREERTOS/CM7/src/LWIP_FREERTOS_CM7-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/gustavo/STM32/LWIP_FREERTOS/CM7/src/LWIP_FREERTOS_CM7-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/gustavo/STM32/LWIP_FREERTOS/CM7/src/LWIP_FREERTOS_CM7-stamp${cfgdir}") # cfgdir has leading slash
endif()
