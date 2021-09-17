void strbuf_set_increment(strbuf_t *s, int increment)
{
    /* Increment > 0:  Linear buffer growth rate
     * Increment < -1: Exponential buffer growth rate */
    if (increment == 0 || increment == -1)
        die("BUG: Invalid string increment");

    s->increment = increment;
}
