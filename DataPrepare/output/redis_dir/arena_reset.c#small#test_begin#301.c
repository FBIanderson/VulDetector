TEST_BEGIN(test_arena_destroy_hooks_unmap) {
	unsigned arena_ind;
	void **ptrs;
	unsigned nptrs;

	extent_hooks_prep();
	try_decommit = false;
	memcpy(&hooks_orig, &hooks, sizeof(extent_hooks_t));
	memcpy(&hooks, &hooks_unmap, sizeof(extent_hooks_t));

	did_alloc = false;
	arena_ind = do_arena_create(&hooks);
	do_arena_reset_pre(arena_ind, &ptrs, &nptrs);

	assert_true(did_alloc, "Expected alloc");

	assert_false(arena_i_initialized(arena_ind, false),
	    "Arena stats should not be initialized");
	assert_true(arena_i_initialized(arena_ind, true),
	    "Arena stats should be initialized");

	did_dalloc = false;
	do_arena_destroy(arena_ind);
	assert_true(did_dalloc, "Expected dalloc");

	assert_false(arena_i_initialized(arena_ind, true),
	    "Arena stats should not be initialized");
	assert_true(arena_i_initialized(MALLCTL_ARENAS_DESTROYED, false),
	    "Destroyed arena stats should be initialized");

	do_arena_reset_post(ptrs, nptrs, arena_ind);

	memcpy(&hooks, &hooks_orig, sizeof(extent_hooks_t));
}
