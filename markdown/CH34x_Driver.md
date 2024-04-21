# CH34x Driver

- Black Wala TTL
- SMD Wala Arduino


## Ubuntu 22.04 LTS (Jammy Jellyfish)

Removing `brltty` works.

```bash
sudo apt autoremove brltty
```


## Ubuntu 20.04 

Install CH340 driver from `https://github.com/juliagoda/CH341SER` 

```bash
git clone https://github.com/juliagoda/CH341SER.git
cd CH341SER
make
sudo make load
```
If error popped saying not permitted 
- install mokutil `sudo mokutil --disable-validate` 
- enter password and restart, it asks for passwords with different charecters, enter them, finally enter `sudo make load`. It should work.


## Upload Error

If upload error persists while uploading on SMD wala Arduino after doing all of above. Try :

- Enter url `https://mcudude.github.io/MiniCore/package_MCUdude_MiniCore_index.json` at `file>preferences>Additional boards manager URLS` 
- Move to board manager and install MCUdude's `minicore` package

- Now for uploading select `minicore>atmega328` from board, select appropriate port, clock : `16MHz`, variants : `328pb` , upload

---
[Home](../README.md)