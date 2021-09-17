TEST_BEGIN(test_arena_destroy_initial) {
	assert_false(arena_i_initialized(MALLCTL_ARENAS_DESTROYED, false),
	    "Destroyed arena stats should not be initialized");
}
