int memtest_compare(unsigned long *l, size_t bytes, int interactive) {
    unsigned long words = bytes/sizeof(unsigned long)/2;
    unsigned long w, *l1, *l2;

    assert((bytes & 4095) == 0);
    l1 = l;
    l2 = l1+words;
    for (w = 0; w < words; w++) {
        if (*l1 != *l2) {
            if (interactive) {
                printf("\n*** MEMORY ERROR DETECTED: %p != %p (%lu vs %lu)\n",
                    (void*)l1, (void*)l2, *l1, *l2);
                exit(1);
            }
            return 1;
        }
        l1 ++;
        l2 ++;
        if ((w & 0xffff) == 0 && interactive)
            memtest_progress_step(w,words,'=');
    }
    return 0;
}
