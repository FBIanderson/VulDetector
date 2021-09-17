static void
ctl_background_thread_stats_read(tsdn_t *tsdn) {
	background_thread_stats_t *stats = &ctl_stats->background_thread;
	if (!have_background_thread ||
	    background_thread_stats_read(tsdn, stats)) {
		memset(stats, 0, sizeof(background_thread_stats_t));
		nstime_init(&stats->run_interval, 0);
	}
}
