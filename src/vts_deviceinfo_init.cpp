/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
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

/**
 * @addtogroup HPK Hardware Porting Kit
 * @{
 * @par The Hardware Porting Kit
 * HPK is the next evolution of the well-defined Hardware Abstraction Layer
 * (HAL), but augmented with more comprehensive documentation and test suites
 * that OEM or SOC vendors can use to self-certify their ports before taking
 * them to RDKM for validation or to an operator for final integration and
 * deployment. The Hardware Porting Kit effectively enables an OEM and/or SOC
 * vendor to self-certify their own Video Accelerator devices, with minimal RDKM
 * assistance.
 *
 */

/**
 * @addtogroup DEVICEINFO DEVICEINFO Module
 * @{
 */

/**
 * @addtogroup DEVICEINFO_HALTEST DEVICEINFO HAL Tests
 * @{
 */

/**
 * @defgroup DEVICEINFO_HALTEST_CLASS DEVICEINFO HAL Tests initialization source File
 * @{
 * @parblock
 *
 * ### Common functions/macros required for the DEVICEINFO module :
 *
 * Common functions/macros required for the DEVICEINFO module .
 *
 * **Pre-Conditions:**  None @n
 * **Dependencies:** None @n
 *
 * @endparblock
 *
 */

/**
 * @file vts_deviceinfo_init.cpp
 *
 */

#include "vts_deviceinfo_init.h"
#include "ut_log.h"

#include "com/rdk/hal/deviceinfo/IDeviceInfo.h"

#include <binder/IServiceManager.h>
#include <binder/IBinder.h>
#include <binder/ProcessState.h>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

using android::sp;
using android::String16;
using android::defaultServiceManager;
using android::binder::Status;

using namespace com::rdk::hal;
using namespace com::rdk::hal::deviceinfo;

sp<IDeviceInfo> gDEVICEINFOHandle = nullptr;

static UT_status_t vts_deviceinfo_getService()
{
    gDEVICEINFOHandle = android::interface_cast<IDeviceInfo>(
        defaultServiceManager()->getService(String16(IDeviceInfo::serviceName().c_str())));

    if (gDEVICEINFOHandle == nullptr)
    {
        UT_LOG_ERROR("Failed to get DeviceInfo service");
        return UT_STATUS_FAILURE;
    }
    UT_LOG_INFO("Successfully obtained DeviceInfo service");
    return UT_STATUS_OK;
}

UT_status_t VTS_DEVICEINFO_init()
{
    if(vts_deviceinfo_getService() != UT_STATUS_OK)
    {
        UT_LOG_ERROR("Failed to get DeviceInfo Service");
        return UT_STATUS_FAILURE;
    }
    // if(vts_deviceinfo_parse_hfp() != UT_STATUS_OK)
    // {
    //     UT_LOG_ERROR("Failed to process the DeviceInfo HFP file");
    // }

    return UT_STATUS_OK;
}

void VTS_DEVICEINFO_destroy()
{
    UT_LOG_INFO("Destroying VTS_DEVICEINFO...");
    // De-initialization code goes here
}

/** @} */ // End of DEVICEINFO_HALTEST_CLASS
/** @} */ // End of DEVICEINFO_HALTEST
/** @} */ // End of DEVICEINFO
/** @} */ // End of HPK

// End of vts_deviceinfo_init.cpp