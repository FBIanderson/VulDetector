TEST_BEGIN(test_bitmap_set) {
	size_t nbits;

	for (nbits = 1; nbits <= BITMAP_MAXBITS; nbits++) {
		bitmap_info_t binfo;
		bitmap_info_init(&binfo, nbits);
		test_bitmap_set_body(&binfo, nbits);
	}
#define NB(nbits) {							\
		bitmap_info_t binfo = BITMAP_INFO_INITIALIZER(nbits);	\
		test_bitmap_set_body(&binfo, nbits);			\
	}
	NBITS_TAB
#undef NB
}
