static bool
extent_can_coalesce(arena_t *arena, extents_t *extents, const extent_t *inner,
    const extent_t *outer) {
	assert(extent_arena_get(inner) == arena);
	if (extent_arena_get(outer) != arena) {
		return false;
	}

	assert(extent_state_get(inner) == extent_state_active);
	if (extent_state_get(outer) != extents->state) {
		return false;
	}

	if (extent_committed_get(inner) != extent_committed_get(outer)) {
		return false;
	}

	return true;
}
