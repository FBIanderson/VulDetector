static int json_cfg_encode_number_precision(lua_State *l)
{
    json_config_t *cfg = json_arg_init(l, 1);

    return json_integer_option(l, 1, &cfg->encode_number_precision, 1, 14);
}
