#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"

class camera {
	public:
		double aspect_ratio = 1.0;
		int im_width = 800;
		int samples_per_pixel = 10;

		void render(const hittable& world) {
			initialize();

			std::cout << "P3\n" << im_width << ' ' << im_height << "\n255\n";

			for (int j = 0; j < im_height; j++)
			{
				std::clog << "\rScanlines remaining: " << (im_height - j) << ' ' << std::flush;
				for (int i = 0; i < im_width; i++)
				{
					color pixel_color(0, 0, 0);
					for (int sample = 0; sample < samples_per_pixel; sample++)
					{
						ray r = get_ray(i, j);
						pixel_color += ray_color(r, world);
					}
					write_color(std::cout, pixel_samples_scale * pixel_color);
				}
			}

			std::clog << "\rDone.\n";
		}

	private:
		int im_height;
		double pixel_samples_scale;
		point3 cam_center;
		point3 pixel00_loc;
		vec3 pixel_delta_u;
		vec3 pixel_delta_v;

		void initialize(){
			im_height = int(im_width / aspect_ratio);
			if (im_height < 1)
			{
				im_height = 1;
			}

			pixel_samples_scale = 1.0 / samples_per_pixel;

			auto focal_len = 1.0;
			auto viewp_height = 2.0;
			auto viewp_width = viewp_height * (double(im_width) / im_height);
			cam_center = point3(0, 0, 0);

			auto viewp_u = vec3(viewp_width, 0, 0);
			auto viewp_v = vec3(0, -viewp_height, 0);

			pixel_delta_u = viewp_u / im_width;
			pixel_delta_v = viewp_v / im_height;

			auto viewp_upper_left = cam_center - vec3(0, 0, focal_len) - (viewp_u / 2) - (viewp_v / 2);
			pixel00_loc = viewp_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
		}

		ray get_ray(int i, int j) const {
			auto offset = sample_square();
			auto pixel_sample = pixel00_loc + ((i + offset.x()) * pixel_delta_u) + ((j + offset.y()) * pixel_delta_v);
			
			auto ray_origin = cam_center;
			auto ray_direction = pixel_sample - ray_origin;
			
			return ray(ray_origin, ray_direction);
		}

		vec3 sample_square() const {
			return vec3(random_double() - 0.5, random_double() - 0.5, 0);
		}

		color ray_color(const ray& r, const hittable& world) const{
			hit_rec rec;
			if (world.hit(r, interval(0, infinity), rec)) {
				return 0.5 * (rec.normal + color(1, 1, 1));
			}

			vec3 unit_dir = unit_vector(r.direction());
			auto a = 0.5 * (unit_dir.y() + 1.0);
			return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
		}
};

#endif