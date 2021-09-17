TEST_BEGIN(test_bitmap_initializer) {
#define NB(nbits) {							\
		if (nbits <= BITMAP_MAXBITS) {				\
			bitmap_info_t binfo =				\
			    BITMAP_INFO_INITIALIZER(nbits);		\
			test_bitmap_initializer_body(&binfo, nbits);	\
		}							\
	}
	NBITS_TAB
#undef NB
}
