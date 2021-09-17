static int json_cfg_decode_invalid_numbers(lua_State *l)
{
    json_config_t *cfg = json_arg_init(l, 1);

    json_enum_option(l, 1, &cfg->decode_invalid_numbers, NULL, 1);

    json_verify_invalid_number_setting(l, &cfg->encode_invalid_numbers);

    return 1;
}
