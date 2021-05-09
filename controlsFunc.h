#pragma once
Camera cam(glm::vec3(0.0f, 0.0f, 3.0f));
extern float deltaTime;
extern float lastFrame;
extern unsigned int SRC_WIDT;
extern unsigned int SRC_HEIGHT;
extern float lastX;
extern float lastY;
extern bool firstMouse;
void processInput(GLFWwindow*);
void mouseCallback(GLFWwindow*, double, double);
void scrollCallback(GLFWwindow*, double, double);
