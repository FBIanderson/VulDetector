static void json_append_array(lua_State *l, json_config_t *cfg, int current_depth,
                              strbuf_t *json, int array_length)
{
    int comma, i;

    strbuf_append_char(json, '[');

    comma = 0;
    for (i = 1; i <= array_length; i++) {
        if (comma)
            strbuf_append_char(json, ',');
        else
            comma = 1;

        lua_rawgeti(l, -1, i);
        json_append_data(l, cfg, current_depth, json);
        lua_pop(l, 1);
    }

    strbuf_append_char(json, ']');
}
