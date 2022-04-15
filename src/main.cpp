#include <iostream>

#include "rtweekend.hpp"

#include "color.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"

color ray_color(const ray& r, const hittable& world) {
    hit_record rec;
    if (world.hit(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + color(1,1,1));
    }
    
    vec3 unit_direction = unit_vector(r.direction());
    // Otherwise, paint background:
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + (t) * color(0.5, 0.7, 1.0);
}

int main()
{
    // Handle scene size based on aspect ratio instead of fixed values
    const auto aspect_ratio = 16.0 / 10.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    hittable_list world;
    world.add(std::make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(std::make_shared<sphere>(point3(0, -100.5, -1), 100));

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
            color pixel_color = ray_color(r, world);
            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "All done!\n";

    return 0;
}
