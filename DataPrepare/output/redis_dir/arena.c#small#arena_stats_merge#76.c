void
arena_stats_merge(tsdn_t *tsdn, arena_t *arena, unsigned *nthreads,
    const char **dss, ssize_t *dirty_decay_ms, ssize_t *muzzy_decay_ms,
    size_t *nactive, size_t *ndirty, size_t *nmuzzy, arena_stats_t *astats,
    bin_stats_t *bstats, arena_stats_large_t *lstats) {
	cassert(config_stats);

	arena_basic_stats_merge(tsdn, arena, nthreads, dss, dirty_decay_ms,
	    muzzy_decay_ms, nactive, ndirty, nmuzzy);

	size_t base_allocated, base_resident, base_mapped, metadata_thp;
	base_stats_get(tsdn, arena->base, &base_allocated, &base_resident,
	    &base_mapped, &metadata_thp);

	arena_stats_lock(tsdn, &arena->stats);

	arena_stats_accum_zu(&astats->mapped, base_mapped
	    + arena_stats_read_zu(tsdn, &arena->stats, &arena->stats.mapped));
	arena_stats_accum_zu(&astats->retained,
	    extents_npages_get(&arena->extents_retained) << LG_PAGE);

	arena_stats_accum_u64(&astats->decay_dirty.npurge,
	    arena_stats_read_u64(tsdn, &arena->stats,
	    &arena->stats.decay_dirty.npurge));
	arena_stats_accum_u64(&astats->decay_dirty.nmadvise,
	    arena_stats_read_u64(tsdn, &arena->stats,
	    &arena->stats.decay_dirty.nmadvise));
	arena_stats_accum_u64(&astats->decay_dirty.purged,
	    arena_stats_read_u64(tsdn, &arena->stats,
	    &arena->stats.decay_dirty.purged));

	arena_stats_accum_u64(&astats->decay_muzzy.npurge,
	    arena_stats_read_u64(tsdn, &arena->stats,
	    &arena->stats.decay_muzzy.npurge));
	arena_stats_accum_u64(&astats->decay_muzzy.nmadvise,
	    arena_stats_read_u64(tsdn, &arena->stats,
	    &arena->stats.decay_muzzy.nmadvise));
	arena_stats_accum_u64(&astats->decay_muzzy.purged,
	    arena_stats_read_u64(tsdn, &arena->stats,
	    &arena->stats.decay_muzzy.purged));

	arena_stats_accum_zu(&astats->base, base_allocated);
	arena_stats_accum_zu(&astats->internal, arena_internal_get(arena));
	arena_stats_accum_zu(&astats->metadata_thp, metadata_thp);
	arena_stats_accum_zu(&astats->resident, base_resident +
	    (((atomic_load_zu(&arena->nactive, ATOMIC_RELAXED) +
	    extents_npages_get(&arena->extents_dirty) +
	    extents_npages_get(&arena->extents_muzzy)) << LG_PAGE)));

	for (szind_t i = 0; i < NSIZES - NBINS; i++) {
		uint64_t nmalloc = arena_stats_read_u64(tsdn, &arena->stats,
		    &arena->stats.lstats[i].nmalloc);
		arena_stats_accum_u64(&lstats[i].nmalloc, nmalloc);
		arena_stats_accum_u64(&astats->nmalloc_large, nmalloc);

		uint64_t ndalloc = arena_stats_read_u64(tsdn, &arena->stats,
		    &arena->stats.lstats[i].ndalloc);
		arena_stats_accum_u64(&lstats[i].ndalloc, ndalloc);
		arena_stats_accum_u64(&astats->ndalloc_large, ndalloc);

		uint64_t nrequests = arena_stats_read_u64(tsdn, &arena->stats,
		    &arena->stats.lstats[i].nrequests);
		arena_stats_accum_u64(&lstats[i].nrequests,
		    nmalloc + nrequests);
		arena_stats_accum_u64(&astats->nrequests_large,
		    nmalloc + nrequests);

		assert(nmalloc >= ndalloc);
		assert(nmalloc - ndalloc <= SIZE_T_MAX);
		size_t curlextents = (size_t)(nmalloc - ndalloc);
		lstats[i].curlextents += curlextents;
		arena_stats_accum_zu(&astats->allocated_large,
		    curlextents * sz_index2size(NBINS + i));
	}

	arena_stats_unlock(tsdn, &arena->stats);

	/* tcache_bytes counts currently cached bytes. */
	atomic_store_zu(&astats->tcache_bytes, 0, ATOMIC_RELAXED);
	malloc_mutex_lock(tsdn, &arena->tcache_ql_mtx);
	cache_bin_array_descriptor_t *descriptor;
	ql_foreach(descriptor, &arena->cache_bin_array_descriptor_ql, link) {
		szind_t i = 0;
		for (; i < NBINS; i++) {
			cache_bin_t *tbin = &descriptor->bins_small[i];
			arena_stats_accum_zu(&astats->tcache_bytes,
			    tbin->ncached * sz_index2size(i));
		}
		for (; i < nhbins; i++) {
			cache_bin_t *tbin = &descriptor->bins_large[i];
			arena_stats_accum_zu(&astats->tcache_bytes,
			    tbin->ncached * sz_index2size(i));
		}
	}
	malloc_mutex_prof_read(tsdn,
	    &astats->mutex_prof_data[arena_prof_mutex_tcache_list],
	    &arena->tcache_ql_mtx);
	malloc_mutex_unlock(tsdn, &arena->tcache_ql_mtx);

#define READ_ARENA_MUTEX_PROF_DATA(mtx, ind)				\
    malloc_mutex_lock(tsdn, &arena->mtx);				\
    malloc_mutex_prof_read(tsdn, &astats->mutex_prof_data[ind],		\
        &arena->mtx);							\
    malloc_mutex_unlock(tsdn, &arena->mtx);

	/* Gather per arena mutex profiling data. */
	READ_ARENA_MUTEX_PROF_DATA(large_mtx, arena_prof_mutex_large);
	READ_ARENA_MUTEX_PROF_DATA(extent_avail_mtx,
	    arena_prof_mutex_extent_avail)
	READ_ARENA_MUTEX_PROF_DATA(extents_dirty.mtx,
	    arena_prof_mutex_extents_dirty)
	READ_ARENA_MUTEX_PROF_DATA(extents_muzzy.mtx,
	    arena_prof_mutex_extents_muzzy)
	READ_ARENA_MUTEX_PROF_DATA(extents_retained.mtx,
	    arena_prof_mutex_extents_retained)
	READ_ARENA_MUTEX_PROF_DATA(decay_dirty.mtx,
	    arena_prof_mutex_decay_dirty)
	READ_ARENA_MUTEX_PROF_DATA(decay_muzzy.mtx,
	    arena_prof_mutex_decay_muzzy)
	READ_ARENA_MUTEX_PROF_DATA(base->mtx,
	    arena_prof_mutex_base)
#undef READ_ARENA_MUTEX_PROF_DATA

	nstime_copy(&astats->uptime, &arena->create_time);
	nstime_update(&astats->uptime);
	nstime_subtract(&astats->uptime, &arena->create_time);

	for (szind_t i = 0; i < NBINS; i++) {
		bin_stats_merge(tsdn, &bstats[i], &arena->bins[i]);
	}
}
