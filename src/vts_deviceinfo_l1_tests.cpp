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
 * @brief L1 Test Cases for the DEVICEINFO HAL (Hardware Abstraction Layer) interface.
 *
 * This file contains unit tests for the DEVICEINFO module as part of the Hardware Porting Kit (HPK).
 * The tests validate the correct implementation of the IDeviceInfo interface, including its capabilities,
 * versioning, and property handling functionalities.
 *
 * @addtogroup HPK Hardware */


#include <ut_log.h>
#include <ut_kvp_profile.h>

#include "vts_deviceinfo.h"

extern android::sp<com::rdk::hal::deviceinfo::IDeviceInfo> gDEVICEINFOHandle;

/* Test class registration with UT_Core */
UT_ADD_TEST_TO_GROUP(VTS_L1_DEVICEINFO, UT_TESTS_L1)

class VTS_L1_DEVICEINFO : public UTCore
{
public:
    VTS_L1_DEVICEINFO() : UTCore() {}

    ~VTS_L1_DEVICEINFO() override = default;

    void SetUp() override
    {
        android::ProcessState::self()->startThreadPool();
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
 * | Step | Action                                          | Input / Test Data                                       | Expected Result                         | Notes                                      |
 * |------|-------------------------------------------------|---------------------------------------------------------|-----------------------------------------|--------------------------------------------|
 * | 1    | Obtain deviceInfo handle                        | gDEVICEINFOHandle                                       | deviceInfo is not nullptr               |                                            |
 * | 2    | Call DEVICEINFO_GET_CAPABILITIES                | deviceInfo, caps                                        | caps.supportedProperties is populated   |                                            |
 * | 3    | Compare supportedProperties count               | caps.supportedProperties, UT_KVP_PROFILE_GET_LIST_COUNT | Counts are equal                        |                                            |
 * | 4    | For each property, check if present in profile  | property, UT_KVP_PROFILE_GET_STRING                     | found == true                           | Checks each property string against profile|
 *
 */

UT_ADD_TEST(VTS_L1_DEVICEINFO, test_getCapabilities)
{
    android::sp<com::rdk::hal::deviceinfo::IDeviceInfo> deviceInfo = gDEVICEINFOHandle;
    UT_ASSERT_NOT_EQUAL(deviceInfo, nullptr);
    com::rdk::hal::deviceinfo::Capabilities caps;
    DEVICEINFO_GET_CAPABILITIES(deviceInfo, caps);

    UT_ASSERT_EQUAL(caps.supportedProperties.size(), UT_KVP_PROFILE_GET_LIST_COUNT("IDeviceInfo.supportedProperties"));
    for (const auto &property : caps.supportedProperties)
    {
        const std::string propertyStr = android::internal::ToString(property);
        UT_LOG_DEBUG("Supported Property: %s", propertyStr.c_str());

        const int propCount = UT_KVP_PROFILE_GET_LIST_COUNT("IDeviceInfo.supportedProperties");
        const std::string baseKey = "IDeviceInfo.supportedProperties.";
        bool found = false;
        std::string key;
        char returnedString[UT_KVP_MAX_ELEMENT_SIZE] = {0};
        for (int i = 0; i < propCount; ++i)
        {
            key.clear();
            key.reserve(baseKey.size() + 16 + propertyStr.size()); // avoid reallocations
            key.append(baseKey).append(std::to_string(i)).append(".").append(propertyStr);

            UT_KVP_PROFILE_GET_STRING(key.c_str(), returnedString);

            if (returnedString[0] != '\0')
            {
                found = true;
                returnedString[0] = '\0'; // reset returnedString
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
 * | Step | Action                          | Input / Test Data                                   | Expected Result                 | Notes      |
 * |------|---------------------------------|-----------------------------------------------------|---------------------------------|------------|
 * | 1    | Obtain deviceInfo handle        | gDEVICEINFOHandle                                   | deviceInfo is not nullptr       |            |
 * | 2    | Call DEVICEINFO_GET_HALVERSION  | deviceInfo, halVersion                              | halVersion is populated         |            |
 * | 3    | Compare HALVersion fields       | halVersion.major/minor/doc, profile values          | All fields match profile values |            |
 *
 */
UT_ADD_TEST(VTS_L1_DEVICEINFO, test_getHALVersion)
{
    android::sp<com::rdk::hal::deviceinfo::IDeviceInfo> deviceInfo = gDEVICEINFOHandle;
    UT_ASSERT_NOT_EQUAL(deviceInfo, nullptr);
    com::rdk::hal::deviceinfo::HALVersion halVersion;
    DEVICEINFO_GET_HALVERSION(deviceInfo, halVersion);
    UT_LOG_DEBUG("HAL Version: Major=%d, Minor=%d, Doc=%d", halVersion.major, halVersion.minor, halVersion.doc);
    UT_ASSERT_EQUAL(halVersion.major, UT_KVP_PROFILE_GET_UINT8("IDeviceInfo.HALVersion.major"));
    UT_ASSERT_EQUAL(halVersion.minor, UT_KVP_PROFILE_GET_UINT8("IDeviceInfo.HALVersion.minor"));
    UT_ASSERT_EQUAL(halVersion.doc, UT_KVP_PROFILE_GET_UINT8("IDeviceInfo.HALVersion.doc"));
}

/**
 * @brief Positive test for verifying getProperty() functions of IDeviceInfo
 *
 * This test verifies that the getProperty() methods of the IDeviceInfo interface
 * correctly set and retrieve property values for all supported properties.
 *
 * **Test Group ID:** 02@n
 * **Test Case ID:** 003@n
 *
 * **Test Procedure:**
 * | Step | Action                                          | Input / Test Data                                       | Expected Result                         | Notes                                      |
 * |------|-------------------------------------------------|---------------------------------------------------------|-----------------------------------------|--------------------------------------------|
 * | 1    | Obtain deviceInfo handle                        | gDEVICEINFOHandle                                       | deviceInfo is not nullptr               |                                            |
 * | 2    | Call DEVICEINFO_GET_CAPABILITIES                | deviceInfo, caps                                        | caps.supportedProperties is populated   |                                            |
 * | 3    | Compare supportedProperties count               | caps.supportedProperties, UT_KVP_PROFILE_GET_LIST_COUNT | Counts are equal                        |                                            |
 * | 4    | For each property, get the property value       | property, value, UT_KVP_PROFILE_GET_STRING              | Retrieved value matches the yaml profile|Checks each property string against profile|
 */
UT_ADD_TEST(VTS_L1_DEVICEINFO, test_getProperty)
{
    android::sp<com::rdk::hal::deviceinfo::IDeviceInfo> deviceInfo = gDEVICEINFOHandle;
    UT_ASSERT_NOT_EQUAL(deviceInfo, nullptr);
    com::rdk::hal::deviceinfo::Capabilities caps;
    com::rdk::hal::deviceinfo::SetPropertyResult result;

    DEVICEINFO_GET_CAPABILITIES(deviceInfo, caps);
    UT_ASSERT_EQUAL(caps.supportedProperties.size(), UT_KVP_PROFILE_GET_LIST_COUNT("IDeviceInfo.supportedProperties"));

    for (const auto &property : caps.supportedProperties)
    {
        const std::string propertyStr = android::internal::ToString(property);
        UT_LOG_DEBUG("Supported Property: %s", propertyStr.c_str());
        std::optional<::android::String16> value = std::nullopt;
        const int propCount = UT_KVP_PROFILE_GET_LIST_COUNT("IDeviceInfo.supportedProperties");
        const std::string baseKey = "IDeviceInfo.supportedProperties.";
        bool found = false;
        std::string key;
        char returnedString[UT_KVP_MAX_ELEMENT_SIZE] = {0}; // or appropriate size

        for (int i = 0; i < propCount; ++i)
        {
            key.clear();
            key.reserve(baseKey.size() + 16 + propertyStr.size()); // avoid reallocations
            key.append(baseKey).append(std::to_string(i)).append(".").append(propertyStr);

            UT_KVP_PROFILE_GET_STRING(key.c_str(), returnedString);
            DEVICEINFO_GET_PROPERTY(deviceInfo, property, value);

            if (returnedString[0] != '\0')
            {
                found = true;
                UT_ASSERT_EQUAL(value.value(), android::String16(android::String8(returnedString)));
                returnedString[0] = '\0'; // reset returnedString
                break;
            }
        }

        UT_ASSERT_TRUE(found);
    }
}

/**
 * @brief Negative Test for getProperty() function of IDeviceInfo
 *
 * This test verifies that the getProperty() method of the IDeviceInfo interface
 * correctly handles invalid, empty, and null property keys.
 *
 * **Test Group ID:** 02@n
 * **Test Case ID:** 004@n
 *
 * **Test Procedure:**
 * | Step | Action                                                 | Input / Test Data                          | Expected Result           | Notes      |
 * |------|--------------------------------------------------------|--------------------------------------------|---------------------------|------------|
 * | 1    | Obtain deviceInfo handle                               | gDEVICEINFOHandle                          | deviceInfo is not nullptr |            |
 * | 2    | Call DEVICEINFO_GET_PROPERTY_NEGATIVE with invalid key | deviceInfo, "KEY_INVALID", value           | value.has_value() is false|            |
 * | 3    | Call DEVICEINFO_GET_PROPERTY_NEGATIVE with empty key   | deviceInfo, "", value                      | value.has_value() is false|            |
 * | 4    | Call DEVICEINFO_GET_PROPERTY_NEGATIVE with null key    | deviceInfo, null, value                    | value.has_value() is false|            |
*/
UT_ADD_TEST(VTS_L1_DEVICEINFO, test_getPropertyNegative)
{
    android::sp<com::rdk::hal::deviceinfo::IDeviceInfo> deviceInfo = gDEVICEINFOHandle;
    UT_ASSERT_NOT_EQUAL(deviceInfo, nullptr);

    // Testing with an invalid property key
    std::optional<::android::String16> value = std::nullopt;
    android::String16 key("KEY_INVALID");
    DEVICEINFO_GET_PROPERTY_NEGATIVE(deviceInfo, key, value);
    UT_ASSERT_FALSE(value.has_value());

    // Testing with an empty property key
    value = std::nullopt;
    key = android::String16("");
    DEVICEINFO_GET_PROPERTY_NEGATIVE(deviceInfo, key, value);
    UT_ASSERT_FALSE(value.has_value());

    // Testing with a null property key
    value = std::nullopt;
    key = android::String16(); // This creates an empty String16, simulating a null key
    DEVICEINFO_GET_PROPERTY_NEGATIVE(deviceInfo, key, value);
    UT_ASSERT_FALSE(value.has_value());

}

/**
* @} // End of DEVICEINFO_HALTEST_CLASS
* @} // End of DEVICEINFO_HALTEST
* @} // End of DEVICEINFO
* @} // End of HPK
*/
/* End of vts_deviceinfo_l1_tests.cpp */