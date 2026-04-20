/*
 *  If not stated otherwise in this file or this component's LICENSE
 *  file the following copyright and licenses apply:
 *
 *  Copyright 2026 RDK Management
 *
 *  Licensed under the Apache License, Version 2.0 (the License);
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an AS IS BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
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
 * @brief Positive test for getCapabilities() function of deviceInfo
 *
 * This test verifies that the getCapabilities() method of the deviceInfo interface
 * correctly populates the Capabilities structure with the supported properties.
 *
 * **Test Group ID:** 01@n
 * **Test Case ID:** 001@n
 *
 * **Test Procedure:**
 * | Step | Action                                          | Input / Test Data                                       | Expected Result                         | Notes                                      |
 * |------|-------------------------------------------------|---------------------------------------------------------|-----------------------------------------|--------------------------------------------|
 * | 1    | Obtain deviceInfo handle                        | gDEVICEINFOHandle                                       | deviceInfo is not nullptr               |                                            |
 * | 2    | Call DEVICEINFO_GET_CAPABILITIES                | deviceInfo, caps                                        | caps.supportedProperties is populated   |                                            |
 * | 3    | Compare supportedProperties count               | caps.supportedProperties, UT_KVP_PROFILE_GET_LIST_COUNT | Counts are equal                        |                                            |
 * | 4    | For each property, get String field "name"      | property, ut_kvp_getStringField                         | Each property is present in the profile | checks each supported property              |
 *
 */

UT_ADD_TEST(VTS_L1_DEVICEINFO, getCapabilities_pos)
{
    android::sp<com::rdk::hal::deviceinfo::IDeviceInfo> deviceInfo = gDEVICEINFOHandle;
    UT_ASSERT_NOT_EQUAL(deviceInfo, nullptr);
    com::rdk::hal::deviceinfo::Capabilities caps;
    DEVICEINFO_GET_CAPABILITIES(deviceInfo, caps);
    const std::string baseKey = "deviceinfo.properties";
    UT_ASSERT_EQUAL(caps.supportedProperties.size(), UT_KVP_PROFILE_GET_LIST_COUNT(baseKey.c_str()));
    for (const auto &property : caps.supportedProperties)
    {
        const std::string propertyStr = android::internal::ToString(property);
        UT_LOG_DEBUG("Supported Property: %s\n", propertyStr.c_str());
        std::string key;
        char propertyValue[UT_KVP_MAX_ELEMENT_SIZE] = {0};
        for(int i = 0;i < (int)caps.supportedProperties.size(); i++)
        {
            key = baseKey + "." + std::to_string(i) + "." + "name";
            if (ut_kvp_getStringField(ut_kvp_profile_getInstance(), key.c_str(), propertyValue, sizeof(propertyValue)) == UT_KVP_STATUS_SUCCESS)
            {
                if (propertyStr == propertyValue)
                {
                    UT_ASSERT_STRING_EQUAL(propertyValue, propertyStr.c_str()); // Key found
                    break;
                }
            }
            else
            {
                // Key not found in profile, fail the test
                UT_LOG_ERROR("Property name field not found in profile for index %d", i);
                UT_ASSERT_FALSE(true); // Fail the test
            }
        }
    }
}

/**
 * @brief Positive test for verifying getProperty() functions of IDeviceInfo
 *
 * This test verifies that the getProperty() methods of the deviceInfo interface
 * correctly set and retrieve property values for all supported properties.
 *
 * **Test Group ID:** 01@n
 * **Test Case ID:** 002@n
 *
 * **Test Procedure:**
 * | Step | Action                                                                           | Input / Test Data                                       | Expected Result                         | Notes                                      |
 * |------|----------------------------------------------------------------------------------|---------------------------------------------------------|-----------------------------------------|--------------------------------------------|
 * | 1    | Obtain deviceInfo handle                                                         | gDEVICEINFOHandle                                       | deviceInfo is not nullptr               |                                            |
 * | 2    | Call DEVICEINFO_GET_CAPABILITIES                                                 | deviceInfo, caps                                        | caps.supportedProperties is populated   |                                            |
 * | 3    | Compare supportedProperties count                                                | caps.supportedProperties, UT_KVP_PROFILE_GET_LIST_COUNT | Counts are equal                        |                                            |
 * | 4    | For each property, get the property name, key, format, max_size, zero_terminated | property, UT_KVP_PROFILE_GET_STRING                     | Retrieved value matches the yaml profile|Checks each property string against profile|
 */
UT_ADD_TEST(VTS_L1_DEVICEINFO, getProperty_pos)
{
    android::sp<com::rdk::hal::deviceinfo::IDeviceInfo> deviceInfo = gDEVICEINFOHandle;
    UT_ASSERT_NOT_EQUAL(deviceInfo, nullptr);
    com::rdk::hal::deviceinfo::Capabilities caps;
    const std::string baseKey = "deviceinfo.properties";
    DEVICEINFO_GET_CAPABILITIES(deviceInfo, caps);
    UT_ASSERT_EQUAL(caps.supportedProperties.size(), UT_KVP_PROFILE_GET_LIST_COUNT(baseKey.c_str()));

    for (const auto &propertyKey : caps.supportedProperties)
    {
        const std::string propertyStr = android::internal::ToString(propertyKey);
        UT_LOG_DEBUG("Supported Property: %s", propertyStr.c_str());
        ::std::optional<::com::rdk::hal::deviceinfo::Property> propertyVal = std::nullopt;

        // Get the property value from HAL
        DEVICEINFO_GET_PROPERTY(deviceInfo, propertyKey, propertyVal);
        UT_ASSERT_TRUE(propertyVal.has_value());

        std::string key;
        char returnedString[UT_KVP_MAX_ELEMENT_SIZE] = {0}; // Buffer to hold expected value from profile
        for (int i = 0; i < (int)caps.supportedProperties.size(); i++)
        {
            key = baseKey + "." + std::to_string(i) + "." + "name";
            if (ut_kvp_getStringField(ut_kvp_profile_getInstance(), key.c_str(), returnedString, sizeof(returnedString)) == UT_KVP_STATUS_SUCCESS)
            {
                if (propertyStr == returnedString)
                {
                    // Key found, now validate other fields
                    // Validate 'key' field
                    key = baseKey + "." + std::to_string(i) + "." + "value";
                    if (ut_kvp_getStringField(ut_kvp_profile_getInstance(), key.c_str(), returnedString, sizeof(returnedString)) == UT_KVP_STATUS_SUCCESS)
                    {
                        UT_ASSERT_STRING_EQUAL(android::String8(propertyVal->key).string(), returnedString); // Value matches
                    }

                    key = baseKey + "." + std::to_string(i) + "." + "format";
                    if (ut_kvp_getStringField(ut_kvp_profile_getInstance(), key.c_str(), returnedString, sizeof(returnedString)) == UT_KVP_STATUS_SUCCESS)
                    {
                        UT_ASSERT_STRING_EQUAL(android::String8(android::internal::ToString(propertyVal->type).c_str()).string(), returnedString); // Format matches
                    }
                    key = baseKey + "." + std::to_string(i) + "." + "max_size";
                    uint32_t expectedSize = ut_kvp_getUInt32Field(ut_kvp_profile_getInstance(), key.c_str());
                    UT_ASSERT_EQUAL(static_cast<uint32_t>(propertyVal->sizeInBytes), expectedSize); // Size matches

                    key = baseKey + "." + std::to_string(i) + "." + "zero_terminated";
                    bool expectedZeroTerminated = ut_kvp_getBoolField(ut_kvp_profile_getInstance(), key.c_str());
                    UT_ASSERT_EQUAL(propertyVal->zeroTerminated, expectedZeroTerminated); // Zero terminated matches
                    // Exit loop after validating the found key
                    break;
                }
            }
            else
            {
                // Key not found in profile, fail the test
                UT_LOG_ERROR("Property name field not found in profile for index %d", i);
                UT_ASSERT_FALSE(true); // Fail the test
            }
        }
    }
}

/**
 * @brief Negative Test for getProperty() function of deviceInfo
 *
 * This test verifies that the getProperty() method of the deviceInfo interface
 * correctly handles invalid, empty, and null property keys.
 *
 * **Test Group ID:** 01@n
 * **Test Case ID:** 003@n
 *
 * **Test Procedure:**
 * | Step | Action                                                 | Input / Test Data                          | Expected Result           | Notes      |
 * |------|--------------------------------------------------------|--------------------------------------------|---------------------------|------------|
 * | 1    | Obtain deviceInfo handle                               | gDEVICEINFOHandle                          | deviceInfo is not nullptr |            |
 * | 2    | Call DEVICEINFO_GET_PROPERTY_NEGATIVE with invalid key | deviceInfo, "KEY_INVALID", value           | value.has_value() is false|            |
 * | 3    | Call DEVICEINFO_GET_PROPERTY_NEGATIVE with empty key   | deviceInfo, "", value                      | value.has_value() is false|            |
 * | 4    | Call DEVICEINFO_GET_PROPERTY_NEGATIVE with null key    | deviceInfo, null, value                    | value.has_value() is false|            |
*/
UT_ADD_TEST(VTS_L1_DEVICEINFO, getProperty_neg)
{
    android::sp<com::rdk::hal::deviceinfo::IDeviceInfo> deviceInfo = gDEVICEINFOHandle;
    UT_ASSERT_NOT_EQUAL(deviceInfo, nullptr);

    // Testing with an invalid property key
    std::optional<com::rdk::hal::deviceinfo::Property> propertyVal = std::nullopt;
    android::String16 key("KEY_INVALID");
    DEVICEINFO_GET_PROPERTY_NEGATIVE(deviceInfo, key, propertyVal);
    UT_ASSERT_FALSE(propertyVal.has_value());

    // Testing with an empty property key
    propertyVal = std::nullopt;
    key = android::String16("");
    DEVICEINFO_GET_PROPERTY_NEGATIVE(deviceInfo, key, propertyVal);
    UT_ASSERT_FALSE(propertyVal.has_value());

    // Testing with a null property key
    propertyVal = std::nullopt;
    key = android::String16(); // This creates an empty String16, simulating a null key
    DEVICEINFO_GET_PROPERTY_NEGATIVE(deviceInfo, key, propertyVal);
    UT_ASSERT_FALSE(propertyVal.has_value());

}

/**
* @} // End of DEVICEINFO_HALTEST_CLASS
* @} // End of DEVICEINFO_HALTEST
* @} // End of DEVICEINFO
* @} // End of HPK
*/
/* End of vts_deviceinfo_l1_tests.cpp */