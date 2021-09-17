static bool
prof_dump_flush(bool propagate_err) {
	bool ret = false;
	ssize_t err;

	cassert(config_prof);

	err = malloc_write_fd(prof_dump_fd, prof_dump_buf, prof_dump_buf_end);
	if (err == -1) {
		if (!propagate_err) {
			malloc_write("<jemalloc>: write() failed during heap "
			    "profile flush\n");
			if (opt_abort) {
				abort();
			}
		}
		ret = true;
	}
	prof_dump_buf_end = 0;

	return ret;
}
