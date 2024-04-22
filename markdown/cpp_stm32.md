# C++ in STM32

`STM32CubeMX` generates `Makefile` and `CMakeLists.txt`that only compiles `C Programs`. So we need to modify them in order to compile `C++ Programs`.


## Using Makefile

1. Generate a basic codes for STM32 using `STM32CubeMX` with `Makefile` selected for toolchain. Click [here](./stm32_initial_guide.md) for guide.

2. Add `CXX SOURCES` after `C_ SOURCES`.
    ```Makefile
    # C sources
    C_SOURCES =  \
    Core/Src/main.c \
    Core/Src/gpio.c \
    Core/Src/stm32f4xx_it.c \
    Core/Src/stm32f4xx_hal_msp.c \
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c \
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c \
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c \
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c \
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c \
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c \
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c \
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c \
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c \
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c \
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c \
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c \
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c \
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c \
    Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c \
    Core/Src/system_stm32f4xx.c \
    Core/Src/sysmem.c \
    Core/Src/syscalls.c
    ```
-   ```Makefile
    # CXX sources
    CXX_SOURCES = 
    ```
    ```Makefile
    # ASM sources
    ASM_SOURCES =  \
    startup_stm32f407xx.s
    ```

3. Add Compiler for C++.
    ```Makefile
    ifdef GCC_PATH
    CC = $(GCC_PATH)/$(PREFIX)gcc
    AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
    CP = $(GCC_PATH)/$(PREFIX)objcopy
    SZ = $(GCC_PATH)/$(PREFIX)size
    ```
-   ```Makefile
    CXX = $(GCC_PATH)/$(PREFIX)g++
    ```
    ```Makefile
    else
    CC = $(PREFIX)gcc
    AS = $(PREFIX)gcc -x assembler-with-cpp
    CP = $(PREFIX)objcopy
    SZ = $(PREFIX)size
    ```
-   ```Makefile
    CXX = $(PREFIX)g++
    ```
    ```Makefile
    endif
    HEX = $(CP) -O ihex
    BIN = $(CP) -O binary -S
    ```

4. Add `CXX_INCLUDE` after `C_INCLUDES`.
   ```Makefile
    # AS includes
    AS_INCLUDES = 

    # C includes
    C_INCLUDES =  \
    -ICore/Inc \
    -IDrivers/STM32F4xx_HAL_Driver/Inc \
    -IDrivers/STM32F4xx_HAL_Driver/Inc/Legacy \
    -IDrivers/CMSIS/Device/ST/STM32F4xx/Include \
    -IDrivers/CMSIS/Include
   ```
-  ```Makefile
   # CXX Includes
    CXX_INCLUDES = \
    $(C_INCLUDES)
   ```

5. Add `CXXFLAGS`.
   ```Makefile
    # compile gcc flags
    ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

    CFLAGS += $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

    ifeq ($(DEBUG), 1)
    CFLAGS += -g -gdwarf-2
    endif


    # Generate dependency information
    CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"
    ```
-   ```Makefile
    CXXFLAGS = $(CFLAGS) $(CXX_INCLUDES)
    ```

6. Add list of objects for CXX.
    ```Makefile
    # list of objects
    OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
    vpath %.c $(sort $(dir $(C_SOURCES)))
    # list of ASM program objects
    OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
    vpath %.s $(sort $(dir $(ASM_SOURCES)))
    ```
-   ```Makefile
    # list of CXX program objects
    OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(CXX_SOURCES:.cpp=.o)))
    vpath %.cpp $(sort $(dir $(CXX_SOURCES)))
    ```
    ```Makefile
    $(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
    	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

    $(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
    	$(AS) -c $(CFLAGS) $< -o $@
    ```
-   ```Makefile
    $(BUILD_DIR)/%.o: %.cpp Makefile | $(BUILD_DIR)
    	$(CXX) -c $(CXXFLAGS) $< -o $@
    ```
    ```Makefile
    $(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
    	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
    	$(SZ) $@

    $(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
    	$(HEX) $< $@
    
    $(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
    	$(BIN) $< $@	
    
    $(BUILD_DIR):
    	mkdir $@	
    ```

 `Makefile` is ready to compile `C++` file. We need to add `.cpp` file to `CXX_sources`.


 ## Using CMake

 CMake is new in STM32CubeMx which makes easier to compile than Makefile. CMake generates Makefile from `CMakeLists.txt`.

 1. Generate a code by selecting `cmake` as toolchain in STM32CubeMX.

2. Add these lines to set compiler for CXX.
   ```cmake
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS ON)
    ```
3. Enabe CXX support by editing the line `enable_language(C ASM)`.
    ```cmake
    enable_language(CXX C ASM)
    ```

Now C++ programs can be compiled. We need to add them inside `target_sources`.


---
[Home](../README.md)