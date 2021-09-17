void strbuf_free(strbuf_t *s)
{
    debug_stats(s);

    if (s->buf) {
        free(s->buf);
        s->buf = NULL;
    }
    if (s->dynamic)
        free(s);
}
