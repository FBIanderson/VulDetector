static void
test_bitmap_initializer_body(const bitmap_info_t *binfo, size_t nbits) {
	bitmap_info_t binfo_dyn;
	bitmap_info_init(&binfo_dyn, nbits);

	assert_zu_eq(bitmap_size(binfo), bitmap_size(&binfo_dyn),
	    "Unexpected difference between static and dynamic initialization, "
	    "nbits=%zu", nbits);
	assert_zu_eq(binfo->nbits, binfo_dyn.nbits,
	    "Unexpected difference between static and dynamic initialization, "
	    "nbits=%zu", nbits);
#ifdef BITMAP_USE_TREE
	assert_u_eq(binfo->nlevels, binfo_dyn.nlevels,
	    "Unexpected difference between static and dynamic initialization, "
	    "nbits=%zu", nbits);
	{
		unsigned i;

		for (i = 0; i < binfo->nlevels; i++) {
			assert_zu_eq(binfo->levels[i].group_offset,
			    binfo_dyn.levels[i].group_offset,
			    "Unexpected difference between static and dynamic "
			    "initialization, nbits=%zu, level=%u", nbits, i);
		}
	}
#else
	assert_zu_eq(binfo->ngroups, binfo_dyn.ngroups,
	    "Unexpected difference between static and dynamic initialization");
#endif
}
