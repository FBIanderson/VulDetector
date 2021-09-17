char *redisBuildIdString(void) {
    static char buf[32];
    static int cached = 0;
    if (!cached) {
        snprintf(buf,sizeof(buf),"%llx",(unsigned long long) redisBuildId());
        cached = 1;
    }
    return buf;
}
