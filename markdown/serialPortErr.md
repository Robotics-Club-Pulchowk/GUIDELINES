# SERIAL PORT ERRORS

## Upload Error

Sometimes, `upload error` can persist due to `grant access` to serial port. 

Grant `read/write` permission to serial port:
```bash
sudo chmod a+rw <path/to/serial/port>
```
For example:
```bash
sudo chmod a+rw /dev/ttyUSB0
```

Provide access to serial port:
```bash
sudo usermod -a -G dialout $USER
```

Now try to upload. It will solve the uplaod problem if it is related to it.


## Cannot Open Serial Port

Serial ports sometimes can be locked if it was not closed properly last time. To open it again, the process of serial port have to be killed.

Kill serial port:
```bash
sudo fuser -k <path/to/serial/port>
```

---
[Home](../README.md)