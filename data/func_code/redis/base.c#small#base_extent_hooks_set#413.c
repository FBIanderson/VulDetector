extent_hooks_t *
base_extent_hooks_set(base_t *base, extent_hooks_t *extent_hooks) {
	extent_hooks_t *old_extent_hooks = base_extent_hooks_get(base);
	atomic_store_p(&base->extent_hooks, extent_hooks, ATOMIC_RELEASE);
	return old_extent_hooks;
}
