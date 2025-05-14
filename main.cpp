#include <GL/glut.h>
#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm> // For std::min and std::max
#include <random>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Scene selector
enum Scene { SCENE_ONE, SCENE_TWO, SCENE_THREE, SCENE_FOUR, SCENE_FIVE };
Scene currentScene = SCENE_ONE;

//Splash time
int splashTime = 16;

// ==== SCENE 1 GLOBALS ====
float nobitaX_SC1 = 0.0f;
float nobitaSpeed_SC1 = 1.0f;
bool isNobitaMoving_SC1 = true;
bool showSubtitleSceneOne = false;
int currentSubtitleIndex_SC1 = 0;
std::vector<std::string> subtitlesSceneOne = {
    "Nobita: Doraemon, help me please.",
    "Nobita: I failed my test again, this is the fifth time I fail, mom must be very angry.",
    "Nobita: Can you help me to make my paper disappear?",
    "Doraemon: Well... Why don't you revision and get better result..."
};
long subtitleStartTimeSceneOne = 0;
const long subtitleDuration_SC1 = 3000;
bool subtitlesFinishedSceneOne = false;
const int ELLIPSE_SEGMENTS = 100;
const int CIRCLE_SEGMENTS = 100;
const float BASE_SEMI_MAJOR_AXIS = 0.6f;
const float BASE_SEMI_MINOR_AXIS = 1.0f;

// ==== SCENE 2 GLOBALS ====
const float HOUSE_X_SC2 = 100.0f;
const float HOUSE_Y_SC2 = 200.0f;
const float HOUSE_WIDTH_SC2 = 300.0f;
const float HOUSE_HEIGHT_SC2 = 350.0f;
const float WINDOW_WIDTH_SC2 = 100.0f;
const float WINDOW_HEIGHT_SC2 = 80.0f;
const float DOOR_WIDTH_SC2 = 100.0f;
const float DOOR_HEIGHT_SC2 = 180.0f;
const float KNOB_RADIUS_SC2 = 5.0f;
const float KNOB_OFFSET_X_SC2 = 15.0f;
const float KNOB_OFFSET_Y_SC2 = 0.5f;
const int CLOUD_CIRCLE_SEGMENTS = 30;
const float THROW_ANGLE_START_SC2 = 20.0f;
const float THROW_ANGLE_END_SC2 = -40.0f;
const float PAPER_SPEED_SC2 = 0.005f;
const float THROW_SPEED_SC2 = 0.05f;
const float TARGET_X_SC2 = 750.0f;
const float TARGET_Y_SC2 = 390.0f;


float windowX_SC2 = HOUSE_X_SC2 + HOUSE_WIDTH_SC2 * 0.6f;
float windowY_SC2 = HOUSE_Y_SC2 + HOUSE_HEIGHT_SC2 * 0.5f;
float doraemonHandX_SC2 = windowX_SC2 + WINDOW_WIDTH_SC2 / 2.0f;
float doraemonHandY_SC2 = windowY_SC2 + WINDOW_HEIGHT_SC2 / 2.0f;
float paperX_SC2 = doraemonHandX_SC2;
float paperY_SC2 = doraemonHandY_SC2;
float progress_SC2 = 0.0f;
float handAngle_SC2 = THROW_ANGLE_START_SC2;
float throwProgress_SC2 = 0.0f;
bool isPlaneVisible_SC2 = true;
bool isHandThrowing_SC2 = true;
bool sceneTwoFinished = false;

// ==== SCENE 3 GLOBALS ====
const int WINDOW_WIDTH_SC3 = 1000;
const int WINDOW_HEIGHT_SC3 = 800;
const float PLANE_WIDTH_SC3 = 60.0f;
const float PLANE_HEIGHT_SC3 = 20.0f;
const float DOOR_WIDTH_SC3 = 100.0f;
const float DOOR_HEIGHT_SC3 = 180.0f;
const float DOOR_OPEN_SPEED_SC3 = 2.0f;
const float DOOR_OPEN_THRESHOLD_SC3 = 120.0f;
const float BUILDING_WIDTH_SC3 = 90.0f;
const float BUILDING_SPACING_SC3 = 130.0f;
const float BUILDING_BASE_Y_SC3 = 0.0f;
const int NUM_SNOWFLAKES_SC3 = 200;
const int CLOUD_CIRCLE_SEGMENTS_SC3 = 30;
const float PLANE_SPEED_SC3 = 2.0f;

float planeX_SC3 = -PLANE_WIDTH_SC3; // Start off-screen
float planeY_SC3 = 575.0f;
float rightDoorX_SC3 = 850.0f;
float doorY_SC3 = planeY_SC3 - DOOR_HEIGHT_SC3 / 2.0f;
float rightDoorOpenAngle_SC3 = 90.0f;
std::vector<float> buildingHeights_SC3 = { 300.0f, 450.0f, 220.0f, 500.0f, 380.0f, 280.0f, 420.0f, 350.0f, 480.0f };
int numBuildings_SC3 = buildingHeights_SC3.size();
float backgroundOffset_SC3 = 0.0f;
struct Snowflake_SC3 { float x; float y; float speed; };
std::vector<Snowflake_SC3> snowflakes_SC3(NUM_SNOWFLAKES_SC3);
struct Cloud_SC3 { float x; float y; float size; };
std::vector<Cloud_SC3> clouds_SC3 = {
    {100.0f, 700.0f, 40.0f}, {300.0f, 650.0f, 60.0f}, {550.0f, 750.0f, 50.0f}, {750.0f, 680.0f, 70.0f}
};
bool animationEnabled_SC3 = true;
bool planeInsideRightDoor_SC3 = false;
int planeStartDelay_SC3 = 100;
bool animationFinished_SC3 = false;

// ==== SCENE 4 GLOBALS ====
const int WINDOW_WIDTH_SC4 = 1000;
const int WINDOW_HEIGHT_SC4 = 800;
const float FLIGHT_DURATION_SC4 = 15.0f;
const float DOOR_DISAPPEAR_DELAY_SC4 = 2.0f;
const float PLANE_NEAR_DOOR_THRESHOLD_SC4 = 700.0f;
const float LEFT_DOOR_OPEN_ANGLE_SC4 = 120.0f;
const float RIGHT_DOOR_OPEN_ANGLE_SC4 = 160.0f;
const float TREE_SCALE_SC4 = 1.0f;
const float BIRD_FLAP_SPEED_SC4 = 0.2f;
const float BIRD_FLAP_AMPLITUDE_SC4 = 20.0f;
const float PLANE_FLIGHT_SPEED_SC4 = 100.0f; // Speed of the paper plane

float planeX_SC4 = 80.0f;
float planeY_SC4 = 540.0f;
float cloudOffset_SC4 = 0.0f;
float birdOffset_SC4 = 0.0f;
float birdX1_SC4 = 300.0f;
float birdY1_SC4 = 600.0f;
float birdX2_SC4 = 500.0f;
float birdY2_SC4 = 630.0f;
float birdX3_SC4 = 700.0f;
float birdY3_SC4 = 620.0f;

float flightProgress_SC4 = 0.0f;
clock_t flightStartTime_SC4 = 0;
clock_t leftDoorDisappearTime_SC4 = 0;
clock_t rightDoorOpenTime_SC4 = 0;

float leftDoorAngle_SC4 = 0.0f;
float rightDoorAngle_SC4 = 0.0f;
bool doorsOpening_SC4 = false;
bool doorsClosing_SC4 = false;
bool planeVisible_SC4 = true; // Initialize as visible
bool leftDoorVisible_SC4 = true;
bool rightDoorVisible_SC4 = true;
bool birdFlipped_SC4 = false;
float wingFlapAngle_SC4 = 0.0f;


GLfloat darkGreen_SC4[3] = { 0.0f, 0.3f, 0.1f };
GLfloat mediumGreen_SC4[3] = { 0.2f, 0.5f, 0.2f };
GLfloat lightGreen_SC4[3] = { 0.4f, 0.7f, 0.3f };
GLfloat treeTrunk_SC4[3] = { 0.4f, 0.3f, 0.1f };
GLfloat groundColor_SC4[3] = { 0.2f, 0.6f, 0.2f };
GLfloat birdColor_SC4[3] = { 0.0f, 0.0f, 0.0f };
GLfloat riverColor_SC4[3] = { 0.1f, 0.4f, 0.8f };
GLfloat mountainColor_SC4[3] = { 0.7f, 0.7f, 0.7f };
GLfloat doorColor_SC4[3] = { 1.0f, 0.4f, 0.7f };
GLfloat sunColor_SC4[3] = { 1.0f, 1.0f, 0.0f };
GLfloat skyColorTop_SC4[3] = { 0.6f, 0.8f, 1.0f };
GLfloat skyColorBottom_SC4[3] = { 0.8f, 0.9f, 1.0f };
GLfloat groundColorTop_SC4[3] = { 0.3f, 0.7f, 0.3f };
GLfloat groundColorBottom_SC4[3] = { 0.2f, 0.6f, 0.2f };

std::vector<std::pair<float, float>> treePositions_SC4;

// ==== SCENE 5 GLOBALS ====
// Animation speed (milliseconds per frame update)
const int ANIMATION_SPEED_MS = 150;

// Cloud parameters for animation
struct Cloud {
    float x, y;
    float width, height;
};

std::vector<Cloud> clouds; // Store multiple clouds
float cloudSpeed = 0.5f; // Adjusted cloud speed for 1000x800


// Random number generator for lily pad sizes
std::mt19937 rng(std::random_device{}());
std::uniform_real_distribution<float> lilyPadSizeDist(8.0f, 18.0f); // Adjusted lily pad size range for 1000x800

// Paper plane animation parameters
bool isPlaneFlying = false; // Flag to control if the plane is currently animating and visible
float planeX, planeY;
float planeRotation = 0.0f; // Current rotation of the plane in degrees

// Path points for the paper plane (now a straight line from door to lake)
std::vector<std::pair<float, float>> paperPlanePath; // Global declaration
int currentPathPointIndex = 0;
float progressAlongSegment = 0.0f;
float segmentSpeed = 0.04f; // Adjusted speed of movement along each path segment

// Splash effect parameters
bool isSplashing = false;
float splashX, splashY;
long splashStartTime = 0; // Use long for time in milliseconds
const long splashDuration = 500; // Splash lasts for 500 milliseconds
const int numberOfSplashLines = 8; // Number of lines in the splash
const float maxSplashLineLength = 60.0f; // Increased maximum length of the splash lines

// Subtitle parameters
bool showSubtitle = false;
std::string subtitleText = "Nobita's mom: Nobita!! Your teacher say you mess up tour exam again!";
long subtitleStartTime = 0;
const long subtitleDuration = 5000; // Subtitle shows for 5 seconds

// Door animation parameters
bool isDoorOpening = true; // Door animation starts on program run
float doorOpenProgress = 0.0f;
long doorAnimationStartTime = 0;
const long doorAnimationDuration = 5000; // Increased door opens over 5 seconds
float doorRotationAngle = 0.0f; // Current rotation angle of the door in degrees

// Door dimensions (from lecturer's provided code)
const float doorPanelWidth = 100;
const float doorPanelHeight = 180;

const int WINDOW_WIDTH = 1000; // Current width
const int WINDOW_HEIGHT = 800; // Current height

// Function Prototypes
void startPaperPlane(); // Added function prototype

// ===== COMMON UTILS =====
inline float interpolate(float start, float end, float t) { return start + (end - start) * std::max(0.0f, std::min(t, 1.0f)); }
inline void setColor(float r, float g, float b) { glColor3f(r, g, b); }
inline void drawFilledRect(float x, float y, float w, float h) { glBegin(GL_QUADS); glVertex2f(x, y); glVertex2f(x + w, y); glVertex2f(x + w, y + h); glVertex2f(x, y + h); glEnd(); }
inline void drawFilledRectangle(float x1, float y1, float x2, float y2) { glBegin(GL_QUADS); glVertex2f(x1, y1); glVertex2f(x2, y1); glVertex2f(x2, y2); glVertex2f(x1, y2); glEnd(); }
inline void drawThickLine(float x1, float y1, float x2, float y2, float thickness) { glLineWidth(thickness); glBegin(GL_LINES); glVertex2f(x1, y1); glVertex2f(x2, y2); glEnd(); glLineWidth(1.0f); }

void drawCircle(float cx, float cy, float r) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < CIRCLE_SEGMENTS; ++i) {
        float theta = 2.0f * M_PI * static_cast<float>(i) / CIRCLE_SEGMENTS;
        glVertex2f(cx + r * cosf(theta), cy + r * sinf(theta));
    }
    glEnd();
}

void drawEllipse(float centerX, float centerY, float radius) {
    float semiMajorAxis = BASE_SEMI_MAJOR_AXIS * radius;
    float semiMinorAxis = BASE_SEMI_MINOR_AXIS * radius;
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < ELLIPSE_SEGMENTS; ++i) {
        float angle = 2.0f * M_PI * static_cast<float>(i) / ELLIPSE_SEGMENTS;
        glVertex2f(centerX + semiMajorAxis * cosf(angle), centerY + semiMinorAxis * sinf(angle));
    }
    glEnd();
}

void drawDownwardSemicircle(float cx, float cy, float radius) {
    setColor(1.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= CIRCLE_SEGMENTS; ++i) {
        float angle = static_cast<float>(i) / CIRCLE_SEGMENTS * M_PI;
        glVertex2f(cx + radius * cosf(angle), cy - radius * sinf(angle));
    }
    glEnd();
}

// === SCENE1 DRAWING FUNCTIONS ===
void drawNobita_SC1(float x, float y) {
    setColor(1.0f, 0.8f, 0.6f); drawCircle(x, y + 105.0f, 45.0f);
    setColor(1.0f, 1.0f, 1.0f); drawCircle(x - 15.0f, y + 112.5f, 7.5f); drawCircle(x + 15.0f, y + 112.5f, 7.5f);
    setColor(0.0f, 0.0f, 0.0f); drawCircle(x - 15.0f, y + 112.5f, 3.0f); drawCircle(x + 15.0f, y + 112.5f, 3.0f);
    setColor(1.0f, 0.6f, 0.4f); drawFilledRect(x - 7.5f, y + 90.0f, 15.0f, 4.5f);
    setColor(0.5f, 0.3f, 0.0f); drawFilledRect(x - 37.5f, y + 135.0f, 75.0f, 15.0f);
    setColor(1.0f, 0.9f, 0.0f); drawFilledRect(x - 30.0f, y + 15.0f, 60.0f, 60.0f);
    setColor(0.0f, 0.2f, 0.8f); drawFilledRect(x - 30.0f, y - 15.0f, 60.0f, 30.0f);
    setColor(1.0f, 0.9f, 0.0f); drawFilledRect(x - 60.0f, y + 45.0f, 30.0f, 15.0f); drawFilledRect(x + 30.0f, y + 45.0f, 30.0f, 15.0f);
    setColor(1.0f, 1.0f, 1.0f); drawFilledRect(x + 60.0f, y + 50.0f, 70.0f, 100.0f); drawCircle(x + 115.0f, y + 135.0f, 8.0f);
    setColor(1.0f, 0.0f, 0.0f); drawEllipse(x + 115.0f, y + 135.0f, 10.0f);
    setColor(1.0f, 1.0f, 1.0f); drawEllipse(x + 115.0f, y + 135.0f, 8.0f);
    setColor(1.0f, 0.8f, 0.6f); drawFilledRect(x - 22.5f, y - 75.0f, 15.0f, 60.0f); drawFilledRect(x + 7.5f, y - 75.0f, 15.0f, 60.0f);
}

void drawDoraemon_SC1(float x, float y) {
    setColor(0.0f, 0.439f, 0.753f); drawCircle(x, y, 60.0f);
    setColor(1.0f, 1.0f, 1.0f); drawCircle(x, y, 50.0f);
    setColor(0.0f, 0.0f, 0.0f); drawCircle(x - 20.0f, y + 20.0f, 8.0f); drawCircle(x + 20.0f, y + 20.0f, 8.0f);
    setColor(1.0f, 0.0f, 0.0f); drawCircle(x, y, 5.0f);
    setColor(0.0f, 0.0f, 0.0f); glBegin(GL_LINE_STRIP); for (int i = -30; i <= 30; i += 5) { float xMouth = static_cast<float>(i); float yMouth = -0.01f * xMouth * xMouth - 15.0f; glVertex2f(x + xMouth, y + yMouth); } glEnd();
    setColor(0.0f, 0.439f, 0.753f); drawFilledRectangle(x - 40.0f, y - 50.0f, x + 40.0f, y - 140.0f);
    setColor(1.0f, 0.0f, 0.0f); drawFilledRectangle(x - 45.0f, y - 55.0f, x + 45.0f, y - 45.0f);
    setColor(1.0f, 0.843f, 0.0f); drawCircle(x, y - 70.0f, 10.0f);
    setColor(0.0f, 0.0f, 0.0f); drawThickLine(x, y - 70.0f, x, y - 85.0f, 1.0f);
    setColor(0.0f, 0.439f, 0.753f); drawCircle(x - 50.0f, y - 100.0f, 15.0f); drawCircle(x + 50.0f, y - 100.0f, 15.0f);
    setColor(1.0f, 1.0f, 1.0f); drawCircle(x - 50.0f, y - 100.0f, 10.0f); drawCircle(x + 50.0f, y - 100.0f, 10.0f);
    setColor(0.0f, 0.439f, 0.753f); drawCircle(x - 20.0f, y - 140.0f, 20.0f); drawCircle(x + 20.0f, y - 140.0f, 20.0f);
    drawDownwardSemicircle(x, y - 80.0f, 30.0f);
}

void drawScene1Characters() { drawNobita_SC1(nobitaX_SC1, 220.0f); drawDoraemon_SC1(550.0f, 300.0f); }
void drawRoom_SC1() {
    setColor(0.95f, 0.92f, 0.85f); drawFilledRect(0.0f, 250.0f, 1000.0f, 550.0f);
    setColor(0.6f, 0.8f, 0.5f); drawFilledRect(0.0f, 0.0f, 1000.0f, 250.0f);
    setColor(0.5f, 0.3f, 0.1f); drawThickLine(0.0f, 250.0f, 1000.0f, 250.0f, 2.0f); drawThickLine(0.0f, 500.0f, 1000.0f, 500.0f, 2.0f);
    setColor(0.7f, 0.7f, 0.7f); drawFilledRect(95.0f, 395.0f, 130.0f, 90.0f);
    setColor(0.6f, 0.9f, 1.0f); drawFilledRect(100.0f, 400.0f, 120.0f, 80.0f);
    setColor(0.3f, 0.7f, 0.3f); drawFilledRect(90.0f, 400.0f, 10.0f, 80.0f); drawFilledRect(220.0f, 400.0f, 10.0f, 80.0f); drawFilledRect(95.0f, 410.0f, 5.0f, 60.0f); drawFilledRect(220.0f, 415.0f, 5.0f, 50.0f);
    setColor(0.7f, 0.5f, 0.3f); drawFilledRect(55.0f, 300.0f, 130.0f, 30.0f);
    setColor(0.5f, 0.3f, 0.1f); drawFilledRect(60.0f, 230.0f, 10.0f, 70.0f); drawFilledRect(175.0f, 230.0f, 10.0f, 70.0f);
    setColor(0.3f, 0.3f, 0.5f); drawFilledRect(85.0f, 270.0f, 50.0f, 20.0f); glBegin(GL_QUADS); glVertex2f(85.0f, 230.0f); glVertex2f(95.0f, 310.0f); glVertex2f(135.0f, 310.0f); glVertex2f(140.0f, 230.0f); glEnd();
    setColor(0.8f, 0.8f, 0.8f); drawFilledRect(420.0f, 250.0f, 160.0f, 200.0f);
    setColor(0.95f, 0.95f, 0.95f); drawFilledRect(425.0f, 255.0f, 70.0f, 190.0f); drawFilledRect(505.0f, 255.0f, 70.0f, 190.0f);
    setColor(0.7f, 0.7f, 0.7f); drawThickLine(500.0f, 310.0f, 500.0f, 450.0f, 1.0f);
    setColor(0.4f, 0.6f, 0.9f); drawFilledRect(750.0f, 250.0f, 80.0f, 160.0f);
    setColor(0.8f, 0.8f, 0.8f); drawFilledRect(755.0f, 290.0f, 70.0f, 5.0f); drawFilledRect(755.0f, 330.0f, 70.0f, 5.0f); drawFilledRect(755.0f, 370.0f, 70.0f, 5.0f);
    setColor(0.9f, 0.6f, 0.3f); drawFilledRect(900.0f, 250.0f, 60.0f, 150.0f);
    setColor(0.2f, 0.2f, 0.2f); drawFilledRect(945.0f, 320.0f, 5.0f, 10.0f);
    if (showSubtitleSceneOne && !subtitlesFinishedSceneOne) { setColor(0.0f, 0.0f, 0.0f); glRasterPos2f(200.0f, 100.0f); for (char c : subtitlesSceneOne[currentSubtitleIndex_SC1]) { glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c); } }
}

// === SCENE2 DRAWING FUNCTIONS ===
void drawBackground_SC2() { glBegin(GL_QUADS); setColor(0.5f, 0.8f, 1.0f); glVertex2f(0.0f, 800.0f); glVertex2f(1000.0f, 800.0f); setColor(0.9f, 1.0f, 1.0f); glVertex2f(1000.0f, 400.0f); glVertex2f(0.0f, 400.0f); glEnd(); }
void drawStylizedCloud_SC2(float x, float y) {
    setColor(1.0f, 1.0f, 1.0f);
    auto drawCloudPart = [&](float centerX, float centerY, float radiusX, float radiusY) {
        glBegin(GL_TRIANGLE_FAN); glVertex2f(centerX, centerY);
        for (int i = 0; i <= CLOUD_CIRCLE_SEGMENTS; ++i) { float angle = 2.0f * M_PI * static_cast<float>(i) / CLOUD_CIRCLE_SEGMENTS; glVertex2f(centerX + cosf(angle) * radiusX, centerY + sinf(angle) * radiusY); }
        glEnd();
        };
    drawCloudPart(x, y, 25.0f, 12.0f); drawCloudPart(x + 20.0f, y + 10.0f, 20.0f, 10.0f); drawCloudPart(x - 15.0f, y + 5.0f, 20.0f, 10.0f);
}
void drawStylizedClouds_SC2() { drawStylizedCloud_SC2(150.0f, 700.0f); drawStylizedCloud_SC2(500.0f, 750.0f); drawStylizedCloud_SC2(850.0f, 680.0f); drawStylizedCloud_SC2(300.0f, 650.0f); }
void drawFloor_SC2() { setColor(0.5f, 0.7f, 0.3f); drawFilledRect(0.0f, 0.0f, 1000.0f, 450.0f); }
void drawHouse_SC2(float x, float y, float width, float height) { setColor(0.8f, 0.6f, 0.4f); drawFilledRect(x, y, width, height); setColor(0.7f, 0.2f, 0.1f); glBegin(GL_TRIANGLES); glVertex2f(x - 20.0f, y + height); glVertex2f(x + width + 20.0f, y + height); glVertex2f(x + width / 2.0f, y + height + 80.0f); glEnd(); setColor(0.5f, 0.3f, 0.1f); drawFilledRect(x + width * 0.15f, y, width * 0.2f, height * 0.4f); }
void drawWindow_SC2(float x, float y, float width, float height) { setColor(0.6f, 0.8f, 1.0f); drawFilledRect(x, y, width, height); setColor(0.3f, 0.3f, 0.3f); glBegin(GL_LINE_LOOP); glVertex2f(x, y); glVertex2f(x + width, y); glVertex2f(x + width, y + height); glVertex2f(x, y + height); glEnd(); }
void drawDoraemonHand_SC2(float x, float y) {
    glPushMatrix(); glTranslatef(x, y, 0.0f); glRotatef(handAngle_SC2, 0.0f, 0.0f, 1.0f);
    setColor(0.2f, 0.6f, 1.0f); drawFilledRect(-30.0f, -8.0f, 45.0f, 16.0f);
    setColor(1.0f, 1.0f, 1.0f); glBegin(GL_TRIANGLE_FAN); glVertex2f(18.0f, 0.0f); for (int i = 0; i <= CLOUD_CIRCLE_SEGMENTS; ++i) { float angle = 2.0f * M_PI * static_cast<float>(i) / CLOUD_CIRCLE_SEGMENTS; glVertex2f(18.0f + cosf(angle) * 12.0f, sinf(angle) * 12.0f); } glEnd();
    glPopMatrix();
}
void drawPaperPlaneAt_SC2(float x, float y) { if (!isPlaneVisible_SC2) return; setColor(1.0f, 1.0f, 1.0f); glBegin(GL_TRIANGLES); glVertex2f(x, y); glVertex2f(x - 10.0f, y - 20.0f); glVertex2f(x + 60.0f, y - 30.0f); glEnd(); glBegin(GL_TRIANGLES); glVertex2f(x, y); glVertex2f(x + 15.0f, y + 10.0f); glVertex2f(x + 60.0f, y - 30.0f); glEnd(); setColor(0.1f, 0.1f, 0.1f); glBegin(GL_LINES); glVertex2f(x, y); glVertex2f(x + 60.0f, y - 30.0f); glEnd(); }
void drawAnywhereDoor_SC2(float x, float y) {
    setColor(1.0f, 0.4f, 0.7f); drawFilledRect(x, y, DOOR_WIDTH_SC2, DOOR_HEIGHT_SC2);
    setColor(0.8f, 0.2f, 0.5f); glLineWidth(4.0f); glBegin(GL_LINE_LOOP); glVertex2f(x, y); glVertex2f(x + DOOR_WIDTH_SC2, y); glVertex2f(x + DOOR_WIDTH_SC2, y + DOOR_HEIGHT_SC2); glVertex2f(x, y + DOOR_HEIGHT_SC2); glEnd(); glLineWidth(1.0f);
    setColor(1.0f, 1.0f, 1.0f); glBegin(GL_TRIANGLE_FAN); glVertex2f(x + DOOR_WIDTH_SC2 - KNOB_OFFSET_X_SC2, y + DOOR_HEIGHT_SC2 * KNOB_OFFSET_Y_SC2); for (int i = 0; i <= CLOUD_CIRCLE_SEGMENTS; ++i) { float angle = 2.0f * M_PI * static_cast<float>(i) / CLOUD_CIRCLE_SEGMENTS; glVertex2f(x + DOOR_WIDTH_SC2 - KNOB_OFFSET_X_SC2 + cosf(angle) * KNOB_RADIUS_SC2, y + DOOR_HEIGHT_SC2 * KNOB_OFFSET_Y_SC2 + sinf(angle) * KNOB_RADIUS_SC2); } glEnd();
}

// === SCENE3 DRAWING FUNCTIONS ===
void drawBackground_SC3() { glClearColor(0.529f, 0.808f, 0.922f, 1.0f); }
void initSnow_SC3() {
    srand(time(0)); for (auto& flake : snowflakes_SC3) { flake.x = static_cast<float>(rand() % WINDOW_WIDTH_SC3); flake.y = static_cast<float>(rand() % WINDOW_HEIGHT_SC3); flake.speed = static_cast<float>(rand() % 5 + 1) / 5.0f; }
}
void drawSnowflake_SC3(float x, float y) { glColor3f(1.0f, 1.0f, 1.0f); glPointSize(2.0f); glBegin(GL_POINTS); glVertex2f(x, y); glEnd(); }
void drawSnow_SC3() { for (const auto& flake : snowflakes_SC3) { drawSnowflake_SC3(flake.x, flake.y); } }
void updateSnow_SC3() { for (auto& flake : snowflakes_SC3) { flake.y -= flake.speed; if (flake.y < 0) { flake.y = WINDOW_HEIGHT_SC3; flake.x = static_cast<float>(rand() % WINDOW_WIDTH_SC3); } } }
void drawWindow_SC3(float bx, float by, float bw, float bh) { glColor3f(0.85f, 0.92f, 0.98f); glBegin(GL_QUADS); glVertex2f(bx, by); glVertex2f(bx + bw, by); glVertex2f(bx + bw, by + bh); glVertex2f(bx, by + bh); glEnd(); }
void drawBuilding_SC3(float x, float y, float width, float height) {
    glColor3f(0.5f, 0.5f, 0.5f); glBegin(GL_QUADS); glVertex2f(x, y); glVertex2f(x + width, y); glVertex2f(x + width, y + height); glVertex2f(x, y + height); glEnd();
    int rows = static_cast<int>(height / 30.0f);
    int cols = static_cast<int>(width / 40.0f);
    float windowWidth = width / (cols + 1) * 0.6f;
    float windowHeight = height / (rows + 1) * 0.5f;
    float paddingX = (width - cols * windowWidth) / (cols + 1);
    float paddingY = (height - rows * windowHeight) / (rows + 1);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            float wx = x + paddingX * (j + 1) + windowWidth * j;
            float wy = y + paddingY * (i + 1) + windowHeight * i;
            drawWindow_SC3(wx, wy, windowWidth, windowHeight);
        }
    }
}
void drawBuildings_SC3() {
    backgroundOffset_SC3 = planeX_SC3 * 0.2f;
    for (int i = 0; i < numBuildings_SC3; ++i) {
        float buildingX = i * BUILDING_SPACING_SC3 + 30.0f - backgroundOffset_SC3;
        if (buildingX + BUILDING_WIDTH_SC3 < 0) { buildingX += numBuildings_SC3 * BUILDING_SPACING_SC3; }
        else if (buildingX > WINDOW_WIDTH_SC3) { buildingX -= numBuildings_SC3 * BUILDING_SPACING_SC3; }
        drawBuilding_SC3(buildingX, BUILDING_BASE_Y_SC3, BUILDING_WIDTH_SC3, buildingHeights_SC3[i]);
    }
}
void drawPaperPlaneAt_SC3(float x, float y) { glColor3f(1.0f, 1.0f, 1.0f); glBegin(GL_TRIANGLES); glVertex2f(x, y); glVertex2f(x - 10, y - 20); glVertex2f(x + 60, y - 30); glEnd(); glBegin(GL_TRIANGLES); glVertex2f(x, y); glVertex2f(x + 15, y + 10); glVertex2f(x + 60, y - 30); glEnd(); glColor3f(0.1f, 0.1f, 0.1f); glBegin(GL_LINES); glVertex2f(x, y); glVertex2f(x + 60, y - 30); glEnd(); }
void drawPaperPlane_SC3() { if (!planeInsideRightDoor_SC3) { drawPaperPlaneAt_SC3(planeX_SC3, planeY_SC3); } }
void drawAnywhereDoor_SC3(float x, float y, float angle, bool visible) {
    if (!visible) return;
    float width = DOOR_WIDTH_SC3; float height = DOOR_HEIGHT_SC3; float hingeX = x; float hingeY = y;
    glPushMatrix(); glTranslatef(hingeX, hingeY, 0.0f); glRotatef(angle, 0.0f, 1.0f, 0.0f); glTranslatef(-hingeX, -hingeY, 0.0f);
    glColor3f(1.0f, 0.4f, 0.7f); glBegin(GL_QUADS); glVertex2f(x, y); glVertex2f(x + width, y); glVertex2f(x + width, y + height); glVertex2f(x, y + height); glEnd();
    glColor3f(0.8f, 0.2f, 0.5f); glLineWidth(4); glBegin(GL_LINE_LOOP); glVertex2f(x, y); glVertex2f(x + width, y); glVertex2f(x + width, y + height); glVertex2f(x, y + height); glEnd(); glLineWidth(1.0f);
    glPopMatrix();
    glColor3f(1.0f, 1.0f, 1.0f); float handleX = x + width - 20; float handleY = y + height / 2; float radius = 5.0f;
    glPushMatrix(); glTranslatef(hingeX, hingeY, 0.0f); glRotatef(angle, 0.0f, 1.0f, 0.0f); glTranslatef(-hingeX, -hingeY, 0.0f); glBegin(GL_TRIANGLE_FAN); glVertex2f(handleX, handleY); for (int i = 0; i <= CLOUD_CIRCLE_SEGMENTS_SC3; ++i) { float a = 2.0f * M_PI * i / CLOUD_CIRCLE_SEGMENTS_SC3; glVertex2f(handleX + cosf(a) * radius, handleY + sinf(a) * radius); } glEnd(); glPopMatrix();
}
void drawCloud_SC3(float x, float y, float size) {
    glColor3f(0.9f, 0.9f, 0.9f);
    auto drawCloudPart = [&](float cx, float cy, float r) { glBegin(GL_TRIANGLE_FAN); glVertex2f(cx, cy); for (int i = 0; i <= CLOUD_CIRCLE_SEGMENTS_SC3; ++i) { float a = 2.0f * M_PI * i / CLOUD_CIRCLE_SEGMENTS_SC3; glVertex2f(cx + cosf(a) * r, cy + sinf(a) * r); } glEnd(); };
    drawCloudPart(x, y, size); drawCloudPart(x + size, y + size * 0.5f, size * 0.7f); drawCloudPart(x + size * 0.5f, y - size * 0.5f, size * 0.8f);
}

// === SCENE4 DRAWING FUNCTIONS ===
void drawAnywhereDoor_SC4(float x, float y, float angle, bool visible, bool isRightDoor) {
    if (!visible) return;
    float width = 100.0f;
    float height = 150.0f;
    float hingeX = x;
    float hingeY = y;

    glPushMatrix();
    glTranslatef(hingeX, hingeY, 0.0f);
    if (isRightDoor)
        glRotatef(-angle, 0.0f, 1.0f, 0.0f);
    else
        glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glTranslatef(-hingeX, -hingeY, 0.0f);

    glColor3fv(doorColor_SC4);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();

    glColor3f(0.8f, 0.2f, 0.5f);
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    float handleX = x + width + 5;
    float handleY = y + height / 2;
    float radius = 4.0f;

    glPushMatrix();
    glTranslatef(hingeX, hingeY, 0.0f);
    if (isRightDoor)
        glRotatef(-angle, 0.0f, 1.0f, 0.0f);
    else
        glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glTranslatef(-hingeX, -hingeY, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(handleX, handleY);
    for (int i = 0; i <= CIRCLE_SEGMENTS; ++i) { // Use consistent segment count
        float angle = 2.0f * M_PI * i / CIRCLE_SEGMENTS;
        glVertex2f(handleX + cos(angle) * radius, handleY + sin(angle) * radius);
    }
    glEnd();
    glPopMatrix();

    glPopMatrix();
}

void drawPaperPlaneAt_SC4(float x, float y) {
    if (!planeVisible_SC4) return;

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(x, y);
    glVertex2f(x - 10, y - 20);
    glVertex2f(x + 60, y - 30);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(x, y);
    glVertex2f(x + 15, y + 10);
    glVertex2f(x + 60, y - 30);
    glEnd();

    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(x + 60, y - 30);
    glEnd();
}

void drawTree_SC4(float x, float y) {
    glColor3fv(darkGreen_SC4);
    glBegin(GL_TRIANGLES);
    glVertex2f(x, y);
    glVertex2f(x - 35 * TREE_SCALE_SC4, y - 80 * TREE_SCALE_SC4);
    glVertex2f(x + 35 * TREE_SCALE_SC4, y - 80 * TREE_SCALE_SC4);
    glEnd();

    glColor3fv(mediumGreen_SC4);
    glBegin(GL_TRIANGLES);
    glVertex2f(x, y + 20 * TREE_SCALE_SC4);
    glVertex2f(x - 30 * TREE_SCALE_SC4, y - 60 * TREE_SCALE_SC4);
    glVertex2f(x + 30 * TREE_SCALE_SC4, y - 60 * TREE_SCALE_SC4);
    glEnd();

    glColor3fv(lightGreen_SC4);
    glBegin(GL_TRIANGLES);
    glVertex2f(x, y + 40 * TREE_SCALE_SC4);
    glVertex2f(x - 25 * TREE_SCALE_SC4, y - 40 * TREE_SCALE_SC4);
    glVertex2f(x + 25 * TREE_SCALE_SC4, y - 40 * TREE_SCALE_SC4);
    glEnd();

    glColor3fv(treeTrunk_SC4);
    glBegin(GL_QUADS);
    glVertex2f(x - 8 * TREE_SCALE_SC4, y - 80 * TREE_SCALE_SC4);
    glVertex2f(x + 8 * TREE_SCALE_SC4, y - 80 * TREE_SCALE_SC4);
    glVertex2f(x + 8 * TREE_SCALE_SC4, y - 120 * TREE_SCALE_SC4);
    glVertex2f(x - 8 * TREE_SCALE_SC4, y - 120 * TREE_SCALE_SC4);
    glEnd();
}

void drawBird_SC4(float x, float y) {
    glColor3fv(birdColor_SC4);
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    if (birdFlipped_SC4)
        glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(sinf(wingFlapAngle_SC4) * BIRD_FLAP_AMPLITUDE_SC4, 0.0f, 0.0f, 1.0f); // Wing flap
    glBegin(GL_TRIANGLES);
    glVertex2f(0, 0);
    glVertex2f(-15, -10);
    glVertex2f(-5, -5);
    glVertex2f(-5, -5);
    glVertex2f(15, -10);
    glVertex2f(0, 0);
    glEnd();
    glPopMatrix();
}

void drawCloud_SC4(float x, float y, float size) {
    glColor3f(0.9f, 0.9f, 1.0f);
    glBegin(GL_POLYGON);
    for (int j = 0; j < CIRCLE_SEGMENTS; ++j) { // Use consistent segment count
        float angle = 2.0f * M_PI * j / CIRCLE_SEGMENTS;
        glVertex2f(x + cos(angle) * size, y + sin(angle) * (size * 0.6f));
    }
    glEnd();
}

void drawRiver_SC4() {
    glColor3fv(riverColor_SC4);
    glBegin(GL_QUADS);
    glVertex2f(0, 300);
    glVertex2f(WINDOW_WIDTH_SC4, 200);
    glVertex2f(WINDOW_WIDTH_SC4, 0);
    glVertex2f(0, 100);
    glEnd();
}

void drawMountain_SC4(float x1, float y1, float x2, float y2, float x3, float y3) {
    glColor3fv(mountainColor_SC4);
    glBegin(GL_TRIANGLES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}

void drawSun_SC4() {
    glPushMatrix();
    glTranslatef(WINDOW_WIDTH_SC4 * 0.8f, WINDOW_HEIGHT_SC4 * 0.8f, 0.0f);
    glColor3fv(sunColor_SC4);
    float radius = 50.0f;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0, 0);
    for (int i = 0; i <= CIRCLE_SEGMENTS; ++i) { // Use consistent segment count
        float angle = 2.0f * M_PI * i / CIRCLE_SEGMENTS;
        glVertex2f(cos(angle) * radius, sin(angle) * radius);
    }
    glEnd();
    glPopMatrix();
}

void drawScene_SC4() {
    // Draw Sky with a vertical gradient
    glBegin(GL_QUADS);
    glColor3fv(skyColorTop_SC4);
    glVertex2f(0, WINDOW_HEIGHT_SC4);
    glVertex2f(WINDOW_WIDTH_SC4, WINDOW_HEIGHT_SC4);
    glColor3fv(skyColorBottom_SC4);
    glVertex2f(WINDOW_WIDTH_SC4, 400);
    glVertex2f(0, 400);
    glEnd();

    drawSun_SC4();

    // Draw Ground with a vertical gradient
    glBegin(GL_QUADS);
    glColor3fv(groundColorTop_SC4);
    glVertex2f(0, 250);
    glVertex2f(WINDOW_WIDTH_SC4, 250);
    glColor3fv(groundColorBottom_SC4);
    glVertex2f(WINDOW_WIDTH_SC4, 0);
    glVertex2f(0, 0);
    glEnd();

    // Mountains
    drawMountain_SC4(100, 350, 400, 350, 250, 500);
    drawMountain_SC4(500, 300, 800, 300, 650, 450);
    drawMountain_SC4(0, 300, 200, 300, 100, 400);

    // River
    glColor3fv(riverColor_SC4);
    glBegin(GL_QUADS);
    glVertex2f(0, 100);
    glVertex2f(WINDOW_WIDTH_SC4, 200);
    glVertex2f(WINDOW_WIDTH_SC4, 170);
    glVertex2f(0, 70);
    glEnd();

    // Doors
    drawAnywhereDoor_SC4(80, 450, leftDoorAngle_SC4, leftDoorVisible_SC4, false);
    drawAnywhereDoor_SC4(800, 450, rightDoorAngle_SC4, rightDoorVisible_SC4, true);

    // Trees (using the initialized positions)
    for (const auto& pos : treePositions_SC4) {
        drawTree_SC4(pos.first, pos.second);
    }

    // Clouds
    drawCloud_SC4(50 + cloudOffset_SC4, 550, 50);
    drawCloud_SC4(300 + cloudOffset_SC4 * 0.8f, 650, 40);
    drawCloud_SC4(600 + cloudOffset_SC4 * 0.6f, 500, 60);

    // Birds
    drawBird_SC4(birdX1_SC4 - birdOffset_SC4, birdY1_SC4 + sinf(glutGet(GLUT_ELAPSED_TIME) * 0.0005f) * 5.0f);
    drawBird_SC4(birdX2_SC4 - birdOffset_SC4 * 0.9f, birdY2_SC4 + sinf(glutGet(GLUT_ELAPSED_TIME) * 0.0006f + 1.0f) * 7.0f);
    drawBird_SC4(birdX3_SC4 - birdOffset_SC4 * 1.1f, birdY3_SC4 + sinf(glutGet(GLUT_ELAPSED_TIME) * 0.0004f + 2.0f) * 6.0f);

    // Paper Plane
    drawPaperPlaneAt_SC4(planeX_SC4, planeY_SC4);
}

// === SCENE5 DRAWING FUNCTIONS ===

void drawRectangle_SC5(float x, float y, float width, float height, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

// Function to draw a triangle
void drawTriangle_SC5(float x1, float y1, float x2, float y2, float x3, float y3, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}

// Function to draw a circle (approximated using triangles)
void drawCircle_SC5(float cx, float cy, float radius, int segments, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy); // Center of the circle
    for (int i = 0; i <= segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(segments); // Get the angle for each segment
        float x = radius * cosf(theta); // Calculate the x component
        float y = radius * sinf(theta); // Calculate the y component
        glVertex2f(cx + x, cy + y); // Output vertex
    }
    glEnd();
}

// Function to draw the paper plane using lecturer's provided vertices and lines, with rotation
void drawPaperPlane_SC5(float x, float y, float rotation) {
    glPushMatrix(); // Save current matrix
    glTranslatef(x, y, 0.0f); // Move to plane's position
    glRotatef(rotation, 0.0f, 0.0f, 1.0f); // Rotate around the z-axis
    glScalef(1.0f, 1.0f, 1.0f); // Base scale

    // Drawing the plane using the provided vertices relative to the plane's local origin (0,0)
    glColor3f(1.0f, 1.0f, 1.0f); // White color for the plane
    glBegin(GL_TRIANGLES);
    // Triangle 1 (adapted from provided x, y relative positions)
    glVertex2f(0.0f, 0.0f);
    glVertex2f(-10.0f, -20.0f);
    glVertex2f(60.0f, -30.0f);

    // Triangle 2 (adapted from provided x, y relative positions)
    glVertex2f(0.0f, 0.0f);
    glVertex2f(15.0f, 10.0f);
    glVertex2f(60.0f, -30.0f);
    glEnd();

    // Drawing the line using the provided vertices relative to the plane's local origin (0,0)
    glColor3f(0.1f, 0.1f, 0.1f); // Dark grey color for the line
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(60.0f, -30.0f);
    glEnd();

    glPopMatrix(); // Restore previous matrix
}


// Function to draw the door based on lecturer's provided code, with opening animation
void drawDoor_SC5(float x, float y, float currentRotation) { // Added currentRotation parameter
    // --- Door drawing based on drawAnywhereDoor ---
    // x, y are the bottom-left coordinates for the closed door panel

    // Calculate the hinge point (right edge, bottom)
    float hingeX = x + doorPanelWidth;
    float hingeY = y;

    glPushMatrix(); // Save current matrix
    // Translate to the hinge point
    glTranslatef(hingeX, hingeY, 0.0f);
    // Apply the rotation around the vertical axis (Y-axis in this local space)
    glRotatef(currentRotation, 0.0f, 1.0f, 0.0f);
    // Translate back so the hinge point is still the reference, but geometry is defined relative to (0,0)
    // We need to define the door geometry relative to the hinge being at (0,0) before this translation.
    // If hinge is on the right, the panel vertices are from (-doorPanelWidth, 0) to (0, doorPanelHeight)

    // Draw the door panel (pink)
    glColor3f(1.0f, 0.4f, 0.7f); // Doraemon pink
    glBegin(GL_QUADS);
    glVertex2f(-doorPanelWidth, 0);
    glVertex2f(0, 0);
    glVertex2f(0, doorPanelHeight);
    glVertex2f(-doorPanelWidth, doorPanelHeight);
    glEnd();

    // Door outline (darker pink)
    glColor3f(0.8f, 0.2f, 0.5f);
    glLineWidth(4); // Set line width for outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(-doorPanelWidth, 0);
    glVertex2f(0, 0);
    glVertex2f(0, doorPanelHeight);
    glVertex2f(-doorPanelWidth, doorPanelHeight);
    glEnd();
    glLineWidth(1.0f); // Reset line width


    // Door handle (white circle) - Positioned relative to the hinge being at (0,0)
    glColor3f(1.0f, 1.0f, 1.0f);
    float handleX = -20.0f; // Position 20 units to the left of the hinge (right edge)
    float handleY = doorPanelHeight / 2.0f; // Position at half the door height
    float radius = 5.0f;
    drawCircle_SC5(handleX, handleY, radius, 10, 1.0f, 1.0f, 1.0f); // Draw the circle


    glPopMatrix(); // Restore previous matrix
}


// Function to draw a simple tree
void drawTree_SC5(float x, float y, float trunkWidth, float trunkHeight, float canopyRadius, float trunkR, float trunkG, float trunkB, float canopyR, float canopyG, float canopyB) {
    // Draw trunk
    drawRectangle_SC5(x - trunkWidth / 2, y, trunkWidth, trunkHeight, trunkR, trunkG, trunkB);

    // Draw canopy (using approximated circle)
    drawCircle_SC5(x, y + trunkHeight, canopyRadius, 20, canopyR, canopyG, canopyB);
}

// Function to draw a cloud (using approximated circles)
void drawCloud_SC5(float x, float y, float width, float height, float r, float g, float b) {
    glColor3f(r, g, b);
    // Approximate cloud shape with a few overlapping circles (adjusted sizes)
    drawCircle_SC5(x, y, height / 2.0f, 15, r, g, b);
    drawCircle_SC5(x + width * 0.3f, y + height * 0.2f, height * 0.6f / 2.0f, 15, r, g, b);
    drawCircle_SC5(x + width * 0.6f, y, height / 2.0f, 15, r, g, b);
    drawCircle_SC5(x + width * 0.2f, y - height * 0.2f, height * 0.5f / 2.0f, 15, r, g, b);
}

// Function to draw a lily pad (simple green circle with random size)
void drawLilyPad_SC5(float x, float y, float r, float g, float b) {
    float radius = lilyPadSizeDist(rng); // Get a random size (from adjusted range)
    drawCircle_SC5(x, y, radius, 20, r, g, b);
}

// Function to draw a slightly more detailed frog
void drawFrog_SC5(float x, float y, float r, float g, float b) {
    // Adjusted frog dimensions for 1000x800
    float bodyWidth = 14.0f;
    float bodyHeight = 11.0f;
    float headRadius = 5.0f;
    float eyeRadius = 2.5f;
    float legLength = 6.0f;
    float legWidth = 3.0f;

    glColor3f(r, g, b);

    // Body (approximated with circles)
    drawCircle_SC5(x, y, bodyWidth * 0.5f, 15, r, g, b);
    drawCircle_SC5(x - bodyWidth * 0.3f, y, bodyWidth * 0.4f, 15, r, g, b);
    drawCircle_SC5(x + bodyWidth * 0.3f, y, bodyWidth * 0.4f, 15, r, g, b);


    // Head
    drawCircle_SC5(x, y + bodyHeight * 0.5f, headRadius, 15, r, g, b);

    // Eyes on top of the head
    drawCircle_SC5(x - headRadius * 0.5f, y + bodyHeight * 0.5f + eyeRadius * 0.8f, eyeRadius, 10, 0.0f, 0.0f, 0.0f); // Black eyes
    drawCircle_SC5(x + headRadius * 0.5f, y + bodyHeight * 0.5f + eyeRadius * 0.8f, eyeRadius, 10, 0.0f, 0.0f, 0.0f);

    // Simple front legs (rectangles)
    glColor3f(r, g, b); // Reset color for legs
    // Left front leg
    drawRectangle_SC5(x - bodyWidth * 0.4f, y - bodyHeight * 0.2f, legLength * 0.7f, legWidth, r, g, b); // Upper part
    drawRectangle_SC5(x - bodyWidth * 0.4f - legWidth, y - bodyHeight * 0.2f - legLength * 0.5f, legWidth, legLength * 0.5f, r, g, b); // Lower part
    // Right front leg
    drawRectangle_SC5(x + bodyWidth * 0.4f - legLength * 0.7f, y - bodyHeight * 0.2f, legLength * 0.7f, legWidth, r, g, b); // Upper part
    drawRectangle_SC5(x + bodyWidth * 0.4f, y - bodyHeight * 0.2f - legLength * 0.5f, legWidth, legLength * 0.5f, r, g, b); // Lower part


    // Simple back legs (more elongated shapes)
    // Drawing simple bent legs with rectangles:
    // Left back leg
    drawRectangle_SC5(x - bodyWidth * 0.4f - legLength * 0.8f, y - bodyHeight * 0.6f, legLength * 0.8f, legWidth * 1.2f, r, g, b); // Thigh
    drawRectangle_SC5(x - bodyWidth * 0.4f - legLength * 0.8f - legLength * 0.7f, y - bodyHeight * 0.6f - legWidth * 1.2f, legLength * 0.7f, legWidth * 1.2f, r, g, b); // Shin
    // Right back leg
    drawRectangle_SC5(x + bodyWidth * 0.4f, y - bodyHeight * 0.6f, legLength * 0.8f, legWidth * 1.2f, r, g, b); // Thigh
    drawRectangle_SC5(x + bodyWidth * 0.4f + legLength * 0.8f, y - bodyHeight * 0.6f - legWidth * 1.2f, legLength * 0.7f, legWidth * 1.2f, r, g, b); // Shin
}

void startPaperPlane() {
    if (!isPlaneFlying) {
        isPlaneFlying = true;
        isSplashing = false; // Ensure splash is off when starting
        showSubtitle = false; // Ensure subtitle is off when starting
        currentPathPointIndex = 0;
        progressAlongSegment = 0.0f;

        // Ensure the path is not empty and set initial position
        if (!paperPlanePath.empty()) {
            planeX = paperPlanePath[0].first;
            planeY = paperPlanePath[0].second;
            planeRotation = 0.0f; // Start with no rotation or match the first segment
            // Set initial rotation to match the first segment if path has more than one point
            if (paperPlanePath.size() > 1) {
                float x1 = paperPlanePath[0].first;
                float y1 = paperPlanePath[0].second;
                float x2 = paperPlanePath[1].first;
                float y2 = paperPlanePath[1].second;

                planeRotation = atan2(y2 - y1, x2 - x1) * 180.0f / 3.1415926f;
            }
        }
    }
}

void drawScene_SC5() {
    // Background color (Sky blue)
    glClearColor(0.529f, 0.808f, 0.922f, 1.0f);

    // Draw Ground (More brown color)
    float groundHeight = WINDOW_HEIGHT / 3.0f;
    drawRectangle_SC5(0, 0, WINDOW_WIDTH, groundHeight, 0.545f, 0.271f, 0.074f); // Saddle Brown

    // Draw Water (Blue, larger on the right side, top aligned with ground)
    glColor3f(0.118f, 0.565f, 1.0f); // Dodger blue
    glBegin(GL_POLYGON);
    glVertex2f(WINDOW_WIDTH * 0.5f, 0); // Bottom-left
    glVertex2f(WINDOW_WIDTH, 0);       // Bottom-right
    glVertex2f(WINDOW_WIDTH, groundHeight); // Top-right, aligned with ground top
    glVertex2f(WINDOW_WIDTH * 0.9f, groundHeight); // Upper vertex, aligned with ground top
    glVertex2f(WINDOW_WIDTH * 0.7f, groundHeight); // Another upper vertex, aligned with ground top
    glVertex2f(WINDOW_WIDTH * 0.6f, WINDOW_HEIGHT * 0.1f); // Vertex curving down below ground
    glEnd();


    // Position for the standalone door (bottom-left corner of the closed door panel)
    float doorX = WINDOW_WIDTH / 3.0f; // Example position
    float doorY = groundHeight;       // Position door on top of the ground


    // Draw the standalone pink door with its current rotation
    drawDoor_SC5(doorX, doorY, doorRotationAngle); // Pass the current rotation angle

    // Draw some trees (positions and sizes adjusted for 1000x800)
    // Position trees relative to the ground height
    drawTree_SC5(WINDOW_WIDTH * 0.1f, groundHeight, 15.0f, 50.0f, 35.0f, 0.5f, 0.35f, 0.05f, 0.2f, 0.6f, 0.1f); // Tree on the left
    drawTree_SC5(WINDOW_WIDTH * 0.7f, groundHeight, 20.0f, 60.0f, 40.0f, 0.5f, 0.35f, 0.05f, 0.2f, 0.6f, 0.1f); // Tree near the larger lake, positioned on ground


    // Draw lily pads in the lake area with different sizes (positions adjusted for 1000x800)
    drawLilyPad_SC5(WINDOW_WIDTH * 0.60f, WINDOW_HEIGHT * 0.05f, 0.1f, 0.5f, 0.1f); // Green lily pad
    drawLilyPad_SC5(WINDOW_WIDTH * 0.72f, WINDOW_HEIGHT * 0.08f, 0.1f, 0.5f, 0.1f);
    drawLilyPad_SC5(WINDOW_WIDTH * 0.85f, WINDOW_HEIGHT * 0.12f, 0.1f, 0.5f, 0.1f);
    drawLilyPad_SC5(WINDOW_WIDTH * 0.97f, WINDOW_HEIGHT * 0.03f, 0.1f, 0.5f, 0.1f);
    drawLilyPad_SC5(WINDOW_WIDTH * 0.78f, WINDOW_HEIGHT * 0.2f, 0.1f, 0.5f, 0.1f);
    drawLilyPad_SC5(WINDOW_WIDTH * 0.63f, WINDOW_HEIGHT * 0.18f, 0.1f, 0.5f, 0.1f);
    drawLilyPad_SC5(WINDOW_WIDTH * 0.90f, WINDOW_HEIGHT * 0.07f, 0.1f, 0.5f, 0.1f);
    drawLilyPad_SC5(WINDOW_WIDTH * 0.70f, WINDOW_HEIGHT * 0.15f, 0.1f, 0.5f, 0.1f);
    drawLilyPad_SC5(WINDOW_WIDTH * 0.88f, WINDOW_HEIGHT * 0.04f, 0.1f, 0.5f, 0.1f);
    drawLilyPad_SC5(WINDOW_WIDTH * 0.99f, WINDOW_HEIGHT * 0.10f, 0.1f, 0.5f, 0.1f);


    // Draw simple frogs near some lily pads (positions adjusted for 1000x800)
    drawFrog_SC5(WINDOW_WIDTH * 0.61f, WINDOW_HEIGHT * 0.07f, 0.2f, 0.6f, 0.2f); // Green frog
    drawFrog_SC5(WINDOW_WIDTH * 0.74f, WINDOW_HEIGHT * 0.10f, 0.2f, 0.6f, 0.2f);
    drawFrog_SC5(WINDOW_WIDTH * 0.86f, WINDOW_HEIGHT * 0.13f, 0.2f, 0.6f, 0.2f);


    // Draw paper plane if flying
    if (isPlaneFlying) {
        drawPaperPlane_SC5(planeX, planeY, planeRotation);
    }

    // Draw splash effect if splashing
    if (isSplashing) {
        long elapsedTime = glutGet(GLUT_ELAPSED_TIME) - splashStartTime;
        float progress = (float)elapsedTime / splashDuration; // 0 to 1 over splash duration
        float currentLength = maxSplashLineLength * progress;
        float alpha = 1.0f - progress; // Fade out as it expands

        glEnable(GL_BLEND); // Enable blending for transparency
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Standard blending

        glColor4f(0.8f, 0.8f, 1.0f, alpha); // Light blue/white color with fading transparency
        glLineWidth(1.5f); // Slightly thicker lines for splash

        glBegin(GL_LINES);
        for (int i = 0; i < numberOfSplashLines; ++i) {
            float angle = (float)i / numberOfSplashLines * 360.0f * 3.1415926f / 180.0f; // Angle for each line
            float x2 = splashX + currentLength * cosf(angle);
            float y2 = splashY + currentLength * sinf(angle);
            glVertex2f(splashX, splashY); // Start at splash center
            glVertex2f(x2, y2); // End point expands outwards
        }
        glEnd();

        glDisable(GL_BLEND); // Disable blending
        glLineWidth(1.0f); // Reset line width
    }

    // Draw subtitle if showSubtitle is true
    if (showSubtitle) {
        glColor3f(1.0f, 1.0f, 1.0f); // White color for subtitle
        // Position the text (e.g., centered at the bottom)
        glRasterPos2f(WINDOW_WIDTH / 2 - glutBitmapLength(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)subtitleText.c_str()) / 2,
            WINDOW_HEIGHT * 0.1f); // Position slightly above bottom

        // Render the text
        for (char c : subtitleText) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c); // Using a standard bitmap font
        }
    }


    // Draw clouds (adjusted initial positions and sizes)
    for (size_t i = 0; i < clouds.size(); ++i) {
        // Initial cloud positions and sizes are now defined directly for 1000x800
        drawCloud_SC5(clouds[i].x, clouds[i].y, clouds[i].width, clouds[i].height, 1.0f, 1.0f, 1.0f); // White clouds
    }

}

void drawScene_SC3() {
    drawBackground_SC3();
    drawBuildings_SC3();
    drawAnywhereDoor_SC3(rightDoorX_SC3, doorY_SC3, rightDoorOpenAngle_SC3, true);
    for (const auto& cloud : clouds_SC3) {
        drawCloud_SC3(cloud.x, cloud.y, cloud.size);
    }
    drawPaperPlane_SC3();
    drawSnow_SC3();
}

void drawScene_SC1() {
    drawRoom_SC1();
    drawScene1Characters();
}

void drawScene_SC2() {
    drawBackground_SC2();
    drawStylizedClouds_SC2();
    drawFloor_SC2();
    drawHouse_SC2(HOUSE_X_SC2, HOUSE_Y_SC2, HOUSE_WIDTH_SC2, HOUSE_HEIGHT_SC2);
    drawWindow_SC2(windowX_SC2, windowY_SC2, WINDOW_WIDTH_SC2, WINDOW_HEIGHT_SC2);
    drawDoraemonHand_SC2(doraemonHandX_SC2, doraemonHandY_SC2);
    drawPaperPlaneAt_SC2(paperX_SC2, paperY_SC2);
    drawAnywhereDoor_SC2(700.0f, 300.0f);
}

void update(int value) {
    long currentTime = glutGet(GLUT_ELAPSED_TIME);
    float deltaTime = static_cast<float>(value) / 1000.0f;

    if (currentScene == SCENE_ONE) {
        if (isNobitaMoving_SC1) {
            nobitaX_SC1 += nobitaSpeed_SC1 * deltaTime * 60.0f;
            if (nobitaX_SC1 > 320.0f) {
                isNobitaMoving_SC1 = false;
                if (!showSubtitleSceneOne) {
                    showSubtitleSceneOne = true;
                    subtitleStartTimeSceneOne = currentTime;
                }
            }
        }
        if (showSubtitleSceneOne && !subtitlesFinishedSceneOne) {
            if (currentTime - subtitleStartTimeSceneOne >= subtitleDuration_SC1) {
                currentSubtitleIndex_SC1++;
                if (currentSubtitleIndex_SC1 >= static_cast<int>(subtitlesSceneOne.size())) {
                    subtitlesFinishedSceneOne = true;
                    sceneTwoFinished = false;
                    currentScene = SCENE_TWO;
                    progress_SC2 = 0.0f;
                    throwProgress_SC2 = 0.0f;
                    handAngle_SC2 = THROW_ANGLE_START_SC2;
                    isPlaneVisible_SC2 = true;
                    isHandThrowing_SC2 = true;
                }
                else {
                    subtitleStartTimeSceneOne = currentTime;
                }
            }
        }
    }
    else if (currentScene == SCENE_TWO) {
        if (isHandThrowing_SC2) {
            throwProgress_SC2 += THROW_SPEED_SC2;
            if (throwProgress_SC2 >= 1.0f) {
                throwProgress_SC2 = 1.0f;
                isHandThrowing_SC2 = false;
            }
            handAngle_SC2 = interpolate(THROW_ANGLE_START_SC2, THROW_ANGLE_END_SC2, throwProgress_SC2);
        }
        if (throwProgress_SC2 > 0.2f && progress_SC2 < 1.0f) {
            progress_SC2 += PAPER_SPEED_SC2;
            paperX_SC2 = interpolate(doraemonHandX_SC2, TARGET_X_SC2, progress_SC2);
            paperY_SC2 = interpolate(doraemonHandY_SC2, TARGET_Y_SC2, progress_SC2);
        }
        else if (progress_SC2 >= 1.0f && !sceneTwoFinished) {
            sceneTwoFinished = true;
            currentScene = SCENE_THREE;
            initSnow_SC3();
            animationEnabled_SC3 = true;
            planeInsideRightDoor_SC3 = false;
            planeStartDelay_SC3 = 100;
            animationFinished_SC3 = false;
            planeX_SC3 = -PLANE_WIDTH_SC3;
            planeY_SC3 = 575.0f;
            rightDoorOpenAngle_SC3 = 90.0f;
            doorY_SC3 = planeY_SC3 - DOOR_HEIGHT_SC3 / 2.0f;
        }
    }
    else if (currentScene == SCENE_THREE) {
        updateSnow_SC3();
        if (animationEnabled_SC3 && !animationFinished_SC3) {
            if (planeStartDelay_SC3 > 0) {
                planeStartDelay_SC3 -= 1;
            }
            else {
                planeX_SC3 += PLANE_SPEED_SC3;
                doorY_SC3 = planeY_SC3 - DOOR_HEIGHT_SC3 / 2.0f;
                float distanceToRightDoor = rightDoorX_SC3 - (planeX_SC3 + PLANE_WIDTH_SC3);
                bool isOverlappingRightDoorHorizontally = (planeX_SC3 + PLANE_WIDTH_SC3 > rightDoorX_SC3 && planeX_SC3 < rightDoorX_SC3 + DOOR_WIDTH_SC3);
                bool isOverlappingRightDoorVertically = (planeY_SC3 > doorY_SC3 && planeY_SC3 < doorY_SC3 + DOOR_HEIGHT_SC3) || (planeY_SC3 - PLANE_HEIGHT_SC3 > doorY_SC3 && planeY_SC3 - PLANE_HEIGHT_SC3 < doorY_SC3 + DOOR_HEIGHT_SC3);
                bool isPastRightDoor = planeX_SC3 > rightDoorX_SC3 + DOOR_WIDTH_SC3;
                if (distanceToRightDoor < DOOR_OPEN_THRESHOLD_SC3 && rightDoorOpenAngle_SC3 > 0.0f) {
                    rightDoorOpenAngle_SC3 -= DOOR_OPEN_SPEED_SC3;
                    if (rightDoorOpenAngle_SC3 < 0.0f) rightDoorOpenAngle_SC3 = 0.0f;
                }
                else if (distanceToRightDoor > DOOR_OPEN_THRESHOLD_SC3 && rightDoorOpenAngle_SC3 < 90.0f) {
                    rightDoorOpenAngle_SC3 += DOOR_OPEN_SPEED_SC3 / 2.0f;
                    if (rightDoorOpenAngle_SC3 > 90.0f) rightDoorOpenAngle_SC3 = 90.0f;
                }
                if (isOverlappingRightDoorHorizontally && isOverlappingRightDoorVertically && rightDoorOpenAngle_SC3 <= 10.0f && !planeInsideRightDoor_SC3) {
                    planeInsideRightDoor_SC3 = true;
                }
                if (isPastRightDoor && !animationFinished_SC3) {
                    animationFinished_SC3 = true;
                    currentScene = SCENE_FOUR;
                    flightStartTime_SC4 = clock();
                    leftDoorDisappearTime_SC4 = 0;
                    rightDoorOpenTime_SC4 = 0;
                    leftDoorAngle_SC4 = 0.0f;
                    rightDoorAngle_SC4 = 0.0f;
                    doorsOpening_SC4 = false;
                    doorsClosing_SC4 = false;
                    planeVisible_SC4 = true;
                    leftDoorVisible_SC4 = true;
                    rightDoorVisible_SC4 = true;
                    planeX_SC4 = 80.0f;
                    planeY_SC4 = 540.0f;
                    flightProgress_SC4 = 0.0f;
                }
            }
        }
    }
    else if (currentScene == SCENE_FOUR) {
        bool animationFinished_SC4 = false;
        cloudOffset_SC4 += 0.5f;
        if (cloudOffset_SC4 > WINDOW_WIDTH_SC4 + 100) cloudOffset_SC4 = -100;

        birdOffset_SC4 += 3.0f;
        if (birdOffset_SC4 > WINDOW_WIDTH_SC4 + 100) birdOffset_SC4 = -100;

        wingFlapAngle_SC4 += BIRD_FLAP_SPEED_SC4 + sinf(currentTime * 0.001f) * 0.05f;

        float elapsedFlight = static_cast<float>(clock() - flightStartTime_SC4) / (CLOCKS_PER_SEC * 15.0f);
        flightProgress_SC4 = std::max(0.0f, std::min(elapsedFlight, 1.0f));

        if (elapsedFlight <= 1.0f) {
            planeX_SC4 = interpolate(80.0f, 800.0f - 60.0f, elapsedFlight);
            planeY_SC4 = 540.0f - 50.0f * sinf(M_PI * elapsedFlight * 1.5f);
        }
        else {
            planeVisible_SC4 = false;
            if (leftDoorDisappearTime_SC4 == 0) {
                leftDoorDisappearTime_SC4 = clock();
            }
        }

        float planeRightEdge = planeX_SC4 + 60.0f;
        float leftDoorRightEdge = 80.0f + 100.0f;
        float rightDoorLeftEdge = 800.0f;

        // Open left door when plane approaches
        if (planeRightEdge > leftDoorRightEdge - 150.0f && leftDoorAngle_SC4 < LEFT_DOOR_OPEN_ANGLE_SC4 && !doorsClosing_SC4) {
            leftDoorAngle_SC4 += 2.0f;
            leftDoorAngle_SC4 = std::min(leftDoorAngle_SC4, LEFT_DOOR_OPEN_ANGLE_SC4);
        }

        // Open right door when plane approaches
        if (planeX_SC4 < rightDoorLeftEdge + 150.0f && rightDoorAngle_SC4 < RIGHT_DOOR_OPEN_ANGLE_SC4 && !doorsClosing_SC4) {
            rightDoorAngle_SC4 += 2.0f;
            rightDoorAngle_SC4 = std::min(rightDoorAngle_SC4, RIGHT_DOOR_OPEN_ANGLE_SC4);
        }

        // Close doors after the plane has passed
        if (planeX_SC4 > rightDoorLeftEdge + 50.0f && !doorsClosing_SC4) {
            doorsClosing_SC4 = true;
        }

        if (doorsClosing_SC4) {
            leftDoorAngle_SC4 -= 2.0f;
            rightDoorAngle_SC4 -= 2.0f;
            leftDoorAngle_SC4 = std::max(leftDoorAngle_SC4, 0.0f);
            rightDoorAngle_SC4 = std::max(rightDoorAngle_SC4, 0.0f);
            if (leftDoorAngle_SC4 <= 0.0f && rightDoorAngle_SC4 <= 0.0f) {
                doorsClosing_SC4 = false;
            }
        }

        if (leftDoorDisappearTime_SC4 != 0) {
            float timeSincePlaneExited = static_cast<float>(clock() - leftDoorDisappearTime_SC4) / (CLOCKS_PER_SEC * (DOOR_DISAPPEAR_DELAY_SC4 / 2.0f));
            if (timeSincePlaneExited >= (DOOR_DISAPPEAR_DELAY_SC4 / 2.0f)) {
                leftDoorVisible_SC4 = false;
                animationFinished_SC4 = true;
            }
        }
        if (!planeVisible_SC4 && leftDoorDisappearTime_SC4 == 0) {
            leftDoorDisappearTime_SC4 = clock();
        }
        if (animationFinished_SC4) {
            currentScene = SCENE_FIVE;
            isPlaneFlying = false;
            isSplashing = false; // Ensure splash is off initially
            showSubtitle = false; // Ensure subtitle is off initially
            planeX = -100; // Start off-screen
            planeY = -100;
            planeRotation = 0.0f; // Start with no rotation

            // Initialize door animation state (door opening starts automatically)
            isDoorOpening = true; // Door animation starts automatically
            doorOpenProgress = 0.0f;
            doorAnimationStartTime = glutGet(GLUT_ELAPSED_TIME); // Start door animation immediately
            doorRotationAngle = 0.0f; // Start closed
        }
    }
    else if (currentScene == SCENE_FIVE) {
        
         splashTime = 150;
       
        long currentTime = glutGet(GLUT_ELAPSED_TIME);

        // Update door opening animation
        if (isDoorOpening) {
            long elapsedTime = currentTime - doorAnimationStartTime;
            doorOpenProgress = (float)elapsedTime / doorAnimationDuration;

            if (doorOpenProgress >= 1.0f) {
                doorOpenProgress = 1.0f; // Ensure it reaches fully open state
                isDoorOpening = false; // End door animation

                // Start the paper plane animation after the door opens
                startPaperPlane();
            }

            // Calculate door rotation angle (e.g., open to -90 degrees)
            // Interpolate from 0 degrees (closed) to -90 degrees (open left)
            doorRotationAngle = 0.0f + (-90.0f - 0.0f) * doorOpenProgress;

            // Force a redisplay during the door animation
            glutPostRedisplay();

        }
        else if (isPlaneFlying) {
            // Paper plane animation logic (only runs after door opens)

            // Check if we are on a valid segment
            if ((size_t)currentPathPointIndex < paperPlanePath.size() - 1) {
                progressAlongSegment += segmentSpeed;

                // Check if we've completed the current segment
                if (progressAlongSegment >= 1.0f) {
                    progressAlongSegment = 0.0f;
                    currentPathPointIndex++;

                    // If we have just moved to the last point's index, trigger the splash and stop flying
                    if ((size_t)currentPathPointIndex == paperPlanePath.size() - 1) {
                        isPlaneFlying = false; // Stop plane animation

                        // Set the final plane position to the last point for the splash location
                        planeX = paperPlanePath.back().first;
                        planeY = paperPlanePath.back().second;

                        // Start the splash animation
                        isSplashing = true;
                        splashX = planeX; // Splash at the plane's final position
                        splashY = planeY;
                        splashStartTime = currentTime; // Use current time

                        // Ensure index stays at the end and progress is complete
                        currentPathPointIndex = paperPlanePath.size() - 1;
                        progressAlongSegment = 1.0f;
                    }
                }

                // Interpolate position along the current segment if still flying
                if (isPlaneFlying && (size_t)currentPathPointIndex < paperPlanePath.size() - 1) {
                    float x1 = paperPlanePath[currentPathPointIndex].first;
                    float y1 = paperPlanePath[currentPathPointIndex].second;
                    float x2 = paperPlanePath[currentPathPointIndex + 1].first;
                    float y2 = paperPlanePath[currentPathPointIndex + 1].second;

                    planeX = x1 + (x2 - x1) * progressAlongSegment;
                    planeY = y1 + (y2 - y1) * progressAlongSegment;

                    // Calculate rotation based on the current segment direction (older code behavior)
                    planeRotation = atan2(y2 - y1, x2 - x1) * 180.0f / 3.1415926f;
                }

            }
            else {
                // If currentPathPointIndex is already the last index,
                // the animation has finished, and splash should be handled.
                if (!isPlaneFlying && (size_t)currentPathPointIndex >= paperPlanePath.size() - 1) {
                    // Ensure the plane is at the last position if not flying
                    planeX = paperPlanePath.back().first;
                    planeY = paperPlanePath.back().second;
                }
            }
        }


        // Update splash animation (runs regardless of door or plane animation state)
        if (isSplashing) {
            long elapsedTime = currentTime - splashStartTime;
            if (elapsedTime >= splashDuration) {
                isSplashing = false; // End splash animation
                // Start showing the subtitle after the splash ends
                if (!showSubtitle) {
                    showSubtitle = true;
                    subtitleStartTime = currentTime; // Use current time
                }
            }
        }

        // Update subtitle visibility (runs regardless of other animation states)
        if (showSubtitle) {
            long elapsedTime = currentTime - subtitleStartTime;
            if (elapsedTime >= subtitleDuration) {
                showSubtitle = false; // Hide subtitle after duration
            }
        }
    }
   
    glutPostRedisplay();
    glutTimerFunc(splashTime, update, 16);
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    if (currentScene == SCENE_ONE) {
        drawScene_SC1();
    }
    else if (currentScene == SCENE_TWO) {
        drawScene_SC2();
    }
    else if (currentScene == SCENE_THREE) {
        drawScene_SC3();
    }
    else if (currentScene == SCENE_FOUR) {
        drawScene_SC4();
    }
    else if (currentScene == SCENE_FIVE) {
        drawScene_SC5();
    }
    glutSwapBuffers();
}



void initializeTreePositions_SC4() {
    for (int i = 0; i < 30; ++i) {
        float x = 50 + (i % 15) * 70;
        float y = 220 + (i / 15) * 50;
        treePositions_SC4.push_back(std::make_pair(x, y));
    }
}

void init_SC5() {
    // Initialize clouds (adjusted initial positions and sizes for 1000x800)
    clouds.push_back({ WINDOW_WIDTH * 0.1f, WINDOW_HEIGHT * 0.8f, 120.0f, 50.0f }); // Adjusted dimensions
    clouds.push_back({ WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.9f, 150.0f, 60.0f });
    clouds.push_back({ WINDOW_WIDTH * 0.9f, WINDOW_HEIGHT * 0.75f, 100.0f, 40.0f });


    // Initialize paper plane path (now a straight line from door to lake)
    paperPlanePath.clear(); // Clear existing path points

    float groundHeight = WINDOW_HEIGHT / 3.0f;

    // Position for the standalone door (bottom-left corner of the closed door panel)
    float doorX = WINDOW_WIDTH / 3.0f; // Example position
    float doorY = groundHeight;       // Position door on top of the ground

    // Dimensions of the door panel
    // const float doorPanelWidth = 100; // Already defined globally
    // const float doorPanelHeight = 180; // Already defined globally


    // Calculate the starting position for the paper plane (top center of the standalone door panel)
    float paperPlaneStartX = doorX + doorPanelWidth / 2.0f;
    float paperPlaneStartY = doorY + doorPanelHeight; // Top edge of door panel

    // Define the end point in the lake
    float paperPlaneEndX = WINDOW_WIDTH * 0.98f; // Reusing the previous end x-coordinate
    float paperPlaneEndY = WINDOW_HEIGHT * 0.06f; // Reusing the previous end y-coordinate

    // Add start and end points to the path
    paperPlanePath.push_back({ paperPlaneStartX, paperPlaneStartY }); // Start: Top center of the standalone door
    paperPlanePath.push_back({ paperPlaneEndX, paperPlaneEndY });     // End: In the lake

}

// Keyboard function - allow ESC to exit only
void keyboard(unsigned char key, int x, int y) { if (key == 27) { exit(0); } }
// Reshape function, keep coordinate projection
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    gluOrtho2D(0.0f, 1000.0f, 0.0f, 800.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Initialization
void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    initializeTreePositions_SC4();
    init_SC5();
}
// Main
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(1000, 800);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Doraemon Scenes: Nobita & Paper Plane");
    init(); glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, update, 16);
    glutMainLoop();
    return 0;
}
