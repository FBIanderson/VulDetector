TEST_BEGIN(test_bitmap_size) {
	size_t nbits, prev_size;

	prev_size = 0;
	for (nbits = 1; nbits <= BITMAP_MAXBITS; nbits++) {
		bitmap_info_t binfo;
		bitmap_info_init(&binfo, nbits);
		prev_size = test_bitmap_size_body(&binfo, nbits, prev_size);
	}
#define NB(nbits) {							\
		bitmap_info_t binfo = BITMAP_INFO_INITIALIZER(nbits);	\
		prev_size = test_bitmap_size_body(&binfo, nbits,	\
		    prev_size);						\
	}
	prev_size = 0;
	NBITS_TAB
#undef NB
}
