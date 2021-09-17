static void
stats_arena_lextents_print(emitter_t *emitter, unsigned i) {
	unsigned nbins, nlextents, j;
	bool in_gap, in_gap_prev;

	CTL_GET("arenas.nbins", &nbins, unsigned);
	CTL_GET("arenas.nlextents", &nlextents, unsigned);

	emitter_row_t header_row;
	emitter_row_init(&header_row);
	emitter_row_t row;
	emitter_row_init(&row);

#define COL(name, left_or_right, col_width, etype)			\
	emitter_col_t header_##name;					\
	emitter_col_init(&header_##name, &header_row);			\
	header_##name.justify = emitter_justify_##left_or_right;	\
	header_##name.width = col_width;				\
	header_##name.type = emitter_type_title;			\
	header_##name.str_val = #name;					\
									\
	emitter_col_t col_##name;					\
	emitter_col_init(&col_##name, &row);				\
	col_##name.justify = emitter_justify_##left_or_right;		\
	col_##name.width = col_width;					\
	col_##name.type = emitter_type_##etype;

	COL(size, right, 20, size)
	COL(ind, right, 4, unsigned)
	COL(allocated, right, 13, size)
	COL(nmalloc, right, 13, uint64)
	COL(ndalloc, right, 13, uint64)
	COL(nrequests, right, 13, uint64)
	COL(curlextents, right, 13, size)
#undef COL

	/* As with bins, we label the large extents table. */
	header_size.width -= 6;
	emitter_table_printf(emitter, "large:");
	emitter_table_row(emitter, &header_row);
	emitter_json_arr_begin(emitter, "lextents");

	for (j = 0, in_gap = false; j < nlextents; j++) {
		uint64_t nmalloc, ndalloc, nrequests;
		size_t lextent_size, curlextents;

		CTL_M2_M4_GET("stats.arenas.0.lextents.0.nmalloc", i, j,
		    &nmalloc, uint64_t);
		CTL_M2_M4_GET("stats.arenas.0.lextents.0.ndalloc", i, j,
		    &ndalloc, uint64_t);
		CTL_M2_M4_GET("stats.arenas.0.lextents.0.nrequests", i, j,
		    &nrequests, uint64_t);
		in_gap_prev = in_gap;
		in_gap = (nrequests == 0);

		if (in_gap_prev && !in_gap) {
			emitter_table_printf(emitter,
			    "                     ---\n");
		}

		CTL_M2_GET("arenas.lextent.0.size", j, &lextent_size, size_t);
		CTL_M2_M4_GET("stats.arenas.0.lextents.0.curlextents", i, j,
		    &curlextents, size_t);

		emitter_json_arr_obj_begin(emitter);
		emitter_json_kv(emitter, "curlextents", emitter_type_size,
		    &curlextents);
		emitter_json_arr_obj_end(emitter);

		col_size.size_val = lextent_size;
		col_ind.unsigned_val = nbins + j;
		col_allocated.size_val = curlextents * lextent_size;
		col_nmalloc.uint64_val = nmalloc;
		col_ndalloc.uint64_val = ndalloc;
		col_nrequests.uint64_val = nrequests;
		col_curlextents.size_val = curlextents;

		if (!in_gap) {
			emitter_table_row(emitter, &row);
		}
	}
	emitter_json_arr_end(emitter); /* Close "lextents". */
	if (in_gap) {
		emitter_table_printf(emitter, "                     ---\n");
	}
}
