/*
 * Generic app work queue API routines
 *
 * Copyright (c) 2025 Emcraft Systems
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */
#include <zephyr/kernel.h>
#define THREAD_PRIORITY		(K_LOWEST_APPLICATION_THREAD_PRIO)
#define STACK_SZ		CONFIG_APP_WORK_QUEUE_STACK_SIZE
K_THREAD_STACK_DEFINE(app_workq_stack, STACK_SZ);

static struct k_work_q app_work_q;

struct k_work_q *app_workq_get(void)
{
	return &app_work_q;
}
static int app_workq_init(void)
{
	struct k_work_queue_config cfg = { .name = "app_workq", };
	k_work_queue_init(&app_work_q);
	k_work_queue_start(&app_work_q, app_workq_stack, K_THREAD_STACK_SIZEOF(app_workq_stack),
		   THREAD_PRIORITY, &cfg);
	return 0;
}
SYS_INIT(app_workq_init, APPLICATION, 0);
