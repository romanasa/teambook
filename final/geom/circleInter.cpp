pair<pt, pt> inter(pt O1, double r1, pt O2, double r2) {
	line m(O1, O2);
    double a = (r2 * r2 - r1 * r1 + d * d) / (2 * d);
    pt HO2(-m.b, m.a);
    HO2.to_dist(-a);
    point H(O2.x + HO2.x, O2.y + HO2.y);
    double h = sqrt(r2 * r2 - a * a);
    pt HP1(m.a, m.b);
    HP1.to_dist(h);
    pt P1(H.x + HP1.x, H.y + HP1.y);
    pt P2(H.x - HP1.x, H.y - HP1.y);
    return { P1, P2 };
}