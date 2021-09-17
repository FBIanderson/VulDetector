void HelloBlock_Disconnected(RedisModuleCtx *ctx, RedisModuleBlockedClient *bc) {
    RedisModule_Log(ctx,"warning","Blocked client %p disconnected!",
        (void*)bc);

    /* Here you should cleanup your state / threads, and if possible
     * call RedisModule_UnblockClient(), or notify the thread that will
     * call the function ASAP. */
}
