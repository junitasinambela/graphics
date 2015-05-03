#include <GL/glew.h>
#define GLFW_DLL
#include <GL/glfw3.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

/* Program entry point */

int main(int argc, char *argv[])
{
    // start GL context and O/S window using the GLFW helper library
      if (!glfwInit ()) {
        fprintf (stderr, "ERROR: could not start GLFW3\n");
        return 1;
      }

      GLFWwindow* window = glfwCreateWindow (640, 480, "Hello Triangle", NULL, NULL);
      if (!window) {
        fprintf (stderr, "ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return 1;
      }

    glfwMakeContextCurrent (window);
    glewInit();

    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);
    printf("Renderer: %s\n", renderer);
    printf("Version: %s\n", version);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    //a, b, m, c, m, d, l, e, k, f, j, g, i, h
    float sayap1[] = {
    0.3f, 0.2f, 0.0f,
    0.35f, -0.05f, 0.0f,
    0.7f, -0.2f, 0.0f,
    0.3f, -0.2f, 0.0f,
    0.7f, -0.2f, 0.0f,
    0.45f, -0.3f, 0.0f,
    0.7f, -0.35f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.8f, -0.5f, 0.0f,
    0.65f, -0.6f, 0.0f,
    0.8f, -0.6f, 0.0f,
    0.7f, -0.7f, 0.0f,
    0.8f, -0.7f, 0.0f,
    0.8f, -0.8f, 0.0f
    };

    //a b m l b k c j i c h g c f d e
    float sayap2_ka[] = {
    0.8f, 0.0f, 0.0f,
    0.2f, -0.2f, 0.0f,
    0.65f, -0.15f, 0.0f,
    0.7f, -0.3f, 0.0f,
    0.2f, -0.2f, 0.0f,
    0.5f, -0.4f, 0.0f,
    0.2f, -0.4f, 0.0f,
    0.45f, -0.5f, 0.0f,
    0.5f, -0.6f, 0.0f,
    0.2f, -0.4f, 0.0f,
    0.4f, -0.6f, 0.0f,
    0.25f, -0.7f, 0.0f,
    0.2f, -0.4f, 0.0f,
    0.1f, -0.8f, 0.0f,
    0.0f, -0.5f, 0.0f,
    0.0f, -0.9f, 0.0f
    };

    //a b m l b k c j i c h g c f d e
    float sayap2_ki[] = {
    0.0f, 0.0f, 0.0f,
    0.6f, -0.2f, 0.0f,
    0.15f, -0.15f, 0.0f,
    0.1f, -0.3f, 0.0f,
    0.6f, -0.2f, 0.0f,
    0.3f, -0.4f, 0.0f,
    0.6f, -0.4f, 0.0f,
    0.35f, -0.5f, 0.0f,
    0.3f, -0.6f, 0.0f,
    0.6f, -0.4f, 0.0f,
    0.4f, -0.6f, 0.0f,
    0.55f, -0.7f, 0.0f,
    0.6f, -0.4f, 0.0f,
    0.55f, -0.8f, 0.0f,
    0.8f, -0.5f, 0.0f,
    0.8f, -0.9f, 0.0f
    };

    GLuint vbo = 0;
    glGenBuffersARB(1, &vbo);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, vbo);
    glBufferDataARB(GL_ARRAY_BUFFER_ARB, 48*sizeof(float), sayap2_ki, GL_STATIC_DRAW);

//    GLuint vbo2 = 0;
//    glGenBuffers(1, &vbo2);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
//    glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), points2, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER_ARB, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray(0);
    //shader
    const char* vertex_shader =
    "#version 400\n"
    "in vec3 vp;"
    "void main () {"
    "  gl_Position = vec4 (vp, 1.0);"
    "}";

    const char* fragment_shader =
    "#version 400\n"
    "out vec4 frag_colour;"
    "void main () {"
    "  frag_colour = vec4 (0.5, 1.0, 1.0, 1.0);"
    "}";

    //load GL shader
    GLuint vs = glCreateShader (GL_VERTEX_SHADER);
    glShaderSource (vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource (fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);

    //combine shader
    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, fs);
    glAttachShader(shader_program, vs);
    glLinkProgram(shader_program);

    //drawing
    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader_program);
        glBindVertexArray(vao);

        //glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
        //glEnableVertexAttribArray(1);
        //glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 16);
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

//    glutMainLoop();
    return EXIT_SUCCESS;
}
