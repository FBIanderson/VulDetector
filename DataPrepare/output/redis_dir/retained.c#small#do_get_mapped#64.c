static size_t
do_get_mapped(unsigned arena_ind) {
	return do_get_size_impl("stats.arenas.0.mapped", arena_ind);
}
