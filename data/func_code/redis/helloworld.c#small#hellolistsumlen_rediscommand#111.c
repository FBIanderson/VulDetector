int HelloListSumLen_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
{
    if (argc != 2) return RedisModule_WrongArity(ctx);

    RedisModuleCallReply *reply;

    reply = RedisModule_Call(ctx,"LRANGE","sll",argv[1],(long long)0,(long long)-1);
    size_t strlen = 0;
    size_t items = RedisModule_CallReplyLength(reply);
    size_t j;
    for (j = 0; j < items; j++) {
        RedisModuleCallReply *ele = RedisModule_CallReplyArrayElement(reply,j);
        strlen += RedisModule_CallReplyLength(ele);
    }
    RedisModule_FreeCallReply(reply);
    RedisModule_ReplyWithLongLong(ctx,strlen);
    return REDISMODULE_OK;
}
