# CS529_project7

Your project submission must include a “README” file containing the following information:

· Course: CS529

· Project: Project 7

· Author: <Boyuan Hu>, <boyuan.hu>

· Project Title: Tile Map System 

· Project Description: Implement a Tile Map system which can read the serialized json data and render the tile map in game scene, and Implement the binary collision feature

#### **Necessary Features:**

· Create a new component for displaying a tile map**(✓)**

· Create a new class for storing the data associated with a tile map**(✓)**

· Create a new class for storing the data associated with a tile set**(✓)**

· Display a 2D tile map within a new or existing scene **(✓)**

#### **Additional Features:** (Choose two is enough)

multiple layers of tile maps.**(✓)**

· Implement binary collision detection sufficient for basic platforming (E.g. floor and walls)**(✓)**

· Implement binary collision detecting sufficient for intermediate platforming(E.g. ceilings, platforms, and/or slopes)**(Half✓)**

(ceilings ok, platform implemented but corner collision is not precise enough, slope not yet implemented)

~~tile map rule system (choice which tile sprite to show according to the adjacent tile value)~~

~~isometric tile map system( if I have time)~~ 

~~tile map batched rendering(if I have time)  NO~~

#### · Project Controls:

No need of additional Control buttons, I will add the tile map in the scene1 

**Run the project and you will see Tile map with binary collision in scene1,  you can use the direction buttons to control the monkey to jump to and stand on the tile map platform.** (or watch the video tilemap.mp4 in the folder)

o <Identify any and all keys, mouse controls, and controller controls necessary to evaluate the implemented features>

· Additional Comments (Optional): ~~I will try to be compatible with **Unity Tile map editor** (steal their tile map data to render the tile map in my project)~~

o 

· Development Log:

Add TileMap, TileMapData, TileSet class

Add JSON Data for tilemap entity, TileMapData, and TileSet

Implement tile map rendering effects in scene1.

Implement the logic to convert position from world space to tile space.

Implement the binary collision detection logic.

Implement the binary collision resolve logic.

Add four hot points for the character. 

Add sprite atlas offset logic and change tile map sprite texture.

Add another tile map layer



**· Estimated Hours:**

**25 hours**

#### **· Known Issues:**

o <>

~~If we don't have batch rendering, the draw call of rendering a tile map will be high~~

render order of different tiles?

~~the efficiency of binary collision~~

I am using 4 hot points, some times the collision at the corner area of tile platforms is not that precise. Maybe using 8 hot points can make it better.

If I use Sprite Atlas, and Frame Index to get the uv offset of the tile texture, sometimes the sprite has a "outline".(Like that image)

it might because the Sprite Atlas is slightly blured, or the uv calculation has a small bias? I 

![image-20251203181106168](C:\Users\21222\AppData\Roaming\Typora\typora-user-images\image-20251203181106168.png) 

 
