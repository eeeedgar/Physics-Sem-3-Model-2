#ifndef SEM_3_MODEL_2_VECTOR_GEOMETRY_H
#define SEM_3_MODEL_2_VECTOR_GEOMETRY_H

using namespace std;

struct Vector
{
    double X, Y, Z;
};

struct GeneralEquationOfTheLine
{
    double A, B, C;
};

Vector vector_product(Vector a, Vector b)
{
    double z = a.X * b.Y - a.Y * b.X;
    Vector c { 0, 0,  z };
    return c;
}

Vector cross_point(GeneralEquationOfTheLine e1, GeneralEquationOfTheLine e2)
{
    cout << "e1: " << e1.A << " " << e1.B << " " << e1.C << "\n";
    cout << "e2: " << e2.A << " " << e2.B << " " << e2.C << "\n";
    double x_cross = (-e1.B * e2.C - e2.B * e1.C) / (e1.A * e2.B + e2.A * e1.B);
    double y_cross;
    if (e1.B != 0)
        y_cross = (e1.A * x_cross + e1.C) / e1.B;
    else
        y_cross = (e2.A * x_cross + e2.C) / e2.B;
    return Vector { x_cross, y_cross, 0 };
}


GeneralEquationOfTheLine get_general_line_equation(Vector m, Vector p)
{
    return GeneralEquationOfTheLine { p.Y, -p.X, p.X * m.Y - p.Y * m.X };
}

Vector get_symmetry(Vector p, Vector c, Vector a)
{
    Vector h { - a.Y, a.X, 0 };
    cout << "h: " << h.X << " " << h.Y << " " << h.Z << "\n";
    Vector cross = cross_point(get_general_line_equation(p, h), get_general_line_equation(c, a));
    cout << "cross: " << cross.X << " " << cross.Y << " " << cross.Z << "\n";
    Vector ph { cross.X - p.X, cross.Y - p.Y, 0 };
    cout << "ph: " << ph.X << " " << ph.Y << " " << ph.Z << "\n";
    Vector p1 { p.X + 2 * ph.X, p.Y + 2 * ph.Y, 0 };
    return p1;
}

#endif //SEM_3_MODEL_2_VECTOR_GEOMETRY_H
