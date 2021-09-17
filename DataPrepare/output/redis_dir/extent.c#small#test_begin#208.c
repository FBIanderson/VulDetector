TEST_BEGIN(test_extent_manual_hook) {
	test_manual_hook_auto_arena();
	test_manual_hook_body();

	/* Test failure paths. */
	try_split = false;
	test_manual_hook_body();
	try_merge = false;
	test_manual_hook_body();
	try_purge_lazy = false;
	try_purge_forced = false;
	test_manual_hook_body();

	try_split = try_merge = try_purge_lazy = try_purge_forced = true;
}
