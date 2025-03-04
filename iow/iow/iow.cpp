#include "rt_commons.h"
#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"



int main() {
    hittable_list world;

    auto material_ground = make_shared<lambertian>(color(0.4, 0.4, 0.55));
    auto material_center = make_shared<lambertian>(color(0.5, 0.45, 0.5));
    auto material_left = make_shared<metals>(color(0.9, 0.9, 0.9), 0.0);
    auto material_right = make_shared<metals>(color(0.9, 0.6, 0.1), 0.2);
    auto material_top = make_shared<metals>(color(0.9, 0.1, 0.2), 1.0);

    world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3(0.0, 0.0, -1.4), 0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.2), 0.5, material_left));
    world.add(make_shared<sphere>(point3(1.0, 0.0, -1.2), 0.5, material_right));
    world.add(make_shared<sphere>(point3(0.0, 1.0, -1.4), 0.3, material_top));



    camera cam;

    cam.aspect_ratio = 16.0 / 10.0;
    cam.im_width = 1600;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;
    cam.render(world);   
}
