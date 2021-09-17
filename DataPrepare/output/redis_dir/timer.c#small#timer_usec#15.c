uint64_t
timer_usec(const timedelta_t *timer) {
	nstime_t delta;

	nstime_copy(&delta, &timer->t1);
	nstime_subtract(&delta, &timer->t0);
	return nstime_ns(&delta) / 1000;
}
