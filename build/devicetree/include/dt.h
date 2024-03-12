// ############################################################################# 
// Device tree content
// Generation time : 11/03/2024 11:25:53 
//
// THIS IS A GENERATED FILE, DO NOT EDIT !
//
// This file is the static output of the device tree. It aims to define all 
// available features from the board you are using. It is generated from the 
// device tree generator python script : dtGenerator.py.
// #############################################################################

#pragma once

#include "pmsis_types.h"
#include "pmsis/pmsis_types.h"
#include "pmsis/errno.h"

// BSP includes ****************************************************************

#include "bsp/boards/bsp_gap9mod_v1_0_b.h"
#include "bsp/boards/bsp_gap9evk_v1_3.h"

// powersupplygpio *************************************************************

#include "bsp/powersupply/powersupplygpio.h"

#define DT_CAM3V3_PAD_ID ( 0 )

extern pi_device_t cam3v3_dev;

// Devices pointers ************************************************************

#define DEVICE_PTR_POWERSUPPLY_CAM3V3 &cam3v3_dev


// Devices enum ****************************************************************

typedef enum {
	PI_POWERSUPPLY_CAM3V3,
} pi_device_e;


// Devices FPV2 register *******************************************************

#if defined(CONFIG_DRIVER_FLASH_PARTITION_V2)
pi_err_t pi_register_fpv2_flashs(void);

#endif
// Devices API *****************************************************************

pi_err_t pi_open(pi_device_e device_enum, pi_device_t** device_ptr);

pi_err_t pi_close(pi_device_e device_enum);

// Padfun registers ************************************************************

#define PADFUN0_INIT ( 0x55555555 )
#define PADFUN1_INIT ( 0x55555555 )
#define PADFUN2_INIT ( 0x55555555 )
#define PADFUN3_INIT ( 0x55555555 )
#define PADFUN4_INIT ( 0x55555555 )
#define PADFUN5_INIT ( 0x55555555 )

// Reprog registers ************************************************************

#define REPROG0_INIT ( 0x040C2040 )
#define REPROG1_INIT ( 0x0C289206 )
#define REPROG2_INIT ( 0x144D240E )
#define REPROG3_INIT ( 0x2179B616 )

// Pads define *****************************************************************


