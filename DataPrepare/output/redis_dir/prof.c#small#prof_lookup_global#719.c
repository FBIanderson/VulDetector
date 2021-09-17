static bool
prof_lookup_global(tsd_t *tsd, prof_bt_t *bt, prof_tdata_t *tdata,
    void **p_btkey, prof_gctx_t **p_gctx, bool *p_new_gctx) {
	union {
		prof_gctx_t	*p;
		void		*v;
	} gctx, tgctx;
	union {
		prof_bt_t	*p;
		void		*v;
	} btkey;
	bool new_gctx;

	prof_enter(tsd, tdata);
	if (ckh_search(&bt2gctx, bt, &btkey.v, &gctx.v)) {
		/* bt has never been seen before.  Insert it. */
		prof_leave(tsd, tdata);
		tgctx.p = prof_gctx_create(tsd_tsdn(tsd), bt);
		if (tgctx.v == NULL) {
			return true;
		}
		prof_enter(tsd, tdata);
		if (ckh_search(&bt2gctx, bt, &btkey.v, &gctx.v)) {
			gctx.p = tgctx.p;
			btkey.p = &gctx.p->bt;
			if (ckh_insert(tsd, &bt2gctx, btkey.v, gctx.v)) {
				/* OOM. */
				prof_leave(tsd, tdata);
				idalloctm(tsd_tsdn(tsd), gctx.v, NULL, NULL,
				    true, true);
				return true;
			}
			new_gctx = true;
		} else {
			new_gctx = false;
		}
	} else {
		tgctx.v = NULL;
		new_gctx = false;
	}

	if (!new_gctx) {
		/*
		 * Increment nlimbo, in order to avoid a race condition with
		 * prof_tctx_destroy()/prof_gctx_try_destroy().
		 */
		malloc_mutex_lock(tsd_tsdn(tsd), gctx.p->lock);
		gctx.p->nlimbo++;
		malloc_mutex_unlock(tsd_tsdn(tsd), gctx.p->lock);
		new_gctx = false;

		if (tgctx.v != NULL) {
			/* Lost race to insert. */
			idalloctm(tsd_tsdn(tsd), tgctx.v, NULL, NULL, true,
			    true);
		}
	}
	prof_leave(tsd, tdata);

	*p_btkey = btkey.v;
	*p_gctx = gctx.p;
	*p_new_gctx = new_gctx;
	return false;
}
