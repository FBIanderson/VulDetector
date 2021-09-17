void
malloc_mutex_prof_data_reset(tsdn_t *tsdn, malloc_mutex_t *mutex) {
	malloc_mutex_assert_owner(tsdn, mutex);
	mutex_prof_data_init(&mutex->prof_data);
}
