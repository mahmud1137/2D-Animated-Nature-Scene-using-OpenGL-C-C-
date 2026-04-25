#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

float cloudX1 = 0.0f, cloudX2 = 25.0f;
float birdX = -5.0f, birdY = 28.0f;
float bird2X = -12.0f, bird2Y = 31.0f;
float bird3X = -20.0f, bird3Y = 30.0f;
int birdFlapCount = 0;
bool birdWingsUp = true;
float waveOffset = 0.0f;
float skyR = 0.4f, skyG = 0.7f, skyB = 1.0f;
float sunX = 0.0f;
float sunSpeed = 0.05f;
bool isDay = true;
float boatX = 20.0f;
float speed = 0.1f;
float boat2X = 0.0f;
float speed2 = 0.05f;
float boat3X = 15.0f;
float speed3 = 0.04f;
bool isRaining = false;
float rainX[200];
float rainY[200];
float windmillAngle = 0.0f;

void drawCircle(float cx, float cy, float r)
{
    glBegin(GL_POLYGON);
    for(int i=0;i<100;i++)
    {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(cx + r*cos(angle), cy + r*sin(angle));
    }
    glEnd();
}
void drawCloud(float cx, float cy) {
    if (isRaining)
        glColor3f(0.7f, 0.7f, 0.7f);
    else
        glColor3f(1.0f, 1.0f, 1.0f);

    drawCircle(cx, cy, 1.5f);
    drawCircle(cx + 1.5f, cy + 0.8f, 1.5f);
    drawCircle(cx + 3.0f, cy, 1.5f);
}

void drawBird(float cx, float cy, bool wingsUp) {
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_STRIP);
    if (wingsUp) {
        glVertex2f(cx, cy + 0.5f);
        glVertex2f(cx + 1.0f, cy);
        glVertex2f(cx + 2.0f, cy + 0.5f);
    } else {
        glVertex2f(cx, cy - 0.5f);
        glVertex2f(cx + 1.0f, cy);
        glVertex2f(cx + 2.0f, cy - 0.5f);
    }
    glEnd();
    glLineWidth(1.0f);
}

void drawWaves() {
    glColor3f(0.5f, 0.8f, 1.0f);
    glLineWidth(0.5f);

    for (float y = 2.0f; y < 24.0f; y += 4.0f) {
        glBegin(GL_LINE_STRIP);
        for (float x = 0.0f; x <= 50.0f; x += 1.0f) {
            float waveY = y + sin(x + waveOffset) * 0.4f;
            glVertex2f(x, waveY);
        }
        glEnd();
    }
    glLineWidth(0.5f);
}

void drawRain() {
    glColor3f(0.7f, 0.7f, 1.0f);
    glLineWidth(1.0f);

    glBegin(GL_LINES);
    for(int i = 0; i < 200; i++) {
        glVertex2f(rainX[i], rainY[i]);
        glVertex2f(rainX[i] - 0.2f, rainY[i] - 0.8f);
    }
    glEnd();
}

// Animation
void update(int value)
{
    // Boat movements
    boatX += speed;
    if (boatX >= 38.0f || boatX <= 20.0f)
        speed = -speed;

    boat2X += speed2;
    if (boat2X >= 50.0f) {
        boat2X = 0.0f;
    }

    boat3X += speed3;
    if (boat3X >= 50.0f) {
        boat3X = 0.0f;
    }

    // Cloud movement
    cloudX1 += 0.05f;
    if (cloudX1 > 55.0f) cloudX1 = -5.0f;
    cloudX2 += 0.03f;
    if (cloudX2 > 55.0f) cloudX2 = -5.0f;

    // Bird movement
    birdX += 0.15f;
    if (birdX > 55.0f) birdX = -5.0f;

    bird2X += 0.13f;
    if (bird2X > 55.0f) bird2X = -10.0f;

    bird3X += 0.17f;
    if (bird3X > 55.0f) bird3X = -8.0f;

    birdFlapCount++;
    if (birdFlapCount % 10 == 0) {
        birdWingsUp = !birdWingsUp;
    }

    // Water Waves
    waveOffset += 0.1f;


        // SUN, SKY CONTROL
    if (!isRaining) {
        sunX += sunSpeed;
        if (sunX >= 50.0f) {
            sunX = 0.0f;
            isDay = !isDay;
        }

        float transition = 0.0f;
        if (isDay) {
            transition = sin((sunX / 50.5f) * 3.1416f);
        } else {
            transition = 0.0f;
        }

        skyR = transition * 0.4f;
        skyG = transition * 0.7f + (1.0f - transition) * 0.1f;
        skyB = transition * 1.0f + (1.0f - transition) * 0.2f;
    }
    else {

        skyR = 0.4f;
        skyG = 0.4f;
        skyB = 0.5f;
    }

    if (isRaining) {
    for(int i = 0; i < 200; i++) {
        rainY[i] -= 0.5f;

        if(rainY[i] < 0) {
            rainY[i] = 40;
            rainX[i] = rand() % 50;
        }
    }
}
   // Windmill rotation
    windmillAngle += 3.0f;
    if (windmillAngle > 360.0f)
        windmillAngle -= 360.0f;

    glutPostRedisplay();
    glutTimerFunc(30, update, 0);
}

void drawWindmill(float x, float y)
{
    // Tower
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(x - 0.3f, y);
    glVertex2f(x + 0.3f, y);
    glVertex2f(x + 0.2f, y + 6.5f);
    glVertex2f(x - 0.2f, y + 6.5f);
    glEnd();

    // Hub (center circle)
    glColor3f(0.2f, 0.2f, 0.2f);
    drawCircle(x, y + 6.5f, 0.3f);

    // Blades (rotating)
    glPushMatrix();
    glTranslatef(x, y + 6.5f, 0.0f);
    glRotatef(windmillAngle, 0.0f, 0.0f, 1.0f);

    glColor3f(1.0f, 1.0f, 1.0f);

    for(int i = 0; i < 4; i++)
    {
        glRotatef(90.0f, 0.0f, 0.0f, 1.0f);

        glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.2f, 2.5f);
        glVertex2f(-0.2f, 2.5f);
        glEnd();
    }

    glPopMatrix();
}

void display(void)
{
    glClearColor(skyR, skyG, skyB, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (!isRaining) {

    float sunY = -0.024f * (sunX - 25.0f) * (sunX - 25.0f) + 37.0f;
    float r = 1.5f;

    if (isDay) {
        glColor3f(1.0f, 1.0f, 0.0f);
        drawCircle(sunX, sunY, r);

        // Sun rays
        glColor3f(1.0f, 0.8f, 0.0f);
        for(int i = 0; i < 12; i++) {
            float angle = 2 * 3.1416f * i / 12;
            glBegin(GL_LINES);
            glVertex2f(sunX + r * cos(angle), sunY + r * sin(angle));
            glVertex2f(sunX + (r + 0.5f) * cos(angle), sunY + (r + 0.5f) * sin(angle));
            glEnd();
        }
    } else {
        glColor3f(0.9f, 0.9f, 0.9f);
        drawCircle(sunX, sunY, r);
    }

}

    // 3. Draw Moving Clouds
    drawCloud(cloudX1, 30.0f);
    drawCloud(cloudX2, 33.0f);

    // 4. Draw Flying Bird
    drawBird(birdX, birdY, birdWingsUp);
    drawBird(bird2X, bird2Y, !birdWingsUp);
    drawBird(bird3X, bird3Y, birdWingsUp);

    //Far scenario
    // Palm Tree Trunk 1
    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(4.95f, 25.0f);
    glVertex2f(5.05f, 25.0f);
    glVertex2f(5.05f, 27.0f);
    glVertex2f(4.95f, 27.0f);
    glEnd();

    //Leaves
    glColor3f(0.0f, 0.4f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(4.45f, 26.5f);
    glVertex2f(4.55f, 26.5f);
    glVertex2f(5.55f, 27.5f);
    glVertex2f(5.45f, 27.5f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(5.45f, 26.5f);
    glVertex2f(5.55f, 26.5f);
    glVertex2f(4.55f, 27.5f);
    glVertex2f(4.45f, 27.5f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(4.2f, 26.75f);
    glVertex2f(4.45f, 26.75f);
    glVertex2f(5.05f, 27.0f);
    glVertex2f(5.05f, 27.05f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(5.7f, 26.75f);
    glVertex2f(5.45f, 26.75f);
    glVertex2f(4.95f, 27.0f);
    glVertex2f(4.95f, 27.05f);
    glEnd();

     // Trunk 2
    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(9.95f, 25.0f);
    glVertex2f(10.05f, 25.0f);
    glVertex2f(10.05f, 27.0f);
    glVertex2f(9.95f, 27.0f);
    glEnd();

    // Leaves
    glColor3f(0.0f, 0.4f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(9.45f, 26.5f);
    glVertex2f(9.55f, 26.5f);
    glVertex2f(10.55f, 27.5f);
    glVertex2f(10.45f, 27.5f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(10.45f, 26.5f);
    glVertex2f(10.55f, 26.5f);
    glVertex2f(9.55f, 27.5f);
    glVertex2f(9.45f, 27.5f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(9.2f, 26.75f);
    glVertex2f(9.45f, 26.75f);
    glVertex2f(10.05f, 27.0f);
    glVertex2f(10.05f, 27.05f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(10.7f, 26.75f);
    glVertex2f(10.45f, 26.75f);
    glVertex2f(9.95f, 27.0f);
    glVertex2f(9.95f, 27.05f);
    glEnd();

    //Palm Tree Trunk 3
    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(14.95f, 25.0f);
    glVertex2f(15.05f, 25.0f);
    glVertex2f(15.05f, 27.0f);
    glVertex2f(14.95f, 27.0f);
    glEnd();

    // Leaves
    glColor3f(0.0f, 0.4f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(14.45f, 26.5f);
    glVertex2f(14.55f, 26.5f);
    glVertex2f(15.55f, 27.5f);
    glVertex2f(15.45f, 27.5f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(15.45f, 26.5f);
    glVertex2f(15.55f, 26.5f);
    glVertex2f(14.55f, 27.5f);
    glVertex2f(14.45f, 27.5f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(14.2f, 26.75f);
    glVertex2f(14.45f, 26.75f);
    glVertex2f(15.05f, 27.0f);
    glVertex2f(15.05f, 27.05f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(15.7f, 26.75f);
    glVertex2f(15.45f, 26.75f);
    glVertex2f(14.95f, 27.0f);
    glVertex2f(14.95f, 27.05f);
    glEnd();

    //Palm Tree Trunk 4
    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(19.95f, 25.0f);
    glVertex2f(20.05f, 25.0f);
    glVertex2f(20.05f, 27.0f);
    glVertex2f(19.95f, 27.0f);
    glEnd();

    // Leaves
    glColor3f(0.0f, 0.4f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(19.45f, 26.5f);
    glVertex2f(19.55f, 26.5f);
    glVertex2f(20.55f, 27.5f);
    glVertex2f(20.45f, 27.5f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(20.45f, 26.5f);
    glVertex2f(20.55f, 26.5f);
    glVertex2f(19.55f, 27.5f);
    glVertex2f(19.45f, 27.5f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(19.2f, 26.75f);
    glVertex2f(19.45f, 26.75f);
    glVertex2f(20.05f, 27.0f);
    glVertex2f(20.05f, 27.05f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(20.7f, 26.75f);
    glVertex2f(20.45f, 26.75f);
    glVertex2f(19.95f, 27.0f);
    glVertex2f(19.95f, 27.05f);
    glEnd();

    //Palm Tree 5
    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(24.95f, 25.0f);
    glVertex2f(25.05f, 25.0f);
    glVertex2f(25.05f, 27.0f);
    glVertex2f(24.95f, 27.0f);
    glEnd();

    glColor3f(0.0f, 0.4f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(24.45f, 26.5f);
    glVertex2f(24.55f, 26.5f);
    glVertex2f(25.55f, 27.5f);
    glVertex2f(25.45f, 27.5f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(25.45f, 26.5f);
    glVertex2f(25.55f, 26.5f);
    glVertex2f(24.55f, 27.5f);
    glVertex2f(24.45f, 27.5f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(24.2f, 26.75f);
    glVertex2f(24.45f, 26.75f);
    glVertex2f(25.05f, 27.0f);
    glVertex2f(25.05f, 27.05f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(25.7f, 26.75f);
    glVertex2f(25.45f, 26.75f);
    glVertex2f(24.95f, 27.0f);
    glVertex2f(24.95f, 27.05f);
    glEnd();

    //Palm Tree 6
    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(29.95f, 25.0f);
    glVertex2f(30.05f, 25.0f);
    glVertex2f(30.05f, 27.0f);
    glVertex2f(29.95f, 27.0f);
    glEnd();

    glColor3f(0.0f, 0.4f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(29.45f, 26.5f);
    glVertex2f(29.55f, 26.5f);
    glVertex2f(30.55f, 27.5f);
    glVertex2f(30.45f, 27.5f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(30.45f, 26.5f);
    glVertex2f(30.55f, 26.5f);
    glVertex2f(29.55f, 27.5f);
    glVertex2f(29.45f, 27.5f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(29.2f, 26.75f);
    glVertex2f(29.45f, 26.75f);
    glVertex2f(30.05f, 27.0f);
    glVertex2f(30.05f, 27.05f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(30.7f, 26.75f);
    glVertex2f(30.45f, 26.75f);
    glVertex2f(29.95f, 27.0f);
    glVertex2f(29.95f, 27.05f);
    glEnd();

    //Palm Tree 7
    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(34.95f, 25.0f);
    glVertex2f(35.05f, 25.0f);
    glVertex2f(35.05f, 27.0f);
    glVertex2f(34.95f, 27.0f);
    glEnd();

    glColor3f(0.0f, 0.4f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(34.45f, 26.5f);
    glVertex2f(34.55f, 26.5f);
    glVertex2f(35.55f, 27.5f);
    glVertex2f(35.45f, 27.5f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(35.45f, 26.5f);
    glVertex2f(35.55f, 26.5f);
    glVertex2f(34.55f, 27.5f);
    glVertex2f(34.45f, 27.5f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(34.2f, 26.75f);
    glVertex2f(34.45f, 26.75f);
    glVertex2f(35.05f, 27.0f);
    glVertex2f(35.05f, 27.05f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(35.7f, 26.75f);
    glVertex2f(35.45f, 26.75f);
    glVertex2f(34.95f, 27.0f);
    glVertex2f(34.95f, 27.05f);
    glEnd();

    //Palm Tree 8
    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(39.95f, 25.0f);
    glVertex2f(40.05f, 25.0f);
    glVertex2f(40.05f, 27.0f);
    glVertex2f(39.95f, 27.0f);
    glEnd();

    glColor3f(0.0f, 0.4f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(39.45f, 26.5f);
    glVertex2f(39.55f, 26.5f);
    glVertex2f(40.55f, 27.5f);
    glVertex2f(40.45f, 27.5f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(40.45f, 26.5f);
    glVertex2f(40.55f, 26.5f);
    glVertex2f(39.55f, 27.5f);
    glVertex2f(39.45f, 27.5f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(39.2f, 26.75f);
    glVertex2f(39.45f, 26.75f);
    glVertex2f(40.05f, 27.0f);
    glVertex2f(40.05f, 27.05f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(40.7f, 26.75f);
    glVertex2f(40.45f, 26.75f);
    glVertex2f(39.95f, 27.0f);
    glVertex2f(39.95f, 27.05f);
    glEnd();

    //Palm Tree 9
    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(44.95f, 25.0f);
    glVertex2f(45.05f, 25.0f);
    glVertex2f(45.05f, 27.0f);
    glVertex2f(44.95f, 27.0f);
    glEnd();

    glColor3f(0.0f, 0.4f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(44.45f, 26.5f);
    glVertex2f(44.55f, 26.5f);
    glVertex2f(45.55f, 27.5f);
    glVertex2f(45.45f, 27.5f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(45.45f, 26.5f);
    glVertex2f(45.55f, 26.5f);
    glVertex2f(44.55f, 27.5f);
    glVertex2f(44.45f, 27.5f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(44.2f, 26.75f);
    glVertex2f(44.45f, 26.75f);
    glVertex2f(45.05f, 27.0f);
    glVertex2f(45.05f, 27.05f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(45.7f, 26.75f);
    glVertex2f(45.45f, 26.75f);
    glVertex2f(44.95f, 27.0f);
    glVertex2f(44.95f, 27.05f);
    glEnd();

    //1
    float cx = 0.5f, cy = 25.0f; float r = 1.0f;
    int i;

    glColor3f(0.0, 0.4, 0.0);
    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();

    //2
    cx = 2.5f, cy = 25.0f;
     r = 1.3f;

    glColor3f(0.0, 0.4, 0.0);
    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();

    //3
     cx = 4.3f, cy = 25.0f;
     r = 0.8f;

    glColor3f(0.0, 0.4, 0.0);
    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();

    //4
    cx = 6.5f, cy = 25.0f;
     r = 1.5f;

    glColor3f(0.0, 0.4, 0.0);
    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();

    //5
     cx = 9.0f, cy = 25.0f;
     r = 1.0f;

    glColor3f(0.0, 0.4, 0.0);
    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();

    //6
    cx = 11.5f, cy = 25.0f;
     r = 1.8f;

    glColor3f(0.0, 0.4, 0.0);
    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();

    //7
     cx = 13.5f, cy = 25.0f;
     r = 0.8f;

    glColor3f(0.0, 0.4, 0.0);
    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();

    //8
    cx = 15.0f, cy = 25.0f;
     r = 1.0f;

    glColor3f(0.0, 0.4, 0.0);
    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();

    //9
     cx = 17.5f, cy = 25.0f;
     r = 1.7f;

    glColor3f(0.0, 0.4, 0.0);
    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();

    //10
     cx = 19.5f, cy = 25.0f;
     r = 1.0f;

    glColor3f(0.0, 0.4, 0.0);
    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();

    //11
     cx = 21.5f, cy = 25.0f;
     r = 1.2f;

    glColor3f(0.0, 0.4, 0.0);
    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();

    //12
    cx = 23.5f, cy = 25.0f;
     r = 1.2f;

    glColor3f(0.0, 0.4, 0.0);
    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();

    //13
     cx = 26.0f, cy = 25.0f;
     r = 1.5f;

    glColor3f(0.0, 0.4, 0.0);
    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();

    //14
    cx = 28.5f, cy = 25.0f;
     r = 1.2f;

    glColor3f(0.0, 0.4, 0.0);
    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();

    //15
     cx = 30.0f, cy = 25.0f;
     r = 0.8f;

    glColor3f(0.0, 0.4, 0.0);
    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();

    //16
    cx = 31.5f, cy = 25.0f;
     r = 1.0f;

    glColor3f(0.0, 0.4, 0.0);
    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();

    //17
     cx = 33.5f, cy = 25.0f;
     r = 1.5f;

    glColor3f(0.0, 0.4, 0.0);
    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();

    //18
    cx = 35.5f, cy = 25.0f;
     r = 1.0f;

    glColor3f(0.0, 0.4, 0.0);
    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();

    //19
     cx = 37.5f, cy = 25.0f;
     r = 1.7f;

    glColor3f(0.0, 0.4, 0.0);
    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();

    //20
     cx = 39.5f, cy = 25.0f;
     r = 1.2f;

    glColor3f(0.0, 0.4, 0.0);
    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();


    //21
    cx = 42.0f, cy = 25.0f;
     r = 1.5;

    glColor3f(0.0, 0.4, 0.0);
    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();

    //22
     cx = 44.0f, cy = 25.0f;
     r = 0.8f;

    glColor3f(0.0, 0.4, 0.0);
    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();

    //23
     cx = 45.5f, cy = 25.0f;
     r = 1.0f;

    glColor3f(0.0, 0.4, 0.0);
    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();

    //12
    cx = 47.5f, cy = 25.0f;
     r = 1.3f;

    glColor3f(0.0, 0.4, 0.0);
    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();

    //13
     cx = 49.3f, cy = 25.0f;
     r = 0.8f;

    glColor3f(0.0, 0.4, 0.0);
    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();

    //tree 1
    glBegin(GL_QUADS);
    glVertex2f(7.0f, 14.0f);
    glVertex2f(10.0f, 14.0f);
    glVertex2f(9.0f, 17.0f);
    glVertex2f(8.0f, 17.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(7.0f, 14.0f);
    glVertex2f(8.0f, 15.0f);
    glVertex2f(7.0f, 17.0f);
    glVertex2f(6.1f, 17.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(9.0f, 15.0f);
    glVertex2f(10.0f, 14.0f);
    glVertex2f(11.0f, 17.0f);
    glVertex2f(10.0f, 17.0f);
    glEnd();

     //background 1 (river)
    glColor3f(0.0f, 0.3f, 0.8f);
    glBegin(GL_QUADS);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(50.0f, 0.0f);
    glVertex2f(50.0f, 25.0f);
    glVertex2f(0.0f, 25.0f);
    glEnd();

    //WAVES
    drawWaves();

    //background 2 (ground 1)
    glColor3f(0.0f, 0.6f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(18.0f, 0.0f);
    glVertex2f(18.0f, 20.0f);
    glVertex2f(0.0f, 20.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(18.0f, 0.0f);
    glVertex2f(29.0f, 0.0f);
    glVertex2f(22.0f, 8.0f);
    glVertex2f(18.0f, 8.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(18.0f, 8.0f);
    glVertex2f(25.0f, 8.0f);
    glVertex2f(18.0f, 16.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(24.0f, 19.0f);
    glVertex2f(18.0f, 20.0f);
    glVertex2f(18.0f, 16.0f);
    glEnd();


     //background 3 (ground 2)
    glBegin(GL_TRIANGLES);
    glVertex2f(50.0f, 10.0f);
    glVertex2f(50.0f, 20.0f);
    glVertex2f(40.0f, 18.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(50.0f, 13.0f);
    glVertex2f(50.0f, 8.0f);
    glVertex2f(44.0f, 13.0f);
    glEnd();

    // Boat 3
    // Body
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(boat3X + 0.0f, 24.0f);
    glVertex2f(boat3X + 1.0f, 24.0f);
    glVertex2f(boat3X + 2.0f, 24.5f);
    glVertex2f(boat3X - 1.0f, 24.5f);
    glEnd();

    // Top
    glColor3f(0.7f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(boat3X - 0.25f, 24.5f);
    glVertex2f(boat3X + 1.25f, 24.5f);
    glVertex2f(boat3X + 1.0f, 25.0f);
    glVertex2f(boat3X + 0.0f, 25.0f);
    glEnd();

    // Mast
    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(boat3X + 0.4f, 25.0f);
    glVertex2f(boat3X + 0.5f, 25.0f);
    glVertex2f(boat3X + 0.5f, 26.0f);
    glVertex2f(boat3X + 0.4f, 26.0f);
    glEnd();

    // Sail
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(boat3X + 0.5f, 25.1f);
    glVertex2f(boat3X + 1.5f, 25.1f);
    glVertex2f(boat3X + 0.5f, 26.0f);
    glEnd();

    // Boat 2
    // Body
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(boat2X + 0.0f, 22.0f);
    glVertex2f(boat2X + 1.0f, 22.0f);
    glVertex2f(boat2X + 2.0f, 22.5f);
    glVertex2f(boat2X - 1.0f, 22.5f);
    glEnd();

    // Top
    glColor3f(0.7f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(boat2X - 0.25f, 22.5f);
    glVertex2f(boat2X + 1.25f, 22.5f);
    glVertex2f(boat2X + 1.0f, 23.0f);
    glVertex2f(boat2X + 0.0f, 23.0f);
    glEnd();

    // Mast
    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(boat2X + 0.4f, 23.0f);
    glVertex2f(boat2X + 0.5f, 23.0f);
    glVertex2f(boat2X + 0.5f, 24.0f);
    glVertex2f(boat2X + 0.4f, 24.0f);
    glEnd();

    // Sail
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(boat2X + 0.5f, 23.1f);
    glVertex2f(boat2X + 1.5f, 23.1f);
    glVertex2f(boat2X + 0.5f, 24.0f);
    glEnd();

    //Far tree

    //leave 1
     cx = 16.0f, cy = 21.0f;
     r = 1.3f;

    glColor3f(0.0, 0.4, 0.0);
    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();

     //leave 2
     cx = 19.0f, cy = 21.0f;
     r = 1.3f;

    glColor3f(0.0, 0.4, 0.0);
    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();

     //leave 3
    cx = 17.5f, cy = 22.0f;
     r = 1.2f;

    glColor3f(0.0, 0.4, 0.0);
    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();


    //Far house 2
    //roof
    glColor3f(0.7f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(14.0f, 21.8f);
    glVertex2f(17.0f, 21.8f);
    glVertex2f(19.0f, 20.5f);
    glVertex2f(16.0f, 20.5f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(14.0f, 21.8f);
    glVertex2f(14.5f, 21.5f);
    glVertex2f(13.5f, 20.5f);
    glVertex2f(13.0f, 20.5f);
    glEnd();

    //wall
    glColor3f(0.8f, 0.5f, 0.3f);
    glBegin(GL_QUADS);
    glVertex2f(16.0f, 20.5f);
    glVertex2f(17.0f, 20.5f);
    glVertex2f(17.0f, 19.5f);
    glVertex2f(16.0f, 19.5f);
    glEnd();

    //leave 1
     cx = 5.0f, cy = 17.0f;
     r = 2.5f;

    glColor3f(0.0, 0.4, 0.0);
    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();
    //leave 2
    cx = 8.5f, cy = 19.0f;
     r = 2.5f;

    glColor3f(0.0, 0.4, 0.0);
    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();

    //leave 3
    cx = 15.0f, cy = 16.0f;
     r = 2.5f;

    glColor3f(0.0, 0.4, 0.0);
    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();

    //leave 4
    cx = 12.0f, cy = 17.0f;
     r = 2.5f;

    glColor3f(0.0, 0.4, 0.0);
    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();

    //leave 5
    cx = 14.0f, cy = 19.0f;
     r = 2.5f;

    glColor3f(0.0, 0.4, 0.0);
    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();

    //leave 6
    cx = 11.0f, cy = 21.0f;
     r = 2.5f;

    glColor3f(0.0, 0.4, 0.0);
    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();

    //leave 7
    cx = 8.0f, cy = 23.0f;
     r = 2.5f;

    glColor3f(0.0, 0.4, 0.0);
    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();

    //leave 8
    cx = 4.5f, cy = 21.0f;
     r = 3.0f;

    glColor3f(0.0, 0.4, 0.0);
    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();

    //leave 9
    cx = 1.0f, cy = 18.0f;
     r = 2.5f;

    glColor3f(0.0, 0.4, 0.0);
    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();


    //house 2
    //roof
    glColor3f(0.7f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(0.0f, 17.0f);
    glVertex2f(3.0f, 17.0f);
    glVertex2f(7.0f, 12.0f);
    glVertex2f(0.0f, 12.0f);
    glEnd();

    //wall
    glColor3f(0.8f, 0.5f, 0.3f);
    glBegin(GL_QUADS);
    glVertex2f(0.0f, 9.0f);
    glVertex2f(4.0f, 9.0f);
    glVertex2f(4.0f, 12.0f);
    glVertex2f(0.0f, 12.0f);
    glEnd();

    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(0.0f, 8.5f);
    glVertex2f(4.0f, 8.5f);
    glVertex2f(4.0f, 9.0f);
    glVertex2f(0.0f, 9.0f);
    glEnd();

    //window
    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(1.5f, 10.5f);
    glVertex2f(3.0f, 10.5f);
    glVertex2f(3.0f, 12.0f);
    glVertex2f(1.5f, 12.0f);
    glEnd();

    //house 1
    glColor3f(0.9f, 0.7f, 0.5f);
    glBegin(GL_POLYGON);
    glVertex2f(9.0f, 9.0f);
    glVertex2f(10.0f, 8.0f);
    glVertex2f(16.0f, 8.0f);
    glVertex2f(16.0f, 4.0f);
    glVertex2f(9.0f, 4.0f);
    glEnd();

    //roof
    glColor3f(0.7f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(4.0f, 14.0f);
    glVertex2f(12.0f, 14.0f);
    glVertex2f(18.0f, 8.0f);
    glVertex2f(10.0f, 8.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(2.0f, 9.0f);
    glVertex2f(3.0f, 9.0f);
    glVertex2f(5.0f, 13.0f);
    glVertex2f(4.0f, 14.0f);
    glEnd();

    //wall
    glColor3f(0.8f, 0.5f, 0.3f);
    glBegin(GL_POLYGON);
    glVertex2f(3.0f, 5.0f);
    glVertex2f(9.0f, 4.0f);
    glVertex2f(9.0f, 9.0f);
    glVertex2f(5.0f, 13.0f);
    glVertex2f(3.0f, 9.0f);
    glEnd();

    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(2.0f, 4.0f);
    glVertex2f(8.0f, 3.0f);
    glVertex2f(9.0f, 4.0f);
    glVertex2f(3.0f, 5.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(8.0f, 3.0f);
    glVertex2f(17.0f, 3.0f);
    glVertex2f(16.0f, 4.0f);
    glVertex2f(8.5f, 4.0f);
    glEnd();

    //door
    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(5.0f, 4.5f);
    glVertex2f(7.0f, 4.3f);
    glVertex2f(7.0f, 8.0f);
    glVertex2f(5.0f, 8.0f);
    glEnd();

    //window
    glBegin(GL_QUADS);
    glVertex2f(10.0f, 8.0f);
    glVertex2f(12.0f, 8.0f);
    glVertex2f(12.0f, 6.0f);
    glVertex2f(10.0f, 6.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(13.1f, 8.0f);
    glVertex2f(15.0f, 8.0f);
    glVertex2f(15.0f, 6.1f);
    glVertex2f(13.1f, 6.1f);
    glEnd();

    //tree 1
    glBegin(GL_QUADS);
    glVertex2f(7.0f, 14.0f);
    glVertex2f(10.0f, 14.0f);
    glVertex2f(9.0f, 17.0f);
    glVertex2f(8.0f, 17.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(7.0f, 14.0f);
    glVertex2f(8.0f, 15.0f);
    glVertex2f(7.0f, 17.0f);
    glVertex2f(6.1f, 17.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(9.0f, 15.0f);
    glVertex2f(10.0f, 14.0f);
    glVertex2f(11.0f, 17.0f);
    glVertex2f(10.0f, 17.0f);
    glEnd();

    //house far 1
    glColor3f(0.7f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(19.0f, 20.0f);
    glVertex2f(21.5f, 20.0f);
    glVertex2f(20.0f, 21.5f);
    glVertex2f(18.0f, 21.5f);
    glVertex2f(18.0f, 20.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(16.5f, 20.0f);
    glVertex2f(17.0f, 20.0f);
    glVertex2f(18.0f, 21.0f);
    glVertex2f(18.0f, 21.5f);
    glEnd();

    //wall
    glColor3f(0.9f, 0.7f, 0.5f);
    glBegin(GL_QUADS);
    glVertex2f(19.0f, 19.0f);
    glVertex2f(21.0f, 19.0f);
    glVertex2f(21.0f, 20.0f);
    glVertex2f(19.0f, 20.0f);
    glEnd();

    glColor3f(0.8f, 0.5f, 0.3f);
    glBegin(GL_POLYGON);
    glVertex2f(17.0f, 19.0f);
    glVertex2f(19.0f, 19.0f);
    glVertex2f(19.0f, 20.0f);
    glVertex2f(18.0f, 21.0f);
    glVertex2f(17.0f, 20.0f);
    glEnd();

    //door
    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(17.6f, 19.0f);
    glVertex2f(18.2f, 19.0f);
    glVertex2f(18.2f, 20.0f);
    glVertex2f(17.6f, 20.0f);
    glEnd();

    //window
     glBegin(GL_QUADS);
    glVertex2f(19.2f, 19.5f);
    glVertex2f(19.7f, 19.5f);
    glVertex2f(19.7f, 20.0f);
    glVertex2f(19.2f, 20.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(20.1f, 19.55f);
    glVertex2f(20.6f, 19.55f);
    glVertex2f(20.6f, 20.0f);
    glVertex2f(20.1f, 20.0f);
    glEnd();

    //river tree 1
    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(44.0f, 19.0f);
    glVertex2f(44.2f, 19.0f);
    glVertex2f(44.2f, 23.0f);
    glVertex2f(44.0f, 23.0f);
    glEnd();

    glColor3f(0.0f, 0.4f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(43.0f, 22.0f);
    glVertex2f(43.2f, 22.0f);
    glVertex2f(45.2f, 24.0f);
    glVertex2f(45.0f, 24.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(45.0f, 22.0f);
    glVertex2f(45.2f, 22.0f);
    glVertex2f(43.2f, 24.0f);
    glVertex2f(43.0f, 24.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(42.5f, 22.5f);
    glVertex2f(43.0f, 22.5f);
    glVertex2f(44.2f, 23.0f);
    glVertex2f(44.2f, 23.1f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(45.5f, 22.5f);
    glVertex2f(45.0f, 22.5f);
    glVertex2f(44.0f, 23.0f);
    glVertex2f(44.0f, 23.1f);
    glEnd();

    //river tree 2
    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(47.0f, 19.0f);
    glVertex2f(47.2f, 19.0f);
    glVertex2f(47.2f, 23.0f);
    glVertex2f(47.0f, 23.0f);
    glEnd();

    glColor3f(0.0f, 0.4f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(46.0f, 22.0f);
    glVertex2f(46.2f, 22.0f);
    glVertex2f(48.2f, 24.0f);
    glVertex2f(48.0f, 24.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(48.0f, 22.0f);
    glVertex2f(48.2f, 22.0f);
    glVertex2f(46.2f, 24.0f);
    glVertex2f(46.0f, 24.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(45.5f, 22.5f);
    glVertex2f(46.0f, 22.5f);
    glVertex2f(47.2f, 23.0f);
    glVertex2f(47.2f, 23.1f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(48.5f, 22.5f);
    glVertex2f(48.0f, 22.5f);
    glVertex2f(47.0f, 23.0f);
    glVertex2f(47.0f, 23.1f);
    glEnd();

    //leave 1
     cx = 46.0f, cy = 20.0f;
     r = 1.5f;

    glColor3f(0.0, 0.4, 0.0);
    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();

    //leave 2
     cx = 44.0f, cy = 19.0f;
     r = 1.5f;

    glColor3f(0.0, 0.4, 0.0);
    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();

     //leave 3
     cx = 48.0f, cy = 19.0f;
     r = 1.5f;

    glColor3f(0.0, 0.4, 0.0);
    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();


     //leave 4
     cx = 50.0f, cy = 18.7f;
     r = 1.5f;

    glColor3f(0.0, 0.4, 0.0);
    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        float angle = 2 * 3.1416f * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();


    //river house 2
    glColor3f(0.7f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(44.0f, 19.0f);
    glVertex2f(47.0f, 19.0f);
    glVertex2f(49.0f, 17.5f);
    glVertex2f(46.0f, 17.5f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(44.0f, 19.0f);
    glVertex2f(44.5f, 19.0f);
    glVertex2f(43.5f, 17.5f);
    glVertex2f(43.0f, 17.5f);
    glEnd();

    //wall
    glColor3f(0.8f, 0.5f, 0.3f);
    glBegin(GL_POLYGON);
    glVertex2f(43.5f, 17.5f);
    glVertex2f(43.5f, 17.0f);
    glVertex2f(46.0f, 17.0f);
    glVertex2f(46.0f, 17.5f);
    glVertex2f(44.3f, 18.8f);
    glEnd();

    //door
    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(44.3f, 17.0f);
    glVertex2f(45.0f, 17.0f);
    glVertex2f(45.0f, 18.0f);
    glVertex2f(44.3f, 18.0f);
    glEnd();

    //river house 1
    glColor3f(0.7f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(45.0f, 17.0f);
    glVertex2f(48.0f, 17.0f);
    glVertex2f(49.0f, 18.5f);
    glVertex2f(46.0f, 18.5f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(49.5f, 17.0f);
    glVertex2f(50.0f, 17.0f);
    glVertex2f(49.0f, 18.5f);
    glVertex2f(48.5f, 18.5f);
    glEnd();

    //wall
    glColor3f(0.9f, 0.7f, 0.5f);
    glBegin(GL_QUADS);
    glVertex2f(45.5f, 16.0f);
    glVertex2f(48.0f, 16.0f);
    glVertex2f(48.0f, 17.0f);
    glVertex2f(45.5f, 17.0f);
    glEnd();

    glColor3f(0.8f, 0.5f, 0.3f);
    glBegin(GL_POLYGON);
    glVertex2f(48.0f, 16.0f);
    glVertex2f(49.5f, 16.2f);
    glVertex2f(49.5f, 17.0f);
    glVertex2f(48.8f, 18.2f);
    glVertex2f(48.0f, 17.0f);
    glEnd();

    //door
    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(48.5f, 16.0f);
    glVertex2f(49.1f, 16.1f);
    glVertex2f(49.1f, 17.0f);
    glVertex2f(48.5f, 17.0f);
    glEnd();

    //window
    glBegin(GL_QUADS);
    glVertex2f(45.9f, 17.0f);
    glVertex2f(46.5f, 17.0f);
    glVertex2f(46.5f, 16.5f);
    glVertex2f(45.9f, 16.5f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(47.0f, 17.0f);
    glVertex2f(47.6f, 17.0f);
    glVertex2f(47.6f, 16.5f);
    glVertex2f(47.0f, 16.5f);
    glEnd();


    //Boat 1
    // Body
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(boatX + 0.0f, 16.0f);
    glVertex2f(boatX + 2.0f, 16.0f);
    glVertex2f(boatX + 4.0f, 17.0f);
    glVertex2f(boatX - 2.0f, 17.0f);
    glEnd();

    // Top
    glColor3f(0.7f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(boatX - 0.5f, 17.0f);
    glVertex2f(boatX + 2.5f, 17.0f);
    glVertex2f(boatX + 2.0f, 18.0f);
    glVertex2f(boatX + 0.0f, 18.0f);
    glEnd();

    // Mast
    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(boatX + 0.8f, 18.0f);
    glVertex2f(boatX + 1.0f, 18.0f);
    glVertex2f(boatX + 1.0f, 20.5f);
    glVertex2f(boatX + 0.8f, 20.5f);
    glEnd();

    // Sail
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(boatX + 1.0f, 18.2f);
    glVertex2f(boatX + 3.0f, 18.2f);
    glVertex2f(boatX + 1.0f, 20.5f);
    glEnd();

    if (isRaining) {
    drawRain();
}

    drawWindmill(46.0f, 12.0f);

    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'r') {
        isRaining = true;
    }
    if (key == 's') {
        isRaining = false;
    }
}

void init(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,50,0,40,-10,10);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 800);
    glutInitWindowPosition(800, 100);
    glutCreateWindow("Mahmud_1137");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);

for(int i = 0; i < 200; i++) {
    rainX[i] = rand() % 50;
    rainY[i] = rand() % 40;
}
glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
