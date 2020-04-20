## STM32 Integrated Developement Framework

STM-IDF is a SDK (Software Development Kit) based on HAL (Hardware Abstraction Layer) Library.

#### What you need

Hardware:

- STM32F4 board.
- USB UART (This SDK flash to stm32 target over usart).

Software:

- Toolchain to compile code.
- Build tools - CMake to build application.
- STM-IDF that contains API (software library and source code) for STM32F4.
- Text editor to write project.
- Minicom to view log output.
- Computer with Linux OS.

### 1. Setting up build environment

#### Install GNU ARM Embedded Toolchain

The GNU Embedder Toolchain for ARM is a open source suite of tools for C, C++ and Assembly programming targeting ARM Cortex-M and Cortex-R family of processors. It includes the GNU Compiler (GCC) and is available free of charge directly from ARM for embedded software development on Windows, Linux and Mac OS X operating systems.

Follow [the link](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads) to see more detail.

Follow this instruction to install gcc-arm-none-eabi on **Linux**.

```
sudo add-apt-repository ppa:team-gcc-arm-embedded/ppa
sudo apt-get update
sudo apt-get install gcc-arm-none-eabi
```

### 2. Setting up STM-IDF

#### Dowload STM-IDF

```
git clone https://github.com/thanhphong98/stm-idf
```

#### Setup environment variable.

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

This SDK flash to STM32 target over USART3, PC10: TX_Pin, PC11: RX_Pin. You have to complete this connection before flash. To flash to STM32 board, run this command:

```
make flash
```

### 6. Viewing log output 

To view log output, run this command:

```
make monitor
```

### 7. Examples

There are many examples in stm-idf/examples folder. You can follow tutorial in README file to implement it.

## Contact us

Email: thanhphongho1998@gmail.com

Github: thanhphong98 