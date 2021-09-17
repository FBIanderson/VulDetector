static void
mutex_stats_init_cols(emitter_row_t *row, const char *table_name,
    emitter_col_t *name,
    emitter_col_t col_uint64_t[mutex_prof_num_uint64_t_counters],
    emitter_col_t col_uint32_t[mutex_prof_num_uint32_t_counters]) {
	mutex_prof_uint64_t_counter_ind_t k_uint64_t = 0;
	mutex_prof_uint32_t_counter_ind_t k_uint32_t = 0;

	emitter_col_t *col;

	if (name != NULL) {
		emitter_col_init(name, row);
		name->justify = emitter_justify_left;
		name->width = 21;
		name->type = emitter_type_title;
		name->str_val = table_name;
	}

#define WIDTH_uint32_t 12
#define WIDTH_uint64_t 16
#define OP(counter, counter_type, human)				\
	col = &col_##counter_type[k_##counter_type];			\
	++k_##counter_type;						\
	emitter_col_init(col, row);					\
	col->justify = emitter_justify_right;				\
	col->width = WIDTH_##counter_type;				\
	col->type = emitter_type_title;					\
	col->str_val = human;
	MUTEX_PROF_COUNTERS
#undef OP
#undef WIDTH_uint32_t
#undef WIDTH_uint64_t
}
