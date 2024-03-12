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

#include "dt.h"

// powersupplygpio *************************************************************

pi_powersupplygpio_conf_t cam3v3_conf = {
	.pad_id = DT_CAM3V3_PAD_ID,
};

pi_powersupplygpio_data_t cam3v3_data;

pi_device_t cam3v3_dev = {
	.config = &cam3v3_conf,
	.data   = &cam3v3_data,
	.api    = (pi_device_api_t *) &powersupplygpio_api
};

// Flash partition v2 memories *************************************************


// Devices FPV2 register *******************************************************

#if defined(CONFIG_DRIVER_FLASH_PARTITION_V2)
pi_err_t pi_register_fpv2_flashs(void)
{
    pi_err_t err = PI_OK;
    for(size_t i = 0; i < sizeof(fpv2_memory_refs)/sizeof(fpv2_memory_refs[0]); i++)
    {
        err = pi_fpv2_device_register(&fpv2_memory_refs[i].ref,
                                      fpv2_memory_refs[i].memory);
        if (PI_OK != err)
        {
            break;
        }
    }
    return err;
}
#endif
// Devices API *****************************************************************

pi_err_t pi_open(pi_device_e device_enum, pi_device_t** device_ptr)
{
	pi_err_t err = PI_OK;
	switch (device_enum)
	{
		case PI_POWERSUPPLY_CAM3V3:
		{
			*device_ptr = DEVICE_PTR_POWERSUPPLY_CAM3V3;
			break;
		}
		default:
		{
			err = PI_ERR_NOT_FOUND;
			break;
		}
	}
	if ((device_ptr != NULL) && (err == PI_OK))
	{
		err = (*device_ptr)->api->open(*device_ptr);
	}
	return err;
}

pi_err_t pi_close(pi_device_e device_enum)
{
	pi_err_t err = PI_OK;
	pi_device_t* device_ptr = NULL;

	switch (device_enum)
	{
		case PI_POWERSUPPLY_CAM3V3:
		{
			device_ptr = DEVICE_PTR_POWERSUPPLY_CAM3V3;
			break;
		}
		default:
		{
			err = PI_ERR_NOT_FOUND;
			break;
		}
	}
	if ((device_ptr != NULL) && (err == PI_OK))
	{
		err = (device_ptr)->api->close(device_ptr);
	}
	return err;
}

