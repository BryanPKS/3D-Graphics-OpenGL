# 3D-Graphics-OpenGL
3D objects, textures and shaders made from base libraries of OpenGL. Shapes and shaders made with algorithms in C++
This scence consists of 7 objects and a background.

# 2D Models
The trangle and square is made using their individual methods.
The circle and octagon are made using the ngon method. The ngon method takes an attribute of amount of sides n and draws the shape in the scene.
By giving the value of n a high value we see a shape with many sides.

# 3D Models
The cube is made with normal coordinates and a generated texture to made the texture on the cube faces.
The sphere is made using a desired radius and creating verticies slices iteratively until the desired shape is made.
The cylinder is made with a similar algorithm to the circle but at every vertex created we made individual squares along the circumference.

# Textures
Besides the cube, all textures have been coverted into PPM format.
With the PPM format all of the picture data corasponds to binary and is converted using the texture loader and pgma loader methods for each model.
The pgma loader is made using C basic code to utilize the fopen and fscanf methods. It works with both color and black and white images.

# Lighting
There are 3 Lighting sources in the Scene. All lights use diffusionand specular properties.
Light0 acts as the light at a finite point at a position of the top right.

Light1 is simular to light0 but at an infinite point in the middle. This creates a light source that makes the whole scene visible 
but still maintaining shader properties

Light 2 is a spot light that goes off in a cone coming from the upper left of the scene.
