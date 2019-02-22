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

    // glfwGetCursorPos(window, &xpos, &ypos);
    // glfwSetCursorPos(window, 1024 / 2, 768 / 2);

    // horizontalAngle += mouseSpeed * deltaTime * float(1024 / 2 - xpos);
    // verticalAngle += mouseSpeed * deltaTime * float(768 / 2 - xpos);

    glm::vec3 direction(glm::cos(verticalAngle) * glm::sin(horizontalAngle),
                        glm::sin(verticalAngle),
                        glm::cos(verticalAngle) * glm::cos(horizontalAngle));

    glm::vec3 right(glm::sin(horizontalAngle - 3.14f / 2.0f), 0, glm::cos(horizontalAngle - 3.14 / 2.0f));
    glm::vec3 up = glm::cross(right, direction);

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        position += direction * deltaTime * speed;
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        position -= direction * deltaTime * speed;
    }

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        position += right * deltaTime * speed;
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        position -= right * deltaTime * speed;
    }
    
    currentTime = glfwGetTime();
    deltaTime = float(currentTime - lastTime);

    glfwSetScrollCallback(window, scroll_callback);

    ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
    ViewMatrix = glm::lookAt(position, position + direction, up);
}

glm::mat4 getProjectionMatrix() {
    return ProjectionMatrix;
}

glm::mat4 getViewMatrix() {
    return ViewMatrix;
}

