#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// ============================================================
// Vertex Shader
// ============================================================

const char* vertexShaderSource = R"(
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 vertexColor;

uniform vec3 offset;
uniform float rotationAngle;

void main()
{
    // --------------------------------------------------------
    // ROTATION around Y-axis
    // --------------------------------------------------------

    float c = cos(rotationAngle);
    float s = sin(rotationAngle);

    vec3 rotatedPos;

    rotatedPos.x = aPos.x * c - aPos.z * s;
    rotatedPos.y = aPos.y;
    rotatedPos.z = aPos.x * s + aPos.z * c;


    // --------------------------------------------------------
    // TRANSLATION
    // --------------------------------------------------------

    vec3 p = rotatedPos + offset;


    // --------------------------------------------------------
    // Simple 3D isometric projection
    // --------------------------------------------------------

    float screenX =
        (p.x - p.z) * 0.10;

    float screenY =
        p.y * 0.22 -
        (p.x + p.z) * 0.05;

    float depth =
        -(p.x + p.z) * 0.03 -
        p.y * 0.01;


    gl_Position = vec4(
        screenX,
        screenY,
        depth,
        1.0
    );

    vertexColor = aColor;
}
)";


// ============================================================
// Fragment Shader
// ============================================================

const char* fragmentShaderSource = R"(
#version 330 core

in vec3 vertexColor;

out vec4 FragColor;

void main()
{
    FragColor = vec4(
        vertexColor,
        1.0
    );
}
)";


// ============================================================
// Cube movement
// ============================================================

float cubeX = 0.0f;
float cubeZ = 0.0f;


// Cube rotation angle
float cubeAngle = 0.0f;


// Movement speed
float moveSpeed = 2.0f;


// Rotation speed
// radians per second
float rotationSpeed = 2.0f;


// ============================================================
// Keyboard Input
// ============================================================

void processInput(
    GLFWwindow* window,
    float deltaTime
)
{
    float movement =
        moveSpeed * deltaTime;

    float rotation =
        rotationSpeed * deltaTime;


    // --------------------------------------------------------
    // ESC
    // --------------------------------------------------------

    if (
        glfwGetKey(
            window,
            GLFW_KEY_ESCAPE
        )
        == GLFW_PRESS
    )
    {
        glfwSetWindowShouldClose(
            window,
            true
        );
    }


    // --------------------------------------------------------
    // MOVEMENT
    // --------------------------------------------------------

    // W = Forward
    if (
        glfwGetKey(
            window,
            GLFW_KEY_W
        )
        == GLFW_PRESS
    )
    {
        cubeZ -= movement;
    }


    // S = Backward
    if (
        glfwGetKey(
            window,
            GLFW_KEY_S
        )
        == GLFW_PRESS
    )
    {
        cubeZ += movement;
    }


    // A = Left
    if (
        glfwGetKey(
            window,
            GLFW_KEY_A
        )
        == GLFW_PRESS
    )
    {
        cubeX -= movement;
    }


    // D = Right
    if (
        glfwGetKey(
            window,
            GLFW_KEY_D
        )
        == GLFW_PRESS
    )
    {
        cubeX += movement;
    }


    // --------------------------------------------------------
    // ROTATION
    // --------------------------------------------------------

    // Q = Counter-clockwise
    if (
        glfwGetKey(
            window,
            GLFW_KEY_Q
        )
        == GLFW_PRESS
    )
    {
        cubeAngle += rotation;
    }


    // E = Clockwise
    if (
        glfwGetKey(
            window,
            GLFW_KEY_E
        )
        == GLFW_PRESS
    )
    {
        cubeAngle -= rotation;
    }


    // --------------------------------------------------------
    // Plane boundary
    // --------------------------------------------------------

    if (cubeX > 4.5f)
        cubeX = 4.5f;

    if (cubeX < -4.5f)
        cubeX = -4.5f;

    if (cubeZ > 4.5f)
        cubeZ = 4.5f;

    if (cubeZ < -4.5f)
        cubeZ = -4.5f;
}


// ============================================================
// Resize callback
// ============================================================

void framebuffer_size_callback(
    GLFWwindow* window,
    int width,
    int height
)
{
    glViewport(
        0,
        0,
        width,
        height
    );
}


// ============================================================
// MAIN
// ============================================================

int main()
{
    // ========================================================
    // GLFW
    // ========================================================

    glfwInit();


    glfwWindowHint(
        GLFW_CONTEXT_VERSION_MAJOR,
        3
    );

    glfwWindowHint(
        GLFW_CONTEXT_VERSION_MINOR,
        3
    );

    glfwWindowHint(
        GLFW_OPENGL_PROFILE,
        GLFW_OPENGL_CORE_PROFILE
    );


    // ========================================================
    // Window
    // ========================================================

    GLFWwindow* window =
        glfwCreateWindow(
            800,
            800,
            "Moving and Rotating Cube",
            NULL,
            NULL
        );


    if (window == NULL)
    {
        std::cout
            << "Failed to create GLFW window"
            << std::endl;

        glfwTerminate();

        return -1;
    }


    glfwMakeContextCurrent(window);


    glfwSetFramebufferSizeCallback(
        window,
        framebuffer_size_callback
    );


    // ========================================================
    // GLAD
    // ========================================================

    gladLoadGL();


    glViewport(
        0,
        0,
        800,
        800
    );


    // Needed for 3D
    glEnable(
        GL_DEPTH_TEST
    );


    // ========================================================
    // Vertex Shader
    // ========================================================

    GLuint vertexShader =
        glCreateShader(
            GL_VERTEX_SHADER
        );


    glShaderSource(
        vertexShader,
        1,
        &vertexShaderSource,
        NULL
    );


    glCompileShader(
        vertexShader
    );


    // ========================================================
    // Fragment Shader
    // ========================================================

    GLuint fragmentShader =
        glCreateShader(
            GL_FRAGMENT_SHADER
        );


    glShaderSource(
        fragmentShader,
        1,
        &fragmentShaderSource,
        NULL
    );


    glCompileShader(
        fragmentShader
    );


    // ========================================================
    // Shader Program
    // ========================================================

    GLuint shaderProgram =
        glCreateProgram();


    glAttachShader(
        shaderProgram,
        vertexShader
    );


    glAttachShader(
        shaderProgram,
        fragmentShader
    );


    glLinkProgram(
        shaderProgram
    );


    glDeleteShader(
        vertexShader
    );

    glDeleteShader(
        fragmentShader
    );


    // ========================================================
    // Cube vertices
    // x y z   r g b
    // ========================================================

    float cubeVertices[] =
    {
        // Front
        -0.5f,-0.5f, 0.5f,   0.9f,0.2f,0.1f,
         0.5f,-0.5f, 0.5f,   0.9f,0.2f,0.1f,
         0.5f, 0.5f, 0.5f,   0.9f,0.2f,0.1f,

         0.5f, 0.5f, 0.5f,   0.9f,0.2f,0.1f,
        -0.5f, 0.5f, 0.5f,   0.9f,0.2f,0.1f,
        -0.5f,-0.5f, 0.5f,   0.9f,0.2f,0.1f,


        // Back
        -0.5f,-0.5f,-0.5f,   0.5f,0.1f,0.1f,
         0.5f,-0.5f,-0.5f,   0.5f,0.1f,0.1f,
         0.5f, 0.5f,-0.5f,   0.5f,0.1f,0.1f,

         0.5f, 0.5f,-0.5f,   0.5f,0.1f,0.1f,
        -0.5f, 0.5f,-0.5f,   0.5f,0.1f,0.1f,
        -0.5f,-0.5f,-0.5f,   0.5f,0.1f,0.1f,


        // Left
        -0.5f, 0.5f, 0.5f,   0.7f,0.2f,0.1f,
        -0.5f, 0.5f,-0.5f,   0.7f,0.2f,0.1f,
        -0.5f,-0.5f,-0.5f,   0.7f,0.2f,0.1f,

        -0.5f,-0.5f,-0.5f,   0.7f,0.2f,0.1f,
        -0.5f,-0.5f, 0.5f,   0.7f,0.2f,0.1f,
        -0.5f, 0.5f, 0.5f,   0.7f,0.2f,0.1f,


        // Right
         0.5f, 0.5f, 0.5f,   1.0f,0.4f,0.1f,
         0.5f, 0.5f,-0.5f,   1.0f,0.4f,0.1f,
         0.5f,-0.5f,-0.5f,   1.0f,0.4f,0.1f,

         0.5f,-0.5f,-0.5f,   1.0f,0.4f,0.1f,
         0.5f,-0.5f, 0.5f,   1.0f,0.4f,0.1f,
         0.5f, 0.5f, 0.5f,   1.0f,0.4f,0.1f,


        // Bottom
        -0.5f,-0.5f,-0.5f,   0.4f,0.1f,0.05f,
         0.5f,-0.5f,-0.5f,   0.4f,0.1f,0.05f,
         0.5f,-0.5f, 0.5f,   0.4f,0.1f,0.05f,

         0.5f,-0.5f, 0.5f,   0.4f,0.1f,0.05f,
        -0.5f,-0.5f, 0.5f,   0.4f,0.1f,0.05f,
        -0.5f,-0.5f,-0.5f,   0.4f,0.1f,0.05f,


        // Top
        -0.5f,0.5f,-0.5f,   1.0f,0.7f,0.2f,
         0.5f,0.5f,-0.5f,   1.0f,0.7f,0.2f,
         0.5f,0.5f, 0.5f,   1.0f,0.7f,0.2f,

         0.5f,0.5f, 0.5f,   1.0f,0.7f,0.2f,
        -0.5f,0.5f, 0.5f,   1.0f,0.7f,0.2f,
        -0.5f,0.5f,-0.5f,   1.0f,0.7f,0.2f
    };


    // ========================================================
    // Plane
    // ========================================================

    float planeVertices[] =
    {
        -5.0f,0.0f,-5.0f,   0.2f,0.6f,0.2f,
         5.0f,0.0f,-5.0f,   0.2f,0.6f,0.2f,
         5.0f,0.0f, 5.0f,   0.2f,0.6f,0.2f,

         5.0f,0.0f, 5.0f,   0.2f,0.6f,0.2f,
        -5.0f,0.0f, 5.0f,   0.2f,0.6f,0.2f,
        -5.0f,0.0f,-5.0f,   0.2f,0.6f,0.2f
    };


    // ========================================================
    // Cube VAO + VBO
    // ========================================================

    GLuint cubeVAO;
    GLuint cubeVBO;


    glGenVertexArrays(
        1,
        &cubeVAO
    );


    glGenBuffers(
        1,
        &cubeVBO
    );


    glBindVertexArray(
        cubeVAO
    );


    glBindBuffer(
        GL_ARRAY_BUFFER,
        cubeVBO
    );


    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(cubeVertices),
        cubeVertices,
        GL_STATIC_DRAW
    );


    // position
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(
        0
    );


    // color
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)(3 * sizeof(float))
    );


    glEnableVertexAttribArray(
        1
    );


    // ========================================================
    // Plane VAO + VBO
    // ========================================================

    GLuint planeVAO;
    GLuint planeVBO;


    glGenVertexArrays(
        1,
        &planeVAO
    );


    glGenBuffers(
        1,
        &planeVBO
    );


    glBindVertexArray(
        planeVAO
    );


    glBindBuffer(
        GL_ARRAY_BUFFER,
        planeVBO
    );


    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(planeVertices),
        planeVertices,
        GL_STATIC_DRAW
    );


    // position
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(
        0
    );


    // color
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)(3 * sizeof(float))
    );


    glEnableVertexAttribArray(
        1
    );


    // ========================================================
    // Uniform Locations
    // ========================================================

    GLint offsetLocation =
        glGetUniformLocation(
            shaderProgram,
            "offset"
        );


    GLint rotationLocation =
        glGetUniformLocation(
            shaderProgram,
            "rotationAngle"
        );


    // ========================================================
    // Delta Time
    // ========================================================

    float lastFrame = 0.0f;


    // ========================================================
    // MAIN LOOP
    // ========================================================

    while (
        !glfwWindowShouldClose(window)
    )
    {
        // ----------------------------------------------------
        // Delta Time
        // ----------------------------------------------------

        float currentFrame =
            static_cast<float>(
                glfwGetTime()
            );


        float deltaTime =
            currentFrame -
            lastFrame;


        lastFrame =
            currentFrame;


        // ----------------------------------------------------
        // Input
        // ----------------------------------------------------

        processInput(
            window,
            deltaTime
        );


        // ----------------------------------------------------
        // Clear
        // ----------------------------------------------------

        glClearColor(
            0.07f,
            0.13f,
            0.17f,
            1.0f
        );


        glClear(
            GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT
        );


        glUseProgram(
            shaderProgram
        );


        // ====================================================
        // DRAW PLANE
        // ====================================================

        glUniform3f(
            offsetLocation,
            0.0f,
            0.0f,
            0.0f
        );


        // Plane should NOT rotate
        glUniform1f(
            rotationLocation,
            0.0f
        );


        glBindVertexArray(
            planeVAO
        );


        glDrawArrays(
            GL_TRIANGLES,
            0,
            6
        );


        // ====================================================
        // DRAW CUBE
        // ====================================================

        glUniform3f(
            offsetLocation,

            cubeX,

            0.5f,

            cubeZ
        );


        // Send current rotation angle
        glUniform1f(
            rotationLocation,
            cubeAngle
        );


        glBindVertexArray(
            cubeVAO
        );


        glDrawArrays(
            GL_TRIANGLES,
            0,
            36
        );


        // ----------------------------------------------------
        // Display
        // ----------------------------------------------------

        glfwSwapBuffers(
            window
        );


        glfwPollEvents();
    }


    // ========================================================
    // Cleanup
    // ========================================================

    glDeleteVertexArrays(
        1,
        &cubeVAO
    );


    glDeleteBuffers(
        1,
        &cubeVBO
    );


    glDeleteVertexArrays(
        1,
        &planeVAO
    );


    glDeleteBuffers(
        1,
        &planeVBO
    );


    glDeleteProgram(
        shaderProgram
    );


    glfwDestroyWindow(
        window
    );


    glfwTerminate();


    return 0;
}