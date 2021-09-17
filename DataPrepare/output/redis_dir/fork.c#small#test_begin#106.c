TEST_BEGIN(test_fork_multithreaded) {
#ifndef _WIN32
	/*
	 * We've seen bugs involving hanging on arenas_lock (though the same
	 * class of bugs can happen on any mutex).  The bugs are intermittent
	 * though, so we want to run the test multiple times.  Since we hold the
	 * arenas lock only early in the process lifetime, we can't just run
	 * this test in a loop (since, after all the arenas are initialized, we
	 * won't acquire arenas_lock any further).  We therefore repeat the test
	 * with multiple processes.
	 */
	for (int i = 0; i < 100; i++) {
		int pid = fork();
		if (pid == -1) {
			/* Error. */
			test_fail("Unexpected fork() failure,");
		} else if (pid == 0) {
			/* Child. */
			do_test_fork_multithreaded();
			_exit(0);
		} else {
			wait_for_child_exit(pid);
		}
	}
#else
	test_skip("fork(2) is irrelevant to Windows");
#endif
}
