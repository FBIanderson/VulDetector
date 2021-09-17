static int json_cfg_encode_invalid_numbers(lua_State *l)
{
    static const char *options[] = { "off", "on", "null", NULL };
    json_config_t *cfg = json_arg_init(l, 1);

    json_enum_option(l, 1, &cfg->encode_invalid_numbers, options, 1);

    json_verify_invalid_number_setting(l, &cfg->encode_invalid_numbers);

    return 1;
}
