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

/* 
* @brief 
* vcomponent_Deviceinfo.cpp
* Implementation of the DeviceInfo service implementation
*/

#include "vcomponent_Deviceinfo.h"
#include "vcomponent_Deviceinfo_parse_config.h"
#include <regex>

namespace com
{
    namespace rdk
    {
        namespace hal
        {
            namespace deviceinfo
            {

                DeviceInfo::DeviceInfo()
                {
                }
                DeviceInfo::~DeviceInfo()
                {
                }

                ::android::binder::Status DeviceInfo::getCapabilities(Capabilities *_aidl_return)
                {
                    if (!_aidl_return)
                    {
                        return android::binder::Status::fromExceptionCode(android::binder::Status::EX_ILLEGAL_ARGUMENT);
                    }
                    *_aidl_return = Capabilities();
                    _aidl_return->supportedProperties.push_back(android::String16("KEY_MANUFACTURER"));
                    _aidl_return->supportedProperties.push_back(android::String16("KEY_MANUFACTURER_OUI"));
                    _aidl_return->supportedProperties.push_back(android::String16("KEY_MODELNAME"));
                    _aidl_return->supportedProperties.push_back(android::String16("KEY_PRODUCTCLASS"));
                    _aidl_return->supportedProperties.push_back(android::String16("KEY_SERIALNUMBER"));
                    _aidl_return->supportedProperties.push_back(android::String16("KEY_WIFIMAC"));
                    _aidl_return->supportedProperties.push_back(android::String16("KEY_BLUETOOTHMAC"));
                    _aidl_return->supportedProperties.push_back(android::String16("KEY_WPSPIN"));
                    _aidl_return->supportedProperties.push_back(android::String16("KEY_ETHERNETMAC"));
                    _aidl_return->supportedProperties.push_back(android::String16("KEY_RF4CEMAC"));
                    _aidl_return->supportedProperties.push_back(android::String16("KEY_IMAGENAME"));
                    _aidl_return->supportedProperties.push_back(android::String16("KEY_IMAGETYPE"));
                    _aidl_return->supportedProperties.push_back(android::String16("KEY_COUNTRYCODE"));
                    _aidl_return->supportedProperties.push_back(android::String16("KEY_LANGUAGECODE"));
                    _aidl_return->supportedProperties.push_back(android::String16("KEY_MANUFACTURERDATA"));
                    return ::android::binder::Status::ok();
                }

                ::android::binder::Status DeviceInfo::getHALVersion(HALVersion *_aidl_return)
                {
                    if (!_aidl_return)
                    {
                        return android::binder::Status::fromExceptionCode(android::binder::Status::EX_ILLEGAL_ARGUMENT);
                    }
                    *_aidl_return = HALVersion();
                    _aidl_return->major = 0;
                    _aidl_return->minor = 7;
                    _aidl_return->doc = 1; // Example version 0.7.1
                    return ::android::binder::Status::ok();
                }

                ::android::binder::Status DeviceInfo::getProperty(const ::android::String16 &propertyKey, std::optional<::android::String16> *_aidl_return)
                {
                    if (!_aidl_return)
                    {
                        return android::binder::Status::fromExceptionCode(android::binder::Status::EX_ILLEGAL_ARGUMENT);
                    }
                    if (propertyKey == android::String16("KEY_MANUFACTURER"))
                    {
                        *_aidl_return = android::String16(gDeviceInfoConfig.manufacturer.c_str());
                    }
                    else if (propertyKey == android::String16("KEY_MANUFACTURER_OUI"))
                    {
                        *_aidl_return = android::String16(gDeviceInfoConfig.manufacturerOUI.c_str());
                    }
                    else if (propertyKey == android::String16("KEY_MODELNAME"))
                    {
                        *_aidl_return = android::String16(gDeviceInfoConfig.modelName.c_str());
                    }
                    else if (propertyKey == android::String16("KEY_PRODUCTCLASS"))
                    {
                        *_aidl_return = android::String16(gDeviceInfoConfig.productClass.c_str());
                    }
                    else if (propertyKey == android::String16("KEY_SERIALNUMBER"))
                    {
                        *_aidl_return = android::String16(gDeviceInfoConfig.serialNumber.c_str());
                    }
                    else if (propertyKey == android::String16("KEY_WIFIMAC"))
                    {
                        *_aidl_return = android::String16(gDeviceInfoConfig.wifiMac.c_str());
                    }
                    else if (propertyKey == android::String16("KEY_BLUETOOTHMAC"))
                    {
                        *_aidl_return = android::String16(gDeviceInfoConfig.bluetoothMac.c_str());
                    }
                    else if (propertyKey == android::String16("KEY_WPSPIN"))
                    {
                        *_aidl_return = android::String16(gDeviceInfoConfig.wpsPin.c_str());
                    }
                    else if (propertyKey == android::String16("KEY_ETHERNETMAC"))
                    {
                        *_aidl_return = android::String16(gDeviceInfoConfig.ethernetMac.c_str());
                    }
                    else if (propertyKey == android::String16("KEY_RF4CEMAC"))
                    {
                        *_aidl_return = android::String16(gDeviceInfoConfig.rf4ceMac.c_str());
                    }
                    else if (propertyKey == android::String16("KEY_IMAGENAME"))
                    {
                        *_aidl_return = android::String16(gDeviceInfoConfig.imageName.c_str());
                    }
                    else if (propertyKey == android::String16("KEY_IMAGETYPE"))
                    {
                        *_aidl_return = android::String16(gDeviceInfoConfig.imageType.c_str());
                    }
                    else if (propertyKey == android::String16("KEY_COUNTRYCODE"))
                    {
                        *_aidl_return = android::String16(gDeviceInfoConfig.countryCode.c_str());
                    }
                    else if (propertyKey == android::String16("KEY_LANGUAGECODE"))
                    {
                        *_aidl_return = android::String16(gDeviceInfoConfig.languageCode.c_str());
                    }
                    else if (propertyKey == android::String16("KEY_MANUFACTURERDATA"))
                    {
                        *_aidl_return = android::String16(gDeviceInfoConfig.manufacturerData.c_str());
                    }
                    else
                    {
                        *_aidl_return = std::nullopt;
                        return android::binder::Status::fromExceptionCode(android::binder::Status::EX_ILLEGAL_ARGUMENT);
                    }
                    return ::android::binder::Status::ok();
                }

                ::android::binder::Status DeviceInfo::setProperty(const ::android::String16 &propertyKey, const ::android::String16 &value, SetPropertyResult *_aidl_return)
                {
                    if (!_aidl_return)
                    {
                        return android::binder::Status::fromExceptionCode(android::binder::Status::EX_ILLEGAL_ARGUMENT);
                    }
                    if (value.size() == 0)
                    {
                        *_aidl_return = SetPropertyResult::ERROR_INVALID_PARAM;
                        return android::binder::Status::fromExceptionCode(android::binder::Status::EX_ILLEGAL_ARGUMENT);
                    }

                    static const std::regex macRegex(
                        R"(^([0-9A-F]{2}:){5}[0-9A-F]{2}$)"); // Regex for MAC address format XX:XX:XX:XX:XX:XX and uppercase letters

                    if (propertyKey == android::String16("KEY_MANUFACTURER"))
                    {
                        gDeviceInfoConfig.manufacturer = android::String8(value).string();
                        *_aidl_return = SetPropertyResult::SUCCESS;
                    }
                    else if (propertyKey == android::String16("KEY_MANUFACTURER_OUI"))
                    {
                        std::string oui = android::String8(value).string();
                        UT_LOG_INFO("OUI: %s", oui.c_str());
                        if (oui.size() != 3) // OUI should be 3 bytes (6 hex digits)
                        {
                            *_aidl_return = SetPropertyResult::ERROR_INVALID_PARAM;
                            UT_LOG_ERROR("Invalid OUI: %s", oui.c_str());
                            return android::binder::Status::fromExceptionCode(android::binder::Status::EX_ILLEGAL_ARGUMENT);
                        }
                        gDeviceInfoConfig.manufacturerOUI = oui;
                        UT_LOG_DEBUG("gDeviceInfoConfig.manufacturerOUI: %s", gDeviceInfoConfig.manufacturerOUI.c_str());
                        *_aidl_return = SetPropertyResult::SUCCESS;
                    }
                    else if (propertyKey == android::String16("KEY_MODELNAME"))
                    {
                        gDeviceInfoConfig.modelName = android::String8(value).string();
                        *_aidl_return = SetPropertyResult::SUCCESS;
                    }
                    else if (propertyKey == android::String16("KEY_PRODUCTCLASS"))
                    {
                        gDeviceInfoConfig.productClass = android::String8(value).string();
                        *_aidl_return = SetPropertyResult::SUCCESS;
                    }
                    else if (propertyKey == android::String16("KEY_SERIALNUMBER"))
                    {
                        gDeviceInfoConfig.serialNumber = android::String8(value).string();
                        *_aidl_return = SetPropertyResult::SUCCESS;
                    }
                    else if (propertyKey == android::String16("KEY_WIFIMAC"))
                    {
                        std::string mac = android::String8(value).string();
                        if (!std::regex_match(mac, macRegex))
                        {
                            *_aidl_return = SetPropertyResult::ERROR_INVALID_PARAM;
                            UT_LOG_ERROR("Invalid Wi-Fi MAC: %s", mac.c_str());
                            return android::binder::Status::fromExceptionCode(android::binder::Status::EX_ILLEGAL_ARGUMENT);
                        }
                        gDeviceInfoConfig.wifiMac = mac;
                        *_aidl_return = SetPropertyResult::SUCCESS;
                    }
                    else if (propertyKey == android::String16("KEY_BLUETOOTHMAC"))
                    {
                        std::string mac = android::String8(value).string();
                        if (!std::regex_match(mac, macRegex))
                        {
                            *_aidl_return = SetPropertyResult::ERROR_INVALID_PARAM;
                            UT_LOG_ERROR("Invalid Bluetooth MAC: %s", mac.c_str());
                            return android::binder::Status::fromExceptionCode(android::binder::Status::EX_ILLEGAL_ARGUMENT);
                        }
                        gDeviceInfoConfig.bluetoothMac = mac;
                        *_aidl_return = SetPropertyResult::SUCCESS;
                    }
                    else if (propertyKey == android::String16("KEY_WPSPIN"))
                    {
                        std::string wpsValue = android::String8(value).string();
                        if (wpsValue.size() != 8 || !std::all_of(wpsValue.begin(), wpsValue.end(), ::isdigit))
                        {
                            *_aidl_return = SetPropertyResult::ERROR_INVALID_PARAM;
                            UT_LOG_ERROR("Invalid WPS PIN: %s", wpsValue.c_str());
                            return android::binder::Status::fromExceptionCode(android::binder::Status::EX_ILLEGAL_ARGUMENT);
                        }
                        gDeviceInfoConfig.wpsPin = wpsValue;
                        *_aidl_return = SetPropertyResult::SUCCESS;
                    }
                    else if (propertyKey == android::String16("KEY_ETHERNETMAC"))
                    {
                        std::string mac = android::String8(value).string();
                        if (!std::regex_match(mac, macRegex))
                        {
                            *_aidl_return = SetPropertyResult::ERROR_INVALID_PARAM;
                            UT_LOG_ERROR("Invalid Ethernet MAC: %s", mac.c_str());
                            return android::binder::Status::fromExceptionCode(android::binder::Status::EX_ILLEGAL_ARGUMENT);
                        }
                        gDeviceInfoConfig.ethernetMac = mac;
                        *_aidl_return = SetPropertyResult::SUCCESS;
                    }
                    else if (propertyKey == android::String16("KEY_RF4CEMAC"))
                    {
                        std::string mac = android::String8(value).string();
                        if (!std::regex_match(mac, macRegex))
                        {
                            *_aidl_return = SetPropertyResult::ERROR_INVALID_PARAM;
                            UT_LOG_ERROR("Invalid RF4CE MAC: %s", mac.c_str());
                            return android::binder::Status::fromExceptionCode(android::binder::Status::EX_ILLEGAL_ARGUMENT);
                        }
                        gDeviceInfoConfig.rf4ceMac = mac;
                        *_aidl_return = SetPropertyResult::SUCCESS;
                    }
                    else if (propertyKey == android::String16("KEY_IMAGENAME"))
                    {
                        gDeviceInfoConfig.imageName = android::String8(value).string();
                        *_aidl_return = SetPropertyResult::SUCCESS;
                    }
                    else if (propertyKey == android::String16("KEY_IMAGETYPE"))
                    {
                        gDeviceInfoConfig.imageType = android::String8(value).string();
                        *_aidl_return = SetPropertyResult::SUCCESS;
                    }
                    else if (propertyKey == android::String16("KEY_COUNTRYCODE"))
                    {
                        gDeviceInfoConfig.countryCode = android::String8(value).string();
                        *_aidl_return = SetPropertyResult::SUCCESS;
                    }
                    else if (propertyKey == android::String16("KEY_LANGUAGECODE"))
                    {
                        gDeviceInfoConfig.languageCode = android::String8(value).string();
                        *_aidl_return = SetPropertyResult::SUCCESS;
                    }
                    else if (propertyKey == android::String16("KEY_MANUFACTURERDATA"))
                    {
                        gDeviceInfoConfig.manufacturerData = android::String8(value).string();
                        *_aidl_return = SetPropertyResult::SUCCESS;
                    }
                    else
                    {
                        *_aidl_return = SetPropertyResult::ERROR_INVALID_PARAM;
                        return android::binder::Status::fromExceptionCode(android::binder::Status::EX_ILLEGAL_ARGUMENT);
                    }
                    return ::android::binder::Status::ok();
                }

                void DeviceInfo::binderDied(const ::android::wp<::android::IBinder> &who)
                {
                    // Handle binder death if necessary
                }

            } // namespace deviceinfo
        } // namespace hal
    } // namespace rdk
} // namespace com
