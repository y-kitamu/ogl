#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
extern GLFWwindow* window; 


namespace {
    glm::vec3 position = glm::vec3(0, 0, 5);
    float horizontalAngle = 3.14f;
    float verticalAngle = 0.0f;
    float FoV = 45.0f;;
    float speed = 3.0f;
    float mouseSpeed = 0.005f;
    float radius = 5.0f;
    float height = 0.0f;
    glm::mat4 ProjectionMatrix, ViewMatrix;
    double currentTime, lastTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);
} // namespace

void scroll_callback (GLFWwindow * window, double xoffset, double yoffset) {
    FoV -= yoffset * 5;
    return;
};

void computeMatrixFromInputs() {

    double xpos, ypos;

    glfwGetCursorPos(window, &xpos, &ypos);
    glfwSetCursorPos(window, 1024 / 2, 768 / 2);

    // horizontalAngle += mouseSpeed  * float(1024 / 2 - xpos);
    // verticalAngle += mouseSpeed  * float(768 / 2 - ypos);

    glm::vec3 direction(glm::cos(verticalAngle) * glm::sin(horizontalAngle),
                        glm::sin(verticalAngle),
                        glm::cos(verticalAngle) * glm::cos(horizontalAngle));

    glm::vec3 right(glm::sin(horizontalAngle - 3.14f / 2.0f), 0, glm::cos(horizontalAngle - 3.14 / 2.0f));
    glm::vec3 up = glm::cross(right, direction);

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        height += deltaTime * speed;
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        height -= deltaTime * speed;
    }

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        radius += deltaTime * speed;
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        radius -= deltaTime * speed;
    }

    position = glm::vec3(radius * cos(currentTime), height, radius * sin(currentTime));
        
    currentTime = glfwGetTime();
    deltaTime = float(currentTime - lastTime);
    lastTime= currentTime;

    glfwSetScrollCallback(window, scroll_callback);

    ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
    ViewMatrix = glm::lookAt(position, glm::vec3(0, 0, 0), up);
}

glm::mat4 getProjectionMatrix() {
    return ProjectionMatrix;
}

glm::mat4 getViewMatrix() {
    return ViewMatrix;
}

