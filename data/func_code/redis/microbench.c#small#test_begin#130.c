TEST_BEGIN(test_mus_vs_sallocx) {
	compare_funcs(10*1000*1000, 100*1000*1000, "malloc_usable_size",
	    malloc_mus_free, "sallocx", malloc_sallocx_free);
}
