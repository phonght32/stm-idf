

# Example: Rosserial

This example shows how to communicate between STM32 and ROS by rosserial.

### Feature

- Rosserial port: UART4, PA0 TX, PA1 RX, baudrate 115200.
- Publish topic: "chatter".
- Subscribe topic: "led"

### How to use

- Follow this [link](https://github.com/thanhphong98/stm-idf) to setup STM-IDF on your computer.

- Copy example project into your workspace.
- Go to blinky project:

```
cd path_to_gpio
```

- Build the project by running command below. If there are no error occurs, project binary .bin file will generate into build folder.

```
make build all
```

- This SDK flash to STM32 target and send log output over USART3 (default). Make sure you have already connected  USB UART to USART3, then run this command:

```
make flash
```

- If flash success, 4 LEDs will blinky.
- To view log output, run this command:

```
make monitor
```

- On computer, run this command to view publish data to "chatter" topic:

```
roscore
rosrun rosserial_python serial_node.py _baud:=115200
```

- Run this command to publish data to "led" topic. If success, LED GREEN on board will toggle level.

```
rostopic pub /led std_msgs/UInt16 "data: 0" 
```



