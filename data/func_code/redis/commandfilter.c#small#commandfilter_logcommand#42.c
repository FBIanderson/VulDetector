int CommandFilter_LogCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
{
    RedisModuleString *s = RedisModule_CreateString(ctx, "", 0);

    int i;
    for (i = 1; i < argc; i++) {
        size_t arglen;
        const char *arg = RedisModule_StringPtrLen(argv[i], &arglen);

        if (i > 1) RedisModule_StringAppendBuffer(ctx, s, " ", 1);
        RedisModule_StringAppendBuffer(ctx, s, arg, arglen);
    }

    RedisModuleKey *log = RedisModule_OpenKey(ctx, log_key_name, REDISMODULE_WRITE|REDISMODULE_READ);
    RedisModule_ListPush(log, REDISMODULE_LIST_HEAD, s);
    RedisModule_CloseKey(log);
    RedisModule_FreeString(ctx, s);

    in_log_command = 1;

    size_t cmdlen;
    const char *cmdname = RedisModule_StringPtrLen(argv[1], &cmdlen);
    RedisModuleCallReply *reply = RedisModule_Call(ctx, cmdname, "v", &argv[2], argc - 2);
    if (reply) {
        RedisModule_ReplyWithCallReply(ctx, reply);
        RedisModule_FreeCallReply(reply);
    } else {
        RedisModule_ReplyWithSimpleString(ctx, "Unknown command or invalid arguments");
    }

    in_log_command = 0;

    return REDISMODULE_OK;
}
