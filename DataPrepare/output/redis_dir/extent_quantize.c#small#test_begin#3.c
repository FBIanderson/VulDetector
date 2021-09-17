TEST_BEGIN(test_small_extent_size) {
	unsigned nbins, i;
	size_t sz, extent_size;
	size_t mib[4];
	size_t miblen = sizeof(mib) / sizeof(size_t);

	/*
	 * Iterate over all small size classes, get their extent sizes, and
	 * verify that the quantized size is the same as the extent size.
	 */

	sz = sizeof(unsigned);
	assert_d_eq(mallctl("arenas.nbins", (void *)&nbins, &sz, NULL, 0), 0,
	    "Unexpected mallctl failure");

	assert_d_eq(mallctlnametomib("arenas.bin.0.slab_size", mib, &miblen), 0,
	    "Unexpected mallctlnametomib failure");
	for (i = 0; i < nbins; i++) {
		mib[2] = i;
		sz = sizeof(size_t);
		assert_d_eq(mallctlbymib(mib, miblen, (void *)&extent_size, &sz,
		    NULL, 0), 0, "Unexpected mallctlbymib failure");
		assert_zu_eq(extent_size,
		    extent_size_quantize_floor(extent_size),
		    "Small extent quantization should be a no-op "
		    "(extent_size=%zu)", extent_size);
		assert_zu_eq(extent_size,
		    extent_size_quantize_ceil(extent_size),
		    "Small extent quantization should be a no-op "
		    "(extent_size=%zu)", extent_size);
	}
}
