int HelloPushCall_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
{
    if (argc != 3) return RedisModule_WrongArity(ctx);

    RedisModuleCallReply *reply;

    reply = RedisModule_Call(ctx,"RPUSH","ss",argv[1],argv[2]);
    long long len = RedisModule_CallReplyInteger(reply);
    RedisModule_FreeCallReply(reply);
    RedisModule_ReplyWithLongLong(ctx,len);
    return REDISMODULE_OK;
}
