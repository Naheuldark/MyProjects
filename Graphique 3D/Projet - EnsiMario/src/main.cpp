#include "../include/Viewer.hpp"
#include "../include/log.hpp"

#include <sstream>

// forward declaration of scene building functions, in separate files
void initialize_snowman_scene(Viewer& viewer);
void initialize_tree_scene(Viewer& viewer);
void initialize_terrain(Viewer& viewer);
void initialize_skierman_scene(Viewer& viewer);
void initialize_panel_scene(Viewer& viewer);
void initialize_snow_scene(Viewer& viewer);
void initialize_airbag_scene(Viewer& viewer);
void initialize_collision_scene(Viewer& viewer);
void initialize_final_scene(Viewer& viewer);
void initialize_box_scene(Viewer& viewer);
void initialize_Pool_scene(Viewer& viewer);
void initialize_Air2_scene(Viewer& viewer);


int main(int argc, char* argv[])
{
    Viewer viewer(1280, 720);   // window size in pixels

    unsigned int scene_to_load = 66;

    for (unsigned int i = 1; i < argc; ++i) {
        std::istringstream tokenizer(std::string(argv[i]));
        tokenizer >> scene_to_load;
        if (tokenizer.fail()) {
            LOG(fatal, "unknown argument " << argv[i] << ". Please launch without argument or the number of the practical you want to load");
            exit(EXIT_FAILURE);
        }
    }

    switch (scene_to_load) {
        case 1:
            initialize_terrain(viewer);
            break;
        case 2:
            initialize_snowman_scene(viewer);
            break; 
        case 3:
            initialize_tree_scene(viewer);
            break;    
        case 4:
            initialize_skierman_scene(viewer);
            break;
        case 5:
            initialize_panel_scene(viewer);
            break;
        case 6:
            initialize_snow_scene(viewer);
            break;
        case 7:
            initialize_airbag_scene(viewer);
            break;
        case 8:
            initialize_collision_scene(viewer);
            break;
        case 9:
            initialize_box_scene(viewer);
            break; 
        case 10:
            initialize_Pool_scene(viewer);
            break;
        case 11:
            initialize_Air2_scene(viewer);
            break;
        case 66:
            initialize_final_scene(viewer);
            break;
    }

    while (viewer.isRunning()) {
        viewer.handleEvent();
        viewer.animate();
        viewer.draw();
        viewer.display();
    }

    return EXIT_SUCCESS;
}
