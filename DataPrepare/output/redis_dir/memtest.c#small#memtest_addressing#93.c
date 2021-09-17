int memtest_addressing(unsigned long *l, size_t bytes, int interactive) {
    unsigned long words = bytes/sizeof(unsigned long);
    unsigned long j, *p;

    /* Fill */
    p = l;
    for (j = 0; j < words; j++) {
        *p = (unsigned long)p;
        p++;
        if ((j & 0xffff) == 0 && interactive)
            memtest_progress_step(j,words*2,'A');
    }
    /* Test */
    p = l;
    for (j = 0; j < words; j++) {
        if (*p != (unsigned long)p) {
            if (interactive) {
                printf("\n*** MEMORY ADDRESSING ERROR: %p contains %lu\n",
                    (void*) p, *p);
                exit(1);
            }
            return 1;
        }
        p++;
        if ((j & 0xffff) == 0 && interactive)
            memtest_progress_step(j+words,words*2,'A');
    }
    return 0;
}
