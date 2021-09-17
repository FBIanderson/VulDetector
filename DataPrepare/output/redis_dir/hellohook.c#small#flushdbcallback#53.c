void flushdbCallback(RedisModuleCtx *ctx, RedisModuleEvent e, uint64_t sub, void *data)
{
    REDISMODULE_NOT_USED(ctx);
    REDISMODULE_NOT_USED(e);

    RedisModuleFlushInfo *fi = data;
    if (sub == REDISMODULE_SUBEVENT_FLUSHDB_START) {
        if (fi->dbnum != -1) {
            RedisModuleCallReply *reply;
            reply = RedisModule_Call(ctx,"DBSIZE","");
            long long numkeys = RedisModule_CallReplyInteger(reply);
            printf("FLUSHDB event of database %d started (%lld keys in DB)\n",
                fi->dbnum, numkeys);
            RedisModule_FreeCallReply(reply);
        } else {
            printf("FLUSHALL event started\n");
        }
    } else {
        if (fi->dbnum != -1) {
            printf("FLUSHDB event of database %d ended\n",fi->dbnum);
        } else {
            printf("FLUSHALL event ended\n");
        }
    }
}
