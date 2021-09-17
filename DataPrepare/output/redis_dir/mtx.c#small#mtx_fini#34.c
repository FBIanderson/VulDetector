void
mtx_fini(mtx_t *mtx) {
#ifdef _WIN32
#elif (defined(JEMALLOC_OS_UNFAIR_LOCK))
#elif (defined(JEMALLOC_OSSPIN))
#else
	pthread_mutex_destroy(&mtx->lock);
#endif
}
