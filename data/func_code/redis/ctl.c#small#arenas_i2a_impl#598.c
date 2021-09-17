static unsigned
arenas_i2a_impl(size_t i, bool compat, bool validate) {
	unsigned a;

	switch (i) {
	case MALLCTL_ARENAS_ALL:
		a = 0;
		break;
	case MALLCTL_ARENAS_DESTROYED:
		a = 1;
		break;
	default:
		if (compat && i == ctl_arenas->narenas) {
			/*
			 * Provide deprecated backward compatibility for
			 * accessing the merged stats at index narenas rather
			 * than via MALLCTL_ARENAS_ALL.  This is scheduled for
			 * removal in 6.0.0.
			 */
			a = 0;
		} else if (validate && i >= ctl_arenas->narenas) {
			a = UINT_MAX;
		} else {
			/*
			 * This function should never be called for an index
			 * more than one past the range of indices that have
			 * initialized ctl data.
			 */
			assert(i < ctl_arenas->narenas || (!validate && i ==
			    ctl_arenas->narenas));
			a = (unsigned)i + 2;
		}
		break;
	}

	return a;
}
