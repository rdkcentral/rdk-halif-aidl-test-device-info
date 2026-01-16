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

#include <binder/IServiceManager.h>
#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>
#include <binder/Status.h>
#include <utils/String16.h>

#include "com/rdk/hal/deviceinfo/IDeviceInfo.h"
#include <com/rdk/hal/deviceinfo/BpDeviceInfo.h>
#include <com/rdk/hal/deviceinfo/Capabilities.h>
#include <com/rdk/hal/deviceinfo/Property.h>
#include <com/rdk/hal/deviceinfo/PropertyType.h>

using android::sp;
using android::String16;
using com::rdk::hal::deviceinfo::IDeviceInfo;
using com::rdk::hal::deviceinfo::Capabilities;
using com::rdk::hal::deviceinfo::Property;
using com::rdk::hal::deviceinfo::PropertyType;

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
    } while (0)

// Macro for getProperty - positive case
#define DEVICEINFO_GET_PROPERTY(deviceinfoHandle, propertyKey, propertyVal)                                \
    do                                                                                                \
    {                                                                                                 \
        ::android::binder::Status status;                                                             \
        UT_LOG_DEBUG("Calling getProperty(IN:key[%s], OUT:value[])", android::String8(propertyKey).string()); \
        status = (deviceinfoHandle)->getProperty(propertyKey, &propertyVal); \
        UT_LOG_DEBUG("Result getProperty(OUT:value), status:[isok:%d, exception:%d]", status.isOk(), status.exceptionCode()); \
        UT_ASSERT_TRUE(status.isOk()); \
        UT_ASSERT_EQUAL(status.exceptionCode(), ::android::binder::Status::EX_NONE); \
        UT_LOG_DEBUG("Property key: %s", android::internal::ToString(propertyVal->key).c_str()); \
        UT_LOG_DEBUG("Property type: %s", android::internal::ToString(propertyVal->type).c_str()); \
        UT_LOG_DEBUG("Property sizeInBytes: %s", android::internal::ToString(propertyVal->sizeInBytes).c_str()); \
        UT_LOG_DEBUG("Property zeroTerminated: %s", android::internal::ToString(propertyVal->zeroTerminated).c_str()); \
    } while (0)

// Macro for getProperty - negative case
#define DEVICEINFO_GET_PROPERTY_NEGATIVE(deviceinfoHandle, key, value)                                \
    do                                                                                                \
    {                                                                                                 \
        ::android::binder::Status status;                                                             \
        UT_LOG_DEBUG("Calling getProperty(IN:key[%s], OUT:value[])", key ? android::String8(key).string() : "null"); \
        status = (deviceinfoHandle)->getProperty(key, &value); \
        UT_LOG_DEBUG("Result getProperty(OUT:value), status:[isok:%d, exception:%d]", status.isOk(), status.exceptionCode()); \
        UT_ASSERT_TRUE(status.isOk()); \
        UT_ASSERT_EQUAL(status.exceptionCode(), ::android::binder::Status::EX_NONE); \
        UT_ASSERT_FALSE(value.has_value()); \
    } while (0)

/**
 * @} // End of DEVICEINFO_HALTEST_CLASS
 * @} // End of DEVICEINFO_HALTEST
 * @} // End of DEVICEINFO
 * @} // End of HPK
 */
/* End of vts_deviceinfo.h */
