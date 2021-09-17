int redisvAppendCommand(redisContext *c, const char *format, va_list ap) {
    char *cmd;
    int len;

    len = redisvFormatCommand(&cmd,format,ap);
    if (len == -1) {
        __redisSetError(c,REDIS_ERR_OOM,"Out of memory");
        return REDIS_ERR;
    } else if (len == -2) {
        __redisSetError(c,REDIS_ERR_OTHER,"Invalid format string");
        return REDIS_ERR;
    }

    if (__redisAppendCommand(c,cmd,len) != REDIS_OK) {
        free(cmd);
        return REDIS_ERR;
    }

    free(cmd);
    return REDIS_OK;
}
