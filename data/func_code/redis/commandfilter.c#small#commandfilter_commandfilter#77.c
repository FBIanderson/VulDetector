void CommandFilter_CommandFilter(RedisModuleCommandFilterCtx *filter)
{
    if (in_log_command) return;  /* don't process our own RM_Call() from CommandFilter_LogCommand() */

    /* Fun manipulations:
     * - Remove @delme
     * - Replace @replaceme
     * - Append @insertbefore or @insertafter
     * - Prefix with Log command if @log encounterd
     */
    int log = 0;
    int pos = 0;
    while (pos < RedisModule_CommandFilterArgsCount(filter)) {
        const RedisModuleString *arg = RedisModule_CommandFilterArgGet(filter, pos);
        size_t arg_len;
        const char *arg_str = RedisModule_StringPtrLen(arg, &arg_len);

        if (arg_len == 6 && !memcmp(arg_str, "@delme", 6)) {
            RedisModule_CommandFilterArgDelete(filter, pos);
            continue;
        } 
        if (arg_len == 10 && !memcmp(arg_str, "@replaceme", 10)) {
            RedisModule_CommandFilterArgReplace(filter, pos,
                    RedisModule_CreateString(NULL, "--replaced--", 12));
        } else if (arg_len == 13 && !memcmp(arg_str, "@insertbefore", 13)) {
            RedisModule_CommandFilterArgInsert(filter, pos,
                    RedisModule_CreateString(NULL, "--inserted-before--", 19));
            pos++;
        } else if (arg_len == 12 && !memcmp(arg_str, "@insertafter", 12)) {
            RedisModule_CommandFilterArgInsert(filter, pos + 1,
                    RedisModule_CreateString(NULL, "--inserted-after--", 18));
            pos++;
        } else if (arg_len == 4 && !memcmp(arg_str, "@log", 4)) {
            log = 1;
        }
        pos++;
    }

    if (log) RedisModule_CommandFilterArgInsert(filter, 0,
            RedisModule_CreateString(NULL, log_command_name, sizeof(log_command_name)-1));
}
