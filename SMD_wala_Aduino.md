###SMDWalaArduino
##USB Port not recognized in UBUNTU 22.04
-try in 20.04
-install CH340 driver using https://github.com/juliagoda/CH341SER
'cd CH341SER'
'make'
'sudo make load'
-if error popped saying not permitted
-install mokutil
'sudo mokutil --disable-validate'
-enter password and restart, it asks for passwords with different charecters, enter them, finally enter 'sudo make load'. It should work.

##Upload Error
-Enter url 'https://mcudude.github.io/MiniCore/package_MCUdude_MiniCore_index.json' at file>preferences>Additional boards manager URLS
-Move to board manager and install MCUdude's 'minicore' package

-Now for uploading select 'minicore>atmega328' from board
-select appropriate port, clock : '16MHz', variants : '328pb'
-upload





