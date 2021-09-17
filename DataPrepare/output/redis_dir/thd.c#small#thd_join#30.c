void
thd_join(thd_t thd, void **ret) {
	pthread_join(thd, ret);
}
