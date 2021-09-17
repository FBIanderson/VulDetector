void HelloACL_UserChanged(uint64_t client_id, void *privdata) {
    REDISMODULE_NOT_USED(privdata);
    REDISMODULE_NOT_USED(client_id);
    global_auth_client_id = 0;
}
