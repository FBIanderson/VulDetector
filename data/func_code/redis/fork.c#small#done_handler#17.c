void done_handler(int exitcode, int bysignal, void *user_data) {
    child_pid = -1;
    exitted_with_code = exitcode;
    assert(user_data==(void*)0xdeadbeef);
    UNUSED(bysignal);
}
