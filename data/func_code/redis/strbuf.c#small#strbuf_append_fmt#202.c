void strbuf_append_fmt(strbuf_t *s, int len, const char *fmt, ...)
{
    va_list arg;
    int fmt_len;

    strbuf_ensure_empty_length(s, len);

    va_start(arg, fmt);
    fmt_len = vsnprintf(s->buf + s->length, len, fmt, arg);
    va_end(arg);

    if (fmt_len < 0)
        die("BUG: Unable to convert number");  /* This should never happen.. */

    s->length += fmt_len;
}
