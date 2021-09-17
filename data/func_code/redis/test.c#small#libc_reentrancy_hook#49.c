static void
libc_reentrancy_hook() {
	do_hook(&libc_hook_ran, &hooks_libc_hook);
}
