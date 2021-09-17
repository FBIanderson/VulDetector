static size_t
arena_stash_decayed(tsdn_t *tsdn, arena_t *arena,
    extent_hooks_t **r_extent_hooks, extents_t *extents, size_t npages_limit,
	size_t npages_decay_max, extent_list_t *decay_extents) {
	witness_assert_depth_to_rank(tsdn_witness_tsdp_get(tsdn),
	    WITNESS_RANK_CORE, 0);

	/* Stash extents according to npages_limit. */
	size_t nstashed = 0;
	extent_t *extent;
	while (nstashed < npages_decay_max &&
	    (extent = extents_evict(tsdn, arena, r_extent_hooks, extents,
	    npages_limit)) != NULL) {
		extent_list_append(decay_extents, extent);
		nstashed += extent_size_get(extent) >> LG_PAGE;
	}
	return nstashed;
}
