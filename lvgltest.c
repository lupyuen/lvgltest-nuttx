/****************************************************************************
 * apps/examples/lvgltest/lvgltest.c
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

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <sys/boardctl.h>
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include <debug.h>

#include <lvgl/lvgl.h>

#include "fbdev.h"
#include "lcddev.h"

#if defined(CONFIG_INPUT_TOUCHSCREEN) || defined(CONFIG_INPUT_MOUSE)
#include "tp.h"
#include "tp_cal.h"
#endif

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Should we perform board-specific driver initialization?  There are two
 * ways that board initialization can occur:  1) automatically via
 * board_late_initialize() during bootupif CONFIG_BOARD_LATE_INITIALIZE
 * or 2).
 * via a call to boardctl() if the interface is enabled
 * (CONFIG_BOARDCTL=y).
 * If this task is running as an NSH built-in application, then that
 * initialization has probably already been performed otherwise we do it
 * here.
 */

#undef NEED_BOARDINIT

#if defined(CONFIG_BOARDCTL) && !defined(CONFIG_NSH_ARCHINIT)
#  define NEED_BOARDINIT 1
#endif

#define DISPLAY_BUFFER_SIZE (CONFIG_LV_HOR_RES * \
                              CONFIG_EXAMPLES_LVGLTEST_BUFF_SIZE)

/* LVGL Canvas Size */

#define CANVAS_WIDTH   100
#define CANVAS_HEIGHT  100

/****************************************************************************
 * Public Functions Prototypes
 ****************************************************************************/

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: monitor_cb
 *
 * Description:
 *   Monitoring callback from lvgl every time the screen is flushed.
 *
 ****************************************************************************/

static void monitor_cb(lv_disp_drv_t * disp_drv, uint32_t time, uint32_t px)
{
  ginfo("%" PRIu32 " px refreshed in %" PRIu32 " ms\n", px, time);
}

/****************************************************************************
 * Private Data
 ****************************************************************************/

static lv_color_t buffer1[DISPLAY_BUFFER_SIZE];

#ifdef CONFIG_EXAMPLES_LVGLTEST_DOUBLE_BUFFERING
static lv_color_t buffer2[DISPLAY_BUFFER_SIZE];
#else
# define buffer2 NULL
#endif

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: create_widgets
 *
 * Description:
 *   Create the LVGL Widgets that will be rendered on the display. Based on
 *   https://docs.lvgl.io/7.11/widgets/label.html#label-recoloring-and-scrolling
 *   https://docs.lvgl.io/7.11/widgets/canvas.html#drawing-on-the-canvas-and-rotate
 *   https://docs.lvgl.io/7.11/widgets/msgbox.html#simple-message-box
 *
 ****************************************************************************/

static void create_widgets(void)
{
  //  Get the Active Screen
  lv_obj_t *screen = lv_scr_act();

  //  Create a Label Widget
  lv_obj_t *label = lv_label_create(screen, NULL);

  //  Wrap long lines in the label text
  lv_label_set_long_mode(label, LV_LABEL_LONG_BREAK);

  //  Interpret color codes in the label text
  lv_label_set_recolor(label, true);

  //  Center align the label text
  lv_label_set_align(label, LV_LABEL_ALIGN_CENTER);

  //  Set the label text and colors
  lv_label_set_text(
    label, 
    "#ff0000 HELLO# "    //  Red Text
    "#00aa00 PINEDIO# "  //  Green Text
    "#0000ff STACK!# "   //  Blue Text
  );

  //  Set the label width
  lv_obj_set_width(label, 200);

  //  Align the label to the center of the screen, shift 30 pixels up
  lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, -30);

#ifdef CONFIG_USE_LV_CANVAS  //  LVGL Canvas Demo
  lv_draw_rect_dsc_t rect_dsc;
  lv_draw_rect_dsc_init(&rect_dsc);
  rect_dsc.radius = 10;
  rect_dsc.bg_opa = LV_OPA_COVER;
  rect_dsc.bg_grad_dir = LV_GRAD_DIR_HOR;
  rect_dsc.bg_color = LV_COLOR_BLUE;
  rect_dsc.bg_grad_color = LV_COLOR_GREEN;
  rect_dsc.border_width = 2;
  rect_dsc.border_opa = LV_OPA_90;
  rect_dsc.border_color = LV_COLOR_SILVER;
  rect_dsc.shadow_width = 5;
  rect_dsc.shadow_ofs_x = 5;
  rect_dsc.shadow_ofs_y = 5;

  lv_draw_label_dsc_t label_dsc;
  lv_draw_label_dsc_init(&label_dsc);
  label_dsc.color = LV_COLOR_YELLOW;

  static lv_color_t cbuf[LV_CANVAS_BUF_SIZE_TRUE_COLOR(CANVAS_WIDTH, CANVAS_HEIGHT)];

  lv_obj_t * canvas = lv_canvas_create(lv_scr_act(), NULL);
  lv_canvas_set_buffer(canvas, cbuf, CANVAS_WIDTH, CANVAS_HEIGHT, LV_IMG_CF_TRUE_COLOR);
  lv_obj_align(canvas, NULL, LV_ALIGN_CENTER, 0, 50);
  lv_canvas_fill_bg(canvas, LV_COLOR_WHITE, LV_OPA_TRANSP);

  lv_canvas_draw_rect(canvas, 0, 0, 95, 95, &rect_dsc);
#endif  //  CONFIG_USE_LV_CANVAS

#ifdef CONFIG_EXAMPLES_LVGLTEST_MESSAGEBOX  //  LVGL Message Box Demo
  //  Create a Message Box Widget
  lv_obj_t *msgbox = lv_msgbox_create(screen, NULL);

  //  Set the Message Box Text
  lv_msgbox_set_text(msgbox, "Hello PineDio Stack!");

  //  Define the Message Box Buttons
  static const char *btns[] = {"Cancel", "OK", ""};

  //  Add the buttons to the Message Box
  lv_msgbox_add_btns(msgbox, btns);
#endif  //  CONFIG_EXAMPLES_LVGLTEST_MESSAGEBOX
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: main or lvgltest_main
 *
 * Description:
 *
 * Input Parameters:
 *   Standard argc and argv
 *
 * Returned Value:
 *   Zero on success; a positive, non-zero value on failure.
 *
 ****************************************************************************/

int main(int argc, FAR char *argv[])
{
  lv_disp_drv_t disp_drv;
  lv_disp_buf_t disp_buf;

#if defined(CONFIG_INPUT_TOUCHSCREEN) || defined(CONFIG_INPUT_MOUSE)
#ifndef CONFIG_EXAMPLES_LVGLTEST_CALIBRATE
  lv_point_t p[4];

  /* top left */

  p[0].x = 0;
  p[0].y = 0;

  /* top right */

  p[1].x = LV_HOR_RES;
  p[1].y = 0;

  /* bottom left */

  p[2].x = 0;
  p[2].y = LV_VER_RES;

  /* bottom right */

  p[3].x = LV_HOR_RES;
  p[3].y = LV_VER_RES;
#endif
#endif

#ifdef NEED_BOARDINIT
  /* Perform board-specific driver initialization */

  boardctl(BOARDIOC_INIT, 0);

#ifdef CONFIG_BOARDCTL_FINALINIT
  /* Perform architecture-specific final-initialization (if configured) */

  boardctl(BOARDIOC_FINALINIT, 0);
#endif
#endif

  /* LVGL initialization */

  lv_init();

  /* Basic LVGL display driver initialization */

  lv_disp_buf_init(&disp_buf, buffer1, buffer2, DISPLAY_BUFFER_SIZE);
  lv_disp_drv_init(&disp_drv);
  disp_drv.buffer = &disp_buf;
  disp_drv.monitor_cb = monitor_cb;

  /* Display interface initialization */

  if (lcddev_init(&disp_drv) != EXIT_SUCCESS)
    {
      /* Failed to use lcd driver falling back to framebuffer */

      if (fbdev_init(&disp_drv) != EXIT_SUCCESS)
        {
          /* No possible drivers left, fail */

          return EXIT_FAILURE;
        }
    }

  lv_disp_drv_register(&disp_drv);

#if defined(CONFIG_INPUT_TOUCHSCREEN) || defined(CONFIG_INPUT_MOUSE)
  /* Touchpad Initialization */

  tp_init();
  lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;

  /* This function will be called periodically (by the library) to get the
   * mouse position and state.
   */

  indev_drv.read_cb = tp_read;
  lv_indev_drv_register(&indev_drv);
#endif

  /* Create the widgets for display */

  create_widgets();

#if defined(CONFIG_INPUT_TOUCHSCREEN) || defined(CONFIG_INPUT_MOUSE)
  /* Start TP calibration */

#ifdef CONFIG_EXAMPLES_LVGLTEST_CALIBRATE
  tp_cal_create();
#else
  tp_set_cal_values(p, p + 1, p + 2, p + 3);
#endif
#endif

  /* Handle LVGL tasks */

  while (1)
    {
      lv_task_handler();
      usleep(10000);
    }

  return EXIT_SUCCESS;
}
