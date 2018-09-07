#include "Scene.h"
Scene::Scene() {}

Scene::~Scene() {
    delete[] light_sources;
    delete[] Spheres;
    delete[] Triangles;
}

Scene::Scene(const char *s) {
    ifstream f_in;
    f_in.open(s);
    while (f_in.is_open()) {
        string buffer;
        double a, b, c, d, n, r, g, bl, ka, kd, ks, krg, ktg, mu, nn;
        while (f_in >> buffer) {
            if (buffer == "Camera") {
                f_in >> a >> b >> c;
                camera.setOrigin(a, b, c);
                f_in >> a >> b >> c;
                camera.setU(a, b, c);
                f_in >> a >> b >> c;
                camera.setV(a, b, c);
                f_in >> a >> b >> c;
                camera.setN(a, b, c);
                double M[4][4];
                M[0][0] = camera.u.x;
                M[0][1] = camera.u.y;
                M[0][2] = camera.u.z;
                M[0][3] = 0;
                M[1][0] = camera.v.x;
                M[1][1] = camera.v.y;
                M[1][2] = camera.v.z;
                M[1][3] = 0;
                M[2][0] = camera.n.x;
                M[2][1] = camera.n.y;
                M[2][2] = camera.n.z;
                M[2][3] = 0;
                M[3][0] = 0;
                M[3][1] = 0;
                M[3][2] = 0;
                M[3][3] = 1;
                VCStoWCS = Matrix(M);
            } else if (buffer == "Display") {
                f_in >> a >> b >> c;
                display.center.set(a, b, c);
                VCSOrigin.set(a, b, c);
                f_in >> a >> b >> c >> d;
                display.dimX = b - a;
                display.dimY = c - d;
                display.top_left_corner.set(-display.dimX / 2,
                                            +display.dimY / 2, 0.0);
            } else if (buffer == "Light") {
                f_in >> a >> b >> c >> d;
                ambient_light = a;
                bgr = b;
                bgg = c;
                bgb = d;
                display.bg.colorPixel(bgr, bgg, bgb);
                display.setBackground();
                f_in >> ln;
                double maxlight = ambient_light;
                light_sources = new light_source[ln];
                for (int i = 0; i < ln; i++) {
                    f_in >> a >> b >> c >> d;
                    maxlight += d;
                    light_sources[i] = (light_source(a, b, c, d));
                }
                ambient_light /= maxlight;
                for (int i = 0; i < ln; i++) {
                    light_sources[i].intensity /= maxlight;
                }
            } else if (buffer == "Spheres") {
                f_in >> sn;
                Spheres = new sphere[sn];
                for (int i = 0; i < sn; i++) {
                    double a1, a2, a3, a4, a5, a6, a7, a8, a9;
                    f_in >> a >> b >> c >> d >> r >> g >> bl >> ka >> kd >>
                        ks >> krg >> ktg >> mu >> nn;
                    f_in >> a1 >> a2 >> a3 >> a4 >> a5 >> a6 >> a7 >> a8 >> a9;
                    Spheres[i].set(a, b, c, d, r, g, bl, ka, kd, ks, krg, ktg,
                                   mu, nn, a1, a2, a3, a4, a5, a6, a7, a8, a9);
                }
            } else if (buffer == "Triangles") {
                double a1, b1, c1, a2, b2, c2;
                f_in >> tn;
                Triangles = new triangle[tn];
                for (int i = 0; i < tn; i++) {
                    f_in >> a >> b >> c >> a1 >> b1 >> c1 >> a2 >> b2 >> c2 >>
                        r >> g >> bl >> ka >> kd >> ks >> krg >> ktg >> mu >>
                        nn;
                    Triangles[i].set(a, b, c, a1, b1, c1, a2, b2, c2, r, g, bl,
                                     ka, kd, ks, krg, ktg, mu, nn);
                }
            }
        }
        f_in.close();
    }
}

double absolute(double t) {
    if (t < 0)
        return -t;
    else
        return t;
}

bool Scene::existRoot(const double &a, const double &b, const double &c,
                      double &x0, double &x1) {
    double discr = b * b - 4 * a * c;
    if (discr < 0) {
        return false;
    } else if (discr <= 0.00001) {
        x0 = x1 = -0.5 * b / a;
    } else {
        double q =
            (b > 0.00001) ? -0.5 * (b + sqrt(discr)) : -0.5 * (b - sqrt(discr));
        x0 = q / a;
        x1 = c / q;
    }
    return true;
}

bool Scene::RaySphereIntersect(Ray &ray, sphere &sphere, double &t,
                               Point &intersection) {
    Ray ray1 = Ray(sphere.trans.transform(ray.origin),
                   sphere.trans.transform(ray.direction));
    double a, b, c, t1, t2;
    Point temp;
    temp = ray.origin - sphere.center;
    Point tmpdir(ray.direction);
    a = (tmpdir * tmpdir);
    b = 2 * (tmpdir * temp);
    c = temp * temp - sphere.radius * sphere.radius;

    if (!existRoot(a, b, c, t1, t2)) {
        return false;
    } else {
        if (t1 > t2) {
            swap(t1, t2);
        }
        if (t1 <= 0.00001) {
            if (t2 <= 0.00001) {
                return false;
            } else {
                t = t2;
                tmpdir.Scale(t2);
                intersection = (ray.origin + tmpdir);
            }
        } else {
            t = t1;
            tmpdir.Scale(t1);
            intersection = (ray.origin + tmpdir);
        }
    }
    return true;
}

bool Scene::RayTriangleIntersect(Ray &ray, triangle &triangle, double &t,
                                 Point &intersection) {
    Point e1, e2, p, s, q;
    Point tmpdir(ray.direction);
    double a, f, u, v;
    // tmpdir.normalise();

    e1 = triangle.v2 - triangle.v1;
    e2 = triangle.v3 - triangle.v1;
    p = ray.direction ^ e2;
    a = e1 * p;

    if (a < 0.00001) {
        return false;
    }

    f = 1.0 / a;

    s = ray.origin - triangle.v1;
    u = (s * p) * f;
    if (u < 0.0 || u > 1.0) {
        return false;
    }

    q = s ^ e1;
    v = (ray.direction * q) * f;
    if (v < 0.0 || u + v > 1.0) {
        return false;
    }

    double t1 = (e2 * q) * f;
    if (t1 > 0.00001) {
        t = t1;
        // tmpdir.printPoint();
        tmpdir.Scale(t);
        // tmpdir.printPoint();
        intersection = ray.origin + tmpdir;
        return true;
    }
    return false;
}

bool Scene::recursiveRayTrace(Ray &ray, double refrac_index, bool recurse,
                              Pixel &outp, int depth) {
    Pixel p;
    Point intersection, minInt;
    double t = 0, minT = -1;
    int type, pos;
    for (int i = 0; i < sn; ++i) {
        if (RaySphereIntersect(ray, Spheres[i], t, intersection)) {
            if ((minT == -1 || minT > t) && ((int)t) != 0) {
                minT = t;
                type = 0;  // type of object 0 for sphere 1 for triangle
                pos = i;
                minInt = intersection;
            }
        }
    }
    for (int i = 0; i < tn; ++i) {
        if (RayTriangleIntersect(ray, Triangles[i], t, intersection)) {
            if ((minT == -1 || minT > t) && t > 0.000001) {
                minT = t;
                type = 1;  // type of object 0 for sphere 1 for triangle
                pos = i;
                minInt = intersection;
            }
        }
    }
    if (minT > 0 && recurse && depth >= 1) {
        double intense = 0.0;
        Point normal;
        if (type == 0) {
            intense += Spheres[pos].ka * ambient_light;
            normal = minInt - Spheres[pos].center;
            normal.normalise();
            if (ray.direction * normal > 0) {
                // cout << "Hulaaaaaaa \n";
                normal.Scale(-1);
            }
        } else {
            intense += Triangles[pos].ka * ambient_light;
            Point e1;
            e1 = Triangles[pos].v1 - Triangles[pos].v2;
            e1.normalise();
            normal = Triangles[pos].v3 - Triangles[pos].v2;
            normal.normalise();
            normal = normal ^ e1;
            if (ray.direction * normal > 0) {
                normal.Scale(-1);
            }
            normal.normalise();
        }
        for (int i = 0; i < ln; ++i) {
            Point tmpdir;
            tmpdir = light_sources[i].location - minInt;
            tmpdir.normalise();
            Ray tolighsources(minInt, tmpdir);
            Pixel pp;
            if (!recursiveRayTrace(tolighsources, 1.0, false, pp,
                                   depth)) {  // if no obstacle between light
                                              // source and intersection point
                if (type == 0) {
                    intense += Spheres[pos].kd * light_sources[i].intensity *
                               absolute(tmpdir * normal);
                    Point H;
                    H = tmpdir - ray.direction;
                    H.normalise();
                    intense += Spheres[pos].ks * light_sources[i].intensity *
                               absolute(pow((H * normal), Spheres[pos].n));
                } else {
                    intense += Triangles[pos].kd * light_sources[i].intensity *
                               absolute((tmpdir * normal));
                    Point H;
                    H = tmpdir - ray.direction;
                    H.normalise();
                    intense += Triangles[pos].ks * light_sources[i].intensity *
                               absolute(pow((H * normal), Triangles[pos].n));
                }
            }
        }
>>>>>>> 9ab2cc5... Code formatting

        Point tmpdir = ray.direction;
        tmpdir.Scale(-1);

        Point R = normal;  //  Reflection
        R.Scale(2 * (tmpdir * normal));
        R = R - tmpdir;
        R.normalise();
        Ray nRRay(minInt, R);
        Pixel Precref;
        bool r = recursiveRayTrace(nRRay, 1.0f, true, Precref, depth - 1);

        R = normal;  // Refraction
        tmpdir = ray.direction;
        double refrac2;
        if (type == 0)
            refrac2 = Spheres[pos].mu;
        else
            refrac2 = Triangles[pos].mu;

        double eta, c1, cs2;
        if (refrac_index == refrac2)
            eta = refrac_index;
        else
            eta = refrac_index / refrac2;

        c1 = R * tmpdir;
        cs2 = 1 - eta * eta * (1 - c1 * c1);

        Pixel Precrefr;
        if (cs2 >= 0) {
            tmpdir.Scale(eta);
            R.Scale(eta * c1 - sqrt(cs2));
            R = tmpdir + R;
            Ray nTRay(minInt, R);
            r = recursiveRayTrace(nTRay, eta, true, Precrefr, depth - 1);
        }

        if (type == 0) {
            p = Spheres[pos].color;
            p.Scale(intense);
            p.normalise();
            p.Scale(1 - Spheres[pos].krg - Spheres[pos].ktg);
            if (cs2 < 0) {
                Precref.Scale(Spheres[pos].krg + Spheres[pos].ktg);
                p = p + Precref;
            } else {
                Precref.Scale(Spheres[pos].krg);
                Precrefr.Scale(Spheres[pos].ktg);
                p = p + Precref + Precrefr;
            }

        } else {
            p = Triangles[pos].color;
            p.Scale(intense);
            p.normalise();
            p.Scale(1 - Triangles[pos].krg - Triangles[pos].ktg);
            if (cs2 < 0) {
                Precref.Scale(Triangles[pos].krg + Triangles[pos].ktg);
                p = p + Precref;
            } else {
                Precref.Scale(Triangles[pos].krg);
                Precrefr.Scale(Triangles[pos].ktg);
                p = p + Precref + Precrefr;
            }
        }

        p.normalise();
        outp = p;

        return true;
    } else if (!recurse && minT > 0) {
        return true;
    }
    return false;
}

void Scene::writeImage() {
    // VCStoWCS.print();
    Point eyeinWCS;
    eyeinWCS = VCStoWCS.transform(camera.origin) + VCSOrigin;
    // eyeinWCS.printPoint();
    Point x = display.top_left_corner;
    Point direction;
    // std::cout << floor(display.dimX)*factor1 << " " <<
    // floor(display.dimY)*factor2;
    for (int i = 0; i < floor(display.dimX) * factor1; i++) {
        for (int j = 0; j < floor(display.dimY) * factor2; j++) {
            direction = x - camera.origin;
            direction.normalise();
            direction = VCStoWCS.transform(direction);
            direction.normalise();
            Ray R(eyeinWCS, direction);
            Pixel P;
            if (recursiveRayTrace(R, 1.0, true, P, 5)) display.grid[i][j] = P;
            x = x + Point(0.0, -1.0 / factor2, 0.0);
        }
        x.y = display.top_left_corner.y;
        x = x + Point(1.0 / factor1, 0.0, 0.0);
    }
}

void Scene::printImage() {
    display.bitmap(display.dimX * factor1 / factor3,
                   display.dimY * factor2 / factor3, display.grid);
}
