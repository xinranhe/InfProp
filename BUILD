cc_library(
	name = "inf_prop",
	srcs = [
		"Dataset.cpp",
		"Graph.cpp",
		"InfProp.cpp",
	],
	hdrs = [
		"Dataset.h",
		"Graph.h",
		"InfProp.h",
	],
	visibility = ["//visibility:public"],
)

cc_binary(
	name = "inf_prop_main",
	srcs = ["main.cpp"],
	deps = ["inf_prop"],
	linkopts = [
		"-lm",
	],
)
