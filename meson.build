project(
	'',
	'c',
)

cc=meson.get_compiler('c')
dep_m=cc.find_library(
	'm',
	required: true,
)

main=executable(
	'main',
	[
		'src/main.c',
		'src/tensor.c',
		'src/linear.c',
		'src/layer.c',
		'src/activation.c',
		'src/xorshift.c',
	],
	dependencies: [
		dep_m,
	],
	include_directories: [
		'include',
	],
	install: true,
)

