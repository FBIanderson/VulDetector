static void
zone_batch_free(struct _malloc_zone_t *zone, void **to_be_freed,
    unsigned num_to_be_freed) {
	unsigned i;

	for (i = 0; i < num_to_be_freed; i++) {
		zone_free(zone, to_be_freed[i]);
		to_be_freed[i] = NULL;
	}
}
