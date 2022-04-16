#include <iostream>

#include "rtweekend.hpp"

#include "camera.hpp"
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
    const int samples_per_pixel = 100;

    hittable_list world;
    world.add(std::make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(std::make_shared<sphere>(point3(0, -100.5, -1), 100));

    camera cam;

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int y = image_height - 1; y >= 0; --y) {
        std::cerr << "\rScanlines remaining: " << y << " " << std::flush;
        for (int x = 0; x < image_width; ++x) {
            color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (double(x) + random_double()) / (image_width - 1);
                auto v = (double(y) + random_double()) / (image_height - 1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world);
            }
        write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }

    std::cerr << "All done!\n";

    return 0;
}
