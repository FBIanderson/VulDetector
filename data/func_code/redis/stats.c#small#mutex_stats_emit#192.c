static void
mutex_stats_emit(emitter_t *emitter, emitter_row_t *row,
    emitter_col_t col_uint64_t[mutex_prof_num_uint64_t_counters],
    emitter_col_t col_uint32_t[mutex_prof_num_uint32_t_counters]) {
	if (row != NULL) {
		emitter_table_row(emitter, row);
	}

	mutex_prof_uint64_t_counter_ind_t k_uint64_t = 0;
	mutex_prof_uint32_t_counter_ind_t k_uint32_t = 0;

	emitter_col_t *col;

#define EMITTER_TYPE_uint32_t emitter_type_uint32
#define EMITTER_TYPE_uint64_t emitter_type_uint64
#define OP(counter, type, human)					\
	col = &col_##type[k_##type];						\
	++k_##type;							\
	emitter_json_kv(emitter, #counter, EMITTER_TYPE_##type,		\
	    (const void *)&col->bool_val);
	MUTEX_PROF_COUNTERS;
#undef OP
#undef EMITTER_TYPE_uint32_t
#undef EMITTER_TYPE_uint64_t
}
