
cdef extern from "gmocoin.h":
	cdef struct gmocoin_st:
		pass
	ctypedef gmocoin_st gmocoin_t
	cdef struct gmocoin_trade_st:
		char price[80]
		char size[8]
		char side[80]
		char timestamp[32]
	ctypedef gmocoin_trade_st gmocoin_trade_t
	int gmocoin_new(gmocoin_t**)
	int gmocoin_del(gmocoin_t*)

