# DeviceInfo High Level Test Specification Document

## Table of Contents

- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [Introduction](#introduction)
- [Module Description](#module-description)
- [L2 Test Specification](#l2-test-specification)
- [L3 Test Specification](#l3-test-specification)

## Acronyms, Terms and Abbreviations

- `HAL`    - Hardware Abstraction Layer
- `API`    - Application Programming Interface
- `AIDL`   - Android Interface Definition Language
- `L2`     - Level 2 Testing
- `L3`     - Level 3 Testing
- `NA`     - Not Applicable
- `WPS`    - Wi-Fi Protected Setup

## Introduction

This document provides an overview of the testing requirements for the Deviceinfo module. It outlines the scope of testing, objectives, testing levels and approaches, specific test requirements.

- DeviceInfo Interface Definitions - [DeviceInfo HAL](https://github.com/rdkcentral/rdk-halif-aidl/tree/main/deviceinfo/current/com/rdk/hal/deviceinfo)
- DeviceInfo Feature Profile - [HFP-Deviceinfo](https://github.com/rdkcentral/rdk-halif-aidl/blob/main/deviceinfo/current/hfp-deviceinfo.yaml)

## Module Description

The DeviceInfo HAL provides a standardized interface for accessing and managing device-specific information on RDK platforms. It is designed to support system-level services, diagnostics, UI components, and vendor-specific features by exposing key device properties through a stable AIDL interface.


## L2 Test Specification

|Test|Description|HAL APIs|
|----|-----------|--------|
|Check Supported Properties	|Ensure the HAL advertises all expected keys for the platform.|	getCapabilities()|
|Validate HAL Version	|Confirm the HAL version matches the expected spec for compatibility.	|getHALVersion()|
| Verify KEY_MANUFACTURER | Verify manufacturer name is returned correctly. Valid ASCII string, e.g., 'RDK Inc.' |getCapabilities(),getProperty("KEY_MANUFACTURER") |
| Verify KEY_MANUFACTURER_OUI | Verify manufacturer IEEE OUI is returned in correct hex format. Hex string of 3 bytes, e.g., '00A1B2' | getCapabilities(),getProperty("KEY_MANUFACTURER_OUI") |
| Verify KEY_MODELNAME | Verify model name is returned for UI and logging.Valid ASCII string, e.g., 'RDK-VirtualBox' | getCapabilities(), getProperty("KEY_MODELNAME") |
| Verify KEY_PRODUCTCLASS | Verify product class string is returned. Valid ASCII string, e.g., 'SetTopBox'| getCapabilities(), getProperty("KEY_PRODUCTCLASS") |
| Verify KEY_SERIALNUMBER | Verify serial number is returned for device identification. Valid ASCII string, e.g., '1234567890' | getCapabilities(),getProperty("KEY_SERIALNUMBER") |
| Verify KEY_WIFIMAC | Verify Wi-Fi MAC address format. MAC format 'XX:XX:XX:XX:XX:XX', uppercase hex| getCapabilities(), getProperty("KEY_WIFIMAC") |
| Verify KEY_BLUETOOTHMAC | Verify Bluetooth MAC address format.MAC format 'XX:XX:XX:XX:XX:XX', uppercase hex | getCapabilities(),getProperty("KEY_BLUETOOTHMAC") |
| Verify KEY_WPSPIN | Verify WPS PIN is returned correctly. 8-digit ASCII string, e.g., '12345678'| getCapabilities(),getProperty("KEY_WPSPIN") |
| Verify KEY_ETHERNETMAC | Verify Ethernet MAC address format.MAC format 'XX:XX:XX:XX:XX:XX', uppercase hex  | getCapabilities(), getProperty("KEY_ETHERNETMAC") |
| Verify KEY_RF4CEMAC | Verify RF4CE MAC address format.MAC format 'XX:XX:XX:XX:XX:XX', uppercase hex | getCapabilities(), getProperty("KEY_RF4CEMAC") |
| Verify KEY_IMAGENAME | Verify firmware image name is returned.Valid ASCII string, e.g., 'rdk-image'  | getCapabilities(), getProperty("KEY_IMAGENAME") |
| Verify KEY_IMAGETYPE | Verify firmware image type is returned. Valid ASCII string, e.g., 'release'| getCapabilities(), "release" ), getProperty("KEY_IMAGETYPE") |
| Verify KEY_COUNTRYCODE | Verify country code is returned.Valid ASCII string, e.g., 'US' | getCapabilities(), getProperty("KEY_COUNTRYCODE") |
| Verify KEY_LANGUAGECODE | Verify language code is returned.Valid ASCII string, e.g., 'en' | getCapabilities(), getProperty("KEY_LANGUAGECODE") |
| Verify KEY_MANUFACTURERDATA | Verify OEM-specific manufacturer data is returned. Valid ASCII string, e.g., 'OEM123' | getCapabilities(), getProperty("KEY_MANUFACTURERDATA") |