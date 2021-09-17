static const char *
test_status_string(test_status_t test_status) {
	switch (test_status) {
	case test_status_pass: return "pass";
	case test_status_skip: return "skip";
	case test_status_fail: return "fail";
	default: not_reached();
	}
}
