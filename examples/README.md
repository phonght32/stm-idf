

# Example tutorial

### How to use

- Follow this [link](https://github.com/thanhphong98/stm-idf) to setup STM-IDF on your computer.

- Copy any example project into your workspace.
- Go to copy project:

```
cd path_to_example_project
```

- Build the project by running command below. If there are no error occurs, project binary .bin file will generate into build folder.

```
make build all
```

- Flash to target:

```
# flash over USART
make flash_usart
# flash over ST-LinkV2
make flash_stlink
```

- To view log output, run the command below . This SDK send log output over USART3, tx_pin: PC10, rx_pin: PC11.

```
make monitor
```

