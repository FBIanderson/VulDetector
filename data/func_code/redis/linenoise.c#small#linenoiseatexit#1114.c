static void linenoiseAtExit(void) {
    disableRawMode(STDIN_FILENO);
    freeHistory();
}
