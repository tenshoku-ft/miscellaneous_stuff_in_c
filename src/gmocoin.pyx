
cdef class GMOCoin:
	cdef gmocoin_t *gmocoin
	def __cinit__(self):
		gmocoin_new(&(self.gmocoin))
	def __deallocate__(self):
		gmocoin_del(self.gmocoin)

