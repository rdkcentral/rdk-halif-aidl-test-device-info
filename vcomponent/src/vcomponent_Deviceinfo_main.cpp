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
* vcomponent_Deviceinfo_main.cpp
*
* Main entry point for the DeviceInfo service
*/


#include "vcomponent_Deviceinfo.h"
#include "vcomponent_Deviceinfo_init.h"
#include <signal.h> 
#include <ut_log.h>

using namespace com::rdk::hal::deviceinfo;
// int main(int , char* []) 
// { 
// 	signal(SIGPIPE, SIG_IGN);
// 	DeviceInfo::publishAndJoinThreadPool();
// 	return 0;
// }

#define DEFAULT_VCOMPONENT_CONFIG_FILE "vcomponent_configurations/deviceinfo_vcomponent_configuration.yaml"

int main(int argc, char** argv)
{
    std::string configFile = DEFAULT_VCOMPONENT_CONFIG_FILE;
    if(argc > 1)
    {
        std::string arg = argv[1];
        if(arg == "-h" || arg == "--help")
        {
            UT_LOG_INFO("[VCOMPONENT_DEVICEINFO]DeviceinfoService -h | --help | -c | --config <file>");
            return 0;
        }
        else if((arg == "-c" || arg == "--config") && argc > 2)
        {
            configFile = argv[2];
        }
        else
        {
            UT_LOG_ERROR("[VCOMPONENT_DEVICEINFO]Unknown option: %s", arg);
            UT_LOG_ERROR("[VCOMPONENT_DEVICEINFO]Use -h or --help for usage information");
            return 1;
        }
    }

    UT_LOG_INFO("[VCOMPONENT_DEVICEINFO]Using configuration file: %s", configFile.c_str());

    if(DeviceInfoInit((char *)configFile.c_str()) == false)
    {
        UT_LOG_ERROR("[VCOMPONENT_DEVICEINFO]Failed to initialize Deviceinfo service with config file: %s", configFile.c_str());
        return -1;
    }

    signal(SIGPIPE, SIG_IGN);
    DeviceInfo::publishAndJoinThreadPool();

    return 0;
}
