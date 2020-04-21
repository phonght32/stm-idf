# Example: PWM

This example shows how to use TIMER pins as PWM generation output.

### Feature

- PD12: PWM output.
- PWM Frequency: 1 Hz.
- PWM duty cycle: 50 %.

### How to use

- Follow this [link](https://github.com/thanhphong98/stm-idf) to setup STM-IDF on your computer.

- Copy example project into your workspace.
- Go to pwm project:

```
cd path_to_pwm
```

- Build the project by running command below. If there are no error occurs, project binary .bin file will generate into build folder.

```
make build all
```

- This SDK flash to STM32 target and send log output over USART3 (default). Make sure you have already connected  USB UART to USART3, then run this command:

```
make flash
```

- If flash success, LED GREEN connected to PD12 will blinky.
- To view log output, run this command:

```
make monitor
```

