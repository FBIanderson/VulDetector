int memtest_preserving_test(unsigned long *m, size_t bytes, int passes) {
    unsigned long backup[MEMTEST_BACKUP_WORDS];
    unsigned long *p = m;
    unsigned long *end = (unsigned long*) (((unsigned char*)m)+(bytes-MEMTEST_DECACHE_SIZE));
    size_t left = bytes;
    int errors = 0;

    if (bytes & 4095) return 0; /* Can't test across 4k page boundaries. */
    if (bytes < 4096*2) return 0; /* Can't test a single page. */

    while(left) {
        /* If we have to test a single final page, go back a single page
         * so that we can test two pages, since the code can't test a single
         * page but at least two. */
        if (left == 4096) {
            left += 4096;
            p -= 4096/sizeof(unsigned long);
        }

        int pass = 0;
        size_t len = (left > sizeof(backup)) ? sizeof(backup) : left;

        /* Always test an even number of pages. */
        if (len/4096 % 2) len -= 4096;

        memcpy(backup,p,len); /* Backup. */
        while(pass != passes) {
            pass++;
            errors += memtest_addressing(p,len,0);
            memtest_fill_random(p,len,0);
            if (bytes >= MEMTEST_DECACHE_SIZE) {
                memtest_compare_times(m,MEMTEST_DECACHE_SIZE,pass,1,0);
                memtest_compare_times(end,MEMTEST_DECACHE_SIZE,pass,1,0);
            }
            errors += memtest_compare_times(p,len,pass,4,0);
            memtest_fill_value(p,len,0,(unsigned long)-1,'S',0);
            if (bytes >= MEMTEST_DECACHE_SIZE) {
                memtest_compare_times(m,MEMTEST_DECACHE_SIZE,pass,1,0);
                memtest_compare_times(end,MEMTEST_DECACHE_SIZE,pass,1,0);
            }
            errors += memtest_compare_times(p,len,pass,4,0);
            memtest_fill_value(p,len,ULONG_ONEZERO,ULONG_ZEROONE,'C',0);
            if (bytes >= MEMTEST_DECACHE_SIZE) {
                memtest_compare_times(m,MEMTEST_DECACHE_SIZE,pass,1,0);
                memtest_compare_times(end,MEMTEST_DECACHE_SIZE,pass,1,0);
            }
            errors += memtest_compare_times(p,len,pass,4,0);
        }
        memcpy(p,backup,len); /* Restore. */
        left -= len;
        p += len/sizeof(unsigned long);
    }
    return errors;
}
