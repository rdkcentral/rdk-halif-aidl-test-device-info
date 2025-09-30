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
 * @defgroup DEVICEINFO_HALTEST_CLASS DEVICEINFO HAL Header File
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
 * @file vts_deviceinfo.h
 *
 */

#pragma once

#include <ut.h>
#include <ut_kvp_profile.h>
#include <com/rdk/hal/deviceinfo/BpDeviceInfo.h>
#include <com/rdk/hal/deviceinfo/Capabilities.h>
#include <com/rdk/hal/deviceinfo/HALVersion.h>
#include <com/rdk/hal/deviceinfo/SetPropertyResult.h>

using android::sp;
using android::String16;
using com::rdk::hal::deviceinfo::IDeviceInfo;
using com::rdk::hal::deviceinfo::Capabilities;
using com::rdk::hal::deviceinfo::HALVersion;
using com::rdk::hal::deviceinfo::SetPropertyResult;

// Macro for getCapabilities - positive case
#define DEVICEINFO_GET_CAPABILITIES(deviceinfoHandle, caps) \
    do { \
        ::android::binder::Status status; \
        UT_LOG_DEBUG("Calling getCapabilities(OUT:caps[])"); \
        status = (deviceinfoHandle)->getCapabilities(&caps); \
        UT_LOG_DEBUG("Result getCapabilities(OUT:caps), status:[isOK:%d, exception:%d]", status.isOk(), status.exceptionCode()); \
        UT_ASSERT_TRUE(status.isOk()); \
        UT_ASSERT_EQUAL(status.exceptionCode(), ::android::binder::Status::EX_NONE); \
        UT_LOG_DEBUG("Capabilities supportedProperties size: %zu", caps.supportedProperties.size()); \
        for (const auto& prop : caps.supportedProperties) { \
            UT_LOG_DEBUG("Supported Property: %s", android::String8(prop).string()); \
        } \
    } while (0)

// Macro for getHALVersion - positive case
#define DEVICEINFO_GET_HALVERSION(deviceinfoHandle, version) \
    do { \
        ::android::binder::Status status; \
        UT_LOG_DEBUG("Calling getHALVersion(OUT:version[])"); \
        status = (deviceinfoHandle)->getHALVersion(&version); \
        UT_LOG_DEBUG("Result getHALVersion(OUT:version), status:[isOK:%d, exception:%d]", status.isOk(), status.exceptionCode()); \
        UT_ASSERT_TRUE(status.isOk()); \
        UT_ASSERT_EQUAL(status.exceptionCode(), ::android::binder::Status::EX_NONE); \
        UT_LOG_DEBUG("HAL Version: %d.%d.%d", version.major, version.minor, version.doc); \
    } while (0)

// Macro for getProperty - positive case
#define DEVICEINFO_GET_PROPERTY(deviceinfoHandle, key, value) \
    do { \
        ::android::binder::Status status; \
        UT_LOG_DEBUG("Calling getProperty(IN:key[%s], OUT:value[])", android::String8(key).string()); \
        status = (deviceinfoHandle)->getProperty(key, &value); \
        UT_LOG_DEBUG("Result getProperty(OUT:%s), status:[isOK:%d, exception:%d]", android::String8(value.value()).string(), status.isOk(), status.exceptionCode()); \
        UT_ASSERT_TRUE(status.isOk()); \
        UT_ASSERT_EQUAL(status.exceptionCode(), ::android::binder::Status::EX_NONE); \
        UT_LOG_DEBUG("Property Value: %s", android::String8(value.value()).string()); \
        value = std::nullopt; \
    } while (0)

// Macro for setProperty - positive case
#define DEVICEINFO_SET_PROPERTY(deviceinfoHandle, key, val, result) \
    do { \
        ::android::binder::Status status; \
        UT_LOG_DEBUG("Calling setProperty(IN:key[%s], IN:val[%s], OUT:result[])", android::String8(key).string(), android::String8(val).string()); \
        status = (deviceinfoHandle)->setProperty(key, val, &result); \
        UT_LOG_DEBUG("Result setProperty(OUT:%d), status:[isOK:%d, exception:%d]", result, status.isOk(), status.exceptionCode()); \
        UT_ASSERT_TRUE(status.isOk()); \
        UT_ASSERT_EQUAL(status.exceptionCode(), ::android::binder::Status::EX_NONE); \
        UT_ASSERT_EQUAL(result, SetPropertyResult::SUCCESS); \
        UT_LOG_DEBUG("Set Property Result: %s", toString(result).c_str()); \
    } while (0)

// Macro for getProperty - negative case
#define DEVICEINFO_GET_PROPERTY_NEGATIVE(deviceinfoHandle, key, value) \
    do { \
        ::android::binder::Status status; \
        UT_LOG_DEBUG("Calling getProperty(IN:key[%s], OUT:value[])", android::String8(key).string()); \
        status = (deviceinfoHandle)->getProperty(key, &value); \
        UT_LOG_DEBUG("Result getProperty(OUT:value), status:[isok:%d, exception:%d]", status.isOk(), status.exceptionCode()); \
        UT_ASSERT_FALSE(status.isOk()); \
        UT_ASSERT_EQUAL(status.exceptionCode(), ::android::binder::Status::EX_ILLEGAL_ARGUMENT); \
        UT_ASSERT_FALSE(value.has_value()); \
    } while (0)

// Macro for setProperty - negative case
#define DEVICEINFO_SET_PROPERTY_NEGATIVE(deviceinfoHandle, key, val, result)                                   \
    do                                                                                                         \
    {                                                                                                          \
        ::android::binder::Status status;                                                    \
        UT_LOG_DEBUG("Calling setProperty(IN:key[%s], IN:val[%s], OUT:result[])", android::String8(key).string(), android::String8(val).string()); \
        status = (deviceinfoHandle)->setProperty(key, val, &result);                                           \
        UT_LOG_DEBUG("Result setProperty(OUT:value), status:[isok:%d, exception:%d, result:%d]", status.isOk(), status.exceptionCode(), result); \
        UT_ASSERT_FALSE(status.isOk());                                                                        \
        UT_ASSERT_EQUAL(status.exceptionCode(), ::android::binder::Status::EX_ILLEGAL_ARGUMENT);               \
        UT_ASSERT_EQUAL(result, SetPropertyResult::ERROR_INVALID_PARAM);                                   \
    } while (0)

// static inline std::string toString(SetPropertyResult result) {
//     switch (result) {
//         case SetPropertyResult::SUCCESS:
//             return "SUCCESS";
//         case SetPropertyResult::ERROR_INVALID_PARAM:
//             return "ERROR_INVALID_PARAM";
//         case SetPropertyResult::ERROR_MEMORY_EXHAUSTED:
//             return "ERROR_MEMORY_EXHAUSTED";
//         default:
//             return "UNKNOWN";
//     }
// }

/**
 * @} // End of DEVICEINFO_HALTEST_CLASS
 * @} // End of DEVICEINFO_HALTEST
 * @} // End of DEVICEINFO
 * @} // End of HPK
 */
/* End of vts_deviceinfo.h */