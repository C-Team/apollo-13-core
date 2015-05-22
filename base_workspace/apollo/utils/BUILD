cc_library(
  name = "error",
  hdrs = ["error.h"],
  visibility = ["//visibility:public"],
)

cc_library(
  name = "initializable",
  hdrs = ["initializable.h"],
  deps = [":error"],
  visibility = ["//visibility:public"],
)

cc_library(
  name = "file",
  hdrs = ["file.h"],
  srcs = ["file.cc"],
  deps = [":error"],
)
