# DeviceInfo High Level Test Specification Document

## Table of Contents

- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [Introduction](#introduction)
- [Module Description](#module-description)
- [Test Specification](#test-specification)

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


## Test Specification

|Test|Description|HAL APIs|
|----|-----------|--------|
|Check Supported Properties	|Ensure the HAL advertises all expected keys for the platform.|	getCapabilities()|
| Verify HAL_VERSION | Verify version of HAL is returned correctly. Valid SEMANTICVERSION format, e.g., '1.0.0' |getCapabilities(),getProperty("HAL_VERSION") |
| Verify MANUFACTURER | Verify manufacturer name is returned correctly. Valid ASCII string, e.g., 'RDK Inc.' |getCapabilities(),getProperty("MANUFACTURER") |
| Verify MANUFACTURER_OUI | Verify manufacturer IEEE OUI is returned in correct hex format. Hex string of 3 bytes, e.g., '00A1B2' | getCapabilities(),getProperty("MANUFACTURER_OUI") |
| Verify MODELNAME | Verify model name is returned for UI and logging.Valid ASCII string, e.g., 'RDK-VirtualBox' | getCapabilities(), getProperty("MODELNAME") |
| Verify PRODUCTCLASS | Verify product class string is returned. Valid ASCII string, e.g., 'SetTopBox'| getCapabilities(), getProperty("PRODUCTCLASS") |
| Verify SERIALNUMBER | Verify serial number is returned for device identification. Valid ASCII string, e.g., '1234567890' | getCapabilities(),getProperty("SERIALNUMBER") |
| Verify WIFIMAC | Verify Wi-Fi MAC address format. MAC format 'XX:XX:XX:XX:XX:XX', uppercase hex| getCapabilities(), getProperty("WIFIMAC") |
| Verify BLUETOOTHMAC | Verify Bluetooth MAC address format.MAC format 'XX:XX:XX:XX:XX:XX', uppercase hex | getCapabilities(),getProperty("BLUETOOTHMAC") |
| Verify WPSPIN | Verify WPS PIN is returned correctly. 8-digit ASCII string, e.g., '12345678'| getCapabilities(),getProperty("WPSPIN") |
| Verify ETHERNETMAC | Verify Ethernet MAC address format.MAC format 'XX:XX:XX:XX:XX:XX', uppercase hex  | getCapabilities(), getProperty("ETHERNETMAC") |
| Verify RF4CEMAC | Verify RF4CE MAC address format.MAC format 'XX:XX:XX:XX:XX:XX', uppercase hex | getCapabilities(), getProperty("RF4CEMAC") |
| Verify COUNTRYCODE | Verify country code is returned.Valid ASCII string, e.g., 'US' | getCapabilities(), getProperty("COUNTRYCODE") |
| Verify LANGUAGECODE | Verify language code is returned.Valid ASCII string, e.g., 'en' | getCapabilities(), getProperty("LANGUAGECODE") |
| Verify DEVICE_TYPE | Verify type of device is returned. Valid string, e.g., 'STB' | getCapabilities(), getProperty("DEVICE_TYPE") |
| Verify CHIPSET_ID | Verify SOC id is returned. Valid string, e.g., 'SAMPLE_CHIPSET_ID' | getCapabilities(), getProperty("CHIPSET_ID") |
