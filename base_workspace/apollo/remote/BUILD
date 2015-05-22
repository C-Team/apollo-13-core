cc_library(
  name = "network_packet",
  hdrs = ["network_packet.h"],
  visibility = ["//visibility:public"],
)

cc_library(
  name = "packet_manager",
  hdrs = ["packet_manager.h"],
  srcs = ["packet_manager.cc"],
  deps = [
    "//apollo/core:safe_exit",
    ":network_packet",
  ],
)

cc_library(
  name = "connection_manager",
  hdrs = ["connection_manager.h"],
  srcs = ["connection_manager.cc"],
  deps = [
    ":network_packet",
    ":packet_manager",
  ],
  visibility = ["//visibility:public"],
)

cc_binary(
  name = "remote",
  srcs = ["main.cc"],
  deps = [
    ":network_packet",
    ":packet_manager",
  ],
)
