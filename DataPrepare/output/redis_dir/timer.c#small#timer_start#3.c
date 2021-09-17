void
timer_start(timedelta_t *timer) {
	nstime_init(&timer->t0, 0);
	nstime_update(&timer->t0);
}
