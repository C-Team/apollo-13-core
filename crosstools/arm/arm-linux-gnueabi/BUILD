#
# Copyright 2015 Google Inc. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
package(default_visibility = ["//visibility:public"])

filegroup(
    name = "toolchain",
    srcs = [
        ":cc-compiler-armeabi",
        ":empty",
        "//arm-linux-gnueabi/libc:everything",
    ],
)

cc_library(
    name = "malloc",
    srcs = [],
)

filegroup(
    name = "gcc-arm-toolchain",
    srcs = glob([
        "bin/**",
    ]),
    output_licenses = ["unencumbered"],
)

filegroup(
    name = "armeabi-files",
    srcs = [
        ":gcc-arm-toolchain",
        "//arm-linux-gnueabi/libc:everything",
    ],
)

cc_toolchain(
    name = "cc-compiler-armeabi",
    all_files = ":armeabi-files",
    compiler_files = ":gcc-arm-toolchain",
    cpu = "armeabi-v7a",
    dwp_files = ":gcc-arm-toolchain",
    dynamic_runtime_libs = [":gcc-arm-toolchain"],
    linker_files = ":gcc-arm-toolchain",
    objcopy_files = ":gcc-arm-toolchain",
    static_runtime_libs = [":gcc-arm-toolchain"],
    strip_files = ":gcc-arm-toolchain",
    supports_param_files = 0,
)
