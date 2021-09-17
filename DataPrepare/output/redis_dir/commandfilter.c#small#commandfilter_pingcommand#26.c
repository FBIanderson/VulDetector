int CommandFilter_PingCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
{
    (void) argc;
    (void) argv;

    RedisModuleCallReply *reply = RedisModule_Call(ctx, "ping", "c", "@log");
    if (reply) {
        RedisModule_ReplyWithCallReply(ctx, reply);
        RedisModule_FreeCallReply(reply);
    } else {
        RedisModule_ReplyWithSimpleString(ctx, "Unknown command or invalid arguments");
    }

    return REDISMODULE_OK;
}
