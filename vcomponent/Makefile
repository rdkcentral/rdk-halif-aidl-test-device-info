#* ******************************************************************************
#*  If not stated otherwise in this file or this component's LICENSE
#*  file the following copyright and licenses apply:
#*
#*  Copyright 2025 RDK Management
#*
#*  Licensed under the Apache License, Version 2.0 (the License);
#*  you may not use this file except in compliance with the License.
#*  You may obtain a copy of the License at
#*
#*  http://www.apache.org/licenses/LICENSE-2.0
#*
#*  Unless required by applicable law or agreed to in writing, software
#*  distributed under the License is distributed on an AS IS BASIS,
#*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#*  See the License for the specific language governing permissions and
#*  limitations under the License.
#*
#* ******************************************************************************

.PHONY: all

AIDL_LIB_NAME := aidl_client
UT_LIB_NAME := ut_control
VCOMPONENT_DEVICEINFO := VComponentDeviceinfoService

BUILD_DIR ?= $(CURDIR)/../build
AIDL_GEN_DIR ?= $(BUILD_DIR)/current
UT_CORE_DIR ?= $(CURDIR)/../ut_core
GTEST_INC_DIR ?= $(UT_CORE_DIR)/framework/gtest/linux/googletest-1.15.2/googletest/include

VCOMPONENT_DEVICEINFO_DIR ?= $(CURDIR)/src

VCOMPONENT_DEVICEINFO_SRC := $(VCOMPONENT_DEVICEINFO_DIR)/vcomponent_Deviceinfo_main.cpp
VCOMPONENT_DEVICEINFO_SRC += $(VCOMPONENT_DEVICEINFO_DIR)/vcomponent_Deviceinfo.cpp
VCOMPONENT_DEVICEINFO_SRC += $(VCOMPONENT_DEVICEINFO_DIR)/vcomponent_Deviceinfo_init.cpp
VCOMPONENT_DEVICEINFO_SRC += $(VCOMPONENT_DEVICEINFO_DIR)/vcomponent_Deviceinfo_parse_config.cpp

VCOMPONENT_DEVICEINFO_INC_FLAGS := -I$(AIDL_GEN_DIR)/h
VCOMPONENT_DEVICEINFO_INC_FLAGS += -I$(BUILD_DIR)/usr/include
VCOMPONENT_DEVICEINFO_INC_FLAGS += -I$(UT_CORE_DIR)/include
VCOMPONENT_DEVICEINFO_INC_FLAGS += -I$(UT_CORE_DIR)/include -I$(UT_CORE_DIR)/framework/ut-control/include -I$(GTEST_INC_DIR)

VCOMPONENT_DEVICEINFO_LDFLAGS := -L. -L$(BUILD_DIR)/usr/lib -L$(BUILD_DIR)/bin
VCOMPONENT_DEVICEINFO_LD_LIBS += -lbinder -lutils -lpthread -l$(AIDL_LIB_NAME) -l$(UT_LIB_NAME)
VCOMPONENT_DEVICEINFO_LDFLAGS += -Wl,-rpath-link=$(BUILD_DIR)/usr/lib -Wl,-rpath,.

VCOMPONENT_DEVICEINFO_CFLAGS := -Wall -Wextra -std=c++17 -ggdb

VCOMPONENT_DEVICEINFO := $(BUILD_DIR)/bin/$(VCOMPONENT_DEVICEINFO)

all: $(VCOMPONENT_DEVICEINFO)

$(VCOMPONENT_DEVICEINFO): $(VCOMPONENT_DEVICEINFO_SRC:%.cpp=%.o)
	g++ $(VCOMPONENT_DEVICEINFO_LDFLAGS) \
		$(VCOMPONENT_DEVICEINFO_SRC:%.cpp=%.o) -o $@ \
		$(VCOMPONENT_DEVICEINFO_LD_LIBS)

%.o: %.cpp
	g++ $(VCOMPONENT_DEVICEINFO_CFLAGS) $(VCOMPONENT_DEVICEINFO_INC_FLAGS) -fPIC -c $< -o $@
