/*
 * Copyright (c) 2024 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include <zephyr/kernel.h>

#include "common/work_q.h"
#ifdef CONFIG_APP_WORK_QUEUE
#include <app_workq.h>
#else
K_THREAD_STACK_DEFINE(work_q_stack, CONFIG_LTE_LC_WORKQUEUE_STACK_SIZE);

static struct k_work_q work_q;

void work_q_start(void)
{
	struct k_work_queue_config cfg = {
		.name = "work_q",
	};

	k_work_queue_start(&work_q, work_q_stack, K_THREAD_STACK_SIZEOF(work_q_stack),
			   K_LOWEST_APPLICATION_THREAD_PRIO, &cfg);
}
#endif

struct k_work_q *work_q_get(void)
{
#ifndef CONFIG_APP_WORK_QUEUE
	return &work_q;
#else
	return app_workq_get();
#endif
}
