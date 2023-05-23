# GUIDELINES
Things we learned while working on the robots!

[toc]
- [Learning Roadmap](./learning_roadmap.md)
- [For Bluetooth Modules](#for-bluetooth-modules)
- [For SMD Wala Arduino](#for-smd-wala-arduino)
- [Footprints from EasyEda to Kicad](#footprints-from-easyeda-to-kicad)
 
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


## For SMD Wala Arduino 
### USB Port not recognized in UBUNTU 22.04 
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
