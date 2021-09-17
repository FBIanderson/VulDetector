static prof_tdata_t *
prof_tdata_dump_iter(prof_tdata_tree_t *tdatas, prof_tdata_t *tdata,
    void *arg) {
	bool propagate_err = *(bool *)arg;

	if (!tdata->dumping) {
		return NULL;
	}

	if (prof_dump_printf(propagate_err,
	    "  t%"FMTu64": %"FMTu64": %"FMTu64" [%"FMTu64": %"FMTu64"]%s%s\n",
	    tdata->thr_uid, tdata->cnt_summed.curobjs,
	    tdata->cnt_summed.curbytes, tdata->cnt_summed.accumobjs,
	    tdata->cnt_summed.accumbytes,
	    (tdata->thread_name != NULL) ? " " : "",
	    (tdata->thread_name != NULL) ? tdata->thread_name : "")) {
		return tdata;
	}
	return NULL;
}
