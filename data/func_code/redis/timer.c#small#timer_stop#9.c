void
timer_stop(timedelta_t *timer) {
	nstime_copy(&timer->t1, &timer->t0);
	nstime_update(&timer->t1);
}
