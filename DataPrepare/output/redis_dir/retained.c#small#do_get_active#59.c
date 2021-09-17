static size_t
do_get_active(unsigned arena_ind) {
	return do_get_size_impl("stats.arenas.0.pactive", arena_ind) * PAGE;
}
