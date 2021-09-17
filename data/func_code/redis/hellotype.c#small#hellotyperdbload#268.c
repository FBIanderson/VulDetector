void *HelloTypeRdbLoad(RedisModuleIO *rdb, int encver) {
    if (encver != 0) {
        /* RedisModule_Log("warning","Can't load data with version %d", encver);*/
        return NULL;
    }
    uint64_t elements = RedisModule_LoadUnsigned(rdb);
    struct HelloTypeObject *hto = createHelloTypeObject();
    while(elements--) {
        int64_t ele = RedisModule_LoadSigned(rdb);
        HelloTypeInsert(hto,ele);
    }
    return hto;
}
