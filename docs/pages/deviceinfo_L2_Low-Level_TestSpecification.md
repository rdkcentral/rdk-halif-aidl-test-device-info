# Deviceinfo L2 Low Level Test Specification and Procedure Documentation

## Table of Contents

- [Overview](#overview)
- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [Definitions](#definitions)
- [References](#references)
- [Level 2 Test Procedure](#level-2-test-procedure)

## Overview

This document describes the level 2 testing suite for the Deviceinfo module.

### Acronyms, Terms and Abbreviations

- `HAL` \- Hardware Abstraction Layer, may include some common components
- `UT`  \- Unit Test(s)
- `OEM`  \- Original Equipment Manufacture
- `SoC`  \- System on a Chip

### Definitions

- `ut-core` \- Common Testing Framework <https://github.com/rdkcentral/ut-core>, which wraps a open-source framework that can be expanded to the requirements for future framework.

### References

- `High Level Test Specification` - [deviceinfo_High-Level_TestSpecification.md](deviceinfo_High-Level_TestSpecification.md)

## Level 2 Test Procedure

The following functions are planned as part of L2 testing.

### Test 1

| Title | Details |
| -- | -- |
| Function Name | `test_getCapabilities` |
| Description | Read supported capabilities using getCapabilities function. |
| Test Group | 02 |
| Test Case ID | 001 |
| Priority | High |

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

**Test Procedure :**

| Step | Action | Input / Test Data | Expected Result | Notes |
|------|---------|-------------------|-----------------|-------|
| 1 | Obtain `IDeviceInfo` handle | N/A | Valid handle acquired | Ensure `gDEVICEINFOHandle`/HAL is initialized |
| 2 | Call `getCapabilities()` | N/A | Capabilities structure is populated | - |
| 3 | Verify `supportedProperties` count against profile | HAL data | Count matches `UT_KVP_PROFILE_GET_LIST_COUNT("IDeviceInfo.supportedProperties")` from HFP file | - |
| 4 | Validate each property against profile | HAL data | Each property exists in HFP list and matches expected value | Use `UT_KVP_PROFILE_GET_STRING` for comparison.<br><br>**Properties to verify:**<br>- `KEY_MANUFACTURER`<br>- `KEY_MANUFACTURER_OUI`<br>- `KEY_MODELNAME`<br>- `KEY_PRODUCTCLASS`<br>- `KEY_SERIALNUMBER`<br>- `KEY_WIFIMAC`<br>- `KEY_BLUETOOTHMAC`<br>- `KEY_WPSPIN`<br>- `KEY_ETHERNETMAC`<br>- `KEY_RF4CEMAC`<br>- `KEY_IMAGENAME`<br>- `KEY_IMAGETYPE`<br>- `KEY_COUNTRYCODE`<br>- `KEY_LANGUAGECODE`<br>- `KEY_MANUFACTURERDATA` |

### Test 2

| Title | Details |
| -- | -- |
| Function Name | `test_getHALVersion` |
| Description | Read HAL version using getHALVersion function.|
| Test Group | 02 |
| Test Case ID | 002 |
| Priority | High |

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

**Test Procedure :**

| Variation / Steps | Description | Test Data | Expected Result | Notes |
|-------------------|-------------|-----------|----------------|-------|
| 1 | Obtain IDeviceInfo handle | N/A | Valid handle acquired | Ensure `gDEVICEINFOHandle`/HAL is initialized |
| 2 | Call `getHALVersion()` | N/A | Function executes without error |  |
| 3 | Verify major version | Read halVersion.major | Matches `UT_KVP_PROFILE_GET_UINT8("IDeviceInfo.HALVersion.major")` |  |
| 4 | Verify minor version | Read halVersion.minor | Matches `UT_KVP_PROFILE_GET_UINT8("IDeviceInfo.HALVersion.minor")` |  |
| 5 | Verify doc version | Read halVersion.doc | Matches `UT_KVP_PROFILE_GET_UINT8("IDeviceInfo.HALVersion.doc")` |  |

### Test 3

| Title | Details |
| -- | -- |
| Function Name | `test_verifyCapabilities` |
| Description | Read supported Deviceinfos using getCapabilities function. /n Loop through supported capabilities /n set and get each of the capabilities supported by platform |
| Test Group | 02 |
| Test Case ID | 003 |
| Priority | High |

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

**Test Procedure :**

| Step | Action | Input / Test Data | Expected Result | Notes |
|------|--------|------------------|-----------------|-------|
| 1 | Obtain IDeviceInfo handle | N/A | Valid handle acquired | Precondition for all steps |
| 2 | Retrieve supported properties via `getCapabilities()` | N/A | List of supported properties | Used for iteration |
| 3 | For each property, call `setProperty()` with valid test value | `KEY_MANUFACTURER_OUI: "ABCDEF"` (hex string 3 bytes) <br>`KEY_WPSPIN: "12345670"` (8-digit PIN) <br>`KEY_WIFIMAC / KEY_BLUETOOTHMAC / KEY_ETHERNETMAC / KEY_RF4CEMAC: "00:11:22:33:44:55"` (MAC address) <br>`KEY_MANUFACTURER / KEY_MODELNAME / KEY_PRODUCTCLASS / KEY_SERIALNUMBER / KEY_IMAGENAME / KEY_IMAGETYPE / KEY_COUNTRYCODE / KEY_LANGUAGECODE / KEY_MANUFACTURERDATA: "TestValue"`| SetPropertyResult::SUCCESS | Value depends on property type |
 | 4 | For each property, call `getProperty()` | Property name | Value matches set value | Verifies correct storage/retrieval |
 | 5 | Log results and assert correctness | N/A | All assertions pass | |