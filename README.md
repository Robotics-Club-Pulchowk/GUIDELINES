# GUIDELINES
Things we learned while working on the robots!

[toc]
- [Learning Roadmap](https://github.com/Robotics-Club-Pulchowk/guide-for-new-members)
- [For Bluetooth Modules](#for-bluetooth-modules)
- [For SMD Wala Arduino and Black wala USB to TTL](#for-smd-wala-arduino-and-black-wala-usb-to-ttl)
- [Footprints from EasyEda to Kicad](#footprints-from-easyeda-to-kicad)
- [For Joystick Controller](#for-joystick-controller)
 
## For Bluetooth Modules
### Checklist of parameters to set:
- [ ] Password
- [ ] UART parameters (baud rate, stop bit, parity)
- [ ] Role
- [ ] Bind address
- [ ] CMODE value

### Guidelines
1. Make sure that both the Bluetooth modules have the same password.
   - Set with `AT+PSWD`

2. Also make sure that UART parameters in each module are:
    - baud rate: 115200
    - stop bit: 1
    - parity: 0 <br>
  `AT+UART=115200,1,0`

3. Set roles in each module as follows:
   - In one module, set role to 0 to make it slave:
      `AT+ROLE=0`
   - In another module, set role to 1 to make it master:
      `AT+ROLE=1`


4. Bind the address of slave to the master.
    - Get address of slave first and note it:
      `AT+ADDR?`
      (e.g. `0021:09:01183A`)
    - Then set the bind address in master:
      `AT+BIND=21,9,1183A`
      (Leading 0s can be ignored; also replace `:` with `,`)

5. Change the value of CMODE in both modules to 0.
  'CMODE=1' means 'connect to any address'.  <br>
   `AT+CMODE=1`
 
### Reference for AT commands
- https://beatyourbit.com/Files/Docs/HC05%20AT%20Command%20List.pdf


## For SMD Wala Arduino and Black wala USB to TTL
### USB Port not recognized in UBUNTU 22.04 
- first try
      `sudo apt remove brltty `
  - if issue stiil occurs then follow below.
- try in 20.04 
- install CH340 driver using `https://github.com/juliagoda/CH341SER` 
      `cd CH341SER`  
      `make`
      `sudo make load`
   - if error popped saying not permitted 
   - install mokutil `sudo mokutil --disable-validate` 
   - enter password and restart, it asks for passwords with different charecters, enter them, finally enter `sudo make load`. It should work.

### Upload Error 
- Enter url `https://mcudude.github.io/MiniCore/package_MCUdude_MiniCore_index.json` at `file>preferences>Additional boards manager URLS` 
- Move to board manager and install MCUdude's `minicore` package

- Now for uploading select `minicore>atmega328` from board, select appropriate port, clock : `16MHz`, variants : `328pb` , upload


## Footprints from EasyEda to Kicad
1. Install easyeda2kicad package using pip  
   `pip install easyeda2kicad`
2. Install wxpython package using pip  
   `pip install wxpython`
3. Find and save the footprints of a part number found in [LCSC](lcsc.com)  
   `easyeda2kicad --lcsc_id <partnumber> --full --output <filename>.kicad_sym`


## For Joystick Controller
### PS4 and ESP32
1. **Setup Arduino IDE**
   - Install `esp32 board` from Arduino Board Manager by Espressif.
   - Downlaod and install `PS4 controller library`. [Click here](https://www.arduino.cc/reference/en/libraries/ps4controller/)
   - For `ESP32 Wroom`, select board `ESP32-DA-WROOM-MODULE` from `Tools > Board > esp32`.
   - Select port from `Tools > Port`.

2. **Setup PS4 Controller**
   - Find out bluetooth mac address of esp32. Copy and upload below code to esp32.
      ```cpp
      #include "esp_bt_main.h"
      #include "esp_bt_device.h"
      #include "BluetoothSerial.h"

      BluetoothSerial SerialBT;

      void printDeviceAddress() {

        const uint8_t* point = esp_bt_dev_get_address();
        for (int i = 0; i < 6; i++) {
          char str[3];
          sprintf(str, "%02X", (int)point[i]);
          Serial.print(str);
          if (i < 5){
            Serial.print(":");
          }
        }
      }
      void setup() {
        Serial.begin(115200);
         SerialBT.begin("ESP32 Bluetooth");
        printDeviceAddress();
      }

      void loop() {}
      ```
   - Open `Serial Monitor`, you can see Bluetooth MAC address at bottom line.
   - [Download SixaxisPairTool](https://sixaxispairtool.en.lo4d.com/download) and install. This is only for windows platform.
   - Open SixaxisPairTool and Plug the `PS4 controller` to your PC using `USB Cable`. Driver for the controller will be installed, if it is first time.
   - Write the `Bluetooth Mac Address` of the `ESP32` into `Master MAC Adrress Field` and click update.

3. **Upload Code**
   - [Downlaod esp32_ps4 codes](https://github.com/Robotics-Club-Pulchowk/Arduino_Codes/tree/main/esp32_ps4) and upload it to `ESP32`. You must define `DEBUG` to see data on `Serial Monitor`.
   - Press `PS4 Button` to power on and connect. If you have set the mac address correctly, it will connect to ESP32 indicated by `solid blue color`.
   - See data on Serial Monitor. The control data is transmitted through `UART2` pins of esp32.

### PS4 and Pico W
- Download, install and setup `Pico W SDK`. [See here](https://github.com/raspberrypi/pico-sdk.git).
- Clone this repository: `https://github.com/Robotics-Club-Pulchowk/picow_ds4.git` and update submodule.
   ```bash
   git clone https://github.com/Robotics-Club-Pulchowk/picow_ds4.git
   cd picow_ds4
   git submodule update --init --recursive
   ```
- Find out `MAC Address` of `PS4 Controller`. In easy way, connect it to yout PC and see the MAC Address.
- Get into the source code folder, open `Src/bt_hid.c`, scroll down a little and replace `remote_addr_string` value by the MAC address of PS4.
- To print data on 'Serial Monitor' enable stdio usb by editing this line of `Src/CMakeLists.txt`.
   ```cmake
   pico_enable_stdio_usb(picow_ds4 1)
   ```
- From the project directory, make build folder, execute cmake and makefile.
   ```bash
   # make build directory
   mkdir build
   # execute cmake file from build directory
   cd build
   cmake ..
   # Build project using make
   make -j8
   ```
- Hold the `boot button` and connect the `Pico W` to `PC` using `USB`.
- Drag and drop the `picow_ds4.uf2` file from `build/src` to `Pico W Mass Storage`. You also can use similar command.
   ```bash
   # Just hit `tab` `tab` after `/media`.
   cp picow_ds4.uf2 /media/pi/PICOW
   ```
- Long press `share` and `PS4 button` simultaneous untill `fast blink of PS4 LED`. It will connect to `Pico W`. Pico W blinks its `green LED` if no controller is connected and `solid green` if it detects and connects to a controller.

*Pico W sends uart packet same as ESP32 througth its UART0 default Tx and Rx pin i.e. pin 0 and 1.*