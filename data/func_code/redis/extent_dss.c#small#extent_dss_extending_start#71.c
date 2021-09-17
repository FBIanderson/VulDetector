static void
extent_dss_extending_start(void) {
	spin_t spinner = SPIN_INITIALIZER;
	while (true) {
		bool expected = false;
		if (atomic_compare_exchange_weak_b(&dss_extending, &expected,
		    true, ATOMIC_ACQ_REL, ATOMIC_RELAXED)) {
			break;
		}
		spin_adaptive(&spinner);
	}
}
