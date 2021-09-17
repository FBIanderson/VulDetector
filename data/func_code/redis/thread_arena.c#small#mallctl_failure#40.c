static void
mallctl_failure(int err) {
	char buf[BUFERROR_BUF];

	buferror(err, buf, sizeof(buf));
	test_fail("Error in mallctl(): %s", buf);
}
