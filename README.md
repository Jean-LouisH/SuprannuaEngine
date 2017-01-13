# Suprannua Engine

The Suprannua Engine is a superannuated, 2D platformer game engine codebase. Just For Fun. 

The highlight of the project is the engine folder, which is intended to be a reusable framework for compiling simple Windows games or easy to make visualisations for physics and algorithms. 

![ScreenShot](docs/Example Screenshots/Suprannua.png)

All game objects within the engine are represented as either regular polygons, rectangular blocks or text, with one 2D camera. Every object is classified as either a background, platform, entity, or foreground to make a distinction between how they interact with each other. E.g. Polygon entities can jump on block platforms. The objects also have a range of other properties like colour, number of edges, angular displacement, elasticity, mass and velocity. The exception to this are text objects which are represented only as heads up displays to be pinned to the camera or as entities to be pinned to world map. All objects have positional data on the x and y axes. These positions are plotted against a user defined game world size in metres.

As my first application based project, the hallmark and namesake of this engine is intended to be a superannuated design where the visuals are minimally done with legacy OpenGL, while the architecture is structured around a procedural runtime with the C programming language. For the sake of simplicity, audio and sprites are not supported in this project.

Diagram of the Suprannua Engine Architecture.
![ScreenShot](docs/Documentation/The Suprannua Engine Architecture Diagram.png)

The engine starts with WinMain(), or alternatively main(), as the container for global variables, and as the entry point to the Freeglut API. When Freeglut is initialised, the engine loops indefinitely within the glutMainLoop. This is where the OpenGL context is established where a 16:9 aspect ratio window of 75% of the detected display width is created. Callbacks for window dimension restoration and centring are also found here, as well as the functions for assigning keyboard inputs to a buffer and calling Suprannua's engine kernel. Freeglut also maintains the timer of the game loop.

At intervals of 1/60th of a second, the engine kernel is called. It then uses timing calculations and frame counting to determine simulation and application runtime. In addition to that, it directly calls the user's game code to structure game objects accordingly and facilitate the input and game logic scripts. The Suprannua systems are used in the engine kernel for geometry transform updates, updating kernel stats for game testing, and for 2D rendering.

Generally in the game code, inputs can be assigned for how the engine interprets key presses. However, the ESC key is hard coded for Freeglut to call the exit() function with the parameter "EXIT_SUCCESS". This will close the application.

Screenshot of the Suprannua Engine Standard Game Template
![ScreenShot](docs/Example Screenshots/The Suprannua Engine Standard Game Template.png)

Games or simulations are made by copying the standard game template global variables and functions; initGame(), runGame(), and readInput(). 

InitGame() is called on the first frame of the engine runtime and is ideally programmed with 2DCamera and Editor functions for setting up game objects and the placement and size of the camera. 

RunGame() is called for every frame unless the pause 'p' key is pressed. Within this function, all the game logic with system calls for Artificial Intelligence, Events, Physics, and Text updates are implemented. 2DCamera and Editor updates can even be made to introduce more changes to the object data structure and how the camera behaves. 

ReadInput() is called throughout the entire runtime of the engine as a script that mainly interprets the input buffer, but can also call system functions that might depend on the state of the input buffer (like decelerating the player when the user releases a key).