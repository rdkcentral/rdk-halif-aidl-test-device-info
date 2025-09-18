/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2024 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/** @brief
* vcomponent_Deviceinfo_parse_config.h
*
* Header file for vcomponent DeviceInfo driver
*/

#pragma once

#include <string>
#include <ut.h>
#include <ut_log.h>
#include <ut_kvp.h>
#include <ut_control_plane.h>
#include "vcomponent_Deviceinfo.h"

typedef struct deviceInfoConfig
{
    std::string manufacturer;                // Mandatory
    std::array<uint8_t, 3> manufacturerOUI;  // Mandatory (3 bytes)
    std::string modelName;                   // Mandatory
    std::string productClass;                // Mandatory
    std::string serialNumber;                // Mandatory
    std::string wifiMac;                     // Mandatory if Wi-Fi present
    std::string bluetoothMac;                // Mandatory if BT present
    std::string wpsPin;                      // Optional (8 digits)
    std::string ethernetMac;                 // Mandatory if Ethernet present
    std::string rf4ceMac;                    // Mandatory if RF4CE present
    std::string imageName;                   // Mandatory
    std::string imageType;                   // Mandatory
    std::string countryCode;                 // Optional
    std::string languageCode;                // Optional
    std::string manufacturerData;            // Optional
} deviceInfoConfig_t;

extern deviceInfoConfig_t gDeviceInfoConfig;

void vcomponent_Deviceinfo_parse_config(char *configurationFile);
void vcomponent_deviceinfo_initialize_ControlPlane();
void vcomponent_deviceinfo_register_and_start_ControlPlane();
void vcomponent_deviceinfo_destroy_ControlPlane();
// void* vcomponent_deviceinfo_kvp_create_instance(char *fileName);
// void vcomponent_deviceinfo_kvp_destroy_instance(void *instance);
// ut_kvp_instance_t* vcomponent_deviceinfo_get_kvp_instance();