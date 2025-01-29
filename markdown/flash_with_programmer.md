# Flashing using STM32CubeProgrammer CLI

First, create a symbolic link to your `STM32_Programmer_CLI` in `~/.local/bin`

```bash
mkdir -p ~/.local/bin
ln -s ~/STMicroelectronics/STM32Cube/STM32CubeProgrammer/bin/STM32_Programmer_CLI ~/.local/bin/CubeProgrammer
```

## Flashing using either STLink or JLink

Create a script `flash.sh` in your project directory with the following script

```bash
#! /bin/bash
arm-none-eabi-objcopy -O binary -S build/<name>.elf build/<name>.bin

if (( $(st-info --probe 2>/dev/null | wc -l) == 1 ))
then
    CubeProgrammer -c port=JLINK -w build/<name>.bin 0x8000000 -c port=JLINK reset=SWrst
else
    CubeProgrammer -c port=SWD -w build/<name>.bin 0x8000000 -c port=SWD reset=SWrst
fi
```

Make the script executable with the following command

```bash
chmod +x flash.sh
```

Then exectue the script to flash to the board

```bash
./flash.sh
```
