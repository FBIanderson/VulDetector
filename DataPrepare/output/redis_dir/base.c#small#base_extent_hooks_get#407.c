extent_hooks_t *
base_extent_hooks_get(base_t *base) {
	return (extent_hooks_t *)atomic_load_p(&base->extent_hooks,
	    ATOMIC_ACQUIRE);
}
