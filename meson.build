project(
	'',
	'c',
)

dep_libsqlite3=dependency('sqlite3')

gmocoin_download_trades=executable(
	'gmocoin_download_trades',
	[
		'src/gmocoin_download_trades.c',
	],
	dependencies: [
		dep_libsqlite3,
	],
	install: true,
)

