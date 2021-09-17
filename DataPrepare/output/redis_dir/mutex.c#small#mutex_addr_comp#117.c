static int
mutex_addr_comp(const witness_t *witness1, void *mutex1,
    const witness_t *witness2, void *mutex2) {
	assert(mutex1 != NULL);
	assert(mutex2 != NULL);
	uintptr_t mu1int = (uintptr_t)mutex1;
	uintptr_t mu2int = (uintptr_t)mutex2;
	if (mu1int < mu2int) {
		return -1;
	} else if (mu1int == mu2int) {
		return 0;
	} else {
		return 1;
	}
}
