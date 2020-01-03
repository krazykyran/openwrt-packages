/*
 * Copyright (c) 2017 Redpine Signals Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 	1. Redistributions of source code must retain the above copyright
 * 	   notice, this list of conditions and the following disclaimer.
 *
 * 	2. Redistributions in binary form must reproduce the above copyright
 * 	   notice, this list of conditions and the following disclaimer in the
 * 	   documentation and/or other materials provided with the distribution.
 *
 * 	3. Neither the name of the copyright holder nor the names of its
 * 	   contributors may be used to endorse or promote products derived from
 * 	   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION). HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/module.h>
#include <linux/firmware.h>
#include "rsi_mgmt.h"
#include "rsi_common.h"
#include "rsi_hal.h"
#if defined(CONFIG_RSI_BT_ALONE) || defined(CONFIG_RSI_COEX)
#include "rsi_hci.h"
#endif
#ifdef CONFIG_RSI_COEX
#include "rsi_coex.h"
#endif

u16 rsi_zone_enabled =	INFO_ZONE |
			INIT_ZONE |
			MGMT_TX_ZONE |
			MGMT_RX_ZONE |
			//DATA_TX_ZONE |
			//DATA_RX_ZONE |
			//FSM_ZONE |
			//ISR_ZONE |
			ERR_ZONE |
			0;
module_param(rsi_zone_enabled, ushort, S_IRUGO);
MODULE_PARM_DESC(rsi_zone_enabled,
		 "BIT(0) - ERROR ZONE \
		  BIT(1) - INFO ZONE \
		  BIT(2) - INIT ZONE \
		  BIT(3) - MGMT TX ZONE \
		  BIT(4) - MGMT RX ZONE \
		  BIT(5) - DATA TX ZONE \
		  BIT(6) - DATA RX ZONE \
		  BIT(7) - FSM ZONE \
		  BIT(8) - ISR ZONE");

/* Default operating mode is Wi-Fi alone */
int dev_oper_mode_count;
#ifdef CONFIG_CARACALLA_BOARD
#if defined (CONFIG_RSI_COEX) || defined(CONFIG_RSI_BT_ALONE)
u16 dev_oper_mode = DEV_OPMODE_STA_BT_DUAL;
#else
u16 dev_oper_mode = DEV_OPMODE_WIFI_ALONE;
#endif
#else
#ifdef CONFIG_RSI_MULTI_MODE
u16 dev_oper_mode[5] = {DEV_OPMODE_WIFI_ALONE,
						0xff, 0xff, 0xff, 0xff};
#else
u16 dev_oper_mode = DEV_OPMODE_WIFI_ALONE;
#endif
#endif

#ifdef CONFIG_RSI_MULTI_MODE
module_param_array(dev_oper_mode, ushort, &dev_oper_mode_count, S_IRUGO);
#else
module_param(dev_oper_mode, ushort, S_IRUGO);
#endif
MODULE_PARM_DESC(dev_oper_mode,
		 "1 -	Wi-Fi Alone \
		  4 -	BT Alone \
		  8 -	BT LE Alone \
		  5 -	Wi-Fi STA + BT classic \
		  9 -	Wi-Fi STA + BT LE \
		  13 -	Wi-Fi STA + BT classic + BT LE \
		  6 -	AP + BT classic \
		  14 -	AP + BT classic + BT LE \
		  16 -	ZIGB ALONE  \
		  17 -	Wi-Fi STA + ZIGB  \
		  32 -	ZIGB COORDINATOR  \
		  48 -	ZIGB ROUTER");

#if defined(CONFIG_RSI_COEX) && defined(CONFIG_RSI_ZIGB)
static struct rsi_proto_ops g_proto_ops = {
	.coex_send_pkt = rsi_coex_send_pkt,
	.get_host_intf = rsi_get_host_intf,
	.set_zb_context = rsi_set_zb_context,
	.get_zb_context = rsi_get_zb_context,
};
#endif

/**
 * rsi_dbg() - This function outputs informational messages.
 * @zone: Zone of interest for output message.
 * @fmt: printf-style format for output message.
 *
 * Return: none
 */
void rsi_dbg(u32 zone, const char *fmt, ...)
{
	struct va_format vaf;
	va_list args;

	va_start(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	if (zone & rsi_zone_enabled)
		pr_info("%pV", &vaf);
	va_end(args);
}
EXPORT_SYMBOL_GPL(rsi_dbg);

/**
 * rsi_hex_dump() - This function prints the packet (/msg) in hex bytes.
 * @zone: Zone of interest for output message.
 * @msg_str: Message to be printed with packet
 * @msg: Packet to be printed
 * @len: Length of the packet
 *
 * Return: none
 */
void rsi_hex_dump(u32 zone, char *msg_str, const u8 *msg, u32 len)
{
	int ii;

	if (!(zone & rsi_zone_enabled))
		return;
	printk("%s: (length = %d)\n", msg_str, len);
	for (ii = 0; ii < len; ii++) {
		if (ii && !(ii % 16))
			printk(KERN_CONT "\n");
		printk(KERN_CONT "%02x ", msg[ii]);
	}
	printk(KERN_CONT "\n");
}
EXPORT_SYMBOL_GPL(rsi_hex_dump);

static char *opmode_str(int oper_mode)
{
	switch (oper_mode) {
	case DEV_OPMODE_WIFI_ALONE:
	       return "Wi-Fi alone";
	case DEV_OPMODE_BT_ALONE:
	       return "BT EDR alone";
	case DEV_OPMODE_BT_LE_ALONE:
	       return "BT LE alone";
	case DEV_OPMODE_BT_DUAL:
	       return "BT Dual";
	case DEV_OPMODE_STA_BT:
	       return "Wi-Fi STA + BT EDR";
	case DEV_OPMODE_STA_BT_LE:
	       return "Wi-Fi STA + BT LE";
	case DEV_OPMODE_STA_BT_DUAL:
	       return "Wi-Fi STA + BT DUAL";
	case DEV_OPMODE_AP_BT:
	       return "Wi-Fi AP + BT EDR";
	case DEV_OPMODE_AP_BT_DUAL:
	       return "Wi-Fi AP + BT DUAL";
	case DEV_OPMODE_ZB_ALONE:
	       return "ZIGB alone";
	case DEV_OPMODE_STA_ZB:
	       return "Wi-Fi STA + ZIGB STA";
	case DEV_OPMODE_ZB_COORDINATOR:
	       return "Wi-Fi STA + ZIGB Coordinator";
	case DEV_OPMODE_ZB_ROUTER:
	       return "Wi-Fi STA + ZIBG Router";
	}
	return "Unknown";
}

void rsi_print_version(struct rsi_common *common)
{
	memcpy(common->driver_ver, DRV_VER, ARRAY_SIZE(DRV_VER));
	common->driver_ver[ARRAY_SIZE(DRV_VER)] = '\0';

	rsi_dbg(ERR_ZONE, "================================================\n");
	rsi_dbg(ERR_ZONE, "================ RSI Version Info ==============\n");
	rsi_dbg(ERR_ZONE, "================================================\n");
	rsi_dbg(ERR_ZONE, "FW Version\t: %d.%d.%d\n",
		common->lmac_ver.major, common->lmac_ver.minor,
		common->lmac_ver.release_num);
	rsi_dbg(ERR_ZONE, "Driver Version\t: %s", common->driver_ver);
	rsi_dbg(ERR_ZONE, "Operating mode\t: %d [%s]",
		common->oper_mode, opmode_str(common->oper_mode));
	rsi_dbg(ERR_ZONE, "Firmware file\t: %s", common->priv->fw_file_name);
	rsi_dbg(ERR_ZONE, "================================================\n");
}

/**
 * rsi_prepare_skb() - This function prepares the skb.
 * @common: Pointer to the driver private structure.
 * @buffer: Pointer to the packet data.
 * @pkt_len: Length of the packet.
 * @extended_desc: Extended descriptor.
 *
 * Return: Successfully skb.
 */
static struct sk_buff *rsi_prepare_skb(struct rsi_common *common,
				       u8 *buffer,
				       u32 pkt_len,
				       u8 extended_desc)
{
	struct ieee80211_tx_info *info;
	struct skb_info *rx_params;
	struct sk_buff *skb = NULL;
	u8 payload_offset;

	if (WARN(!pkt_len, "%s: Dummy pkt received", __func__))
		return NULL;

	if (pkt_len > (RSI_RCV_BUFFER_LEN * 4)) {
		rsi_dbg(ERR_ZONE, "%s: Pkt size > max rx buf size %d\n",
			__func__, pkt_len);
		pkt_len = RSI_RCV_BUFFER_LEN * 4;
	}

	pkt_len -= extended_desc;
	skb = dev_alloc_skb(pkt_len + FRAME_DESC_SZ);
	if (!skb)
		return NULL;

	payload_offset = (extended_desc + FRAME_DESC_SZ);
	skb_put(skb, pkt_len);
	memcpy((skb->data), (buffer + payload_offset), skb->len);

	info = IEEE80211_SKB_CB(skb);
	rx_params = (struct skb_info *)info->driver_data;
	rx_params->rssi = rsi_get_rssi(buffer);

	rx_params->channel = rsi_get_connected_channel(common->priv);

	return skb;
}

/**
 * rsi_read_pkt() - This function reads frames from the card.
 * @common: Pointer to the driver private structure.
 * @rcv_pkt_len: Received pkt length. In case of USB it is 0.
 *
 * Return: 0 on success, -1 on failure.
 */
int rsi_read_pkt(struct rsi_common *common, u8 *rx_pkt, s32 rcv_pkt_len)
{
	u8 *frame_desc = NULL, extended_desc = 0;
	u32 index = 0, length = 0, queueno = 0;
	u16 actual_length = 0, offset;
	struct sk_buff *skb = NULL;
#if defined(CONFIG_RSI_COEX) && defined(CONFIG_RSI_ZIGB)
	struct rsi_mod_ops *zb_ops = g_proto_ops.zb_ops;
	u8 zb_pkt_type;
#endif

	do {
		frame_desc = &rx_pkt[index];
		actual_length = *(u16 *)&frame_desc[0];
		offset = *(u16 *)&frame_desc[2];

		queueno = rsi_get_queueno(frame_desc, offset);
		length = rsi_get_length(frame_desc, offset);

		if (queueno != RSI_ZIGB_Q) {
			if ((actual_length < (4 + FRAME_DESC_SZ)) || (offset < 4)) {
				rsi_dbg(ERR_ZONE,
					"%s: actual_length (%d) is less than 20 or"
					" offset(%d) is less than 4\n",
					__func__, actual_length, offset);
				break;
			}
		}
		if (queueno == RSI_WIFI_DATA_Q || queueno == RSI_WIFI_MGMT_Q)
			extended_desc = rsi_get_extended_desc(frame_desc,
							      offset);

		switch (queueno) {
		case RSI_COEX_Q:
			rsi_hex_dump(MGMT_RX_ZONE,
				     "RX Command co ex packet",
				     frame_desc + offset,
				     FRAME_DESC_SZ + length);
#ifdef CONFIG_RSI_COEX
			rsi_coex_recv_pkt(common, (frame_desc + offset));
#else
			rsi_mgmt_pkt_recv(common, (frame_desc + offset));
#endif
			break;
		case RSI_WIFI_DATA_Q:
			rsi_hex_dump(DATA_RX_ZONE,
				     "RX Data pkt",
				     frame_desc + offset,
				     FRAME_DESC_SZ + length);
			skb = rsi_prepare_skb(common,
					      (frame_desc + offset),
					      length,
					      extended_desc);
			if (!skb)
				goto fail;

			rsi_indicate_pkt_to_os(common, skb);
			break;

		case RSI_WIFI_MGMT_Q:
			rsi_mgmt_pkt_recv(common, (frame_desc + offset));
			break;
#if defined(CONFIG_RSI_BT_ALONE) || defined(CONFIG_RSI_COEX)
		case RSI_BT_MGMT_Q:
		case RSI_BT_DATA_Q:
			rsi_hex_dump(DATA_RX_ZONE,
				     "RX BT Pkt",
				     frame_desc + offset,
				     FRAME_DESC_SZ + length);
			rsi_hci_recv_pkt(common, frame_desc + offset);
			break;
#endif

#if defined(CONFIG_RSI_COEX) && defined(CONFIG_RSI_ZIGB)
		case RSI_ZIGB_Q:
			rsi_hex_dump(DATA_RX_ZONE,
					"RX ZB Pkt",
					frame_desc + offset,
					FRAME_DESC_SZ + length);
#define ZB_RX_PKT_TYPE_OFST	15
#define ZB_CARD_READY_IND	0xff
			zb_pkt_type = frame_desc[offset + ZB_RX_PKT_TYPE_OFST];
			if ((zb_pkt_type == ZB_CARD_READY_IND) &&
			    (common->zb_fsm_state == ZB_DEVICE_NOT_READY)) {
				rsi_dbg(INFO_ZONE, "ZIGB Card ready recvd\n");
				common->zb_fsm_state = ZB_DEVICE_READY;
				if (zb_ops && zb_ops->attach) {
					if (zb_ops->attach(common,
							   &g_proto_ops))
						rsi_dbg(ERR_ZONE,
							"Failed to attach ZIGB module\n");
				}
			} else {
				if ((common->zb_fsm_state == ZB_DEVICE_READY) &&
				    zb_ops && zb_ops->recv_pkt)
					zb_ops->recv_pkt(common,
							 frame_desc + offset);
			}
			break;
#endif

		default:
			rsi_dbg(ERR_ZONE, "%s: pkt from invalid queue: %d\n",
				__func__,   queueno);
			goto fail;
		}

		index  += actual_length;
		rcv_pkt_len -= actual_length;
	} while (rcv_pkt_len > 0);

	return 0;
fail:
	return -EINVAL;
}
EXPORT_SYMBOL_GPL(rsi_read_pkt);

/**
 * rsi_tx_scheduler_thread() - This function is a kernel thread to send the
 *			       packets to the device.
 * @common: Pointer to the driver private structure.
 *
 * Return: None.
 */
static void rsi_tx_scheduler_thread(struct rsi_common *common)
{
	int status = 0;
	struct rsi_hw *adapter = common->priv;
	u32 timeout = EVENT_WAIT_FOREVER;

	do {
		if (adapter->determine_event_timeout)
			timeout = adapter->determine_event_timeout(adapter);
		status = rsi_wait_event(&common->tx_thread.event, timeout);
		if (status < 0)
			break;
		rsi_reset_event(&common->tx_thread.event);

		if (common->init_done)
			rsi_core_qos_processor(common);
	} while (atomic_read(&common->tx_thread.thread_done) == 0);
	complete_and_exit(&common->tx_thread.completion, 0);
}

#ifdef CONFIG_SDIO_INTR_POLL
void rsi_sdio_intr_poll_scheduler_thread(struct rsi_common *common)
{
        struct rsi_hw *adapter = common->priv;
        int status = 0;

        do {
                status = adapter->check_intr_status_reg(adapter);
                if (adapter->isr_pending)
                        adapter->isr_pending = 0;
                msleep(20);

        } while (atomic_read(&common->sdio_intr_poll_thread.thread_done) == 0);
        complete_and_exit(&common->sdio_intr_poll_thread.completion, 0);
}

void init_sdio_intr_status_poll_thread(struct rsi_common *common)
{
	rsi_init_event(&common->sdio_intr_poll_thread.event);
	if (rsi_create_kthread(common,
			       &common->sdio_intr_poll_thread,
			       rsi_sdio_intr_poll_scheduler_thread,
			       "Sdio Intr poll-Thread")) {
		rsi_dbg(ERR_ZONE, "%s: Unable to init sdio intr poll thrd\n",
				__func__);
	}
}
EXPORT_SYMBOL_GPL(init_sdio_intr_status_poll_thread);
#endif

#ifdef CONFIG_RSI_COEX
enum host_intf rsi_get_host_intf(void *priv)
{
	struct rsi_common *common = (struct rsi_common *)priv;

	return common->priv->rsi_host_intf;
}

void rsi_set_zb_context(void *priv, void *zb_context)
{
	struct rsi_common *common = (struct rsi_common *)priv;

	common->zb_adapter = zb_context;
}

void *rsi_get_zb_context(void *priv)
{
	struct rsi_common *common = (struct rsi_common *)priv;

	return common->zb_adapter;
}
#endif

/**
 * rsi_91x_init() - This function initializes os interface operations.
 * @void: Void.
 *
 * Return: Pointer to the adapter structure on success, NULL on failure.
 */
struct rsi_hw *rsi_91x_init(void)
{
	struct rsi_hw *adapter = NULL;
	struct rsi_common *common = NULL;
	u8 ii = 0;

	adapter = kzalloc(sizeof(*adapter), GFP_KERNEL);
	if (!adapter)
		return NULL;

	adapter->priv = kzalloc(sizeof(*common), GFP_KERNEL);
	if (!adapter->priv) {
		rsi_dbg(ERR_ZONE, "%s: Failed in allocation of priv\n",
			__func__);
		kfree(adapter);
		return NULL;
	}
	common = adapter->priv;
	common->priv = adapter;

	for (ii = 0; ii < NUM_SOFT_QUEUES; ii++)
		skb_queue_head_init(&common->tx_queue[ii]);

#ifdef CONFIG_RSI_11K
	skb_queue_head_init(&common->rrm_queue);
#endif
	rsi_init_event(&common->tx_thread.event);
	mutex_init(&common->mutex);
	mutex_init(&common->tx_lock);
	mutex_init(&common->rx_lock);
	sema_init(&common->tx_bus_lock, 1);
	rsi_init_event(&common->mgmt_cfm_event);
#ifdef CONFIG_HW_SCAN_OFFLOAD
	rsi_init_event(&common->chan_set_event);
	rsi_init_event(&common->probe_cfm_event);
	rsi_init_event(&common->chan_change_event);
	rsi_init_event(&common->cancel_hw_scan_event);
	common->scan_workqueue = 
		create_singlethread_workqueue("rsi_scan_worker");
	INIT_WORK(&common->scan_work, rsi_scan_start);
#endif
#ifdef CONFIG_RSI_MULTI_MODE
	common->dev_oper_mode[0] = dev_oper_mode_count;
	memcpy(&common->dev_oper_mode[1], &dev_oper_mode, 5 * sizeof(u16));
#else
	common->dev_oper_mode = dev_oper_mode;
#endif

	if (rsi_create_kthread(common,
			       &common->tx_thread,
			       rsi_tx_scheduler_thread,
			       "Tx-Thread")) {
		rsi_dbg(ERR_ZONE, "%s: Unable to init tx thrd\n", __func__);
		goto err;
	}

#ifdef CONFIG_RSI_COEX
	if (rsi_coex_init(common)) {
		rsi_dbg(ERR_ZONE, "Failed to init COEX module\n");
		goto err;
	}
#endif
	/* Power save related */
	rsi_default_ps_params(adapter);
	spin_lock_init(&adapter->ps_lock);
	common->uapsd_bitmap = 0;

	/* BGScan related */
	init_bgscan_params(common);

	/* Wi-Fi direct related */
#if LINUX_VERSION_CODE < KERNEL_VERSION (4, 15, 0)
	common->roc_timer.data = (unsigned long)common;
	common->roc_timer.function = (void *)&rsi_roc_timeout;
	init_timer(&common->roc_timer);
#else
	timer_setup(&common->roc_timer, rsi_roc_timeout, 0);
#endif
	init_completion(&common->wlan_init_completion);

	common->init_done = true;
	return adapter;

err:
	kfree(common);
	kfree(adapter);
	return NULL;
}
EXPORT_SYMBOL_GPL(rsi_91x_init);

/**
 * rsi_91x_deinit() - This function de-intializes os intf operations.
 * @adapter: Pointer to the adapter structure.
 *
 * Return: None.
 */
void rsi_91x_deinit(struct rsi_hw *adapter)
{
	struct rsi_common *common = adapter->priv;
	u8 ii;

	rsi_dbg(INFO_ZONE, "%s: Deinit core module...\n", __func__);

#ifdef CONFIG_HW_SCAN_OFFLOAD
	flush_workqueue(common->scan_workqueue);
	destroy_workqueue(common->scan_workqueue);
#endif

	rsi_kill_thread(&common->tx_thread);

	for (ii = 0; ii < NUM_SOFT_QUEUES; ii++)
		skb_queue_purge(&common->tx_queue[ii]);

#ifdef CONFIG_RSI_COEX
	if (common->coex_mode > 1) {
#ifdef CONFIG_RSI_ZIGB
		if ((common->zb_fsm_state == ZB_DEVICE_READY) &&
		    g_proto_ops.zb_ops->detach) {
			rsi_dbg(INFO_ZONE,
				"%s: Detaching the zigbee module\n", __func__);
			g_proto_ops.zb_ops->detach(common);
		}
#endif
	}
	rsi_coex_deinit(common);
#endif
#ifdef CONFIG_RSI_MULTI_MODE
	rsi_dbg(ERR_ZONE, "%s: reset drv instance: %d\n",
			__func__, adapter->drv_instance_index);
	DRV_INSTANCE_SET(adapter->drv_instance_index, 0);
#endif
	common->init_done = false;

	kfree(common);
	kfree(adapter->rsi_dev);
	kfree(adapter);
}
EXPORT_SYMBOL_GPL(rsi_91x_deinit);

/**
 * rsi_91x_hal_module_init() - This function is invoked when the module is
 *			       loaded into the kernel.
 *			       It registers the client driver.
 * @void: Void.
 *
 * Return: 0 on success, -1 on failure.
 */
static int rsi_91x_hal_module_init(void)
{
	rsi_dbg(INIT_ZONE, "%s: Module init called\n", __func__);
#if defined(CONFIG_RSI_COEX) && defined(CONFIG_RSI_ZIGB)
	g_proto_ops.zb_ops = rsi_get_zb_ops();
	if (!g_proto_ops.zb_ops)
		rsi_dbg(ERR_ZONE, "Failed to get ZIGB ops\n");
#endif

	return 0;
}

/**
 * rsi_91x_hal_module_exit() - This function is called at the time of
 *			       removing/unloading the module.
 *			       It unregisters the client driver.
 * @void: Void.
 *
 * Return: None.
 */
static void rsi_91x_hal_module_exit(void)
{
	rsi_dbg(INIT_ZONE, "%s: Module exit called\n", __func__);
}

module_init(rsi_91x_hal_module_init);
module_exit(rsi_91x_hal_module_exit);
MODULE_AUTHOR("Redpine Signals Inc");
MODULE_DESCRIPTION("Station driver for RSI 91x devices");
MODULE_SUPPORTED_DEVICE("RSI-91x");
MODULE_VERSION(DRV_VER);
MODULE_LICENSE("Dual BSD/GPL");
