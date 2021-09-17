uint8_t log_incr(uint8_t counter) {
    if (counter == 255) return counter;
    double r = (double)rand()/RAND_MAX;
    double baseval = counter-COUNTER_INIT_VAL;
    if (baseval < 0) baseval = 0;
    double limit = 1.0/(baseval*10+1);
    if (r < limit) counter++;
    return counter;
}
