# Zappy GUI

## Description
The Zappy GUI features a Core system and utilizes shared libraries for graphical display. It connects a Client, which sends and receives requests from a server, and uses the data for display purposes. The program is divided into five main parts:

1. **Core**: The central part that connects the other components.
2. **Client**: Handles communication with the server.
3. **Scene Manager**: Manages the display in the form of scenes (Loading & Game).
4. **Game Data**: Contains all information about the current game session.
5. **Graphics**: Responsible for displaying images and playing sounds.

## Features
- The display is divided into two sections: the game area and an overlay.
- The map allows users to move around and see what is happening.
- Clicking on tiles provides information in the overlay.
- The overlay displays global information.
- Pressing the 'M' key shows messages from AI.

## Architecture
The architecture of the project is modular and follows a component-based design. Here are the key components:

### Core
The `Core` class is the main entry point of the application. It initializes and runs the main program loop, handling the overall flow of the application.

### Graphical Library Loader
The `GraphicalLibraryLoader` is responsible for loading shared graphical libraries dynamically at runtime. This allows for flexibility and modularity in the graphical components used by the application.

- **LibraryObject**: Manages individual shared library objects.
- **LibraryLoader**: Handles loading and managing multiple shared library objects.

### Client
The client component handles network communication with the server. It sends requests and receives responses, which are then used to update the graphical display and game state.

#### Key Functions:
- **connectToServer()**: Connects the client to the server, handles initial communication, and exchanges welcome messages.
- **queueRequest()**: Queues a request to be sent to the server.
- **queueRequests()**: Queues multiple requests to be sent to the server.
- **send()**: Sends the queued requests to the server, handling timeouts and connection issues.
- **receive()**: Receives responses from the server and processes them.
- **disconnect()**: Disconnects the client from the server gracefully.
- **popResponse()**: Retrieves the latest response from the server.

### Scene Manager
The Scene Manager component is responsible for managing different scenes in the application, ensuring smooth transitions and proper rendering. The main scenes include the Loading scene and the Game scene.

#### Key Classes:
- **IScene**: An interface that defines the structure for different scenes.
- **Loading**: Manages the loading screen, showing loading progress and preparing the game environment.
- **Game**: Manages the main game screen, handling game logic and rendering the game state.

#### Loading Scene
The Loading scene is responsible for displaying the loading progress to the user. It prepares the game environment by loading necessary resources and displaying team names, map size, and other relevant information.

##### Key Functions:
- **initialize()**: Initializes resources such as music and sound effects.
- **update()**: Updates the loading text and manages the transition to the Game scene.
- **draw()**: Renders the loading text and other information on the screen.
- **onEnter()**: Executes actions when entering the Loading scene.
- **onExit()**: Executes actions when exiting the Loading scene.

#### Game Scene
The Game scene handles the main gameplay, rendering the game state and managing game logic. It loads textures and sounds, processes user input, and updates the game state.

##### Key Functions:
- **initialize()**: Loads game assets and initializes the game environment.
- **update()**: Updates the game state based on user input and server responses.
- **draw()**: Renders the game elements, including the map, players, and UI components.
- **onEnter()**: Executes actions when entering the Game scene.
- **onExit()**: Executes actions when exiting the Game scene.

### Game Data
The game data component stores and manages all the information related to the current game session. This includes player information, game state, and other relevant data.

### Graphics
The graphics component is responsible for rendering images and playing sounds. It interacts with the graphical libraries loaded by the `GraphicalLibraryLoader`.

#### Key Classes and Interfaces:
- **ILibrary**: Interface for the graphical library, providing access to textures, sounds, music, fonts, and display functions.
- **ITextureManager**: Manages textures used in the application.
- **ISoundManager**: Manages sound effects.
- **IMusicManager**: Manages background music.
- **IFontManager**: Manages fonts used for rendering text.
- **IDisplay**: Interface for the display, providing functions to draw textures, print text, and manage the display window.

#### SFML2d
The `SFML2d` class is an implementation of the `ILibrary` interface using the SFML library for 2D graphics rendering. It handles the window creation, drawing operations, and resource management.

##### Key Functions:
- **initialize()**: Initializes the SFML window and resources.
- **clear()**: Clears the display with a specified color.
- **draw()**: Draws textures to the display.
- **print()**: Prints text to the display using specified fonts and colors.
- **measure()**: Measures the size of a string when printed.
- **flush()**: Flushes the drawn content to the display.
- **_resizeWindow()**: Resizes the SFML window based on specified dimensions.