static bool
extent_merge_impl(tsdn_t *tsdn, arena_t *arena,
    extent_hooks_t **r_extent_hooks, extent_t *a, extent_t *b,
    bool growing_retained) {
	witness_assert_depth_to_rank(tsdn_witness_tsdp_get(tsdn),
	    WITNESS_RANK_CORE, growing_retained ? 1 : 0);

	extent_hooks_assure_initialized(arena, r_extent_hooks);

	if ((*r_extent_hooks)->merge == NULL) {
		return true;
	}

	bool err;
	if (*r_extent_hooks == &extent_hooks_default) {
		/* Call directly to propagate tsdn. */
		err = extent_merge_default_impl(extent_base_get(a),
		    extent_base_get(b));
	} else {
		extent_hook_pre_reentrancy(tsdn, arena);
		err = (*r_extent_hooks)->merge(*r_extent_hooks,
		    extent_base_get(a), extent_size_get(a), extent_base_get(b),
		    extent_size_get(b), extent_committed_get(a),
		    arena_ind_get(arena));
		extent_hook_post_reentrancy(tsdn);
	}

	if (err) {
		return true;
	}

	/*
	 * The rtree writes must happen while all the relevant elements are
	 * owned, so the following code uses decomposed helper functions rather
	 * than extent_{,de}register() to do things in the right order.
	 */
	rtree_ctx_t rtree_ctx_fallback;
	rtree_ctx_t *rtree_ctx = tsdn_rtree_ctx(tsdn, &rtree_ctx_fallback);
	rtree_leaf_elm_t *a_elm_a, *a_elm_b, *b_elm_a, *b_elm_b;
	extent_rtree_leaf_elms_lookup(tsdn, rtree_ctx, a, true, false, &a_elm_a,
	    &a_elm_b);
	extent_rtree_leaf_elms_lookup(tsdn, rtree_ctx, b, true, false, &b_elm_a,
	    &b_elm_b);

	extent_lock2(tsdn, a, b);

	if (a_elm_b != NULL) {
		rtree_leaf_elm_write(tsdn, &extents_rtree, a_elm_b, NULL,
		    NSIZES, false);
	}
	if (b_elm_b != NULL) {
		rtree_leaf_elm_write(tsdn, &extents_rtree, b_elm_a, NULL,
		    NSIZES, false);
	} else {
		b_elm_b = b_elm_a;
	}

	extent_size_set(a, extent_size_get(a) + extent_size_get(b));
	extent_szind_set(a, NSIZES);
	extent_sn_set(a, (extent_sn_get(a) < extent_sn_get(b)) ?
	    extent_sn_get(a) : extent_sn_get(b));
	extent_zeroed_set(a, extent_zeroed_get(a) && extent_zeroed_get(b));

	extent_rtree_write_acquired(tsdn, a_elm_a, b_elm_b, a, NSIZES, false);

	extent_unlock2(tsdn, a, b);

	extent_dalloc(tsdn, extent_arena_get(b), b);

	return false;
}
