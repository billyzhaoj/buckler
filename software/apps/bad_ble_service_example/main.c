// BLE TX app
//
// Sends BLE advertisements with data

#include <stdbool.h>
#include <stdint.h>

#include "app_util.h"
#include "nrf.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#include "simple_ble.h"

// BLE configuration
static simple_ble_config_t ble_config = {
        // BLE address is c0:98:e5:49:00:01
        .platform_id       = 0x49,    // used as 4th octet in device BLE address
        .device_id         = 0x0001,  // used as the 5th and 6th octet in the device BLE address, you will need to change this for each device you have
        .adv_name          = "Buckler Service", // irrelevant in this example
        .adv_interval      = MSEC_TO_UNITS(1000, UNIT_0_625_MS), // send a packet once per second (minimum is 20 ms)
        .min_conn_interval = MSEC_TO_UNITS(100, UNIT_1_25_MS), // irrelevant if advertising only
        .max_conn_interval = MSEC_TO_UNITS(200, UNIT_1_25_MS), // irrelevant if advertising only
};
simple_ble_app_t* simple_ble_app;


int main(void) {
  ret_code_t error_code = NRF_SUCCESS;

  // initialize RTT library
  error_code = NRF_LOG_INIT(NULL);
  APP_ERROR_CHECK(error_code);
  NRF_LOG_DEFAULT_BACKENDS_INIT();
  printf("RTT initialized\n");
  
  // Setup BLE
  // Note: simple BLE is our own library. You can find it in `nrf5x-base/lib/simple_ble/`
  simple_ble_app = simple_ble_init(&ble_config);
  simple_ble_adv_only_name();
  printf("BLE initialized\n");

  // go into low power mode
  while(1) {
    //power_manage();
    nrf_pwr_mgmt_run();
  }
}

