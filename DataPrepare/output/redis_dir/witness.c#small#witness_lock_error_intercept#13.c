static void
witness_lock_error_intercept(const witness_list_t *witnesses,
    const witness_t *witness) {
	saw_lock_error = true;
}
