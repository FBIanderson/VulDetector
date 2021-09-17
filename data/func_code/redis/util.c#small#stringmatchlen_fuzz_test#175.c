int stringmatchlen_fuzz_test(void) {
    char str[32];
    char pat[32];
    int cycles = 10000000;
    int total_matches = 0;
    while(cycles--) {
        int strlen = rand() % sizeof(str);
        int patlen = rand() % sizeof(pat);
        for (int j = 0; j < strlen; j++) str[j] = rand() % 128;
        for (int j = 0; j < patlen; j++) pat[j] = rand() % 128;
        total_matches += stringmatchlen(pat, patlen, str, strlen, 0);
    }
    return total_matches;
}
