project(
	'random',
	'c',
)

librandom=library(
	'random',
	[
		'src/xorshift.c',
	],
	include_directories: [
		'include',
	],
)

pkgconfig=import('pkgconfig')

pkgconfig.generate(
	librandom,
)
