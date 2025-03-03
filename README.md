# FDF
The project is about creating a simple wireframe model representation of a
3D land-scape by linking various points.  
## Details
The coordinates (x, y, z) of the landscape are stored in a .fdf file passed as a parameter to
your program.

Here is an example of input file:

<img src="https://github.com/user-attachments/assets/054477f6-d381-4d2f-a228-506ac17c8980" width="700">

Each number represents a point in space:
- The horizontal position corresponds to its axis.
- The vertical position corresponds to its ordinate.
- The value corresponds to its altitude.

Executing program using the example file should render a landscape similar to:

<img src="https://github.com/user-attachments/assets/74156c2e-d153-45f0-bb7d-08ef05b535b4" width="700">

Program displays the image in a window, and management of the window should remain smooth 
(changing to another window, minimizing, and so forth).

Pressing ESC or clicking on the cross on the window’s frame closes the window and quits
the program in a clean way.

FDF uses the images of the MLX42 library (https://github.com/codam-coding-college/MLX42),
which provides primitive tools to draw textures onto the window.

## How to run the program
## Results
<img src="https://github.com/user-attachments/assets/f45a1eb4-d821-486b-b1c4-a10f763d8fb3" width="700">










