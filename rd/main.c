#include "mr_read.h"
#include "rd_read.h"

int main()
{
	t_scene	scene;

	if (rd_read_scene("test.rt", &scene) == false)
	{
		return (1);
	}
	printf("ambient:\t");
	debug_rd_print_element_list(scene.ambient);
	printf("\n");
	printf("camera: \t");
	debug_rd_print_element_list(scene.camera);
	printf("\n");
	printf("lights: \t");
	debug_rd_print_element_array(scene.lights);
	printf("\n");
	printf("objects:\t");
	debug_rd_print_element_array(scene.objects);
	printf("\n");

	rd_destroy_scene(&scene);
}
