project(
	'libgmocoin',
	'c',
	'cython'
)

py=import('python').find_installation()
dep_py=py.dependency()
dep_libcjson=dependency('libcjson')
dep_libcurl=dependency('libcurl')
dep_python3=dependency('python3-embed')

inc_libgmocoin=include_directories(
	'include',
)

libgmocoin=library(
	'libgmocoin',
	[
		'src/gmocoin.c',
	],
	name_prefix: '',
	dependencies: [
		dep_libcjson,
		dep_libcurl,
	],
	include_directories: [
		inc_libgmocoin,
	],
	install: true,
)

dep_libgmocoin=declare_dependency(
	dependencies: [
		dep_libcjson,
		dep_libcurl,
	],
	include_directories: [
		inc_libgmocoin,
	],
	link_with: [
		libgmocoin,
	],
)

pkgconfig=import('pkgconfig')

pkgconfig.generate(
	libgmocoin,
)

python_gmocoin=py.extension_module(
	'gmocoin',
	[
		'src/gmocoin.pyx',
	],
	dependencies: [
		dep_libgmocoin,
	],
)

example_gmocoin_status=executable(
	'gmocoin_status',
	[
		'examples/gmocoin_status.c',
	],
	dependencies: [
		dep_libgmocoin,
	],
)

example_gmocoin_trades=executable(
	'gmocoin_trades',
	[
		'examples/gmocoin_trades.c',
	],
	dependencies: [
		dep_libgmocoin,
	],
)

