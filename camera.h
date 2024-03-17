#include"glad/glad.h"
#include"GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
static class Camera {

	glm::vec3 cameraTarget;//ԭ��

	glm::vec3 cameraRight;//�����
	glm::vec3 cameraUp;//�����

public:
	glm::vec3 cameraPos;//���λ��
	glm::mat4 view;
	glm::vec3 cameraDirection;//�������
	float lastX, lastY;
	float pitch, yaw;
	bool firstMouse;
	Camera() {
		glm::vec3 cameraPos = glm::vec3(0.0f, 5.0f, 7.0f);
		glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
		this->view = glm::mat4(1.0f);
		this->cameraPos = cameraPos;
		this->cameraTarget = cameraTarget;
		this->cameraDirection = cameraTarget- cameraPos ;
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);//�Ϸ���
		this->cameraRight = glm::cross(up, cameraDirection);//�����
		this->cameraUp = glm::cross(cameraDirection, cameraRight);//�����
		this->view = glm::lookAt(cameraPos, cameraPos + cameraDirection, cameraUp);
		this->lastX = 400;
		this->lastY = 300;
		this->pitch = 0;
		this->yaw = 0;
		this->firstMouse = 1;
	}
	glm::mat4 CameraMove(float speed, GLFWwindow* window) {
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			speed += 0.2f;
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			cameraPos += speed * cameraDirection;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			cameraPos -= speed * cameraDirection;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			cameraPos += this->cameraRight * speed;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			cameraPos -= this->cameraRight * speed;
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
			cameraPos += this->cameraUp * speed;
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
			cameraPos -= this->cameraUp * speed;

		view = glm::lookAt(cameraPos, cameraPos + cameraDirection, cameraUp);
		return this->view;
	}
	void recomp() {
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);//�Ϸ���
		this->cameraRight = glm::cross(up, cameraDirection);//�����
		this->cameraUp = glm::cross(cameraDirection, cameraRight);//�����
	}
};