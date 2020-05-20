#include "..\include\game.h"

Game::Game(int w, int h) {
    if (!glfwInit()) {
        GFX_ERROR("GLFW failed to initialize");
    }
    gameWindow.create(w, h);
    GFX_INFO("glfw window created");

    if (!gladLoadGL()) {
        GFX_ERROR("glad init error.");
    }

    // glfwSetInputMode(myWindow.window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetInputMode(gameWindow.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(gameWindow.window, mouseCallback);

    // Defaults
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glLineWidth(3);              
}



void Game::startGame() {
    GFX_INFO("starting app...");
    
    MapLoader mapObjects;
    mapObjects.loadMap();
    //mapObjects.normalsGenerator(10, 10);
    
    Renderer renderer;


    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    do {
        //  DELTATIME FUNCTIONALITY 
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        //////////////////////////////////////////////////////

        gameWindow.setViewport();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



        //renderer.loadMap(mapObjects.getWallVector(), mapObjects.getPlayer());
        mapObjects.getPlayer()->movePlayer(&gameWindow, deltaTime);
        mapObjects.MVP();
        mapObjects.render();


        gameWindow.swapBuffers();         
        glfwPollEvents();               
    } while (!gameWindow.shouldClose());

    glfwTerminate();             
}
