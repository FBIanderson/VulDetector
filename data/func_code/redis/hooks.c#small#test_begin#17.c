TEST_BEGIN(unhooked_call) {
	hooks_libc_hook = NULL;
	hook_called = false;
	assert_d_eq(3, func_to_hook(1, 2), "Hooking changed return value.");
	assert_false(hook_called, "Nulling out hook didn't take.");
}
