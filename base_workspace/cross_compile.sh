#! /bin/sh

bazel build --dynamic_mode=off \
    --package_path=%workspace%:$HOME/crosstools/arm:$HOME/bazel-src \
    --crosstool_top=//arm-linux-gnueabi:toolchain \
    --host_crosstool_top=//tools/cpp:toolchain \
    --cpu=armeabi \
    --custom_malloc=//arm-linux-gnueabi:malloc \
    --verbose_failures \
    //apollo/control 
