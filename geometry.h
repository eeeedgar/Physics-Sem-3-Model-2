#ifndef SEM_3_MODEL_2_GEOMETRY_H
#define SEM_3_MODEL_2_GEOMETRY_H

#include <vector>

struct Point
{
    double x, y, z;
};

struct Line
{
    Point a, b;
};

struct Circle
{
    Point center;
    double radius;
};

struct Circle_segment
{
    Circle circle;
    Point a, b, c;
};

struct Ray
{
    Point Start;
    Point Vector;
};

double line_section_length(Point a, Point b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double coefficient(Line line)
{
    return (line.a.y - line.b.y) / (line.a.x - line.b.x);
}

double line_b(Line line)
{
    return line.a.y - coefficient(line) * line.a.x;
}

Point intersection_point(Line line1, Line line2)
{
    double k1 = coefficient(line1);
    double k2 = coefficient(line2);
    double b1 = line_b(line1);
    double b2 = line_b(line2);

    double x_cross = (b2 - b1) / (k1 - k2);
    double y_cross = k1 * x_cross + b1;
    return Point { x_cross, y_cross };
}

bool does_line_segment_contains_point(Line line_section, Point point)
{
    // do for cross-point
    double ac = line_section_length(line_section.a, point);
    double bc = line_section_length(line_section.b, point);
    double ab = line_section_length(line_section.a, line_section.b);
    double possible_error = ab / 4;
    return (std::abs(ab - (ac + bc)) < possible_error);
}

bool does_ray_contains_point(Line ray, Point point)
{
    double ac = line_section_length(ray.a, point);
    double bc = line_section_length(ray.b, point);
    double ab = line_section_length(ray.a, ray.b);
    double possible_error = ab / 4;
    return (std::abs(ab - (ac + bc)) < possible_error || std::abs(ac - (ab + bc)) < possible_error);
}

std::vector<Point> line_and_circle_cross(Line line, Circle circle)
{
    double k = coefficient(line);
    double b = line_b(line);
    double eq_a = k * k + 1;
    double eq_b = 2 * (k * (b - circle.center.y) - circle.center.x);
    double eq_c = circle.center.x * circle.center.x + (b - circle.center.y) * (b - circle.center.y) - circle.radius * circle.radius;

    double disk = eq_b * eq_b - 4 * eq_a * eq_c;
    if (disk < 0)
    {
        return {};
    }
    else if (disk == 0)
    {
        double x_cross = eq_b / (2 * eq_a);
        double y_cross = k * x_cross + b;
        return { Point { x_cross, y_cross } };
    }
    else
    {
        double x_cross_1 = (eq_b + sqrt(disk)) / (2 * eq_a);
        double y_cross_1 = k * x_cross_1 + b;
        double x_cross_2 = (eq_b - sqrt(disk)) / (2 * eq_a);
        double y_cross_2 = k * x_cross_2 + b;
        return { Point { x_cross_1, y_cross_1 }, Point { x_cross_2, y_cross_2 } };
    }
}

bool does_circle_square_contain_point(Circle circle, Point point)
{
    double length =  line_section_length(circle.center, point);
    double possible_error = circle.radius / 1000;
    return length < circle.radius;
}

bool does_circle_segment_contain_point(Circle_segment circle_segment, Point point)
{
    // if circle contains this point
    Line ac = Line { circle_segment.a, circle_segment.c };
    Line bd = Line { circle_segment.b, point };

    Point cross = intersection_point(ac, bd);
    return line_section_length(circle_segment.circle.center, cross) > circle_segment.circle.radius;
}

#endif //SEM_3_MODEL_2_GEOMETRY_H
