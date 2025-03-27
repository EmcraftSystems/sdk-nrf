/*
 * Copyright (c) 2025 Emcraft Systems
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

/**@file dlc_wrapper.h
 * @brief Download Client wrapper API
 *
 * Wrapper API that allows to re-use a single download_client thread for
 * multiple downloads
 *
 */

#include <net/download_client.h>

struct download_client *dlc_wrapper_get_client(void);
int dlc_wrapper_set_callback(download_client_callback_t callback);
bool dlc_wrapper_is_idle(void);
