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
 * @defgroup DEVICEINFO_HALTEST_CLASS DEVICEINFO HAL Tests L2 Test Cases
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
 * @file vts_deviceinfo_l2_tests.cpp
 *
 */

#include "vts_deviceinfo.h"
#include "com/rdk/hal/deviceinfo/IDeviceInfo.h"
#include "ut_log.h"

extern sp<IDeviceInfo> gDEVICEINFOHandle;

/* Test class registration with UT_Core */
UT_ADD_TEST_TO_GROUP(VTS_L2_DEVICEINFO, UT_TESTS_L2)

class VTS_L2_DEVICEINFO : public UTCore
{
public:
    VTS_L2_DEVICEINFO() : UTCore() {}

    ~VTS_L2_DEVICEINFO() override = default;

    void SetUp() override
    {
        // android::ProcessState::self()->startThreadPool();
    }

    void TearDown() override
    {
    }
};

/**
 * @brief Test for getCapabilities() function of IDeviceInfo
 *
 * This test verifies that the getCapabilities() method of the IDeviceInfo interface
 * correctly populates the Capabilities structure with the supported properties.
 *
 * **Test Group ID:** 02@n
 * **Test Case ID:** 001@n
 *
 * **Test Procedure:**
 * Refer to Deviceinfo specification documentation [deviceinfo_L2_Low-Level_TestSpecification](../docs/pages/)
 */

UT_ADD_TEST(VTS_L2_DEVICEINFO, test_getCapabilities)
{
    android::sp<com::rdk::hal::deviceinfo::IDeviceInfo> deviceInfo = gDEVICEINFOHandle;
    UT_ASSERT_NOT_EQUAL(deviceInfo, nullptr);
    com::rdk::hal::deviceinfo::Capabilities caps;
    deviceInfo->getCapabilities(&caps);
    char returnedString[UT_KVP_MAX_ELEMENT_SIZE];
    UT_ASSERT_EQUAL(caps.supportedProperties.size(), UT_KVP_PROFILE_GET_LIST_COUNT("IDeviceInfo.supportedProperties"));
    for (const auto &property : caps.supportedProperties)
    {
        UT_LOG_DEBUG("Supported Property: %s", android::internal::ToString(property).c_str());
        bool found = false;
        for (int i = 0; i < UT_KVP_PROFILE_GET_LIST_COUNT("IDeviceInfo.supportedProperties"); i++)
        {
            std::string key = "IDeviceInfo.supportedProperties." + std::to_string(i);
            UT_KVP_PROFILE_GET_STRING(key.c_str(), returnedString);
            if (property == android::String16(returnedString))
            {
                found = true;
                break;
            }
        }
        UT_ASSERT_TRUE(found);
    }
}

/**
 * @brief Test for getHALVersion() function of IDeviceInfo
 *
 * This test verifies that the getHALVersion() method of the IDeviceInfo interface
 * correctly populates the HALVersion structure with the expected version values.
 *
 * **Test Group ID:** 02@n
 * **Test Case ID:** 002@n
 *
 * **Test Procedure:**
 * Refer to Deviceinfo specification documentation [deviceinfo_L2_Low-Level_TestSpecification](../docs/pages/)
 */
UT_ADD_TEST(VTS_L2_DEVICEINFO, test_getHALVersion)
{
    android::sp<com::rdk::hal::deviceinfo::IDeviceInfo> deviceInfo = gDEVICEINFOHandle;
    UT_ASSERT_NOT_EQUAL(deviceInfo, nullptr);
    com::rdk::hal::deviceinfo::HALVersion halVersion;
    deviceInfo->getHALVersion(&halVersion);
    UT_LOG_DEBUG("HAL Version: Major=%d, Minor=%d, Doc=%d", halVersion.major, halVersion.minor, halVersion.doc);
    UT_ASSERT_EQUAL(halVersion.major, UT_KVP_PROFILE_GET_UINT8("IDeviceInfo.HALVersion.major"));
    UT_ASSERT_EQUAL(halVersion.minor, UT_KVP_PROFILE_GET_UINT8("IDeviceInfo.HALVersion.minor"));
    UT_ASSERT_EQUAL(halVersion.doc, UT_KVP_PROFILE_GET_UINT8("IDeviceInfo.HALVersion.doc"));
}

/**
 * @brief Test for verifying setProperty() and getProperty() functions of IDeviceInfo
 *
 * This test verifies that the setProperty() and getProperty() methods of the IDeviceInfo interface
 * correctly set and retrieve property values for all supported properties.
 *
 * **Test Group ID:** 02@n
 * **Test Case ID:** 003@n
 *
 * **Test Procedure:**
 * Refer to Deviceinfo specification documentation [deviceinfo_L2_Low-Level_TestSpecification](../docs/pages/)
 */
UT_ADD_TEST(VTS_L2_DEVICEINFO, test_verifyCapabilities)
{
    android::sp<com::rdk::hal::deviceinfo::IDeviceInfo> deviceInfo = gDEVICEINFOHandle;
    UT_ASSERT_NOT_EQUAL(deviceInfo, nullptr);
    com::rdk::hal::deviceinfo::Capabilities caps;
    com::rdk::hal::deviceinfo::SetPropertyResult result;
    std::optional<::android::String16> value;
    deviceInfo->getCapabilities(&caps);
    UT_ASSERT_EQUAL(caps.supportedProperties.size(), UT_KVP_PROFILE_GET_LIST_COUNT("IDeviceInfo.supportedProperties"));

    for(const auto& property : caps.supportedProperties) {
        UT_LOG_DEBUG("Supported Property: %s", android::internal::ToString(property).c_str());

        if (property == android::String16("KEY_MANUFACTURER_OUI")) {
            deviceInfo->setProperty(property, android::String16("ABCDEF"), &result); // Valid OUI (3 bytes)
            UT_ASSERT_EQUAL(result, com::rdk::hal::deviceinfo::SetPropertyResult::SUCCESS);
            result = com::rdk::hal::deviceinfo::SetPropertyResult::ERROR_INVALID_PARAM;
            deviceInfo->getProperty(property, &value);
            UT_ASSERT_TRUE(value.has_value());
            UT_ASSERT_EQUAL(value.value(), android::String16("ABCDEF"));
        } else if (property == android::String16("KEY_WPSPIN")) {
            deviceInfo->setProperty(property, android::String16("12345670"), &result); // Valid 8-digit PIN
            UT_ASSERT_EQUAL(result, com::rdk::hal::deviceinfo::SetPropertyResult::SUCCESS);
            result = com::rdk::hal::deviceinfo::SetPropertyResult::ERROR_INVALID_PARAM;
            deviceInfo->getProperty(property, &value);
            UT_ASSERT_TRUE(value.has_value());
            UT_ASSERT_EQUAL(value.value(), android::String16("12345670"));
        } else if (property == android::String16("KEY_WIFIMAC") ||
                   property == android::String16("KEY_BLUETOOTHMAC") ||
                   property == android::String16("KEY_ETHERNETMAC") ||
                   property == android::String16("KEY_RF4CEMAC")) {
            deviceInfo->setProperty(property, android::String16("00:11:22:33:44:55"), &result); // Valid MAC address
            UT_ASSERT_EQUAL(result, com::rdk::hal::deviceinfo::SetPropertyResult::SUCCESS);
            result = com::rdk::hal::deviceinfo::SetPropertyResult::ERROR_INVALID_PARAM;
            deviceInfo->getProperty(property, &value);
            UT_ASSERT_TRUE(value.has_value());
            UT_ASSERT_EQUAL(value.value(), android::String16("00:11:22:33:44:55"));
        } else if (property == android::String16("KEY_MANUFACTURER") ||
                   property == android::String16("KEY_MODELNAME") ||
                   property == android::String16("KEY_PRODUCTCLASS") ||
                   property == android::String16("KEY_SERIALNUMBER") ||
                   property == android::String16("KEY_IMAGENAME") ||
                   property == android::String16("KEY_IMAGETYPE") ||
                   property == android::String16("KEY_COUNTRYCODE") ||
                   property == android::String16("KEY_LANGUAGECODE") ||
                   property == android::String16("KEY_MANUFACTURERDATA")) {
            deviceInfo->setProperty(property, android::String16("TestValue"), &result);
            UT_ASSERT_EQUAL(result, com::rdk::hal::deviceinfo::SetPropertyResult::SUCCESS);
            result = com::rdk::hal::deviceinfo::SetPropertyResult::ERROR_INVALID_PARAM;
            deviceInfo->getProperty(property, &value);
            UT_ASSERT_TRUE(value.has_value());
            UT_ASSERT_EQUAL(value.value(), android::String16("TestValue"));
        } else {
            UT_LOG_DEBUG("No test case defined for property: %s", android::internal::ToString(property).c_str());
        }
    }
}

/**
* @} // End of DEVICEINFO_HALTEST_CLASS
* @} // End of DEVICEINFO_HALTEST
* @} // End of DEVICEINFO
* @} // End of HPK
*/
/* End of vts_deviceinfo_l2_tests.cpp */