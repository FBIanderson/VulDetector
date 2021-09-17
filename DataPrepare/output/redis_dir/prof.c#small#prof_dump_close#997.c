static bool
prof_dump_close(bool propagate_err) {
	bool ret;

	assert(prof_dump_fd != -1);
	ret = prof_dump_flush(propagate_err);
	close(prof_dump_fd);
	prof_dump_fd = -1;

	return ret;
}
