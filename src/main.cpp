#include <iostream>

#include "color.hpp"
#include "vec3.hpp"

int main()
{

    const int image_width = 256;
    const int image_height = 256;

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int y = image_height - 1; y >= 0; --y) {
        std::cerr << "\rScanlines remaining: " << y << " " << std::flush;
        for (int x = 0; x < image_width; ++x) {
            color pixel_color (double(x) / (image_width - 1),
                               double(y) / (image_height - 1),
                               0.25);
            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "All done!\n";

    return 0;
}