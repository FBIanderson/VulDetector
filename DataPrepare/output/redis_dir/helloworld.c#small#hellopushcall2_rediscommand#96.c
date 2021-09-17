int HelloPushCall2_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
{
    if (argc != 3) return RedisModule_WrongArity(ctx);

    RedisModuleCallReply *reply;

    reply = RedisModule_Call(ctx,"RPUSH","ss",argv[1],argv[2]);
    RedisModule_ReplyWithCallReply(ctx,reply);
    RedisModule_FreeCallReply(reply);
    return REDISMODULE_OK;
}
