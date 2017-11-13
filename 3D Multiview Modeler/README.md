*************************************
*       3D MULTIVIEW MODELER        *
*************************************

FILES:
- Camera
    Declarations and functions for the camera
    Compute the position
- Drawing
    Functions to load and add to the renderables an OBJ file
    Cube, Sphere, Scale space
- Keyboard
    Handle the keyboards events
    Moving forward, backward, left and right
    Escape the app
- main
    Main file 
    Declaration of the variables
    Initialize the main window
    Assign the callback functions
    Draw the frame (some cubes to create some walls and a floor)
- Mesh3D
    Class for a textured 3D object
    Implements the render function of the object
    Loads a PPM texture file and map it
    Computes the vertices (translation, rotation, scaling) to export the whole scene as an OBJ file
- Mouse
    Handle the mouse events
    Camera rotation
- PopUpMenu
    Create the menu and the different options
- Rendering
    Rendering functions for the different windows / sub-windows
    For each object in the renderables list, call its render function
    Creates the lighting in the main scene
- Vec3
    Header file containing simplify functions for 3D vectors / 3D points
- Vec2
    Header file containing simplify functions for 2D vectors
- Window
    Contains the resizing and other global functions
    Projections functions
    Text rendering
    Function generating the OBJ file


USAGE:
- make
    Compile the files and run the executable
- make clean
    Delete the object files, the executable and all the OBJ files


OUTPUT:
- main.exe
- possible .obj files if the user uses the "Export as OBJ file" function


FUNCTIONALITIES:
- Render a 3D scene and allow the user to:
    + move around using the keyboard arrows or the z,q,s,d keys (AZERTY keyboard, sorry ;-))
    + mouve the camera holding the left mouse button (only in the horizontal plane for now)
- See the historic of the user's actions
- See a top view and a first person view
- See a FPS counter in real time
- Create a menu, accessible with a right-click, allowing the user to:
    + switch between "fill" mode and "wireframe" mode
    + draw features (not yet implemented)
- Visualize textured OBJ files loaded into the scene, provided with a simple lighting system


KNOWN BUGS TO BE FIXED:
- Some unknown lag may appears after several rotation around the whole scene
    --> the potential problem might be that some rendering is made incorrectly
- The objects in the scene appear transparent
    --> an option might not have been enabled or (unlikely since we use Blender OBJ files) the normals are not correct


TODO:
- DONE ## Generate a OBJ file
- Generate an image using ray tracing of the current view
- DONE ## Add lights in the scene
- ALMOST DONE ## Draw features in the scene
- DONE ## Map textures on the objects
- Move the camera in 3D (instead of the current 2D plane)
- and even more...