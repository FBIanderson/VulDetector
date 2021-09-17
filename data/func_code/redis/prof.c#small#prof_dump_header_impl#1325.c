static bool
prof_dump_header_impl(tsdn_t *tsdn, bool propagate_err,
    const prof_cnt_t *cnt_all) {
	bool ret;

	if (prof_dump_printf(propagate_err,
	    "heap_v2/%"FMTu64"\n"
	    "  t*: %"FMTu64": %"FMTu64" [%"FMTu64": %"FMTu64"]\n",
	    ((uint64_t)1U << lg_prof_sample), cnt_all->curobjs,
	    cnt_all->curbytes, cnt_all->accumobjs, cnt_all->accumbytes)) {
		return true;
	}

	malloc_mutex_lock(tsdn, &tdatas_mtx);
	ret = (tdata_tree_iter(&tdatas, NULL, prof_tdata_dump_iter,
	    (void *)&propagate_err) != NULL);
	malloc_mutex_unlock(tsdn, &tdatas_mtx);
	return ret;
}
