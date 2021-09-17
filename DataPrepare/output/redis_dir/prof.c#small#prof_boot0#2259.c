void
prof_boot0(void) {
	cassert(config_prof);

	memcpy(opt_prof_prefix, PROF_PREFIX_DEFAULT,
	    sizeof(PROF_PREFIX_DEFAULT));
}
