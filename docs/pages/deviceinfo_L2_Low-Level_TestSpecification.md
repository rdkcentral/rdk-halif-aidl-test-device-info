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
| Function Name | `test_l2_Deviceinfo_getCapabilities` |
| Description | Read supported capabilities using getCapabilities function. |
| Test Group | Module : 02 |
| Test Case ID | 001 |
| Priority | High |

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

**Test Procedure :**

| Variation / Steps     | Description                          | Test Data                                  | Expected Result                               | Notes                          |
|-----------------------|--------------------------------------|--------------------------------------------|-----------------------------------------------|--------------------------------|
| 1. Initialization     | Obtain IDeviceInfo handle            | gDEVICEINFOHandle                           | Handle is not nullptr                          | Ensure HAL is initialized      |
| 2. Get Capabilities   | Call getCapabilities on IDeviceInfo  | deviceInfo->getCapabilities(caps)           | Function returns successfully                  | -                              |
| 3. Validate Properties| Check supportedProperties size       | caps.supportedProperties.size()             | Matches UT_KVP_PROFILE_GET_LIST_COUNT          | Validates property count       |

### Test 2

| Title | Details |
| -- | -- |
| Function Name | `test_l2_Deviceinfo_getHALVersion` |
| Description | Read HAL version using getHALVersion function.|
| Test Group | Module : 02 |
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
| 1 | Obtain IDeviceInfo handle | N/A | Valid handle acquired | Ensure gDEVICEINFOHandle is initialized |
| 2 | Call getHALVersion() | N/A | Function executes without error |  |
| 3 | Verify major version | Read halVersion.major | Matches UT_KVP_PROFILE_GET_UINT8("IDeviceInfo.halVersion.major") |  |
| 4 | Verify minor version | Read halVersion.minor | Matches UT_KVP_PROFILE_GET_UINT8("IDeviceInfo.halVersion.minor") |  |
| 5 | Verify doc version | Read halVersion.doc | Matches UT_KVP_PROFILE_GET_UINT8("IDeviceInfo.halVersion.doc") |  |

### Test 3

| Title | Details |
| -- | -- |
| Function Name | `test_l2_Deviceinfo_verifyCapabilities` |
| Description | Read supported Deviceinfos using getCapabilities function. /n Loop through supported capabilities /n set and get each of the capabilities supported by platform |
| Test Group | Module : 02 |
| Test Case ID | 003 |
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
| 1 | Obtain IDeviceInfo handle | N/A | Valid handle acquired | Ensure gDEVICEINFOHandle is initialized |
| 2 | Call getCapabilities() to get supported properties | N/A | Function executes without error |  |
| 3 | For each supported property, perform the following: | N/A | N/A |  |
| 3.1 | Call setProperty() with a valid value | Property key and valid value | Function executes without error | Valid values depend on property type |
| 3.2 | Call getProperty() to retrieve the value | Property key | Retrieved value matches set value |  | |
| 4 | Log results and any discrepancies | N/A | All properties set and retrieved successfully | |  |