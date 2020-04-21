# Example: Timer ETR function

This example shows how to configure Timer pins as ETR (extern clock) function to count pulse input.

### Feature

- ETR Pin: PA5.
- Counter mode: up.
- Max reload value: 10.

### How to use

- Follow this [link](https://github.com/thanhphong98/stm-idf) to setup STM-IDF on your computer.

- Copy example project into your workspace.
- Go to etr project:

```
cd path_to_etr
```

- Build the project by running command below. If there are no error occurs, project binary .bin file will generate into build folder.

```
make build all
```

- This SDK flash to STM32 target and send log output over USART3 (default). Make sure you have already connected  USB UART to USART3, then run this command:

```
make flash
```

- If flash success, connect clock source has any frequency or generate clock by button to PA5.
- To view log output, run this command:

```
make monitor
```

