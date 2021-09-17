void
mtx_lock(mtx_t *mtx) {
#ifdef _WIN32
	EnterCriticalSection(&mtx->lock);
#elif (defined(JEMALLOC_OS_UNFAIR_LOCK))
	os_unfair_lock_lock(&mtx->lock);
#elif (defined(JEMALLOC_OSSPIN))
	OSSpinLockLock(&mtx->lock);
#else
	pthread_mutex_lock(&mtx->lock);
#endif
}
