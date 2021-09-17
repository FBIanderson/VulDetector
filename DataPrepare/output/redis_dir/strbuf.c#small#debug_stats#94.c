static inline void debug_stats(strbuf_t *s)
{
    if (s->debug) {
        fprintf(stderr, "strbuf(%lx) reallocs: %d, length: %d, size: %d\n",
                (long)s, s->reallocs, s->length, s->size);
    }
}
