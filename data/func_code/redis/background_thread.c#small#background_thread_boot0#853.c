bool
background_thread_boot0(void) {
	if (!have_background_thread && opt_background_thread) {
		malloc_printf("<jemalloc>: option background_thread currently "
		    "supports pthread only\n");
		return true;
	}
#ifdef JEMALLOC_PTHREAD_CREATE_WRAPPER
	if ((config_lazy_lock || opt_background_thread) &&
	    pthread_create_fptr_init()) {
		return true;
	}
#endif
	return false;
}
