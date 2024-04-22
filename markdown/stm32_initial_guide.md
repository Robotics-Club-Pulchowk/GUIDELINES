# STM32 Initial Guide

## Software Install

-----------------------------------------------------------------------------
| Software            | Description                                 | Install Guide                                                                      |
| ------------------- | ------------------------------------------- | ---------------------------------------------------------------------------------- |
| STM32CubeMx         | STM32 configuration tool                    | Install from [here](https://www.st.com/en/development-tools/stm32cubemx.html)      |
| STM32CubeProgrammer | Program and debug STM32 devices             | Install from [here](https://www.st.com/en/development-tools/stm32cubeprog.html)    |
| STM32CubeMonitor    | Plot graphs for monitoring                  | Install from [here](https://www.st.com/en/development-tools/stm32cubemonitor.html) |
| stlink-tools        | Command line tools for STM32 flash          | sudo apt install stlink-tools                                                      |
| arm-none-eabi-gcc   | GCC compiler for ARM-based microcontrollers | sudo apt install gcc-arm-none-eabi                                                 |
-----------------------------------------------------------------------------

## Edit Makefile for Flash

For `stlink`, add these lines below your `Makefile`.
```Makefile
flash:
    st-flash write $(BUILD_DIR)/$(TARGET).bin 0x8000000
```

For `jlink`, add these lines  below you makefile.
```Makefile
device = STM32F103C8
$(BUILD_DIR)/jflash: $(BUILD_DIR)/$(TARGET).bin
	@touch $@
	@echo device $(device) > $@
	@echo -e si 1'\n'speed 4000 >> $@
	@echo loadbin $< 0x8000000 >> $@
	@echo -e r'\n'g'\n'qc >> $@

jflash: $(BUILD_DIR)/jflash
	JLinkExe -commanderscript $<
```

Use `make flash` or `make jflash` commands in order to flash.

## Debugging Setup

1. Install `Cortex-Debug` by `marus25` in VSCODE.
2. Download Arm Toolchain from [here](https://developer.arm.com/Tools%20and%20Software/GNU%20Toolchain).
3. Extract and copy arm-none-eabi-gdb inside `/usr/bin`.
4. Click `debug` button in VSCODE and create `lanch.json` inside `.vscode`.
5. Update `lauch.json` the json as below.
   ```json
   {
    // Use IntelliSense to learn about possible attributes.
    // Hover to view descriptions of existing attributes.
    // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Cortex Debug",
            "cwd": "${workspaceFolder}",
            "executable": "${workspaceFolder}/build/base-0.1.elf",
            "request": "launch",
            "type": "cortex-debug",
            "runToEntryPoint": "main",
            "servertype": "stlink",
            "device": "STM32F407VG"
        }
    ]
   }
   ```
6. Run `Coretex-Debug` from play `icon`.

[home](../README.md)