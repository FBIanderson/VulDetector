static bool
log_var_matches_segment(const char *segment_begin, const char *segment_end,
    const char *log_var_begin, const char *log_var_end) {
	assert(segment_begin <= segment_end);
	assert(log_var_begin < log_var_end);

	ptrdiff_t segment_len = segment_end - segment_begin;
	ptrdiff_t log_var_len = log_var_end - log_var_begin;
	/* The special '.' segment matches everything. */
	if (segment_len == 1 && *segment_begin == '.') {
		return true;
	}
        if (segment_len == log_var_len) {
		return strncmp(segment_begin, log_var_begin, segment_len) == 0;
	} else if (segment_len < log_var_len) {
		return strncmp(segment_begin, log_var_begin, segment_len) == 0
		    && log_var_begin[segment_len] == '.';
        } else {
		return false;
	}
}
