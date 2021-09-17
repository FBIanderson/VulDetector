static void
base_auto_thp_switch(tsdn_t *tsdn, base_t *base) {
	assert(opt_metadata_thp == metadata_thp_auto);
	malloc_mutex_assert_owner(tsdn, &base->mtx);
	if (base->auto_thp_switched) {
		return;
	}
	/* Called when adding a new block. */
	bool should_switch;
	if (base_ind_get(base) != 0) {
		should_switch = (base_get_num_blocks(base, true) ==
		    BASE_AUTO_THP_THRESHOLD);
	} else {
		should_switch = (base_get_num_blocks(base, true) ==
		    BASE_AUTO_THP_THRESHOLD_A0);
	}
	if (!should_switch) {
		return;
	}

	base->auto_thp_switched = true;
	assert(!config_stats || base->n_thp == 0);
	/* Make the initial blocks THP lazily. */
	base_block_t *block = base->blocks;
	while (block != NULL) {
		assert((block->size & HUGEPAGE_MASK) == 0);
		pages_huge(block, block->size);
		if (config_stats) {
			base->n_thp += HUGEPAGE_CEILING(block->size -
			    extent_bsize_get(&block->extent)) >> LG_HUGEPAGE;
		}
		block = block->next;
		assert(block == NULL || (base_ind_get(base) == 0));
	}
}
