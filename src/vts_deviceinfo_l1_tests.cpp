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
 * @defgroup DEVICEINFO_HALTEST_CLASS DEVICEINFO HAL Tests L1 Test Cases
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
 * @file vts_deviceinfo_l1_tests.cpp
 *
 */

#include "vts_deviceinfo.h"
#include "com/rdk/hal/deviceinfo/IDeviceInfo.h"
#include "ut_log.h"

extern sp<IDeviceInfo> gDEVICEINFOHandle;

/* Test class registration with UT_Core */
UT_ADD_TEST_TO_GROUP(VTS_L1_DEVICEINFO, UT_TESTS_L1)

class VTS_L1_DEVICEINFO : public UTCore
{
public:
    VTS_L1_DEVICEINFO() : UTCore() {}

    ~VTS_L1_DEVICEINFO() override = default;

    void SetUp() override
    {
        // android::ProcessState::self()->startThreadPool();
    }

    void TearDown() override
    {
    }
};

// Test case for getCapabilities, getHALVersion, getProperty positive scenarios
UT_ADD_TEST(VTS_L1_DEVICEINFO, testGet_pos)
{
    com::rdk::hal::deviceinfo::Capabilities caps;
    DEVICEINFO_GET_CAPABILITIES(gDEVICEINFOHandle, caps); //getCapabilities()
    UT_ASSERT_EQUAL(caps.supportedProperties.size(), UT_KVP_PROFILE_GET_LIST_COUNT("IDeviceInfo.supportedProperties"));
    com::rdk::hal::deviceinfo::HALVersion version;
    DEVICEINFO_GET_HALVERSION(gDEVICEINFOHandle, version); //getHALVersion
    UT_ASSERT_EQUAL(version.major, UT_KVP_PROFILE_GET_UINT8("IDeviceInfo.HALVersion.major"));
    UT_ASSERT_EQUAL(version.minor, UT_KVP_PROFILE_GET_UINT8("IDeviceInfo.HALVersion.minor"));
    UT_ASSERT_EQUAL(version.doc, UT_KVP_PROFILE_GET_UINT8("IDeviceInfo.HALVersion.doc"));
    com::rdk::hal::deviceinfo::SetPropertyResult result;
    std::optional<::android::String16> value;
    android::String16 key("KEY_MANUFACTURER");
    android::String16 val;
    DEVICEINFO_GET_PROPERTY(gDEVICEINFOHandle, key, value); //getProperty
    key = android::String16("KEY_MANUFACTURER_OUI");
    DEVICEINFO_GET_PROPERTY(gDEVICEINFOHandle, key, value);
    key = android::String16("KEY_MODELNAME");
    DEVICEINFO_GET_PROPERTY(gDEVICEINFOHandle, key, value);
    key = android::String16("KEY_PRODUCTCLASS");
    DEVICEINFO_GET_PROPERTY(gDEVICEINFOHandle, key, value);
    key = android::String16("KEY_SERIALNUMBER");
    DEVICEINFO_GET_PROPERTY(gDEVICEINFOHandle, key, value);
    key = android::String16("KEY_WIFIMAC");
    DEVICEINFO_GET_PROPERTY(gDEVICEINFOHandle, key, value);
    key = android::String16("KEY_BLUETOOTHMAC");
    DEVICEINFO_GET_PROPERTY(gDEVICEINFOHandle, key, value);
    key = android::String16("KEY_WPSPIN");
    DEVICEINFO_GET_PROPERTY(gDEVICEINFOHandle, key, value);
    key = android::String16("KEY_ETHERNETMAC");
    DEVICEINFO_GET_PROPERTY(gDEVICEINFOHandle, key, value);
    key = android::String16("KEY_RF4CEMAC");
    DEVICEINFO_GET_PROPERTY(gDEVICEINFOHandle, key, value);
    key = android::String16("KEY_IMAGENAME");
    DEVICEINFO_GET_PROPERTY(gDEVICEINFOHandle, key, value);
    key = android::String16("KEY_IMAGETYPE");
    DEVICEINFO_GET_PROPERTY(gDEVICEINFOHandle, key, value);
    key = android::String16("KEY_COUNTRYCODE");
    DEVICEINFO_GET_PROPERTY(gDEVICEINFOHandle, key, value);
    key = android::String16("KEY_LANGUAGECODE");
    DEVICEINFO_GET_PROPERTY(gDEVICEINFOHandle, key, value);
    key = android::String16("KEY_MANUFACTURERDATA");
    DEVICEINFO_GET_PROPERTY(gDEVICEINFOHandle, key, value);
    return;
}

UT_ADD_TEST(VTS_L1_DEVICEINFO, testGet_neg)
{
    android::String16 key("KEY_INVALID");
    std::optional<::android::String16> value;
    DEVICEINFO_GET_PROPERTY_NEGATIVE(gDEVICEINFOHandle, key, value);
    return;
}

/**
* @} // End of DEVICEINFO_HALTEST_CLASS
* @} // End of DEVICEINFO_HALTEST
* @} // End of DEVICEINFO
* @} // End of HPK
*/
/* End of vts_deviceinfo_l1_tests.cpp */