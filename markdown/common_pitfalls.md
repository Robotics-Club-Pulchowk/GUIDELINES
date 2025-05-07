## Initializing hardware peripherals inside constructors
In CPP, if you instantiate an object globally, and the class that the object belongs to deals with hardware peripherals like **timers**, **uart**, etc. then the constructor for that object could be called before the peripherals have been initialized. This will cause your program to get stuck in **HardFault_Handler** and the program cannot further be executed.

To avoid this write your class's constructors and initializing functions in such a way that they access the hardware peripherals inside their **init()** functions and not in their constructor.
### Example Usage
In Robot.h file
```cpp
class Robot {
  Encoder e1;
  UART uart;
  public:
    void init(void);
}

extern Robot robot;
```
In Robot.cpp file
```cpp
Robot robot;

void Robot::init(void) {
  e1 = Encoder{&htim1, CPR, 5, true};
  uart = UART{&huart3, UARTMode::UART_TRANSMITTING, sizeof(Twist)};

  e1.init();
  uart.init();
}
```
Writing your functions in this way ensures that the program accesses the peripherals only after they have been initialized insided **main.c**.
