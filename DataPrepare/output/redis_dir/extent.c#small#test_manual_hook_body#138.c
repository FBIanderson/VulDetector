static void
test_manual_hook_body(void) {
	unsigned arena_ind;
	size_t old_size, new_size, sz;
	size_t hooks_mib[3];
	size_t hooks_miblen;
	extent_hooks_t *new_hooks, *old_hooks;

	extent_hooks_prep();

	sz = sizeof(unsigned);
	assert_d_eq(mallctl("arenas.create", (void *)&arena_ind, &sz, NULL, 0),
	    0, "Unexpected mallctl() failure");

	/* Install custom extent hooks. */
	hooks_miblen = sizeof(hooks_mib)/sizeof(size_t);
	assert_d_eq(mallctlnametomib("arena.0.extent_hooks", hooks_mib,
	    &hooks_miblen), 0, "Unexpected mallctlnametomib() failure");
	hooks_mib[1] = (size_t)arena_ind;
	old_size = sizeof(extent_hooks_t *);
	new_hooks = &hooks;
	new_size = sizeof(extent_hooks_t *);
	assert_d_eq(mallctlbymib(hooks_mib, hooks_miblen, (void *)&old_hooks,
	    &old_size, (void *)&new_hooks, new_size), 0,
	    "Unexpected extent_hooks error");
	assert_ptr_ne(old_hooks->alloc, extent_alloc_hook,
	    "Unexpected extent_hooks error");
	assert_ptr_ne(old_hooks->dalloc, extent_dalloc_hook,
	    "Unexpected extent_hooks error");
	assert_ptr_ne(old_hooks->commit, extent_commit_hook,
	    "Unexpected extent_hooks error");
	assert_ptr_ne(old_hooks->decommit, extent_decommit_hook,
	    "Unexpected extent_hooks error");
	assert_ptr_ne(old_hooks->purge_lazy, extent_purge_lazy_hook,
	    "Unexpected extent_hooks error");
	assert_ptr_ne(old_hooks->purge_forced, extent_purge_forced_hook,
	    "Unexpected extent_hooks error");
	assert_ptr_ne(old_hooks->split, extent_split_hook,
	    "Unexpected extent_hooks error");
	assert_ptr_ne(old_hooks->merge, extent_merge_hook,
	    "Unexpected extent_hooks error");

	if (!check_background_thread_enabled()) {
		test_extent_body(arena_ind);
	}

	/* Restore extent hooks. */
	assert_d_eq(mallctlbymib(hooks_mib, hooks_miblen, NULL, NULL,
	    (void *)&old_hooks, new_size), 0, "Unexpected extent_hooks error");
	assert_d_eq(mallctlbymib(hooks_mib, hooks_miblen, (void *)&old_hooks,
	    &old_size, NULL, 0), 0, "Unexpected extent_hooks error");
	assert_ptr_eq(old_hooks, default_hooks, "Unexpected extent_hooks error");
	assert_ptr_eq(old_hooks->alloc, default_hooks->alloc,
	    "Unexpected extent_hooks error");
	assert_ptr_eq(old_hooks->dalloc, default_hooks->dalloc,
	    "Unexpected extent_hooks error");
	assert_ptr_eq(old_hooks->commit, default_hooks->commit,
	    "Unexpected extent_hooks error");
	assert_ptr_eq(old_hooks->decommit, default_hooks->decommit,
	    "Unexpected extent_hooks error");
	assert_ptr_eq(old_hooks->purge_lazy, default_hooks->purge_lazy,
	    "Unexpected extent_hooks error");
	assert_ptr_eq(old_hooks->purge_forced, default_hooks->purge_forced,
	    "Unexpected extent_hooks error");
	assert_ptr_eq(old_hooks->split, default_hooks->split,
	    "Unexpected extent_hooks error");
	assert_ptr_eq(old_hooks->merge, default_hooks->merge,
	    "Unexpected extent_hooks error");
}
