#include <iostream>
#include <glad.h>
#include <glfw3.h>
#include <cmath>
#include <fstream>
#include <sstream>

using namespace std;

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window);

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "StudyTwo", NULL, NULL);
    if (window == NULL) {
        cout << "Failed to create GLFW Window" << endl;
        glfwTerminate();
        return -1;

    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    ifstream vShaderFile;
    vShaderFile.open("/Users/kevinjing/Study/C/OpenGLStudy/StudyTwo/vertex.vert");
    stringstream vShaderStream;
    vShaderStream << vShaderFile.rdbuf();
    vShaderFile.close();
    string vertexCode = vShaderStream.str();

    ifstream vFragmentFile;
    vFragmentFile.open("/Users/kevinjing/Study/C/OpenGLStudy/StudyTwo/fragment.frag");
    stringstream vFragmentStream;
    vFragmentStream << vFragmentFile.rdbuf();
    vFragmentFile.close();
    string fragCode = vFragmentStream.str();

    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragCode.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderCode, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
    glCompileShader(fragmentShader);

    GLint success;
    GLchar infoLog[1024];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 1024, NULL, infoLog);
        cout << "Error::vertex Shader compile error: " << infoLog << endl;
    }
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 1024, NULL, infoLog);
        cout << "Error::fragment Shader compile error: " << infoLog << endl;
    }

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 1024, NULL, infoLog);
        cout << "Error::program link error: " << infoLog << endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    float vertices[] = {
            0.0f, 0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5, -0.5f, 0.0f
    };
//    float vertices[] = {
//            -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
//            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
//            0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
////        0.5f,0.5f,0.0f,0.0f,1.0f,0.0f,
////        1.0f,0.0f,0.0f,1.0f,0.0f,0.0f
//    };
    unsigned int indices[] = { // 注意索引从0开始!
            0, 1, 2, // 第一个三角形
//            2, 3, 4  // 第二个三角形
    };

//    float vertices[] = {
//            0.5f, 0.5f, 0.0f,   // 右上角
//            0.5f, -0.5f, 0.0f,  // 右下角
//            -0.5f, -0.5f, 0.0f, // 左下角
//            -0.5f, 0.5f, 0.0f   // 左上角
//    };

//    unsigned int indices[] = { // 注意索引从0开始!
//            0, 1, 3, // 第一个三角形
//            1, 2, 3  // 第二个三角形
//    };
    unsigned int VBO, VAO;
    unsigned int EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
//    glGenBuffers(1, &EBO);
//
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
//    glEnableVertexAttribArray(1);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.4f, 0.8f, 0.66f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);

//        float timeValue = glfwGetTime();
//        float greenV = sin(timeValue) / 2 + 0.5;
//        GLint colorLocation = glGetUniformLocation(program, "ourColor");
//        glUniform4f(colorLocation, 0.0f, greenV, 0.0f, 1.0f);
//        GLint i = glGetUniformLocation(program, "xOffset");
//        glUniform1f(i, 0.5f);//向右平移0.5f

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
//        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//线性的矩形
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);//通过EBO绘制矩形
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}