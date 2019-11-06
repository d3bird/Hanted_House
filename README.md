# haunted_House


This is my interpretation of a haunted house



controls:

 w: moves forward
 s: moves backwards
 a: strafe right
 d: strafe left

 space-bar: moves up
 e: moves down
 f: interact
 r: start/stop rotating (for the model viewer only)
 q: quits

moving the mouse will move the camera to look at different things

right click brings ups a menu that allows the user to view the different
furniture models

Goal for each room is to find the object that does not grow dim when you
approach it. When you get close the object, press the interact key to tag 
the object and open up the next room. A wall will disappear to show the 
entrance to the next room.

I have a simple AI that makes a couple chairs fly around the second room 

the puzzle in each room is the same; however the amount of other objects and distractions 
make it harder to find the one piece that stands out.

There is also collision detection for the first two rooms and part of the third room.
You can go though the walls of the room.

Interactive objects that open the next room. There objects that can detect when the 
player interacts with them 

coolness points:

-Built in Model Viewer-
if you right click with the mouse you can select a model. The program will then show
one of three furniture models. It will be rotating by default it can be stopped/started 
by pressing r

-models-
I am really proud of how the models for the different furniture turned out.

-dynamic lighting-
There is dynamic lighting on the different piece of furniture based on how far away 
they are from the player. The close the player gets the darker the will become unless it 
the special one that unlocks the next room.

-dynamic resizing-
The window can be resized to any dimentions and it will still work fine
