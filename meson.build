project(
	'random',
	'c',
)

cc=meson.get_compiler('c')
dep_m=cc.find_library(
	'm',
	required: true,
)

librandom=library(
	'random',
	[
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

pkgconfig=import('pkgconfig')

pkgconfig.generate(
	librandom,
)

