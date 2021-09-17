TEST_BEGIN(test_arena_reset) {
	unsigned arena_ind;
	void **ptrs;
	unsigned nptrs;

	arena_ind = do_arena_create(NULL);
	do_arena_reset_pre(arena_ind, &ptrs, &nptrs);
	do_arena_reset(arena_ind);
	do_arena_reset_post(ptrs, nptrs, arena_ind);
}
