## STM32 Integrated Developement Framework

STM-IDF is a SDK (Software Development Kit) based on HAL (Hardware Abstraction Layer) Library.

#### What you need

Hardware:

- STM32 board.
- USB UART or ST-LinkV2 programmer/debugger.

Software:

- Toolchain GNU ARM Embedded to compile code.
- Build tools - CMake to build application.
- STM-IDF that contains API (software library and source code) for STM32.
- Text editor.
- Terminal (support ANSI/VT100) to view log output: minicom, putty,...
- Computer with Linux OS.

### 1. Setting up environment

#### Install GNU ARM Embedded Toolchain

The GNU Embedder Toolchain for ARM is a open source suite of tools for C, C++ and Assembly programming targeting ARM Cortex-M and Cortex-R family of processors. It includes the GNU Compiler (GCC) and is available free of charge directly from ARM for embedded software development on Windows, Linux and Mac OS X operating systems.

Follow [the link](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads) to see more detail.

Follow this instruction to install gcc-arm-none-eabi on **Linux**.

```
sudo add-apt-repository ppa:team-gcc-arm-embedded/ppa
sudo apt-get update
sudo apt-get install gcc-arm-none-eabi
```

#### Install ST-LinkV2 driver 

Install dependency:

```
sudo apt-get install git make cmake libusb-1.0-0-dev
sudo apt-get install gcc build-essential
```

Install ST-LinkV2 driver:

```
cd ~download_directory
git clone https://github.com/texane/stlink
cd stlink
cmake .
make

sudo cp bin/st-* /usr/local/bin
sudo cp etc/udev/rules.d/49-stlinkv* /etc/udev/rules.d/
```

### 2. Setting up STM-IDF

#### Dowload STM-IDF

```
git clone https://github.com/thanhphong98/stm-idf
```

#### Setup environment variable

You need to export STM_IDF_PATH to use STM-IDF. Open your bash file and add this instruction:

```
export STM_IDF_PATH=path_to_stm_idf
```

Don't forget to source your bash file:

```
source ~/.bashrc
```

Check your setup:

```
printenv STM_IDF_PATH
```

### 3. Configuring the project 

STM-IDF build all source code in any folder which contains **component.mk** file. Header folder default in include folder which same directory with the **component.mk** file. You also can configure path to source and header folder by using **INCLUDE_PATHS** and **SOURCE_PATHS** .

You can get the template project using STM-IDF at this [link](https://github.com/thanhphong98/stm32-template).

### 4. Compling the project

Build the project by running:

```
make build all
```

If the are no error occurs. the build will finish by generating binary .bin file into build folder.

### 5. Flashing to target

Flash over USART:

```
make flash_usart
```

Flash over ST-LinkV2:

```
make flash_stlink
```

### 6. Viewing log output 

This SDK send log out put over UART3, tx_pin: PC10, rx_pin: PC11.

To view log output, run this command:

```
make monitor
```

### 7. Examples

There are many examples in stm-idf/examples folder. Follow tutorial in README file to implement.

## Problem

Any problem when using this SDK, please create in [Issues.](https://github.com/thanhphong98/stm-idf/issues)