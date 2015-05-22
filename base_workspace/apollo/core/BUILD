cc_library(
  name = "serial",
  hdrs = ["serial.h"],
  srcs = ["serial.cc"],
)

cc_library(
  name = "motor_controller",
  hdrs = ["motor_controller.h"],
  srcs = ["motor_controller.cc"],
  deps = [":serial"],
)

cc_library(
  name = "motor_definitions",
  hdrs = ["motor_definitions.h"],
)

cc_library(
  name = "wheel_controller",
  hdrs = ["wheel_controller.h"],
  srcs = ["wheel_controller.cc"],
  deps = [
    ":motor_controller",
    ":motor_definitions",
  ],
  visibility = ["//visibility:public"],
)

cc_library(
  name = "conveyor_controller",
  hdrs = ["conveyor_controller.h"],
  srcs = ["conveyor_controller.cc"],
  deps = [
    ":motor_controller",
    ":motor_definitions",
  ],
  visibility = ["//visibility:public"],
)

cc_library(
  name = "feedback_potentiometer",
  hdrs = ["feedback_potentiometer.h"],
  srcs = ["feedback_potentiometer.cc"],
  deps = [":motor_definitions"],
)

cc_library(
  name = "position_controller",
  hdrs = ["position_controller.h"],
  srcs = ["position_controller.cc"],
  deps = [":feedback_potentiometer"],
)

cc_library(
  name = "digger_controller",
  hdrs = ["digger_controller.h"],
  srcs = ["digger_controller.cc"],
  deps = [
    ":feedback_potentiometer",
    ":motor_controller",
    ":motor_definitions",
    ":position_controller",
  ],
  visibility = ["//visibility:public"],
)

cc_library(
  name = "safe_exit",
  hdrs = ["safe_exit.h"],
  srcs = ["safe_exit.cc"],
  deps = [
    ":motor_definitions",
    ":serial",
  ],
  visibility = ["//visibility:public"],
)

cc_binary(
  name = "hello",
  srcs = ["hello.cc"],
  deps = [
    ":digger_controller",
    ":feedback_potentiometer",
    ":motor_controller",
    ":serial",
  ],
)
