#include <sqlite3.h>
#include <stdio.h>

int init_schema(sqlite3*db,char**error_message){
	int ret;
	const char*SCHEMA_TABLE_TRADES="CREATE TABLE IF NOT EXISTS `gmocoin_trades` (`symbol` TEXT,`price` TEXT,`side` TEXT,`size` TEXT,`timestamp` NUMERIC,UNIQUE(`symbol`,`price`,`timestamp`));";
	const char*SCHEMA_INDEX_TRADES_SYMBOL="CREATE INDEX IF NOT EXISTS `gmocoin_trades_symbol` ON `gmocoin_trades`(`symbol`);";
	const char*SCHEMA_INDEX_TRADES_SIDE="CREATE INDEX IF NOT EXISTS `gmocoin_trades_side` ON `gmocoin_trades`(`side`);";
	const char*SCHEMA_INDEX_TRADES_TIMESTAMP="CREATE INDEX IF NOT EXISTS `gmocoin_trades_timestamp` ON `gmocoin_trades`(`timestamp`);";
	ret=sqlite3_exec(db,SCHEMA_TABLE_TRADES,0,0,error_message);
	if(SQLITE_OK!=ret){
		return ret;
	}
	ret=sqlite3_exec(db,SCHEMA_INDEX_TRADES_SYMBOL,0,0,error_message);
	if(SQLITE_OK!=ret){
		return ret;
	}
	ret=sqlite3_exec(db,SCHEMA_INDEX_TRADES_SIDE,0,0,error_message);
	if(SQLITE_OK!=ret){
		return ret;
	}
	ret=sqlite3_exec(db,SCHEMA_INDEX_TRADES_TIMESTAMP,0,0,error_message);
	return ret;
}

int main(int argc,const char**argv,const char**envp){
	if(argc!=3){
		printf("Usage: %s database symbol\n",argv[0]);
		return !0;
	}
	const char*dbfilename=argv[1];
	sqlite3*db;
	int ret;
	char*error_message;
	ret=sqlite3_open(dbfilename,&db);
	if(SQLITE_OK!=ret){
		return !0;
	}
	ret=init_schema(db,&error_message);
	if(SQLITE_OK!=ret){
		return ret;
	}
	sqlite3_close(db);
	return 0;
}
