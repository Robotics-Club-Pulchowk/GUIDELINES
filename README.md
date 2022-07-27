# GUIDELINES
Things we learned while working on the robots!

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
