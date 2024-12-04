# Flashing using STM32CubeProgrammer CLI

First, create a symbolic link to your `STM32_Programmer_CLI` in `~/.local/bin`
```bash
mkdir -p ~/.local/bin
ln -s ~/STMicroelectronics/STM32Cube/STM32CubeProgrammer/bin/STM32_Programmer_CLI ~/.local/bin/CubeProgrammer
```

## Flashing using STLink

Create a script `flash.sh` in your project directory with the following script
```bash
#! /bin/bash
CubeProgrammer -c port=SWD -w <build_directory>/<program_name>.bin 0x8000000 -c port=SWD reset=SWrst
```

## Flashing using JLink

Create a script `flash.sh` in your project directory with the following script
```bash
#! /bin/bash
CubeProgrammer -c port=JLINK -w <build_directory>/<program_name>.bin 0x8000000 -c port=JLINK reset=SWrst
```
