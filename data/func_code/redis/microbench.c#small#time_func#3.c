static inline void
time_func(timedelta_t *timer, uint64_t nwarmup, uint64_t niter,
    void (*func)(void)) {
	uint64_t i;

	for (i = 0; i < nwarmup; i++) {
		func();
	}
	timer_start(timer);
	for (i = 0; i < niter; i++) {
		func();
	}
	timer_stop(timer);
}
