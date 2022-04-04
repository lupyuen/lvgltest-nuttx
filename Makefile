############################################################################
# apps/examples/lvgltest/Makefile
#
# Licensed to the Apache Software Foundation (ASF) under one or more
# contributor license agreements.  See the NOTICE file distributed with
# this work for additional information regarding copyright ownership.  The
# ASF licenses this file to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance with the
# License.  You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
# License for the specific language governing permissions and limitations
# under the License.
#
############################################################################

include $(APPDIR)/Make.defs

# LittleVGL demo built-in application info

PROGNAME = lvgltest
PRIORITY = $(CONFIG_EXAMPLES_LVGLTEST_PRIORITY)
STACKSIZE = $(CONFIG_EXAMPLES_LVGLTEST_STACKSIZE)
MODULE = $(CONFIG_EXAMPLES_LVGLTEST)

# LittleVGL demo Example

CSRCS += fbdev.c lcddev.c

ifneq ($(CONFIG_INPUT_TOUCHSCREEN)$(CONFIG_INPUT_MOUSE),)
CSRCS += tp.c tp_cal.c
endif

MAINSRC = lvgltest.c

CFLAGS += ${shell $(DEFINE) "$(CC)" LV_LVGL_H_INCLUDE_SIMPLE} -Wno-format
CXXFLAGS += ${shell $(DEFINE) "$(CC)" LV_LVGL_H_INCLUDE_SIMPLE} -Wno-format

context::

distclean::
	$(call DELDIR, $(LVGL_EXAMPLES_UNPACKNAME))
	$(call DELFILE, $(LVGL_EXAMPLES_TARBALL))

include $(APPDIR)/Application.mk
