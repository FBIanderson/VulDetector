int geohashDecodeToLongLatType(const GeoHashBits hash, double *xy) {
    GeoHashArea area = {{0}};
    if (!xy || !geohashDecodeType(hash, &area))
        return 0;
    return geohashDecodeAreaToLongLat(&area, xy);
}
