static void
stats_arena_bins_print(emitter_t *emitter, bool mutex, unsigned i) {
	size_t page;
	bool in_gap, in_gap_prev;
	unsigned nbins, j;

	CTL_GET("arenas.page", &page, size_t);

	CTL_GET("arenas.nbins", &nbins, unsigned);

	emitter_row_t header_row;
	emitter_row_init(&header_row);

	emitter_row_t row;
	emitter_row_init(&row);
#define COL(name, left_or_right, col_width, etype)			\
	emitter_col_t col_##name;					\
	emitter_col_init(&col_##name, &row);				\
	col_##name.justify = emitter_justify_##left_or_right;		\
	col_##name.width = col_width;					\
	col_##name.type = emitter_type_##etype;				\
	emitter_col_t header_col_##name;				\
	emitter_col_init(&header_col_##name, &header_row);		\
	header_col_##name.justify = emitter_justify_##left_or_right;	\
	header_col_##name.width = col_width;				\
	header_col_##name.type = emitter_type_title;			\
	header_col_##name.str_val = #name;

	COL(size, right, 20, size)
	COL(ind, right, 4, unsigned)
	COL(allocated, right, 13, uint64)
	COL(nmalloc, right, 13, uint64)
	COL(ndalloc, right, 13, uint64)
	COL(nrequests, right, 13, uint64)
	COL(curregs, right, 13, size)
	COL(curslabs, right, 13, size)
	COL(regs, right, 5, unsigned)
	COL(pgs, right, 4, size)
	/* To buffer a right- and left-justified column. */
	COL(justify_spacer, right, 1, title)
	COL(util, right, 6, title)
	COL(nfills, right, 13, uint64)
	COL(nflushes, right, 13, uint64)
	COL(nslabs, right, 13, uint64)
	COL(nreslabs, right, 13, uint64)
#undef COL

	/* Don't want to actually print the name. */
	header_col_justify_spacer.str_val = " ";
	col_justify_spacer.str_val = " ";


	emitter_col_t col_mutex64[mutex_prof_num_uint64_t_counters];
	emitter_col_t col_mutex32[mutex_prof_num_uint32_t_counters];

	emitter_col_t header_mutex64[mutex_prof_num_uint64_t_counters];
	emitter_col_t header_mutex32[mutex_prof_num_uint32_t_counters];

	if (mutex) {
		mutex_stats_init_cols(&row, NULL, NULL, col_mutex64,
		    col_mutex32);
		mutex_stats_init_cols(&header_row, NULL, NULL, header_mutex64,
		    header_mutex32);
	}

	/*
	 * We print a "bins:" header as part of the table row; we need to adjust
	 * the header size column to compensate.
	 */
	header_col_size.width -=5;
	emitter_table_printf(emitter, "bins:");
	emitter_table_row(emitter, &header_row);
	emitter_json_arr_begin(emitter, "bins");

	for (j = 0, in_gap = false; j < nbins; j++) {
		uint64_t nslabs;
		size_t reg_size, slab_size, curregs;
		size_t curslabs;
		uint32_t nregs;
		uint64_t nmalloc, ndalloc, nrequests, nfills, nflushes;
		uint64_t nreslabs;

		CTL_M2_M4_GET("stats.arenas.0.bins.0.nslabs", i, j, &nslabs,
		    uint64_t);
		in_gap_prev = in_gap;
		in_gap = (nslabs == 0);

		if (in_gap_prev && !in_gap) {
			emitter_table_printf(emitter,
			    "                     ---\n");
		}

		CTL_M2_GET("arenas.bin.0.size", j, &reg_size, size_t);
		CTL_M2_GET("arenas.bin.0.nregs", j, &nregs, uint32_t);
		CTL_M2_GET("arenas.bin.0.slab_size", j, &slab_size, size_t);

		CTL_M2_M4_GET("stats.arenas.0.bins.0.nmalloc", i, j, &nmalloc,
		    uint64_t);
		CTL_M2_M4_GET("stats.arenas.0.bins.0.ndalloc", i, j, &ndalloc,
		    uint64_t);
		CTL_M2_M4_GET("stats.arenas.0.bins.0.curregs", i, j, &curregs,
		    size_t);
		CTL_M2_M4_GET("stats.arenas.0.bins.0.nrequests", i, j,
		    &nrequests, uint64_t);
		CTL_M2_M4_GET("stats.arenas.0.bins.0.nfills", i, j, &nfills,
		    uint64_t);
		CTL_M2_M4_GET("stats.arenas.0.bins.0.nflushes", i, j, &nflushes,
		    uint64_t);
		CTL_M2_M4_GET("stats.arenas.0.bins.0.nreslabs", i, j, &nreslabs,
		    uint64_t);
		CTL_M2_M4_GET("stats.arenas.0.bins.0.curslabs", i, j, &curslabs,
		    size_t);

		if (mutex) {
			mutex_stats_read_arena_bin(i, j, col_mutex64,
			    col_mutex32);
		}

		emitter_json_arr_obj_begin(emitter);
		emitter_json_kv(emitter, "nmalloc", emitter_type_uint64,
		    &nmalloc);
		emitter_json_kv(emitter, "ndalloc", emitter_type_uint64,
		    &ndalloc);
		emitter_json_kv(emitter, "curregs", emitter_type_size,
		    &curregs);
		emitter_json_kv(emitter, "nrequests", emitter_type_uint64,
		    &nrequests);
		emitter_json_kv(emitter, "nfills", emitter_type_uint64,
		    &nfills);
		emitter_json_kv(emitter, "nflushes", emitter_type_uint64,
		    &nflushes);
		emitter_json_kv(emitter, "nreslabs", emitter_type_uint64,
		    &nreslabs);
		emitter_json_kv(emitter, "curslabs", emitter_type_size,
		    &curslabs);
		if (mutex) {
			emitter_json_dict_begin(emitter, "mutex");
			mutex_stats_emit(emitter, NULL, col_mutex64,
			    col_mutex32);
			emitter_json_dict_end(emitter);
		}
		emitter_json_arr_obj_end(emitter);

		size_t availregs = nregs * curslabs;
		char util[6];
		if (get_rate_str((uint64_t)curregs, (uint64_t)availregs, util))
		{
			if (availregs == 0) {
				malloc_snprintf(util, sizeof(util), "1");
			} else if (curregs > availregs) {
				/*
				 * Race detected: the counters were read in
				 * separate mallctl calls and concurrent
				 * operations happened in between.  In this case
				 * no meaningful utilization can be computed.
				 */
				malloc_snprintf(util, sizeof(util), " race");
			} else {
				not_reached();
			}
		}

		col_size.size_val = reg_size;
		col_ind.unsigned_val = j;
		col_allocated.size_val = curregs * reg_size;
		col_nmalloc.uint64_val = nmalloc;
		col_ndalloc.uint64_val = ndalloc;
		col_nrequests.uint64_val = nrequests;
		col_curregs.size_val = curregs;
		col_curslabs.size_val = curslabs;
		col_regs.unsigned_val = nregs;
		col_pgs.size_val = slab_size / page;
		col_util.str_val = util;
		col_nfills.uint64_val = nfills;
		col_nflushes.uint64_val = nflushes;
		col_nslabs.uint64_val = nslabs;
		col_nreslabs.uint64_val = nreslabs;

		/*
		 * Note that mutex columns were initialized above, if mutex ==
		 * true.
		 */

		emitter_table_row(emitter, &row);
	}
	emitter_json_arr_end(emitter); /* Close "bins". */

	if (in_gap) {
		emitter_table_printf(emitter, "                     ---\n");
	}
}
