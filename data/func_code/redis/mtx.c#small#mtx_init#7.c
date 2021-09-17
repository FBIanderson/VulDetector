bool
mtx_init(mtx_t *mtx) {
#ifdef _WIN32
	if (!InitializeCriticalSectionAndSpinCount(&mtx->lock,
	    _CRT_SPINCOUNT)) {
		return true;
	}
#elif (defined(JEMALLOC_OS_UNFAIR_LOCK))
	mtx->lock = OS_UNFAIR_LOCK_INIT;
#elif (defined(JEMALLOC_OSSPIN))
	mtx->lock = 0;
#else
	pthread_mutexattr_t attr;

	if (pthread_mutexattr_init(&attr) != 0) {
		return true;
	}
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_DEFAULT);
	if (pthread_mutex_init(&mtx->lock, &attr) != 0) {
		pthread_mutexattr_destroy(&attr);
		return true;
	}
	pthread_mutexattr_destroy(&attr);
#endif
	return false;
}
