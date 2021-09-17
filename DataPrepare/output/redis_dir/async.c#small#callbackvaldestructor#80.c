static void callbackValDestructor(void *privdata, void *val) {
    ((void) privdata);
    free(val);
}
