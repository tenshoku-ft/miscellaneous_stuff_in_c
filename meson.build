project(
	'libgmocoin',
	'c',
)

dep_libcjson=dependency('libcjson')
dep_libcurl=dependency('libcurl')

libgmocoin=library(
	'gmocoin',
	[
		'src/gmocoin.c',
	],
	dependencies: [
		dep_libcjson,
		dep_libcurl,
	],
	include_directories: [
		'include',
	],
	install: true,
)

pkgconfig=import('pkgconfig')

pkgconfig.generate(
	libgmocoin,
)

example_gmocoin=executable(
	'gmocoin_status',
	[
		'examples/gmocoin_status.c',
	],
	include_directories: [
		'include',
	],
	link_with: [
		libgmocoin,
	],
)

