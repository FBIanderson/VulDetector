static const char *
log_var_extract_segment(const char* segment_begin) {
	const char *end;
	for (end = segment_begin; *end != '\0' && *end != '|'; end++) {
	}
	return end;
}
