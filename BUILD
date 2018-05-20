cc_library(
	name = "info_prop",
	srcs = [
		"Graph.cpp",
		"InfoProp.cpp",
	],
	hdrs = [
		"Graph.h",
		"InfoProp.h",
	],
	visibility = ["//visibility:public"],
)

cc_binary(
	name = "info_prop_main",
	srcs = ["main.cpp"],
	deps = ["info_prop"],
	linkopts = [
		"-lm",
	],
)
