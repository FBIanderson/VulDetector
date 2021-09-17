static int json_cfg_encode_keep_buffer(lua_State *l)
{
    json_config_t *cfg = json_arg_init(l, 1);
    int old_value;

    old_value = cfg->encode_keep_buffer;

    json_enum_option(l, 1, &cfg->encode_keep_buffer, NULL, 1);

    /* Init / free the buffer if the setting has changed */
    if (old_value ^ cfg->encode_keep_buffer) {
        if (cfg->encode_keep_buffer)
            strbuf_init(&cfg->encode_buf, 0);
        else
            strbuf_free(&cfg->encode_buf);
    }

    return 1;
}
