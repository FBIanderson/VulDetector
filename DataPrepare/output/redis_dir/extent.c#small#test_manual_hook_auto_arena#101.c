static void
test_manual_hook_auto_arena(void) {
	unsigned narenas;
	size_t old_size, new_size, sz;
	size_t hooks_mib[3];
	size_t hooks_miblen;
	extent_hooks_t *new_hooks, *old_hooks;

	extent_hooks_prep();

	sz = sizeof(unsigned);
	/* Get number of auto arenas. */
	assert_d_eq(mallctl("opt.narenas", (void *)&narenas, &sz, NULL, 0),
	    0, "Unexpected mallctl() failure");
	if (narenas == 1) {
		return;
	}

	/* Install custom extent hooks on arena 1 (might not be initialized). */
	hooks_miblen = sizeof(hooks_mib)/sizeof(size_t);
	assert_d_eq(mallctlnametomib("arena.0.extent_hooks", hooks_mib,
	    &hooks_miblen), 0, "Unexpected mallctlnametomib() failure");
	hooks_mib[1] = 1;
	old_size = sizeof(extent_hooks_t *);
	new_hooks = &hooks;
	new_size = sizeof(extent_hooks_t *);
	assert_d_eq(mallctlbymib(hooks_mib, hooks_miblen, (void *)&old_hooks,
	    &old_size, (void *)&new_hooks, new_size), 0,
	    "Unexpected extent_hooks error");
	static bool auto_arena_created = false;
	if (old_hooks != &hooks) {
		assert_b_eq(auto_arena_created, false,
		    "Expected auto arena 1 created only once.");
		auto_arena_created = true;
	}
}
