project(
	'libtensor',
	'c',
)

cc=meson.get_compiler('c')
dep_m=cc.find_library(
	'm',
	required: true,
)

libtensor=library(
	'tensor',
	[
		'src/tensor.c',
	],
	dependencies: [
		dep_m,
	],
	include_directories: [
		'include',
	],
	install: true,
)

pkgconfig=import('pkgconfig')

pkgconfig.generate(
	libtensor,
)

