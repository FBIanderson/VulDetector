static void *
thd_start(void *varg) {
	thd_start_arg_t *arg = (thd_start_arg_t *)varg;
	unsigned i;

	for (i = 0; i < NINCRS; i++) {
		mtx_lock(&arg->mtx);
		arg->x++;
		mtx_unlock(&arg->mtx);
	}
	return NULL;
}
