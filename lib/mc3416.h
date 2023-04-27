#ifndef _MC34X9_H
#define _MC34X9_H

#include "stdbool.h"
#include "main.h"

extern TS_state_accel state_accel;

/******************************************************************************
 *** Register Map
 *****************************************************************************/
#define MC34X9_REG_DEV_STAT         (0x05)
#define MC34X9_REG_INTR_CTRL        (0x06)
#define MC34X9_REG_MODE             (0x07)
#define MC34X9_REG_SR               (0x08)
#define MC34X9_REG_MOTION_CTRL      (0x09)
#define MC34X9_REG_FIFO_STAT        (0x0A)
#define MC34X9_REG_FIFO_RD_P        (0x0B)
#define MC34X9_REG_FIFO_WR_P        (0x0C)
#define MC34X9_REG_XOUT_EX_L        (0x0D)
#define MC34X9_REG_XOUT_MSB         (0x0E)
#define MC34X9_REG_YOUT_LSB         (0x0F)
#define MC34X9_REG_YOUT_MSB         (0x10)
#define MC34X9_REG_ZOUT_LSB         (0x11)
#define MC34X9_REG_ZOUT_MSB         (0x12)
#define MC34X9_REG_STATUS           (0x13)
#define MC34X9_REG_INTR_STAT        (0x14)
#define MC34X9_REG_PROD             (0x18)
#define MC34X9_REG_RANGE_C          (0x20)
#define MC34X9_REG_XOFFL            (0x21)
#define MC34X9_REG_XOFFH            (0x22)
#define MC34X9_REG_YOFFL            (0x23)
#define MC34X9_REG_YOFFH            (0x24)
#define MC34X9_REG_ZOFFL            (0x25)
#define MC34X9_REG_ZOFFH            (0x26)
#define MC34X9_REG_XGAIN            (0x27)
#define MC34X9_REG_YGAIN            (0x28)
#define MC34X9_REG_ZGAIN            (0x29)

#define MC34X9_REG_TF_THRESH_LSB    (0x40)
#define MC34X9_REG_TF_THRESH_MSB    (0x41)
#define MC34X9_REG_TF_DB            (0x42)
#define MC34X9_REG_AM_THRESH_LSB    (0x43)
#define MC34X9_REG_AM_THRESH_MSB    (0x44)
#define MC34X9_REG_AM_DB            (0x45)
#define MC34X9_REG_SHK_THRESH_LSB   (0x46)
#define MC34X9_REG_SHK_THRESH_MSB   (0x47)
#define MC34X9_REG_PK_P2P_DUR_THRESH_LSB    (0x48)
#define MC34X9_REG_PK_P2P_DUR_THRESH_MSB    (0x49)
#define MC34X9_REG_TIMER_CTRL       (0x4A)

typedef enum{
  MC34X9_MODE_SLEEP    = 0,
  MC34X9_MODE_CWAKE    = 1,
  MC34X9_MODE_RESERVED = 2,
  MC34X9_MODE_STANDBY  = 3,
}   MC34X9_mode_t;

typedef enum{
  MC34X9_RANGE_2G    = 0,
  MC34X9_RANGE_4G    = 1,
  MC34X9_RANGE_8G    = 2,
  MC34X9_RANGE_16G   = 3,
  MC34X9_RANGE_12G   = 4,
  MC34X9_RANGE_END,
}   MC34X9_range_t;

typedef enum{
  MC34X9_SR_25Hz            = 0x10,
  MC34X9_SR_50Hz            = 0x11,
  MC34X9_SR_62_5Hz          = 0x12,
  MC34X9_SR_100Hz           = 0x13,
  MC34X9_SR_125Hz           = 0x14,
  MC34X9_SR_250Hz           = 0x15,
  MC34X9_SR_500Hz           = 0x16,
  MC34X9_SR_DEFAULT_1000Hz  = 0x17,
  MC34X9_SR_END,
}   MC34X9_sr_t;

typedef enum{
  MC34X9_TILT_FEAT = 0,
  MC34X9_ANYM_FEAT = 2,
  MC34X9_SHAKE_FEAT = 3,
  MC34X9_TILT35_FEAT = 4,
}   MC34X9_motion_feature_t;

typedef enum{
  MC34X9_FIFO_CTL_DISABLE = 0,
  MC34X9_FIFO_CTL_ENABLE,
  MC34X9_FIFO_CTL_END,
}   MC34X9_fifo_ctl_t;

typedef enum{
  MC34X9_FIFO_MODE_NORMAL = 0,
  MC34X9_FIFO_MODE_WATERMARK,
  MC34X9_FIFO_MODE_END,
}   MC34X9_fifo_mode_t;

typedef enum{
  MC34X9_COMB_INT_DISABLE = 0,
  MC34X9_COMB_INT_ENABLE,
  MC34X9_COMB_INT_END,
}   MC34X9_fifo_int_t;

TE_init MC34X9_Init(TS_state_system *state_system);
uint8_t MC34X9Read(I2C_HandleTypeDef *hi2cx, uint8_t add, TS_state_accel *state_accel);

#endif



