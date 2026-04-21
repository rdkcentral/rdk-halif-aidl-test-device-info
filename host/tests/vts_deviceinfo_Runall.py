#!/usr/bin/env python3
# If not stated otherwise in this file or this component's LICENSE
# file the following copyright and licenses apply:
#
# Copyright 2026 RDK Management
#
# Licensed under the Apache License, Version 2.0 (the License);
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an AS IS BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import os
import sys
import importlib

dir_path = os.path.dirname(os.path.realpath(__file__))
sys.path.append(os.path.join(dir_path, "../"))

from raft.framework.plugins.ut_raft.configRead import ConfigRead
from raft.framework.core.logModule import logModule

def Run_L1():
    SummerLogL1 = logModule("vts_deviceinfo_L1", level=logModule.INFO)
    test_module_name = "vts_deviceinfo_L1_tests"
    try:
        module = importlib.import_module(test_module_name)
        test_class = getattr(module, test_module_name)
        test_instance = test_class(SummerLogL1)
        test_instance.run(False)
    except (ImportError, AttributeError) as e:
        SummerLogL1.error(f"Failed to import {test_module_name}: {e}")

if __name__ == '__main__':
    Run_L1()