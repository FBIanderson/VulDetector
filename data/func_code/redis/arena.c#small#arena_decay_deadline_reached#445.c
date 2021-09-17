static bool
arena_decay_deadline_reached(const arena_decay_t *decay, const nstime_t *time) {
	return (nstime_compare(&decay->deadline, time) <= 0);
}
