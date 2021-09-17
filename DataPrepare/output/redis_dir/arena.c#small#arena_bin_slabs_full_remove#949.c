static void
arena_bin_slabs_full_remove(arena_t *arena, bin_t *bin, extent_t *slab) {
	if (arena_is_auto(arena)) {
		return;
	}
	extent_list_remove(&bin->slabs_full, slab);
}
