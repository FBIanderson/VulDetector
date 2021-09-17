static void json_append_number(lua_State *l, json_config_t *cfg,
                               strbuf_t *json, int lindex)
{
    double num = lua_tonumber(l, lindex);
    int len;

    if (cfg->encode_invalid_numbers == 0) {
        /* Prevent encoding invalid numbers */
        if (isinf(num) || isnan(num))
            json_encode_exception(l, cfg, json, lindex, "must not be NaN or Inf");
    } else if (cfg->encode_invalid_numbers == 1) {
        /* Encode invalid numbers, but handle "nan" separately
         * since some platforms may encode as "-nan". */
        if (isnan(num)) {
            strbuf_append_mem(json, "nan", 3);
            return;
        }
    } else {
        /* Encode invalid numbers as "null" */
        if (isinf(num) || isnan(num)) {
            strbuf_append_mem(json, "null", 4);
            return;
        }
    }

    strbuf_ensure_empty_length(json, FPCONV_G_FMT_BUFSIZE);
    len = fpconv_g_fmt(strbuf_empty_ptr(json), num, cfg->encode_number_precision);
    strbuf_extend_length(json, len);
}
