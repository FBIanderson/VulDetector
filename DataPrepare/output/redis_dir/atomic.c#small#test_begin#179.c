TEST_BEGIN(test_atomic_u64) {
#if !(LG_SIZEOF_PTR == 3 || LG_SIZEOF_INT == 3)
	test_skip("64-bit atomic operations not supported");
#else
	INTEGER_TEST_BODY(uint64_t, u64);
#endif
}
