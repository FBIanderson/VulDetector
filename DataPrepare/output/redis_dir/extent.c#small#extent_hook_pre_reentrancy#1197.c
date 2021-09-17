static void
extent_hook_pre_reentrancy(tsdn_t *tsdn, arena_t *arena) {
	tsd_t *tsd = tsdn_null(tsdn) ? tsd_fetch() : tsdn_tsd(tsdn);
	if (arena == arena_get(tsd_tsdn(tsd), 0, false)) {
		/*
		 * The only legitimate case of customized extent hooks for a0 is
		 * hooks with no allocation activities.  One such example is to
		 * place metadata on pre-allocated resources such as huge pages.
		 * In that case, rely on reentrancy_level checks to catch
		 * infinite recursions.
		 */
		pre_reentrancy(tsd, NULL);
	} else {
		pre_reentrancy(tsd, arena);
	}
}
