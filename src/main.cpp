#include <iostream>

#include "color.hpp"
#include "ray.hpp"
#include "vec3.hpp"

bool hit_sphere(const point3& center, double radius, const ray& r) {
    // We're looking to solve (P(t) - C)(P(t) - C) = r^2
    // This expands to:
    //   b * b * t^2 + 2 * (A - C) * b  * t + (A - C) * (A - C) * r^2 = 0
    //
    // We can then use the determinant of the quadratric to check if the
    // ray hits the sphere.
    //
    // oc = (A - C)
    vec3 oc = r.origin() - center;
    // a = b * b
    auto a = dot(r.direction(), r.direction());
    // b = 2 * b * (A - C) = 2 * b * oc
    auto b = 2.0 * dot(oc, r.direction());
    // c = (A - C) * (A - C) - r^2 = oc * oc - r^2
    auto c = dot(oc, oc) - radius * radius;
    // \Delta = b^2 - 4 * a * c
    auto discriminant = b * b - 4.0 * a * c;
    return (discriminant > 0);
}

color ray_color(const ray& r) {
    if (hit_sphere(point3(0, 0, -1), 0.5, r)) {
        return color(1, 0, 0);
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + (t) * color(0.5, 0.7, 1.0);
}

int main()
{
    // Handle scene size based on aspect ratio instead of fixed values
    const auto aspect_ratio = 16.0 / 10.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // Set up camera parameters
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0.0, 0.0);
    auto vertical = vec3(0.0, viewport_height, 0.0);
    auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int y = image_height - 1; y >= 0; --y) {
        std::cerr << "\rScanlines remaining: " << y << " " << std::flush;
        for (int x = 0; x < image_width; ++x) {
            auto u = double(x) / (image_width - 1);
            auto v = double(y) / (image_height - 1);
            ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "All done!\n";

    return 0;
}