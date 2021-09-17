void
arena_basic_stats_merge(UNUSED tsdn_t *tsdn, arena_t *arena, unsigned *nthreads,
    const char **dss, ssize_t *dirty_decay_ms, ssize_t *muzzy_decay_ms,
    size_t *nactive, size_t *ndirty, size_t *nmuzzy) {
	*nthreads += arena_nthreads_get(arena, false);
	*dss = dss_prec_names[arena_dss_prec_get(arena)];
	*dirty_decay_ms = arena_dirty_decay_ms_get(arena);
	*muzzy_decay_ms = arena_muzzy_decay_ms_get(arena);
	*nactive += atomic_load_zu(&arena->nactive, ATOMIC_RELAXED);
	*ndirty += extents_npages_get(&arena->extents_dirty);
	*nmuzzy += extents_npages_get(&arena->extents_muzzy);
}
