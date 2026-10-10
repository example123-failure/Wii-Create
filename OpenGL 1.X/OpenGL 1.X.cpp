// OpenGL 1.X.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <GLFW/glfw3.h> 
#include <iostream>
#include <glm/glm.hpp>
#include <cmath>

using namespace std;


const int width = 1920;
const int height = 1080;


float xpos = 0.0f;
float ypos = 0.0f;



float rotationX = 0.0f;
float rotationY = 0.0f;



glm::vec3 campos(0.0f, 0.0f, 0.0f);

glm::vec3 camforward(0.0f, 0.0f, -1.0f);

glm::vec3 camright(1.0f, 0.0f, 0.0f);

glm::vec3 camup(0.0f, 1.0f, 0.0f);

float camx = 0.0f;
float camy = 0.0f;
float camz = 0.0f;

float yaw = 0.0f;
float pitch = 0.0f;



// Functions

void input(GLFWwindow* window, float deltarune, float speed);


void draw_cube();

void update_camera_vectors();


// Main function

int main()
{

    float deltatime = 0.0f;
    float lastframe = 0.0f;

    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    // Request a depth buffer for 3D visibility.
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
       
    GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL 1.X", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);


    // GL STUFF

    
    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);

    glClearColor(0.12f, 0.12f, 0.16f, 1.0f);


    // Change the GL matrix settings to GL_projection to calculate the projection matrices
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();


    float aspect = static_cast<float>(width) / height;
    float fov = 60.0f;

    float nearPlane = 0.01f;
    float farPlane = 1000.0f;

    float top = nearPlane * tanf(fov * 3.14159265f / 360.0f);
    float right = top * aspect;

    glFrustum(-right, right, -top, top, nearPlane, farPlane);

    // Finished calculating projection matrices.

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();




    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltatime = currentFrame - lastframe;
        lastframe = currentFrame;

        // clear both the color of the screen and the depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            

        // Render stuff

        /*
        
        glBegin(GL_TRIANGLES);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex2f(-0.5f - xpos, -0.5f - ypos);

            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex2f(0.5f - xpos, -0.5f - ypos);

            glColor3f(0.0f, 0.0f, 1.0f - ypos);
            glVertex2f(0.0f - xpos, 1.0f - ypos);
        glEnd();

        */



        // Model view is how the model is viewed, and the MatrixMode should be set to GL_MODELVIEW when this is true
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();


        // Transform the vertices 6 units from camera
        

        glRotatef(-pitch, 1.0f, 0.0f, 0.0f);
        glRotatef(-yaw, 0.0f, 1.0f, 0.0f);

        glTranslatef(
            -campos.x,
            -campos.y,
            -campos.z
        );

        draw_cube();
        glfwSwapBuffers(window);

        glfwPollEvents();
        input(window, deltatime, 10.0f);
        



    }
    glfwTerminate();
    return 0;
}




// Function def


void input(GLFWwindow* window, float deltarune, float speed)
{


    int state = glfwGetKey(window, GLFW_KEY_W);
    if (state == GLFW_PRESS)
    {
        campos += camforward * speed * deltarune;
    }
    state = glfwGetKey(window, GLFW_KEY_A);
    if (state == GLFW_PRESS)
    {
        campos -= camright * speed * deltarune;
    }
    state = glfwGetKey(window, GLFW_KEY_S);
    if (state == GLFW_PRESS)
    {
        campos -= camforward * speed * deltarune;
    }
    state = glfwGetKey(window, GLFW_KEY_D);
    if (state == GLFW_PRESS)
    {
        campos += camright * speed * deltarune;
    }

    float turnSpeed = 90.0f * deltarune;

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        yaw += turnSpeed;

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        yaw -= turnSpeed;

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        pitch += turnSpeed;

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        pitch -= turnSpeed;



    if (pitch > 89.0f)
        pitch = 89.0f;

    if (pitch < -89.0f)
        pitch = -89.0f;

    update_camera_vectors();
    
}

void draw_cube()
{
    glBegin(GL_QUADS);

    // Front face: red
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-1, -1, 1);
    glVertex3f(1, -1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(-1, 1, 1);

    // Back face: green
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1, -1, -1);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, 1, -1);
    glVertex3f(1, 1, -1);

    // Right face: blue
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(1, -1, 1);
    glVertex3f(1, -1, -1);
    glVertex3f(1, 1, -1);
    glVertex3f(1, 1, 1);

    // Left face: yellow
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, -1, 1);
    glVertex3f(-1, 1, 1);
    glVertex3f(-1, 1, -1);

    // Top face: magenta
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(-1, 1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(1, 1, -1);
    glVertex3f(-1, 1, -1);

    // Bottom face: cyan
    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(-1, -1, -1);
    glVertex3f(1, -1, -1);
    glVertex3f(1, -1, 1);
    glVertex3f(-1, -1, 1);

    glEnd();
}


void update_camera_vectors()
{
    float yawRad = glm::radians(yaw);
    float pitchRad = glm::radians(pitch);


    camforward = glm::normalize(glm::vec3(
        -sin(yawRad) * cos(pitchRad),
        sin(pitchRad),
        -cos(yawRad) * cos(pitchRad)
    ));

    glm::vec3 worldUp(0.0f, 1.0f, 0.0f);


    camright = glm::normalize(
        glm::cross(camforward, worldUp)
    );

    camup = glm::normalize(
        glm::cross(camright, camforward)
    );
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
