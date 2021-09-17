static ctl_arena_t *
arenas_i_impl(tsd_t *tsd, size_t i, bool compat, bool init) {
	ctl_arena_t *ret;

	assert(!compat || !init);

	ret = ctl_arenas->arenas[arenas_i2a_impl(i, compat, false)];
	if (init && ret == NULL) {
		if (config_stats) {
			struct container_s {
				ctl_arena_t		ctl_arena;
				ctl_arena_stats_t	astats;
			};
			struct container_s *cont =
			    (struct container_s *)base_alloc(tsd_tsdn(tsd),
			    b0get(), sizeof(struct container_s), QUANTUM);
			if (cont == NULL) {
				return NULL;
			}
			ret = &cont->ctl_arena;
			ret->astats = &cont->astats;
		} else {
			ret = (ctl_arena_t *)base_alloc(tsd_tsdn(tsd), b0get(),
			    sizeof(ctl_arena_t), QUANTUM);
			if (ret == NULL) {
				return NULL;
			}
		}
		ret->arena_ind = (unsigned)i;
		ctl_arenas->arenas[arenas_i2a_impl(i, compat, false)] = ret;
	}

	assert(ret == NULL || arenas_i2a(ret->arena_ind) == arenas_i2a(i));
	return ret;
}
