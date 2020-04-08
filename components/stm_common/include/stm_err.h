#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t stm_err_t;

#define STM_OK          0
#define STM_FAIL        -1

#define STM_ERR_NO_MEM              0x101
#define STM_ERR_INVALID_ARG         0x102
#define STM_ERR_INVALID_STATE       0x103
#define STM_ERR_INVALID_SIZE        0x104
#define STM_ERR_NOT_FOUND           0x105
#define STM_ERR_NOT_SUPPORTED       0x106
#define STM_ERR_TIMEOUT             0x107
#define STM_ERR_INVALID_RESPONSE    0x108
#define STM_ERR_INVALID_CRC         0x109
#define STM_ERR_INVALID_VERSION     0x10A


#ifdef __cplusplus
}
#endif