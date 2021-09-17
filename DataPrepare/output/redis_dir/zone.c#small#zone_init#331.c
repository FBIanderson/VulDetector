static void
zone_init(void) {
	jemalloc_zone.size = zone_size;
	jemalloc_zone.malloc = zone_malloc;
	jemalloc_zone.calloc = zone_calloc;
	jemalloc_zone.valloc = zone_valloc;
	jemalloc_zone.free = zone_free;
	jemalloc_zone.realloc = zone_realloc;
	jemalloc_zone.destroy = zone_destroy;
	jemalloc_zone.zone_name = "jemalloc_zone";
	jemalloc_zone.batch_malloc = zone_batch_malloc;
	jemalloc_zone.batch_free = zone_batch_free;
	jemalloc_zone.introspect = &jemalloc_zone_introspect;
	jemalloc_zone.version = 9;
	jemalloc_zone.memalign = zone_memalign;
	jemalloc_zone.free_definite_size = zone_free_definite_size;
	jemalloc_zone.pressure_relief = zone_pressure_relief;

	jemalloc_zone_introspect.enumerator = zone_enumerator;
	jemalloc_zone_introspect.good_size = zone_good_size;
	jemalloc_zone_introspect.check = zone_check;
	jemalloc_zone_introspect.print = zone_print;
	jemalloc_zone_introspect.log = zone_log;
	jemalloc_zone_introspect.force_lock = zone_force_lock;
	jemalloc_zone_introspect.force_unlock = zone_force_unlock;
	jemalloc_zone_introspect.statistics = zone_statistics;
	jemalloc_zone_introspect.zone_locked = zone_locked;
	jemalloc_zone_introspect.enable_discharge_checking = NULL;
	jemalloc_zone_introspect.disable_discharge_checking = NULL;
	jemalloc_zone_introspect.discharge = NULL;
#ifdef __BLOCKS__
	jemalloc_zone_introspect.enumerate_discharged_pointers = NULL;
#else
	jemalloc_zone_introspect.enumerate_unavailable_without_blocks = NULL;
#endif
	jemalloc_zone_introspect.reinit_lock = zone_reinit_lock;
}
