/***************************************************************************//**
 * @file
 * @brief Top level application functions
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/
#include <stdio.h>
#include <stdint.h>

#include "ezradio_cmd.h"
#include "ezradio_api_lib.h"
#include "ezradio_plugin_manager.h"


void ezradio_print_part_info(void)
{
	ezradio_cmd_reply_t reply;
	EZRADIODRV_HandleData_t appRadioInitData = EZRADIODRV_INIT_DEFAULT;

	ezradioInit( &appRadioInitData );
	ezradio_part_info(&reply);
	printf("REV: 0x%02x, PART: 0x%04x, ID: 0x%04x, CUSTOMER: 0x%02x, PBUILD: 0x%02x, ROMID: 0x%02x\n", reply.PART_INFO.CHIPREV, reply.PART_INFO.PART, reply.PART_INFO.ID, reply.PART_INFO.CUSTOMER, reply.PART_INFO.PBUILD, reply.PART_INFO.ROMID);
}


/***************************************************************************//**
 * Initialize application.
 ******************************************************************************/
void app_init(void)
{
	ezradio_print_part_info();
}

/***************************************************************************//**
 * App ticking function.
 ******************************************************************************/
void app_process_action(void)
{
}
