static void datatype_free(void *value) {
    if (value) {
        DataType *dt = (DataType *) value;

        if (dt->strval) RedisModule_FreeString(NULL, dt->strval);
        RedisModule_Free(dt);
    }
}
