static void
stats_arena_print(emitter_t *emitter, unsigned i, bool bins, bool large,
    bool mutex) {
	unsigned nthreads;
	const char *dss;
	ssize_t dirty_decay_ms, muzzy_decay_ms;
	size_t page, pactive, pdirty, pmuzzy, mapped, retained;
	size_t base, internal, resident, metadata_thp;
	uint64_t dirty_npurge, dirty_nmadvise, dirty_purged;
	uint64_t muzzy_npurge, muzzy_nmadvise, muzzy_purged;
	size_t small_allocated;
	uint64_t small_nmalloc, small_ndalloc, small_nrequests;
	size_t large_allocated;
	uint64_t large_nmalloc, large_ndalloc, large_nrequests;
	size_t tcache_bytes;
	uint64_t uptime;

	CTL_GET("arenas.page", &page, size_t);

	CTL_M2_GET("stats.arenas.0.nthreads", i, &nthreads, unsigned);
	emitter_kv(emitter, "nthreads", "assigned threads",
	    emitter_type_unsigned, &nthreads);

	CTL_M2_GET("stats.arenas.0.uptime", i, &uptime, uint64_t);
	emitter_kv(emitter, "uptime_ns", "uptime", emitter_type_uint64,
	    &uptime);

	CTL_M2_GET("stats.arenas.0.dss", i, &dss, const char *);
	emitter_kv(emitter, "dss", "dss allocation precedence",
	    emitter_type_string, &dss);

	CTL_M2_GET("stats.arenas.0.dirty_decay_ms", i, &dirty_decay_ms,
	    ssize_t);
	CTL_M2_GET("stats.arenas.0.muzzy_decay_ms", i, &muzzy_decay_ms,
	    ssize_t);
	CTL_M2_GET("stats.arenas.0.pactive", i, &pactive, size_t);
	CTL_M2_GET("stats.arenas.0.pdirty", i, &pdirty, size_t);
	CTL_M2_GET("stats.arenas.0.pmuzzy", i, &pmuzzy, size_t);
	CTL_M2_GET("stats.arenas.0.dirty_npurge", i, &dirty_npurge, uint64_t);
	CTL_M2_GET("stats.arenas.0.dirty_nmadvise", i, &dirty_nmadvise,
	    uint64_t);
	CTL_M2_GET("stats.arenas.0.dirty_purged", i, &dirty_purged, uint64_t);
	CTL_M2_GET("stats.arenas.0.muzzy_npurge", i, &muzzy_npurge, uint64_t);
	CTL_M2_GET("stats.arenas.0.muzzy_nmadvise", i, &muzzy_nmadvise,
	    uint64_t);
	CTL_M2_GET("stats.arenas.0.muzzy_purged", i, &muzzy_purged, uint64_t);

	emitter_row_t decay_row;
	emitter_row_init(&decay_row);

	/* JSON-style emission. */
	emitter_json_kv(emitter, "dirty_decay_ms", emitter_type_ssize,
	    &dirty_decay_ms);
	emitter_json_kv(emitter, "muzzy_decay_ms", emitter_type_ssize,
	    &muzzy_decay_ms);

	emitter_json_kv(emitter, "pactive", emitter_type_size, &pactive);
	emitter_json_kv(emitter, "pdirty", emitter_type_size, &pdirty);
	emitter_json_kv(emitter, "pmuzzy", emitter_type_size, &pmuzzy);

	emitter_json_kv(emitter, "dirty_npurge", emitter_type_uint64,
	    &dirty_npurge);
	emitter_json_kv(emitter, "dirty_nmadvise", emitter_type_uint64,
	    &dirty_nmadvise);
	emitter_json_kv(emitter, "dirty_purged", emitter_type_uint64,
	    &dirty_purged);

	emitter_json_kv(emitter, "muzzy_npurge", emitter_type_uint64,
	    &muzzy_npurge);
	emitter_json_kv(emitter, "muzzy_nmadvise", emitter_type_uint64,
	    &muzzy_nmadvise);
	emitter_json_kv(emitter, "muzzy_purged", emitter_type_uint64,
	    &muzzy_purged);

	/* Table-style emission. */
	emitter_col_t decay_type;
	emitter_col_init(&decay_type, &decay_row);
	decay_type.justify = emitter_justify_right;
	decay_type.width = 9;
	decay_type.type = emitter_type_title;
	decay_type.str_val = "decaying:";

	emitter_col_t decay_time;
	emitter_col_init(&decay_time, &decay_row);
	decay_time.justify = emitter_justify_right;
	decay_time.width = 6;
	decay_time.type = emitter_type_title;
	decay_time.str_val = "time";

	emitter_col_t decay_npages;
	emitter_col_init(&decay_npages, &decay_row);
	decay_npages.justify = emitter_justify_right;
	decay_npages.width = 13;
	decay_npages.type = emitter_type_title;
	decay_npages.str_val = "npages";

	emitter_col_t decay_sweeps;
	emitter_col_init(&decay_sweeps, &decay_row);
	decay_sweeps.justify = emitter_justify_right;
	decay_sweeps.width = 13;
	decay_sweeps.type = emitter_type_title;
	decay_sweeps.str_val = "sweeps";

	emitter_col_t decay_madvises;
	emitter_col_init(&decay_madvises, &decay_row);
	decay_madvises.justify = emitter_justify_right;
	decay_madvises.width = 13;
	decay_madvises.type = emitter_type_title;
	decay_madvises.str_val = "madvises";

	emitter_col_t decay_purged;
	emitter_col_init(&decay_purged, &decay_row);
	decay_purged.justify = emitter_justify_right;
	decay_purged.width = 13;
	decay_purged.type = emitter_type_title;
	decay_purged.str_val = "purged";

	/* Title row. */
	emitter_table_row(emitter, &decay_row);

	/* Dirty row. */
	decay_type.str_val = "dirty:";

	if (dirty_decay_ms >= 0) {
		decay_time.type = emitter_type_ssize;
		decay_time.ssize_val = dirty_decay_ms;
	} else {
		decay_time.type = emitter_type_title;
		decay_time.str_val = "N/A";
	}

	decay_npages.type = emitter_type_size;
	decay_npages.size_val = pdirty;

	decay_sweeps.type = emitter_type_uint64;
	decay_sweeps.uint64_val = dirty_npurge;

	decay_madvises.type = emitter_type_uint64;
	decay_madvises.uint64_val = dirty_nmadvise;

	decay_purged.type = emitter_type_uint64;
	decay_purged.uint64_val = dirty_purged;

	emitter_table_row(emitter, &decay_row);

	/* Muzzy row. */
	decay_type.str_val = "muzzy:";

	if (muzzy_decay_ms >= 0) {
		decay_time.type = emitter_type_ssize;
		decay_time.ssize_val = muzzy_decay_ms;
	} else {
		decay_time.type = emitter_type_title;
		decay_time.str_val = "N/A";
	}

	decay_npages.type = emitter_type_size;
	decay_npages.size_val = pmuzzy;

	decay_sweeps.type = emitter_type_uint64;
	decay_sweeps.uint64_val = muzzy_npurge;

	decay_madvises.type = emitter_type_uint64;
	decay_madvises.uint64_val = muzzy_nmadvise;

	decay_purged.type = emitter_type_uint64;
	decay_purged.uint64_val = muzzy_purged;

	emitter_table_row(emitter, &decay_row);

	/* Small / large / total allocation counts. */
	emitter_row_t alloc_count_row;
	emitter_row_init(&alloc_count_row);

	emitter_col_t alloc_count_title;
	emitter_col_init(&alloc_count_title, &alloc_count_row);
	alloc_count_title.justify = emitter_justify_left;
	alloc_count_title.width = 25;
	alloc_count_title.type = emitter_type_title;
	alloc_count_title.str_val = "";

	emitter_col_t alloc_count_allocated;
	emitter_col_init(&alloc_count_allocated, &alloc_count_row);
	alloc_count_allocated.justify = emitter_justify_right;
	alloc_count_allocated.width = 12;
	alloc_count_allocated.type = emitter_type_title;
	alloc_count_allocated.str_val = "allocated";

	emitter_col_t alloc_count_nmalloc;
	emitter_col_init(&alloc_count_nmalloc, &alloc_count_row);
	alloc_count_nmalloc.justify = emitter_justify_right;
	alloc_count_nmalloc.width = 12;
	alloc_count_nmalloc.type = emitter_type_title;
	alloc_count_nmalloc.str_val = "nmalloc";

	emitter_col_t alloc_count_ndalloc;
	emitter_col_init(&alloc_count_ndalloc, &alloc_count_row);
	alloc_count_ndalloc.justify = emitter_justify_right;
	alloc_count_ndalloc.width = 12;
	alloc_count_ndalloc.type = emitter_type_title;
	alloc_count_ndalloc.str_val = "ndalloc";

	emitter_col_t alloc_count_nrequests;
	emitter_col_init(&alloc_count_nrequests, &alloc_count_row);
	alloc_count_nrequests.justify = emitter_justify_right;
	alloc_count_nrequests.width = 12;
	alloc_count_nrequests.type = emitter_type_title;
	alloc_count_nrequests.str_val = "nrequests";

	emitter_table_row(emitter, &alloc_count_row);

#define GET_AND_EMIT_ALLOC_STAT(small_or_large, name, valtype)		\
	CTL_M2_GET("stats.arenas.0." #small_or_large "." #name, i,	\
	    &small_or_large##_##name, valtype##_t);			\
	emitter_json_kv(emitter, #name, emitter_type_##valtype,		\
	    &small_or_large##_##name);					\
	alloc_count_##name.type = emitter_type_##valtype;		\
	alloc_count_##name.valtype##_val = small_or_large##_##name;

	emitter_json_dict_begin(emitter, "small");
	alloc_count_title.str_val = "small:";

	GET_AND_EMIT_ALLOC_STAT(small, allocated, size)
	GET_AND_EMIT_ALLOC_STAT(small, nmalloc, uint64)
	GET_AND_EMIT_ALLOC_STAT(small, ndalloc, uint64)
	GET_AND_EMIT_ALLOC_STAT(small, nrequests, uint64)

	emitter_table_row(emitter, &alloc_count_row);
	emitter_json_dict_end(emitter); /* Close "small". */

	emitter_json_dict_begin(emitter, "large");
	alloc_count_title.str_val = "large:";

	GET_AND_EMIT_ALLOC_STAT(large, allocated, size)
	GET_AND_EMIT_ALLOC_STAT(large, nmalloc, uint64)
	GET_AND_EMIT_ALLOC_STAT(large, ndalloc, uint64)
	GET_AND_EMIT_ALLOC_STAT(large, nrequests, uint64)

	emitter_table_row(emitter, &alloc_count_row);
	emitter_json_dict_end(emitter); /* Close "large". */

#undef GET_AND_EMIT_ALLOC_STAT

	/* Aggregated small + large stats are emitter only in table mode. */
	alloc_count_title.str_val = "total:";
	alloc_count_allocated.size_val = small_allocated + large_allocated;
	alloc_count_nmalloc.uint64_val = small_nmalloc + large_nmalloc;
	alloc_count_ndalloc.uint64_val = small_ndalloc + large_ndalloc;
	alloc_count_nrequests.uint64_val = small_nrequests + large_nrequests;
	emitter_table_row(emitter, &alloc_count_row);

	emitter_row_t mem_count_row;
	emitter_row_init(&mem_count_row);

	emitter_col_t mem_count_title;
	emitter_col_init(&mem_count_title, &mem_count_row);
	mem_count_title.justify = emitter_justify_left;
	mem_count_title.width = 25;
	mem_count_title.type = emitter_type_title;
	mem_count_title.str_val = "";

	emitter_col_t mem_count_val;
	emitter_col_init(&mem_count_val, &mem_count_row);
	mem_count_val.justify = emitter_justify_right;
	mem_count_val.width = 12;
	mem_count_val.type = emitter_type_title;
	mem_count_val.str_val = "";

	emitter_table_row(emitter, &mem_count_row);
	mem_count_val.type = emitter_type_size;

	/* Active count in bytes is emitted only in table mode. */
	mem_count_title.str_val = "active:";
	mem_count_val.size_val = pactive * page;
	emitter_table_row(emitter, &mem_count_row);

#define GET_AND_EMIT_MEM_STAT(stat)					\
	CTL_M2_GET("stats.arenas.0."#stat, i, &stat, size_t);		\
	emitter_json_kv(emitter, #stat, emitter_type_size, &stat);	\
	mem_count_title.str_val = #stat":";				\
	mem_count_val.size_val = stat;					\
	emitter_table_row(emitter, &mem_count_row);

	GET_AND_EMIT_MEM_STAT(mapped)
	GET_AND_EMIT_MEM_STAT(retained)
	GET_AND_EMIT_MEM_STAT(base)
	GET_AND_EMIT_MEM_STAT(internal)
	GET_AND_EMIT_MEM_STAT(metadata_thp)
	GET_AND_EMIT_MEM_STAT(tcache_bytes)
	GET_AND_EMIT_MEM_STAT(resident)
#undef GET_AND_EMIT_MEM_STAT

	if (mutex) {
		stats_arena_mutexes_print(emitter, i);
	}
	if (bins) {
		stats_arena_bins_print(emitter, mutex, i);
	}
	if (large) {
		stats_arena_lextents_print(emitter, i);
	}
}
