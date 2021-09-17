static void datatype_save(RedisModuleIO *io, void *value) {
    DataType *dt = (DataType *) value;
    RedisModule_SaveSigned(io, dt->intval);
    RedisModule_SaveString(io, dt->strval);
}
