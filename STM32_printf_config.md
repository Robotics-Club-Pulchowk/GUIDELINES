# STM32 Printf Config

## Basic Task

1. Create `printf_config.c` inside `Core/Src`.

2. Copy and paste this code.
    ```cpp
    #include "stm32f4xx_hal.h"

    #ifdef STDIO_USB

    #include "usbd_cdc_if.h"

    int _write(int file, char *data, int len)
    {
        CDC_Transmit_FS((uint8_t*)data, (uint16_t)len);
        return len;
    }

    #else

    int _write(int file, char *data, int len)
    {
        int i  = 0;
        for (; i < len; ++i)
        {
            ITM_SendChar(data[i]);
        }
        return i;
    }

    #endif
    ```

    This config is for `STM32F407VGT`. For others, you need to modify `hal` include.

3. Modify Makefile
    - Add `printf_config.c` on `C_SOURCES`.
    - Add `-u _printf_float` on `LDFLAGS` to print floating points.


## STM32 Cube Programmer
1. Open `STM32CubeProgrammer`
2. Click `SVW`.
3. Specify frequency correctly.
4. Start

## Serial Monitor
1. Open `STM32CubeMX`
2. Go to `Connectivity > USB_OTG_FS`
3. Select Mode: `Device Only`
4. Go  to `Middleware and Software Pack > USB_Device`
5. Select Class For FS IP:  `Communication Device Class (Virtual Prt Com)`
6. Generate Code
7. Open Makefile and add `-DSTDIO_USB` on `C_DEFS`
8. Connect STM32 using `Micro-B` to your PC.
8. Compile and flash
8. Open `Serial Monitor` and connect.

---
[Home](./README.md)