void *HelloBlock_ThreadMain(void *arg) {
    void **targ = arg;
    RedisModuleBlockedClient *bc = targ[0];
    long long delay = (unsigned long)targ[1];
    RedisModule_Free(targ);

    sleep(delay);
    int *r = RedisModule_Alloc(sizeof(int));
    *r = rand();
    RedisModule_UnblockClient(bc,r);
    return NULL;
}
