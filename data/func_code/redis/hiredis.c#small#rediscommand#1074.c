void *redisCommand(redisContext *c, const char *format, ...) {
    va_list ap;
    va_start(ap,format);
    void *reply = redisvCommand(c,format,ap);
    va_end(ap);
    return reply;
}
