sed -i 's|./Startup/startup_stm32h755xx_CM4.s|./Core/startup/startup_stm32h755xx_CM4.s|g' CM4/mx-generated.cmake
sed -i 's|./Startup/startup_stm32h755xx_CM7.s|./Core/startup/startup_stm32h755xx_CM7.s|g' CM7/mx-generated.cmake
git checkout CM7/stm32h755xx_flash_CM7.ld
