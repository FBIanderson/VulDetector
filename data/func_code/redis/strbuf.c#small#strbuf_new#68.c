strbuf_t *strbuf_new(int len)
{
    strbuf_t *s;

    s = malloc(sizeof(strbuf_t));
    if (!s)
        die("Out of memory");

    strbuf_init(s, len);

    /* Dynamic strbuf allocation / deallocation */
    s->dynamic = 1;

    return s;
}
