static void
mutex_prof_data_init(mutex_prof_data_t *data) {
	memset(data, 0, sizeof(mutex_prof_data_t));
	nstime_init(&data->max_wait_time, 0);
	nstime_init(&data->tot_wait_time, 0);
	data->prev_owner = NULL;
}
