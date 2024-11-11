/**
 * Copyright (c) @CompanyNameMagicTag 2023-2023. All rights reserved. \n
 *
 * Description: SPI Sample Source. \n
 * Author: @CompanyNameTag \n
 * History: \n
 * 2023-06-25, Create file. \n
 */
#include "led.h"
#include "common_def.h"
#include "dma.h"
#include "gpio.h"
#include "hal_gpio.h"
#include "osal_debug.h"
#include "osal_task.h"
#include "pinctrl.h"
#include "platform_core.h"
#include "soc_osal.h"

#ifndef debug
// #define debug
#endif

#ifndef dma_enable
// #define dma_enable
#endif

/**
 * @brief 将原始数据编码为 LED 驱动器可识别的数据
 *
 * @param input_data 原始数据 @ref grb_t
 * @param output_data 编码后的数据 (每个字节包含两个 4-bit 编码信息)
 * @param length  数据长度 (LED 数量) @ref LED_COUNT
 */
void encode_led_data(grb_t *input_data, uint8_t *output_data, uint32_t length)
{
    for (uint32_t i = 0; i < length; i++) {
        uint8_t *byte_ptr = (uint8_t *)(&input_data[i]);
        for (uint8_t color = 0; color < LED_DATE_LEN; color++) {
            uint8_t byte = byte_ptr[color];
            for (uint8_t bit_pair = 0; bit_pair < 4; bit_pair++) {
                uint8_t bit_val_1 = (byte >> (7 - 2 * bit_pair)) & 0x01; // 取出高位
                uint8_t bit_val_2 = (byte >> (6 - 2 * bit_pair)) & 0x01; // 取出低位

                uint8_t encoded_val_1 = (bit_val_1 == 0) ? 0b1000 : 0b1100;
                uint8_t encoded_val_2 = (bit_val_2 == 0) ? 0b1000 : 0b1100;

                // 将两个 4-bit 编码信息组合到一个字节
                output_data[i * LED_DATE_LEN * 4 + color * 4 + bit_pair] = (encoded_val_1 << 4) | encoded_val_2;
            }
        }
    }
#ifdef debug
    osal_printk("encode_led_data: ");
    for (uint32_t i = 0; i < length * LED_DATE_LEN * 4; i++) {
        osal_printk("0x%02x ", output_data[i]);
    }
    osal_printk("\r\n");
#endif
}

static inline void app_spi_init_pin(pin_t pin, spi_bus_t bus)
{ // TODO: 增加防止重复初始化的逻辑
    errcode_t ret;
    // 发送reset信号
    // uapi_pin_set_mode(pin, HAL_PIO_FUNC_GPIO);
    // uapi_gpio_set_dir(pin, GPIO_DIRECTION_OUTPUT);
    // uapi_gpio_set_val(pin, GPIO_LEVEL_LOW);
    // osal_udelay(100);
#ifdef debug
    osal_printk("spi%d pinmux start!\r\n", bus); // TODO:debug
#endif
    switch (bus) {
        case SPI_BUS_0:
            ret = uapi_pin_set_mode(pin, HAL_PIO_SPI0_TXD);
            break;
        case SPI_BUS_1:
            ret = uapi_pin_set_mode(pin, HAL_PIO_SPI1_TXD);
            break;
        case SPI_BUS_2:
            ret = uapi_pin_set_mode(pin, HAL_PIO_SPI2_TXD);
            break;
        default:
            osal_printk("spi bus error!\r\n");
            ret = ERRCODE_DMA_REG_ADDR_INVALID;
            break;
    }
    if (ret != ERRCODE_SUCC) {
        osal_printk("set pin mode failed with errcode = %d\n", ret);
    }
}

static inline void __attribute__((always_inline)) app_spi_master_init_config(spi_bus_t bus)
{
#ifdef debug
    osal_printk("spi%d master init start!\r\n", bus); // TODO:debug
#endif
    spi_attr_t config = {0};
    spi_extra_attr_t ext_config = {0};

#define SPI_SLAVE_NUM 1
#define SPI_FREQUENCY 3
#define SPI_CLK_POLARITY 0
#define SPI_CLK_PHASE 0
#define SPI_FRAME_FORMAT 0
#define SPI_FRAME_FORMAT_STANDARD 0
#define SPI_FRAME_SIZE_8 0x1f
#define SPI_TMOD 0
#define SPI_WAIT_CYCLES 0x10

    config.is_slave = false;
    config.slave_num = SPI_SLAVE_NUM;
    config.bus_clk = SPI_CLK_FREQ;
    config.freq_mhz = SPI_FREQUENCY;
    config.clk_polarity = SPI_CLK_POLARITY;
    config.clk_phase = SPI_CLK_PHASE;
    config.frame_format = SPI_FRAME_FORMAT;
    config.spi_frame_format = HAL_SPI_FRAME_FORMAT_STANDARD;
    config.frame_size = SPI_FRAME_SIZE_8;
    config.tmod = SPI_TMOD;
    config.sste = 1;

    errcode_t ret;
#ifdef dma_enable
    ext_config.tx_use_dma = true;
#ifdef debug
    osal_printk("spi%d master dma init start!\r\n", bus); // TODO:debug
#endif
    ret = uapi_dma_init();
    if (ret != ERRCODE_SUCC) {
        osal_printk("uapi_dma_init failed .\n");
    }
#ifdef debug
    osal_printk("spi%d master dma init end!\r\n", bus);   // TODO:debug
    osal_printk("spi%d master dma open start!\r\n", bus); // TODO:debug
#endif
    ret = uapi_dma_open();
    if (ret != ERRCODE_SUCC) {
        osal_printk("uapi_dma_init failed .\n");
    }
#ifdef debug
    osal_printk("spi%d master dma open end!\r\n", bus); // TODO:debug
#endif
#endif
    ret = uapi_spi_init(bus, &config, &ext_config);
    if (ret != ERRCODE_SUCC) {
        osal_printk("uapi_spi_init failed .\n");
        osal_printk("errcode = %d\n", ret);
    } else {
        osal_printk("uapi_spi_init success .\n");
    }
#ifdef debug
    osal_printk("spi%d master init end!\r\n", bus); // TODO:debug
#endif
}

/**
 * @brief 处理用于LED数据传输的SPI通信的任务函数。
 *
 * 该函数初始化SPI引脚和SPI主机配置，编码LED数据，并通过SPI循环发送，直到传输成功。
 *
 * @param arg 指向LED数据和配置结构的指针 (led_data_p)。
 * @return 当任务完成时返回NULL。
 */
void *spi_led_transfer_task(led_data_p arg)
{
    if (arg != NULL) {
        osal_printk("spi_master_task arg is not NULL\n");
    } else {
        osal_printk("spi_master_task arg is NULL\nspi_master_task exit\n");
        return NULL;
    }

    /* SPI master init config. */
    app_spi_master_init_config(arg->bus);

    int SPI_TRANSFER_LEN = arg->length * LED_DATE_LEN * 4;

    /* SPI data config. */
    uint8_t *tx_data = osal_kmalloc(SPI_TRANSFER_LEN, (unsigned int)NULL);

    encode_led_data(arg->led_data, tx_data, arg->length);

    spi_xfer_data_t data = {
        .tx_buff = tx_data,
        .tx_bytes = SPI_TRANSFER_LEN,
    };
    // 复位信号
    uint8_t tx_reset_data[80] = {0};
    spi_xfer_data_t reset_data = {
        .tx_buff = tx_reset_data,
        .tx_bytes = 80,
    };

    while (1) {
        osal_printk("spi%d master send start!\r\n", arg->bus);
        /* SPI pinmux. */
        app_spi_init_pin(arg->pin, arg->bus);
        uapi_spi_master_write(arg->bus, &reset_data, 0xFFFFFFFF);
        if (uapi_spi_master_write(arg->bus, &data, 0xFFFFFFFF) == ERRCODE_SUCC) {
            osal_printk("spi%d master send succ!\r\n", arg->bus);
            uapi_pin_set_mode(arg->pin, HAL_PIO_FUNC_GPIO);
            uapi_gpio_set_dir(arg->pin, GPIO_DIRECTION_OUTPUT);
            uapi_gpio_set_val(arg->pin, GPIO_LEVEL_LOW);
            break;
        } else {
#ifdef debug
            osal_printk("spi%d master send failed!\r\n", arg->bus);
#endif
            continue;
        }
    }
    osal_kfree(tx_data);
    return NULL;
}

#include "app_init.h"
#include "gpio.h"
#include "led.h"
#include "osal_task.h"
#include "pinctrl.h"
#include "platform_core.h"
#include "soc_osal.h"
#include "trng.h"

#ifndef debug
// #define debug
#endif

static void spi_master_entry(void)
{
#define SPI_TASK_STACK_SIZE 0x800
#define SPI_TASK_PRIO OSAL_TASK_PRIORITY_HIGH

    osal_task *taskid;

    // 创建任务调度
    // osal_kthread_lock();

// 定义所需的led_data_t结构体的数量
#define LED_DATA_COUNT 6

    // 初始化LED数据
    grb_t led_data_0[10];
    grb_t led_data_1[14];
    grb_t led_data_28[14];
    grb_t led_data_29[15];
    grb_t led_data_30[15];
    grb_t led_data_31[16];

    grb_t *led_data_array[LED_DATA_COUNT] = {led_data_0,  led_data_1,  led_data_28,
                                             led_data_29, led_data_30, led_data_31};
    uint8_t led_data_lengths[LED_DATA_COUNT] = {10, 14, 14, 15, 15, 16};
    pin_t led_data_pins[LED_DATA_COUNT] = {0, 1, 28, 29, 30, 31};

    // 缓冲区，用于存储生成的随机数
    uint8_t random_buffer[3];

    // 生成并填充随机数据
    for (int j = 0; j < LED_DATA_COUNT; j++) {
        for (int i = 0; i < led_data_lengths[j]; i++) {
            // 获取3字节的随机数，用于填充green, red, blue
            errcode_t ret = uapi_drv_cipher_trng_get_random_bytes(random_buffer, sizeof(random_buffer));
            if (ret == ERRCODE_SUCC) {
                // 将随机数填充到led_data数组中
                led_data_array[j][i].green = random_buffer[0] & 0b1111;
                led_data_array[j][i].red = random_buffer[1] & 0b1111;
                led_data_array[j][i].blue = random_buffer[2] & 0b1111;
            } else {
                // 处理错误情况，例如输出错误信息
                osal_printk(
                    "Failed to get random number for LED data, index: %d, "
                    "led_data_index: %d\n",
                    i, j);
            }
        }
    }

    // 创建6个led_data_t结构体并创建任务
    for (int j = 0; j < LED_DATA_COUNT; j++) {
        led_data_t led_data_config = {
            .led_data = led_data_array[j],
            .length = led_data_lengths[j],
            .pin = led_data_pins[j],
            .bus = SPI_BUS_0,
        };
        // 创建任务
        taskid = osal_kthread_create((osal_kthread_handler)spi_led_transfer_task, &led_data_config, "spi_master_task",
                                     SPI_TASK_STACK_SIZE);
        osal_msleep(10); ///< 100ms延时, 防止任务创建失败
        if (taskid == NULL) {
            osal_printk("create spi_master_task %d failed .\n", j);
            return;
        } else {
            osal_printk("create spi_master_task %d success .\n", j);
            osal_kfree(taskid);
        }
        int ret;
        ret = osal_kthread_set_priority(taskid, SPI_TASK_PRIO);
        if (ret != OSAL_SUCCESS) {
            osal_printk("set spi_master_task %d priority failed .\n", j);
            osal_kfree(taskid);
        } else {
            osal_kfree(taskid);
        }
    }
}

/* Run the spi_master_entry. */
app_run(spi_master_entry);