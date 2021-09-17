void
malloc_tsd_cleanup_register(bool (*f)(void)) {
	assert(ncleanups < MALLOC_TSD_CLEANUPS_MAX);
	cleanups[ncleanups] = f;
	ncleanups++;
}
