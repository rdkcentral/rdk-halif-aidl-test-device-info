#!/usr/bin/env python3
#** *****************************************************************************
# *
# * If not stated otherwise in this file or this component's LICENSE file the
# * following copyright and licenses apply:
# *
# * Copyright 2025 RDK Management
# *
# * Licensed under the Apache License, Version 2.0 (the "License");
# * you may not use this file except in compliance with the License.
# * You may obtain a copy of the License at
# *
# *
# http://www.apache.org/licenses/LICENSE-2.0
# *
# * Unless required by applicable law or agreed to in writing, software
# * distributed under the License is distributed on an "AS IS" BASIS,
# * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# * See the License for the specific language governing permissions and
# * limitations under the License.
# *
#* ******************************************************************************

import os
import sys
import tarfile
import time

dir_path = os.path.dirname(os.path.realpath(__file__))
sys.path.append(os.path.join(dir_path, "../"))

from raft.framework.plugins.ut_raft.configRead import ConfigRead
from raft.framework.plugins.ut_raft import utHelperClass
from raft.framework.core.logModule import logModule
from raft.framework.plugins.ut_raft.utSuiteNavigator import UTSuiteNavigatorClass
from raft.framework.plugins.ut_raft.utBaseUtils import utBaseUtils
from raft.framework.plugins.ut_raft.utUserResponse import utUserResponse

DEVICEINFO_TEST_MENU_CONFIGURATION_FILE = os.path.join(dir_path, "vts_deviceinfo_testMenuConfiguration.yaml")
DEVICEINFO_TESTCASES_CONFIGURATION_FILE = os.path.join(os.path.join(dir_path, "../configs"), "vts_deviceinfo_testcase_configuration.yaml")
DEVICEINFO_L3_TEST_CONFIG_FILE = os.path.join(os.path.join(dir_path, "../../test_configuration"), "vts_l3_deviceinfo.yaml")

class deviceinfoHelperClass(utHelperClass):
    """
    Helper class for Device Information HAL testing.
    This class extends utHelperClass to provide specific functionality for testing
    the Device Information HAL interface. It handles test initialization, session
    management, artifact deployment, and test cleanup operations.
    Attributes:
        moduleName (str): Name of the module being tested ("Deviceinfo")
        profile_moduleName (str): Name of the profile module ("IDeviceinfo")
        log (logModule): Logger instance for test logging
        deviceTestSetup (dict): Device test configuration
        targetWorkspace (str): Target directory path for test artifacts
        moduleHFPFile (str): Path to the HAL Function Profile file
        waitTime (int): Wait time for test operations
        device_type (str): Type of device under test
        platform (str): Platform identifier
        l3TestConfigFile (str): L3 test configuration file path
        l3TestConfigFolder (str): L3 test configuration folder path
        testMenuConfiguration (ConfigRead): Test menu configuration object
        testCaseConfiguration (ConfigRead): Test case configuration object
        hal_session: HAL test console session
        hal_session_1: Secondary HAL test console session
        utMenu (UTSuiteNavigatorClass): UT menu navigation utility
        utilities (utBaseUtils): Base utility functions
        testUserResponse (utUserResponse): User response handler
    Methods:
        __init__(testName, qcId, log): Initializes the deviceinfo helper class
        testEndFunction(powerOff): Cleans up and ends the test case
    """
    def __init__(self, testName:str, qcId:str, log:logModule=None ):
        """
        Initializes the test class
        """
        self.moduleName = "Deviceinfo"
        self.profile_moduleName = "IDeviceinfo"
        super().__init__(testName, qcId, log)

        self.log = log
        if log is None:
            self.log = logModule(self.__class__.__name__)
            self.log.setLevel(self.log.INFO)

        # Parse device configuration
        self.deviceTestSetup = self.cpe.get("test")
        self.targetWorkspace = os.path.join(self.cpe.get("target_directory"), self.moduleName)
        self.moduleHFPFile = os.path.join(dir_path, self.deviceTestSetup.get("profile"))
        profileOnTarget = os.path.join(self.targetWorkspace, "profiles")
        profileOnTarget = os.path.join(profileOnTarget, os.path.basename(self.moduleHFPFile))
        profileOnTarget = profileOnTarget.replace("\\", "/")

        self.l3TestConfigFolder = os.path.join(self.targetWorkspace, "test_configuration")
        self.l3TestConfigFolder = self.l3TestConfigFolder.replace("\\", "/")

        self.waitTime = self.cpe.get("wait_time")
        self.device_type = self.cpe.get("device_type")
        self.platform = self.cpe.get("platform")

        # Load test menu and test case configuration files
        self.l3TestConfigFile = DEVICEINFO_L3_TEST_CONFIG_FILE
        self.testMenuConfiguration = ConfigRead(DEVICEINFO_TEST_MENU_CONFIGURATION_FILE, self.moduleName)
        self.testCaseConfiguration = ConfigRead(DEVICEINFO_TESTCASES_CONFIGURATION_FILE, self.moduleName)
        self.testMenuConfiguration.test.execute = self.testMenuConfiguration.test.execute + f" -p {profileOnTarget}"

        # Establish HAL session
        self.hal_session = self.dut.getConsoleSession("ssh_hal_test")
        self.hal_session_1 = self.dut.getConsoleSession("ssh_hal_test_1")

        # Initialize UT menu navigator and utilities
        self.utMenu = UTSuiteNavigatorClass(self.testMenuConfiguration, None, self.hal_session)
        self.utilities = utBaseUtils()

        # Create user response Class
        self.testUserResponse = utUserResponse()

        # Copy required artifacts to target device
        self.utilities.change_directory(self.hal_session, self.targetWorkspace)
        for artifact in self.testMenuConfiguration.test.artifacts:
            filesPath = os.path.join(dir_path, artifact)
            self.utilities.sftpCopy(self.hal_session, filesPath, self.targetWorkspace)

            if tarfile.is_tarfile(filesPath):
                target_tarfile = os.path.join(self.targetWorkspace, os.path.basename(artifact))
                target_tarfile = target_tarfile.replace("\\", "/")
                self.utilities.untar(self.hal_session, target_tarfile, self.targetWorkspace)

        self.utilities.change_directory(self.hal_session_1, self.targetWorkspace)
        self.hal_session_1.write(f"./{self.cpe.get('deviceinfo_process_name')} &")
        time.sleep(2)

    def testEndFunction(self, powerOff=True):
        """
        Ends the test case.
        Args:
            powerOff (bool): Whether to power off the device
        """
        super().testEndFunction(powerOff)
