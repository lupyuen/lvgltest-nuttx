/****************************************************************************
 * apps/examples/lvgltest/lcddev.h
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

#ifndef __APPS_EXAMPLES_LVGLTEST_LCDDEV_H
#define __APPS_EXAMPLES_LVGLTEST_LCDDEV_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <stdint.h>
#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

int lcddev_init(lv_disp_drv_t *lv_drvr);
lv_disp_drv_t *get_disp_drv(void);
lv_disp_buf_t *get_disp_buf(void);
void init_disp_drv(lv_disp_drv_t *disp_drv,
  lv_disp_buf_t *disp_buf,
  void (*monitor_cb)(struct _disp_drv_t *, uint32_t, uint32_t));
void init_disp_buf(lv_disp_buf_t *disp_buf);

#ifdef __cplusplus
}
#endif

#endif /* __APPS_EXAMPLES_LVGLTEST_LCDDEV_H */
