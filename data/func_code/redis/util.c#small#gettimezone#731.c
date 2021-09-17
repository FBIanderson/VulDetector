unsigned long getTimeZone(void) {
#ifdef __linux__
    return timezone;
#else
    struct timeval tv;
    struct timezone tz;

    gettimeofday(&tv, &tz);

    return tz.tz_minuteswest * 60UL;
#endif
}
