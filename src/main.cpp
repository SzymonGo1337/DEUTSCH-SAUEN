#include "libs.hpp"

bool loadShaders(GLuint &program) {
    bool loadSuccess = true;
    char infoLog[512];
    GLint success;

    std::string temp = "";
    std::string src = "";

    std::ifstream in_file;

    in_file.open("vertex_core.glsl");

    if(in_file.is_open()) {
        while(std::getline(in_file, temp)) {
            src += temp + "\n";
        }
    } else {
        std::cerr << "SHADER ERROR COULDN'T LOAD VERTEX FILE" << "\n";
        loadSuccess = false;
    }

    in_file.close();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const GLchar* vertSrc = src.c_str();
    glShaderSource(vertexShader, 1, &vertSrc, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "SHADER ERROR COULDN'T COMPILE VERTEX FILE" << "\n";
        std::cerr << infoLog << "\n";
        loadSuccess = false;
    }

    temp = "";
    src = "";

    in_file.open("fragment_core.glsl");

    if(in_file.is_open()) {
        while(std::getline(in_file, temp)) {
            src += temp + "\n";
        }
    } else {
        std::cerr << "SHADER ERROR COULDN'T LOAD FRAGMENT FILE" << "\n";
        loadSuccess = false;
    }

    in_file.close();

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar* fragSrc = src.c_str();
    glShaderSource(fragmentShader, 1, &fragSrc, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "SHADER ERROR COULDN'T COMPILE FRAGMENT FILE" << "\n";
        std::cerr << infoLog << "\n";
        loadSuccess = false;
    }

    program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(program, 512, NULL, infoLog);
        std::cerr << "SHADER ERROR COULDN'T COMPILE PROGRAM FILE" << "\n";
        std::cerr << infoLog << "\n";
        loadSuccess = false;
    }

    glUseProgram(0);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return loadSuccess;
}

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

    GLuint core_program;
    if(!loadShaders(core_program)) {
        glfwTerminate();
    }

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


        glfwSwapBuffers(window);
        glFlush();
    }

    glfwTerminate();
    return 0;
}