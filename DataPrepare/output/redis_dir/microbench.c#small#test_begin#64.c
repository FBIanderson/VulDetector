TEST_BEGIN(test_malloc_vs_mallocx) {
	compare_funcs(10*1000*1000, 100*1000*1000, "malloc",
	    malloc_free, "mallocx", mallocx_free);
}
