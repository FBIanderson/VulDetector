static int json_destroy_config(lua_State *l)
{
    json_config_t *cfg;

    cfg = lua_touserdata(l, 1);
    if (cfg)
        strbuf_free(&cfg->encode_buf);
    cfg = NULL;

    return 0;
}
