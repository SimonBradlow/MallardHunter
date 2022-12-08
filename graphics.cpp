#include "graphics.h"
#include "rect.h"
#include "sprite.h"
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

GLdouble width, height;
const color skyBlue(77/255.0, 213/255.0, 240/255.0);
const color black(0, 0, 0);

vector<unique_ptr<Shape>> clouds;
vector<unique_ptr<Shape>> parallaxClouds;
Sprite bigCloud = initSprite("bigCloud.png");
Sprite smallCloud = initSprite("smallCloud.png");

Sprite duck;
Sprite duck1 = initSprite("duck1.png");
Sprite duck2 = initSprite("duck2.png");
Sprite duck3 = initSprite("duck3.png");
Sprite duckShot = initSprite("duckShot.png");
Sprite duckFalling = initSprite("duckFalling.png");
double duckDeltaX;
double duckDeltaY;
bool duckHit;
int duckFlap;

Sprite grass;
Sprite grassSprite = initSprite("grass.png");

int score;
Rect scoreUI;
int shots;
Sprite shotUI;
Sprite shotUISprite = initSprite("shotUI.png");
Sprite shot1;
Sprite shot2;
Sprite shot3;
Sprite shotSprite = initSprite("shotIcon.png");

Rect userHidden;
Rect user1;
Rect user2;

bool gameOver;
bool playAgain;
Sprite gameOverUI;
Sprite playAgainUI;
Sprite gameOverUISprite = initSprite("gameOver.png");
Sprite playAgainUISprite = initSprite("playAgain.png");

void initClouds() {
    clouds.clear();
    parallaxClouds.clear();
    // First cloud
    Sprite cloud1;
    cloud1.setScale(2);
    cloud1.setVec(smallCloud);
    cloud1.setAlpha(0.5);
    cloud1.setCenter(width/6, 75);
    clouds.push_back(make_unique<Sprite>(cloud1));
    // Second cloud
    Sprite cloud2;
    cloud2.setScale(2);
    cloud2.setVec(bigCloud);
    cloud2.setAlpha(0.5);
    cloud2.setCenter((width/6)*3, 105);
    clouds.push_back(make_unique<Sprite>(cloud2));
    // Third cloud
    Sprite cloud3;
    cloud3.setScale(2);
    cloud3.setVec(smallCloud);
    cloud3.setAlpha(0.5);
    cloud3.setCenter(((width/6)*5)+50, 125);
    clouds.push_back(make_unique<Sprite>(cloud3));
    // Fourth cloud
    Sprite cloud4;
    cloud4.setScale(3);
    cloud4.setVec(smallCloud);
    cloud4.setCenter((width/3), 50);
    parallaxClouds.push_back(make_unique<Sprite>(cloud4));
    // Fifth cloud
    Sprite cloud5;
    cloud5.setScale(3);
    cloud5.setVec(bigCloud);
    cloud5.setCenter(width, 80);
    parallaxClouds.push_back(make_unique<Sprite>(cloud5));
}

void initGrass() {
    grass.setScale(4);
    grass.setVec(grassSprite);
    grass.setCenter(width/2, height-64);
}

void initDuck() {
    duck.setScale(2);
    duck.setVec(duck1);
    duck.setCenter(width/2, height);
    duckDeltaX = (rand() % 6 - 3) + 0.5;
    duckDeltaY = -3;
    duckHit = false;
    duckFlap = 0;
}

void initUI() {
    score = 0;
    shots = 3;
    shotUI.setScale(3);
    shotUI.setVec(shotUISprite);
    shotUI.setCenter(54, height-38);
    shot1.setScale(3);
    shot1.setVec(shotSprite);
    shot1.setCenter(shotUI.getCenterX()-20, height-50);
    shot2.setScale(3);
    shot2.setVec(shotSprite);
    shot2.setCenter(shotUI.getCenterX(), height-50);
    shot3.setScale(3);
    shot3.setVec(shotSprite);
    shot3.setCenter(shotUI.getCenterX()+20, height-50);
    gameOverUI.setScale(3);
    gameOverUI.setVec(gameOverUISprite);
    gameOverUI.setAlpha(0.0);
    gameOverUI.setCenter(width/2, (height/2)-40);
    playAgainUI.setScale(2);
    playAgainUI.setVec(playAgainUISprite);
    playAgainUI.setAlpha(0.0);
    playAgainUI.setCenter(width / 2, (height / 2) + 40);
}

void initUser() {
    // Initialize the user to be a 20x20 white block
    // centered in the top left corner of the graphics window
    user1.setSize(20, 2);
    user1.setColor(black);
    user1.setCenter(0, 0);
    user2.setSize(2, 20);
    user2.setColor(black);
    user2.setCenter(0, 0);
    userHidden.setSize(20, 20);
    userHidden.setCenter(0, 0);
}

void init() {
    width = 512;
    height = 512;
    srand(time(nullptr));
    gameOver = false;
    playAgain = false;
    initClouds();
    initDuck();
    initGrass();
    initUI();
    initUser();
}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(skyBlue.red, skyBlue.green, skyBlue.blue, 1.0f);
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    // Tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width*2, height*2); // DO NOT CHANGE THIS LINE (unless you are running Catalina on Mac)

    // Do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION); // DO NOT CHANGE THIS LINE
    glLoadIdentity(); // DO NOT CHANGE THIS LINE
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f); // DO NOT CHANGE THIS LINE

    // Clear the color buffer with current clearing color
    glClear(GL_COLOR_BUFFER_BIT); // DO NOT CHANGE THIS LINE

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // DO NOT CHANGE THIS LINE

    // Enable alpha channel blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );

    /*
     * Draw here
     */
    for (unique_ptr<Shape> &s : clouds) {
        // #polymorphism
        s->draw();
    }
    for (unique_ptr<Shape> &s : parallaxClouds) {
        // #polymorphism
        s->draw();
    }

    duck.draw();

    grass.draw();

    //scoreUI.draw();
    shotUI.draw();
    if (shots > 0) {
        shot1.draw();
        if (shots > 1) {
            shot2.draw();
            if (shots > 2) {
                shot3.draw();
            }
        }
    }

    if (gameOver) {
        gameOverUI.draw();
        playAgainUI.draw();
    }

    user1.draw();
    user2.draw();

    glFlush();  // Render now
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // escape
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwTerminate();
        exit(0);
    }
    if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {
        if (playAgain) {
            gameOver = false;
            playAgain = false;
            score = 0;
            shots = 3;
            shotUI.setAlpha(1);
            gameOverUI.setAlpha(0);
            playAgainUI.setAlpha(0);
        }
    }
}

void cursor(GLFWwindow* window, double x, double y) {
    // Set the user's center point to be the coordinates
    // passed in as parameters to this function. This will make
    // the user block move with the mouse.
    glfwGetCursorPos(window, &x, &y);
    user1.setCenter(x, y);
    user2.setCenter(x, y);
    userHidden.setCenter(x, y);
}

void mouse(GLFWwindow* window, int button, int action, int mods) {
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        if (shots > 0){
            --shots;
            if (duck.isOverlapping(userHidden)) {
                duckDeltaX = 0;
                duckDeltaY = 0;
                duckFlap = 3;
                ++score;
                shots = 3;
            }
        }
    }
}

void cloudTimer(int dummy) {
    for (unique_ptr<Shape> &s : clouds) {
        // Move all the clouds to the left
        s->moveX(-0.4);
        // If a shape has moved off the screen
        if (s->getCenterX() < -48) {
            // Set it to the right of the screen so that it passes through again
            s->setCenterX(width + 48);
        }
    }
    for (unique_ptr<Shape> &s : parallaxClouds) {
        // Move all the clouds to the left
        s->moveX(-0.8);
        // If a shape has moved off the screen
        if (s->getCenterX() < -72) {
            // Set it to the right of the screen so that it passes through again
            s->setCenterX(width + 72);
        }
    }
}

void duckTimer(int dummy) {
    if (duckHit) {
        duckDeltaX = 0;
        duckDeltaY = 8;
    }
    duck.moveY(duckDeltaY);
    duck.moveX(duckDeltaX/2);
    // If a shape has moved off the top of the screen
    if (duck.getCenterY() < -(duck.getHeight()/2)) {
        if (shots > 0) {
            double duckCenterOffset = rand() % 150 - 75;
            duck.setCenter(width / 2 + duckCenterOffset, height);
            duckDeltaX = (rand() % 6 - 3) + 0.5;
        }
        else gameOver = true;
    }
    // If a shape has moved off the bottom of the screen
    if (duck.getCenterY() > height+(duck.getHeight()/2)) {
            double duckCenterOffset = rand() % 150 - 75;
            duck.setCenter(width/2+duckCenterOffset, height);
            duckHit = false;
            duckDeltaX = (rand() % 6 - 3) + 0.5;
            duckDeltaY = -3;
            duckFlap = 0;
    }
}

void flapTimer(int dummy) {
    if (duckFlap == 0) {
        duck.setVec(duck2);
        duckFlap = 1;
    }
    else if (duckFlap == 1) {
        duck.setVec(duck3);
        duckFlap = 2;
    }
    else if (duckFlap == 2) {
        duck.setVec(duck1);
        duckFlap = 0;
    }
    // only happens once a duck is hit
    else if (duckFlap == 3) {
        duck.setVec(duckShot);
        duckFlap++;
    }
    else if (duckFlap == 4 || duckFlap == 5 || duckFlap == 6 || duckFlap == 7) {
        duckFlap++;
    }
    else if (duckFlap == 8) {
        duckHit = true;
        duck.setVec(duckFalling);
    }
}

void gameOverTimer(int dummy) {
    shotUI.addAlpha(-0.05);
    // Game Over fades in after shotUI has faded out
    if (shotUI.opacity < 0) gameOverUI.addAlpha(0.05);
    if (gameOverUI.opacity >= 1) playAgainUI.addAlpha(0.05);
    if (playAgainUI.opacity >= 1) playAgain = true;
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
    init();
    if (!glfwInit()) exit(EXIT_FAILURE);

    GLFWwindow* window;
    window = glfwCreateWindow(width, height, "Duck Hunt", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // Our own OpenGL initialization
    initGL();

    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glfwSetKeyCallback(window, kbd);

    // handles mouse movement
    glfwSetCursorPosCallback(window, cursor);

    // handles mouse clicks
    glfwSetMouseButtonCallback(window, mouse);

    // handles timer
    float time1 = 0.03f;
    float time2 = 0.05f;
    float time3 = 0.03f;
    float time4 = 0.03f;
    float previous = glfwGetTime();

    // Enter the event-processing loop
    while (!glfwWindowShouldClose(window)) {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        float now = glfwGetTime();
        float delta = now - previous;
        previous = now;
        time1 -= delta;
        time2 -= delta;
        time3 -= delta;
        time4 -= delta;
        if (time1 <= 0.f) {
            duckTimer(0);
        }
        if (time2 <= 0.f) {
            cloudTimer(0);
        }
        if (time3 <= 0.f) {
            flapTimer(0);
            time3 = 0.10f;
        }

        // Game over event
        if ((gameOver) && (time4 <= 0.f)) {
            gameOverTimer(0);
            time4 = 0.03f;
        }

        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
    return 0;
}