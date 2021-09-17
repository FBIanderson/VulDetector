void
mtx_unlock(mtx_t *mtx) {
#ifdef _WIN32
	LeaveCriticalSection(&mtx->lock);
#elif (defined(JEMALLOC_OS_UNFAIR_LOCK))
	os_unfair_lock_unlock(&mtx->lock);
#elif (defined(JEMALLOC_OSSPIN))
	OSSpinLockUnlock(&mtx->lock);
#else
	pthread_mutex_unlock(&mtx->lock);
#endif
}
