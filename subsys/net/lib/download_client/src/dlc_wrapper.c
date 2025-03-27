/*
 * Copyright (c) 2025 Emcraft Systems
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

#include <net/download_client.h>
#include <zephyr/logging/log.h>

LOG_MODULE_DECLARE(download_client);

static struct download_client dlc_wrapper_client;
static download_client_callback_t dlc_wrapper_client_cb = NULL;

static int dlc_wrapper_callback(const struct
		download_client_evt *event)
{
	if (dlc_wrapper_client_cb) {
		return dlc_wrapper_client_cb(event);
	}
	return 0;
}

static int dlc_wrapper_init(void)
{
	int ret = download_client_init(&dlc_wrapper_client,
			dlc_wrapper_callback);
	if (ret) {
		LOG_ERR("Failed to initialize the client, ret %d", ret);
	}
	return ret;
}

struct download_client *dlc_wrapper_get_client(void)
{
	return &dlc_wrapper_client;
}

int dlc_wrapper_set_callback(download_client_callback_t callback)
{
	int ret = 0;
	if (dlc_wrapper_client.state == DOWNLOAD_CLIENT_IDLE) {
		dlc_wrapper_client_cb = callback;
	} else {
		ret = -1;
	}

	return ret;
}

bool dlc_wrapper_is_idle(void)
{
	bool ret;

	k_mutex_lock(&dlc_wrapper_client.mutex, K_FOREVER);
	ret = dlc_wrapper_client.state == DOWNLOAD_CLIENT_IDLE;
	k_mutex_unlock(&dlc_wrapper_client.mutex);
	return ret;
}

SYS_INIT(dlc_wrapper_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);
