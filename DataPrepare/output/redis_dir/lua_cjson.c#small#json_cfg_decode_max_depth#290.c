static int json_cfg_decode_max_depth(lua_State *l)
{
    json_config_t *cfg = json_arg_init(l, 1);

    return json_integer_option(l, 1, &cfg->decode_max_depth, 1, INT_MAX);
}
