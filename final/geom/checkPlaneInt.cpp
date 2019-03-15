bool eq(dbl A, dbl B) { return abs(A - B) < 1e-9; }

bool ls(dbl A, dbl B) { return A < B && !eq(A, B); }

bool le(dbl A, dbl B) { return A < B || eq(A, B); }
struct pt {
    double x, y;
    pt(double x, double y) : x(x), y(y) {}
    pt() : pt(0, 0) {}
    double operator%(pt b) const { return x * b.x + y * b.y; }
    // Orintation of cross product and rotation DO matter in some algorithms
    double operator*(pt b) const { return x * b.y - y * b.x; }
    pt rotate() { return {y, -x}; }
    pt operator-(pt b) const { return {x - b.x, y - b.y}; }
    pt operator*(double t) const { return {x * t, y * t}; }
    pt operator+(pt b) const { return {x + b.x, y + b.y}; }
};

// Also this is half-plane struct
struct Line {
    pt O, v;

    // Ax + By + C <= 0
    Line(double A, double B, double C) {
        double l = sqrt(A * A + B * B);
        A /= l, B /= l, C /= l;
        O = pt(-A * C, -B * C);
        v = pt(-B, A);
    }
    //intersection with l
    pt operator*(Line l) {
        pt u = l.v.rotate();
        dbl t = (l.O - O) % u / (v % u);
        return O + v * t;
    }
    // Half-plane with point O on the border, everything to the LEFT of direction vector v is inside
    Line(pt O, pt v) : O(O), v(v) {}
};

const double EPS = 1e-14;
double INF = 1e50;

// vector<Line> lines{
//         Line(pt(0, 0), pt(0, -1)),
//         Line(pt(0, 0), pt(-1, 0)),
//         Line(pt(1, 1), pt(0, 1)),
// };
// checkPoint(lines, p) == true
// Intersection of lines is rectangle of set o
// Time complexity is O(n)
bool checkPoint(vector<Line> &l, pt &ret) {
    random_shuffle(l.begin(), l.end());
    pt A = l[0].O;
    for (int i = 1; i < l.size(); i++) {
        if (l[i].v * (A - l[i].O) < -EPS) {
            double mn = -INF;
            double mx = INF;
            for (int j = 0; j < i; j++) {
                if (abs(l[j].v * l[i].v) < EPS) {
                    if (l[j].v % l[i].v < 0 && (l[j].O - l[i].O) % l[i].v.rotate() < EPS) {
                        return false;
                    }
                } else {
                    pt u = l[j].v.rotate();
                    double proj = (l[j].O - l[i].O) % u / (l[i].v % u);
                    if (l[i].v * l[j].v > 0) {
                        mx = min(mx, proj);
                    } else {
                        mn = max(mn, proj);
                    }
                }
            }
            if (mn <= mx) {
                A = l[i].O + l[i].v * mn;
            } else {
                return false;
            }
        }
    }
    ret = A;
    return true;
}