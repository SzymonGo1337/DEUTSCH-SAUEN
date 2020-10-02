#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main() {
    glfwInit();

    int framebufferWidth = 0, framebufferHeight = 0;

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(640, 480, "DEUTSCH-SAUEN", NULL, NULL);
    if(window == NULL) {
        const char* description;
        int code = glfwGetError(&description);
        std::cerr << "WINDOW ERROR: " << code << " | " << description << "\n";
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
    glViewport(0, 0, framebufferWidth, framebufferHeight);

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;

    if(glewInit() != GLEW_OK) {
        std::cerr << "ERROR: GLEW INIT FAILED" << "\n";
        glfwTerminate();
    }

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


        glfwSwapBuffers(window);
        glFlush();
    }

    glfwTerminate();
    return 0;
}