static void
stats_arena_mutexes_print(emitter_t *emitter, unsigned arena_ind) {
	emitter_row_t row;
	emitter_col_t col_name;
	emitter_col_t col64[mutex_prof_num_uint64_t_counters];
	emitter_col_t col32[mutex_prof_num_uint32_t_counters];

	emitter_row_init(&row);
	mutex_stats_init_cols(&row, "", &col_name, col64, col32);

	emitter_json_dict_begin(emitter, "mutexes");
	emitter_table_row(emitter, &row);

	for (mutex_prof_arena_ind_t i = 0; i < mutex_prof_num_arena_mutexes;
	    i++) {
		const char *name = arena_mutex_names[i];
		emitter_json_dict_begin(emitter, name);
		mutex_stats_read_arena(arena_ind, i, name, &col_name, col64,
		    col32);
		mutex_stats_emit(emitter, &row, col64, col32);
		emitter_json_dict_end(emitter); /* Close the mutex dict. */
	}
	emitter_json_dict_end(emitter); /* End "mutexes". */
}
