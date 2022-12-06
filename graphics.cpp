#include "graphics.h"
#include "circle.h"
#include "rect.h"
#include "sprite.h"
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

GLdouble width, height;
int wd;
const color skyBlue(77/255.0, 213/255.0, 240/255.0);
const color grassGreen(26/255.0, 176/255.0, 56/255.0);
const color black(0, 0, 0);
const color brickRed(201/255.0, 20/255.0, 20/255.0);

Rect grass;



vector<unique_ptr<Shape>> clouds;
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

int score;
Rect scoreUI;
int shots;
Rect shotsUI;
Rect shot1;
Rect shot2;
Rect shot3;

Rect userHidden;
Rect user1;
Rect user2;

void initClouds() {
    clouds.clear();
    // First cloud
    Sprite cloud1;
    cloud1.setScale(2);
    cloud1.setVec(smallCloud);
    cloud1.setCenter(width/6, 55);
    clouds.push_back(make_unique<Sprite>(cloud1));
    // Second cloud
    Sprite cloud2;
    cloud2.setScale(2);
    cloud2.setVec(bigCloud);
    cloud2.setCenter((width/6)*3, 85);
    clouds.push_back(make_unique<Sprite>(cloud2));
    // Third cloud
    Sprite cloud3;
    cloud3.setScale(2);
    cloud3.setVec(smallCloud);
    cloud3.setCenter(((width/6)*5)+50, 105);
    clouds.push_back(make_unique<Sprite>(cloud3));
}

void initGrass() {
    grass.setCenter(250, 450);
    grass.setSize(width, height/3);
    grass.setColor(grassGreen);
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

void initDuck() {
    duck.setScale(2);
    duck.setVec(duck1);
    duck.setCenter(width/2, height);
    duckDeltaX = rand() % 6 - 3;
    duckDeltaY = -3;
    duckHit = false;
    duckFlap = 0;
}

void init() {
    width = 500;
    height = 500;
    srand(time(0));
    initClouds();
    initDuck();
    initGrass();
    initUser();

    score = 0;
    scoreUI.setSize(50, 20);
    scoreUI.setColor(black);
    scoreUI.setCenter((width/2)+60, height-30);

    shots = 3;
    shotsUI.setSize(110, 40);
    shotsUI.setColor(black);
    shotsUI.setCenter(65, height-30);

    shot1.setColor(brickRed);
    shot1.setSize(26, 30);
    shot1.setCenter(31, height-30);
    shot2.setColor(brickRed);
    shot2.setSize(26, 30);
    shot2.setCenter(65, height-30);
    shot3.setColor(brickRed);
    shot3.setSize(26, 30);
    shot3.setCenter(99, height-30);
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

    /*
     * Draw here
     */

    // Add logic to draw the grass, the user, and the
    // rest of the buildings. Note that the order of drawing
    // matters because whatever is drawn last appears on top.
    // Note that darkBlue buildings turn cyan when overlapping
    // with the user, and purple buildings turn magenta.

    for (unique_ptr<Shape> &s : clouds) {
        // #polymorphism
        s->draw();
    }

    duck.draw();

    grass.draw();

    user1.draw();
    user2.draw();

    //scoreUI.draw();
    shotsUI.draw();
    if (shots > 0) {
        shot1.draw();
        if (shots > 1) {
            shot2.draw();
            if (shots > 2) {
                shot3.draw();
            }
        }
    }




    glFlush();  // Render now
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // escape
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwTerminate();
        exit(0);
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
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        shots -= 1;
        if (duck.isOverlapping(userHidden)) {
            duckDeltaX = 0;
            duckDeltaY = 0;
            duckFlap = 3;
            ++score;
            shots = 3;
        }
    }
}

void cloudTimer(int dummy) {
    for (unique_ptr<Shape> &s : clouds) {
        // Move all the clouds to the left
        s->moveX(-1);
        // If a shape has moved off the screen
        if (s->getCenterX() < -48) {
            // Set it to the right of the screen so that it passes through again
            s->setCenterX(width + 48);
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
            duckDeltaX = rand() % 6 - 3;
        }
    }
    // If a shape has moved off the bottom of the screen
    if (duck.getCenterY() > height+(duck.getHeight()/2)) {
            double duckCenterOffset = rand() % 150 - 75;
            duck.setCenter(width/2+duckCenterOffset, height);
            duckHit = false;
            duckDeltaX = rand() % 6 - 3;
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

    // handles timer
    float time1 = 0.03f;
    float time2 = 0.05f;
    float time3 = 0.03f;
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

        display();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
    return 0;
}