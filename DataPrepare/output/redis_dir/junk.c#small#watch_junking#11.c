static void
watch_junking(void *p) {
	watch_for_junking = p;
	saw_junking = false;
}
