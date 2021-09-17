static void
base_extent_bump_alloc_post(base_t *base, extent_t *extent, size_t gap_size,
    void *addr, size_t size) {
	if (extent_bsize_get(extent) > 0) {
		/*
		 * Compute the index for the largest size class that does not
		 * exceed extent's size.
		 */
		szind_t index_floor =
		    sz_size2index(extent_bsize_get(extent) + 1) - 1;
		extent_heap_insert(&base->avail[index_floor], extent);
	}

	if (config_stats) {
		base->allocated += size;
		/*
		 * Add one PAGE to base_resident for every page boundary that is
		 * crossed by the new allocation. Adjust n_thp similarly when
		 * metadata_thp is enabled.
		 */
		base->resident += PAGE_CEILING((uintptr_t)addr + size) -
		    PAGE_CEILING((uintptr_t)addr - gap_size);
		assert(base->allocated <= base->resident);
		assert(base->resident <= base->mapped);
		if (metadata_thp_madvise() && (opt_metadata_thp ==
		    metadata_thp_always || base->auto_thp_switched)) {
			base->n_thp += (HUGEPAGE_CEILING((uintptr_t)addr + size)
			    - HUGEPAGE_CEILING((uintptr_t)addr - gap_size)) >>
			    LG_HUGEPAGE;
			assert(base->mapped >= base->n_thp << LG_HUGEPAGE);
		}
	}
}
