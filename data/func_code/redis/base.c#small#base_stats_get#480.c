void
base_stats_get(tsdn_t *tsdn, base_t *base, size_t *allocated, size_t *resident,
    size_t *mapped, size_t *n_thp) {
	cassert(config_stats);

	malloc_mutex_lock(tsdn, &base->mtx);
	assert(base->allocated <= base->resident);
	assert(base->resident <= base->mapped);
	*allocated = base->allocated;
	*resident = base->resident;
	*mapped = base->mapped;
	*n_thp = base->n_thp;
	malloc_mutex_unlock(tsdn, &base->mtx);
}
