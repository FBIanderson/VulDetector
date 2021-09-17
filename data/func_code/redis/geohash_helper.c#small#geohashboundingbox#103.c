int geohashBoundingBox(double longitude, double latitude, double radius_meters,
                       double *bounds) {
    if (!bounds) return 0;

    bounds[0] = longitude - rad_deg(radius_meters/EARTH_RADIUS_IN_METERS/cos(deg_rad(latitude)));
    bounds[2] = longitude + rad_deg(radius_meters/EARTH_RADIUS_IN_METERS/cos(deg_rad(latitude)));
    bounds[1] = latitude - rad_deg(radius_meters/EARTH_RADIUS_IN_METERS);
    bounds[3] = latitude + rad_deg(radius_meters/EARTH_RADIUS_IN_METERS);
    return 1;
}
