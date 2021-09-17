static int
prof_dump_open_impl(bool propagate_err, const char *filename) {
	int fd;

	fd = creat(filename, 0644);
	if (fd == -1 && !propagate_err) {
		malloc_printf("<jemalloc>: creat(\"%s\"), 0644) failed\n",
		    filename);
		if (opt_abort) {
			abort();
		}
	}

	return fd;
}
