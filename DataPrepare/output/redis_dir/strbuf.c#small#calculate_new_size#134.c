static int calculate_new_size(strbuf_t *s, int len)
{
    int reqsize, newsize;

    if (len <= 0)
        die("BUG: Invalid strbuf length requested");

    /* Ensure there is room for optional NULL termination */
    reqsize = len + 1;

    /* If the user has requested to shrink the buffer, do it exactly */
    if (s->size > reqsize)
        return reqsize;

    newsize = s->size;
    if (s->increment < 0) {
        /* Exponential sizing */
        while (newsize < reqsize)
            newsize *= -s->increment;
    } else {
        /* Linear sizing */
        newsize = ((newsize + s->increment - 1) / s->increment) * s->increment;
    }

    return newsize;
}
