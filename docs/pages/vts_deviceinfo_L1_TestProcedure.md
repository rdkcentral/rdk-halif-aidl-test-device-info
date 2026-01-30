# Deviceinfo L1 Test Procedure

## Table of Contents
- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [Build the VTS](#build-the-vts)
- [Run L1 Tests Without Python](#run-l1-tests-without-python)
- [Run Tests in Python Environment](#run-tests-in-python-environment)
  - [Update Configuration Files](#update-configuration-files)
  - [Install the Python Packages](#install-the-python-packages)
  - [Run the Tests](#run-test-cases)
- [Notes](#note)

## Acronyms, Terms and Abbreviations

- `HAL`    - Hardware Abstraction Layer
- `VTS`    - Vendor Test Suite
- `L1`     - Level 1 Testing
- `DUT`    - Device Under Test
- `RAFT`   - Rapid Automation Framework for Testing
- `YAML`   - YAML Ain't Markup Language
- `AIDL`   - Android Interface Definition Language

## Build the VTS

### 1. Build linux binder

The test suite depends on the Linux binder with `AIDL` support. Follow these steps to build it:

For detail build instruction, please refer to [Linux Binder](https://github.com/rdkcentral/linux_binder_idl/tree/main)

Here are the simplest steps outlined:

```bash
git clone -b develop 'https://github.com/rdkcentral/linux_binder_idl.git'

cd linux_binder_idl

sc docker run rdk-kirkstone /bin/bash //preferred

./build-linux-binder-aidl.sh 64
```

### 2. Build this test

Clone and build the test suite:

```bash
git clone git@github.com:rdkcentral/rdk-halif-aidl-test-device-info.git
```

```bash
cd rdk-halif-aidl-test-device-info
```

Set below environment variable:

- AIDL_BIN: Path to the `AIDL` compiler (e.g., /path/to/linux_binder_idl/out/aidl).

- LINUX_BINDER_OUT_DIR: Path to the Linux binder output directory (e.g., /path/to/linux_binder_idl/local).

- UT_CORE_VERSION: Specific version of the UT-Core framework (e.g., 4.7.0). Defaults to the latest tagged version.

- RDK_HALIF_AIDL_VERSION: Specific version of the AIDL HAL Specification (e.g, 0.7.1). Defaults to the latest HEAD.

Example:

```bash
export UT_CORE_VERSION=5.0.0
export RDK_HALIF_AIDL_VERSION=0.13.1
export AIDL_BIN=/path/linux_binder_idl/out/aidl
export LINUX_BINDER_OUT_DIR=/path//linux_binder_idl/local/
```

By default, UT logs are disabled. To enable them, Set below environment variable

```bash
export ENABLE_UT_INFO_LOGGING=1
```

Run the build script:

```bash
./build.sh Target=linux
```

The build.sh script:

- Clones the `rdk-halif-aidl` repository and UT-Core framework.

- Compiles the test suite.

- Generates binaries in the `build/bin` directory.

- Also generates `vts-deviceinfo.tar.gz` tar ball in `build/bin` folder

## Run L1 tests without python

- Transfer to Target Device:

Copy the tarball to the target device (e.g., using scp):

```bash
scp -p <port> vts-deviceinfo.tar.gz root@target-device:/home/root/

```

- Extract on Target Device:

Log into the target device and extract the tarball:

```bash
ssh root@target-device
cd /home/root
mkdir deviceinfo
tar -zxf vts-deviceinfo.tar.gz -C deviceinfo
cd deviceinfo
```

- Run the VTS Test on Target Device

Run below command to execute the VTS Test:

```bash
./run.sh -p profiles/hfp-deviceinfo-vcomponent.yaml
```

## Run Tests in Python Environment

### Update Configuration Files

#### Rack Configuration File

Example Rack configuration File: [vts_rack_configuration.yml](../../host/configs/vts_rack_configuration.yml)

For more details on rack configuration refer [RAFT](https://github.com/rdkcentral/python_raft/blob/1.7.1/README.md) and [example_rack_config.yml](https://github.com/rdkcentral/python_raft/blob/1.7.1/examples/configs/example_rack_config.yml)

In this file, update the configuration to define the console sessions for the `DUT` and the outbound settings:

|Console Session|Description|
|---------------|-----------|
|default|This session is used for basic operations, such as verifying the device status and retrieving the MAC address|
|ssh_hal_test|Executes the `HAL` binary for the test case|
|ssh_hal_test_1|Console to control device|

```yaml
rackConfig:
    rack1:
        name: "rack1"
        description: "example config at my desk"
        slot1:
            name: "slot1"
            devices:
                - dut:
                    ip: ""  # IP Address of the ADA Hub
                    description: "PC"
                    platform: "vDevice"
                    consoles:
                        - default:
                            type: "ssh"
                            port: 5522
                            username: "root"
                            ip: "" #IP address
                            password: ""
                            prompt: "~#" # Prompt string on console
                        - ssh_hal_test:
                            type: "ssh"
                            port: 5522
                            username: ""
                            ip: "" #IP address
                            password: ""
                            prompt: "~#" # Prompt string on console
                        - ssh_hal_test_1:
                            type: "ssh"
                            port: 5522
                            username: ""
                            ip: "" #IP address
                            password: ""
                            prompt: "~#" # Prompt string on console
                    outbound:
                        download_url: "tftp://tftp-server.com/rack1/slot1/"    # download location for the CPE device
                        upload_url: "sftp://server-address/home/workspace/tftp/rack1/slot1/" # upload location
                        upload_url_base_dir: "sftp://server-address/home/workspace/tftp/rack1/slot1" # alternative upload location
                        httpProxy:    # Local Proxy if required
                        workspaceDirectory: './logs/workspace'   # Local working directory
```

#### Device Configuration File

Example Device configuration File: [vts_device_configuration.yml](../../host/configs/vts_device_configuration.yml)

For more details refer [RAFT](https://github.com/rdkcentral/python_raft/blob/1.7.0/README.md) and [example_device_config.yml](https://github.com/rdkcentral/python_raft/blob/1.7.0/examples/configs/example_device_config.yml)

Ensure the `platform` should match with the `DUT` platform in [Rack Configuration](#rack-configuration-file)

```yaml
deviceConfig:
    cpe1:
        platform:   "vDevice"
        model:      "VTV"
        soc_vendor: "appleM3"
        target_directory: "/tmp/"
        deviceinfo_process_name: "Vendor-DeviceInfo"
        prompt: "~#" # Prompt string on console
        wait_time: 20 #Configurable timeout value to limit the total duration of individual tests
        test:
            profile: "../../profiles/hfp-deviceinfo-vcomponent.yaml" #HFP profile used to meet platform requirements
            controller_port: 8075 #Port where the ut-controller is listening
```

### Install the Python Packages

[host](../../host/) folder contains the script files to install required packages and set up the Python environment.

- Run install.sh once to create the virtual environment
- source activate_venv.sh
- Run install.sh again to install dependencies inside the environment.

Run the following commands:

```bash
./install.sh
source activate_venv.sh
./install.sh
```

For more details refer [Python Set up](https://github.com/rdkcentral/ut-raft/wiki/Guide-for-Setting-up-the-Python-RAFT-Testing-Suite) and [Raft Setup](https://github.com/rdkcentral/python_raft/?tab=readme-ov-file#installation)

### Run Test Cases

#### L1

Once the environment is set up, execute the test cases with the following command:

```bash
python vts_deviceinfo_Runall.py --deviceConfig ../configs/vts_device_configuration.yml --config ../configs/vts_rack_configuration.yml
```

## Note

### Test Setup on vDevice

To validate automation on vDevice, create a password for the root user using the following command:

```bash
passwd root
```

Then, update the same password in the `vts_rack_configuration.yaml` file.

Currently, the Python `paramiko` library does not support empty passwords on vDevice, so setting a password is necessary.

### Run on Windows Environment

To run the Python environment tests in a Windows environment, follow these additional steps after checking out the repository and compiling the code:

1. Install the python environment and update the rack configuration files as in the Linux environment.

2. Move the entire project folder (including `host`) to the Windows machine.

3. Open the file located at `framework/plugins/ut_raft/interactive_shell.py`.

   - Comment out or remove the following import lines to avoid errors on Windows:
     ```python
     import pty
     import fcntl
     ```

4. After these changes, run the test cases using Python on the Windows system.
