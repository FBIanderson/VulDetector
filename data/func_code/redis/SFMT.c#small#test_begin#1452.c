TEST_BEGIN(test_gen_rand_32) {
	uint32_t array32[BLOCK_SIZE] JEMALLOC_ATTR(aligned(16));
	uint32_t array32_2[BLOCK_SIZE] JEMALLOC_ATTR(aligned(16));
	int i;
	uint32_t r32;
	sfmt_t *ctx;

	assert_d_le(get_min_array_size32(), BLOCK_SIZE,
	    "Array size too small");
	ctx = init_gen_rand(1234);
	fill_array32(ctx, array32, BLOCK_SIZE);
	fill_array32(ctx, array32_2, BLOCK_SIZE);
	fini_gen_rand(ctx);

	ctx = init_gen_rand(1234);
	for (i = 0; i < BLOCK_SIZE; i++) {
		if (i < COUNT_1) {
			assert_u32_eq(array32[i], init_gen_rand_32_expected[i],
			    "Output mismatch for i=%d", i);
		}
		r32 = gen_rand32(ctx);
		assert_u32_eq(r32, array32[i],
		    "Mismatch at array32[%d]=%x, gen=%x", i, array32[i], r32);
	}
	for (i = 0; i < COUNT_2; i++) {
		r32 = gen_rand32(ctx);
		assert_u32_eq(r32, array32_2[i],
		    "Mismatch at array32_2[%d]=%x, gen=%x", i, array32_2[i],
		    r32);
	}
	fini_gen_rand(ctx);
}
