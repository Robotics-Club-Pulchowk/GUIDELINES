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

## Generate Basic Code

### Pinout & Configuration
-  Clear default pinouts by pressing `Ctrl + P` and `Enter`.
-  Go to `RCC > High Speed Clock (HSE)` and select `Crystal Ceramic Resonator`.
-  Go to `SYS > Debug` and select `Serial Wire`.

    Now you can select pins for LED, UART, Timers and many more.

### Clock Configuration
- Specify `HCLK (MHx)`. We prefer to use maximum clock frequency.

### Project Manager
**Project**:
- Write `Project Name`.
- Select `Toolchanin/IDE`. We prefer to choose `Makefile`. `Cmake` was not available before.

**Code Generator**:
- Select copy all used libraries in to the project folder.
- Tick:
    - Generate eripheral initialization as a pair '.c/.h' file per peripheral.
    - Keep user code when regenerating.
    - Delete priviously generated file when not in use.

Generate code by clicking `GENERATE CODE`. Open your project folder, open terminal at your project folder and run `make` command in your terminal.

If you have selected `Cmake` for your project.
```bash
mkdir build
cd build
cmake ..
make
```
But this does not generate `.bin` file which is needed for flashing you microcontroller. To generate, you need to use `arm-none-eabi-objcopy`.
```bash
arm-none-eabi-objcopy -O binary <your_project_name.elf> <your_project_name.bin>
```

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
2. Extract and copy arm-none-eabi-gdb inside `/usr/bin`.
3. Click `debug` button in VSCODE and create `lanch.json` inside `.vscode`.
4. Update `lauch.json` the json as below.
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
            "device": "STM32F407VG",
            "interface": "swd",
            "gdbPath": "/usr/bin/gdb-multiarch"
        }
    ]
   }
   ```
5. Run `Cortex-Debug` from play `icon`.

   For `OpenOCD`, watch [this](https://www.youtube.com/watch?v=_1u7IOnivnM).


## Debugging using GDB
1. Install `OpenOCD`
``` sudo apt install openocd```

2. Install `GDB MultiArch`
``` sudo apt install gdb-multiarch```

3. For STM32F4xx
``` openocd -f /usr/share/openocd/scripts/interface/stlink.cfg -f /usr/share/openocd/scripts/target/stm32f4x.cfg ```

4. For STM32F1xx
``` openocd -f /usr/share/openocd/scripts/interface/stlink.cfg -f /usr/share/openocd/scripts/target/stm32f1x.cfg ```

If `OpenOCD server` is successfully opened in the target device, the command logs something like the following in the terminal :
```
Open On-Chip Debugger 0.12.0
Licensed under GNU GPL v2
For bug reports, read
        http://openocd.org/doc/doxygen/bugs.html
Info : auto-selecting first available session transport "hla_swd". To override use 'transport select <transport>'.
Info : The selected transport took over low-level target control. The results might differ compared to plain JTAG/SWD
Info : Listening on port 6666 for tcl connections
Info : Listening on port 4444 for telnet connections
Info : clock speed 1000 kHz
Info : STLINK V2J43S7 (API v2) VID:PID 0483:3748
Info : Target voltage: 3.309237
Info : [stm32f1x.cpu] Cortex-M3 r2p1 processor detected
Info : [stm32f1x.cpu] target has 6 breakpoints, 4 watchpoints
Info : starting gdb server for stm32f1x.cpu on 3333
Info : Listening on port 3333 for gdb connections
```

As the log says, `GDB` connections are listened on port 3333.
To connect to the target and run `GDB` go to your project directory and run:
```bash
gdb-multiarch $PWD/build/your_executable_name.elf
```

You need to tell GDB that you are running the program on a remote chip.
```bash
GNU gdb (Ubuntu 15.0.50.20240403-0ubuntu1) 15.0.50.20240403-git
Copyright (C) 2024 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from build/your_executable_name.elf...
```

Type 
```bash
target extended-remote localhost:3333
```
Now, if you do `lay src` or `list`, you will find that the program has reached a random point.
Set breakpoint at a point you desire and re-run the program. The code will halt at desired breakpoint.
Happy Debugging.

## Issues with OpenOCD
You may have chinese clones of the devices. To debug them change ` #jtag scan chain` portion of `/usr/share/openocd/scripts/target/stm32f1x.cfg` from
```ASCII
 #jtag scan chain
if { [info exists CPUTAPID] } {
   set _CPUTAPID $CPUTAPID
} else {
   if { [using_jtag] } {
      # See STM Document RM0008 Section 26.6.3
      set _CPUTAPID 0x3ba00477
   } {
      # this is the SW-DP tap id not the jtag tap id
      set _CPUTAPID 0x1ba00477
   }
}
```
to
```ASCII
 #jtag scan chain
if { [info exists CPUTAPID] } {
   set _CPUTAPID $CPUTAPID
} else {
   if { [using_jtag] } {
      # See STM Document RM0008 Section 26.6.3
      set _CPUTAPID 0x3ba00477
   } {
      # this is the SW-DP tap id not the jtag tap id
      set _CPUTAPID 0
   }
}
```


---
[home](../README.md)
