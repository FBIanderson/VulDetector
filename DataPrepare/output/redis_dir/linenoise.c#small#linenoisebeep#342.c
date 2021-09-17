static void linenoiseBeep(void) {
    fprintf(stderr, "\x7");
    fflush(stderr);
}
