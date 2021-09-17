static void *datatype_load(RedisModuleIO *io, int encver) {
    (void) encver;

    int intval = RedisModule_LoadSigned(io);
    if (RedisModule_IsIOError(io)) return NULL;

    RedisModuleString *strval = RedisModule_LoadString(io);
    if (RedisModule_IsIOError(io)) return NULL;

    DataType *dt = (DataType *) RedisModule_Alloc(sizeof(DataType));
    dt->intval = intval;
    dt->strval = strval;
    return dt;
}
