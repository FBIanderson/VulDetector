static bool
prof_dump_maps(bool propagate_err) {
	bool ret;
	int mfd;

	cassert(config_prof);
#ifdef __FreeBSD__
	mfd = prof_open_maps("/proc/curproc/map");
#elif defined(_WIN32)
	mfd = -1; // Not implemented
#else
	{
		int pid = prof_getpid();

		mfd = prof_open_maps("/proc/%d/task/%d/maps", pid, pid);
		if (mfd == -1) {
			mfd = prof_open_maps("/proc/%d/maps", pid);
		}
	}
#endif
	if (mfd != -1) {
		ssize_t nread;

		if (prof_dump_write(propagate_err, "\nMAPPED_LIBRARIES:\n") &&
		    propagate_err) {
			ret = true;
			goto label_return;
		}
		nread = 0;
		do {
			prof_dump_buf_end += nread;
			if (prof_dump_buf_end == PROF_DUMP_BUFSIZE) {
				/* Make space in prof_dump_buf before read(). */
				if (prof_dump_flush(propagate_err) &&
				    propagate_err) {
					ret = true;
					goto label_return;
				}
			}
			nread = malloc_read_fd(mfd,
			    &prof_dump_buf[prof_dump_buf_end], PROF_DUMP_BUFSIZE
			    - prof_dump_buf_end);
		} while (nread > 0);
	} else {
		ret = true;
		goto label_return;
	}

	ret = false;
label_return:
	if (mfd != -1) {
		close(mfd);
	}
	return ret;
}
