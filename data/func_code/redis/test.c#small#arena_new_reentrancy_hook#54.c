static void
arena_new_reentrancy_hook() {
	do_hook(&arena_new_hook_ran, &hooks_arena_new_hook);
}
