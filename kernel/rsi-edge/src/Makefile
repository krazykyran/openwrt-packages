#/*
# Copyright (c) 2017 Redpine Signals Inc. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 	1. Redistributions of source code must retain the above copyright
# 	   notice, this list of conditions and the following disclaimer.
#
# 	2. Redistributions in binary form must reproduce the above copyright
# 	   notice, this list of conditions and the following disclaimer in the
# 	   documentation and/or other materials provided with the distribution.
#
# 	3. Neither the name of the copyright holder nor the names of its
# 	   contributors may be used to endorse or promote products derived from
# 	   this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION). HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#*/

rsi_91x-y									+= rsi_91x_main.o
rsi_91x-y									+= rsi_91x_core.o
rsi_91x-y									+= rsi_91x_mac80211.o
rsi_91x-y									+= rsi_91x_mgmt.o
rsi_91x-y									+= rsi_91x_hal.o
rsi_91x-y									+= rsi_91x_ps.o
rsi_91x-$(CONFIG_RSI_DEBUGFS)				+= rsi_91x_debugfs.o
rsi_91x-$(CONFIG_RSI_BT_ALONE)				+= rsi_91x_hci.o
rsi_91x-$(CONFIG_RSI_COEX)					+= rsi_91x_hci.o
rsi_91x-$(CONFIG_RSI_COEX)					+= rsi_91x_coex.o
rsi_91x-$(CONFIG_RSI_ZIGB)					+= rsi_91x_zigb.o
rsi_91x-$(CONFIG_RSI_11K)					+= rsi_91x_rrm.o
	
ccflags-$(CONFIG_CARACALLA_BOARD)			+= -DCONFIG_CARACALLA_BOARD
ccflags-$(CONFIG_RSI_MULTI_MODE)			+= -DCONFIG_RSI_MULTI_MODE
ccflags-$(CONFIG_HW_SCAN_OFFLOAD)			+= -DCONFIG_HW_SCAN_OFFLOAD
ccflags-$(CONFIG_SDIO_INTR_POLL)			+= -DCONFIG_SDIO_INTR_POLL
ccflags-$(CONFIG_RSI_DEBUGFS)				+= -DCONFIG_RSI_DEBUGFS
ccflags-$(CONFIG_RSI_BT_ALONE)				+= -CONFIG_RSI_BT_ALONE
ccflags-$(CONFIG_RSI_COEX)					+= -DCONFIG_RSI_COEX
ccflags-$(CONFIG_RSI_ZIGB)					+= -DCONFIG_RSI_ZIGB
ccflags-$(CONFIG_RSI_WOW)					+= -DCONFIG_RSI_WOW
ccflags-$(CONFIG_RSI_WOW)					+= -DRSI_HW_CONN_MONITOR
ccflags-$(CONFIG_RSI_P2P)					+= -DCONFIG_RSI_P2P
ccflags-$(CONFIG_RSI_11K)					+= -DCONFIG_RSI_11K
ccflags-$(RSI_DEBUG_RRM)					+= -DRSI_DEBUG_RRM
ccflags-$(CONFIG_RSI_NO_SDIO_MULTIBLOCK)	+= -DCONFIG_RSI_NO_SDIO_MULTIBLOCK

obj-$(CONFIG_RSI_91X)						+= rsi_91x.o
obj-$(CONFIG_RSI_SDIO)						+= rsi_sdio.o
obj-$(CONFIG_RSI_USB)						+= rsi_usb.o
