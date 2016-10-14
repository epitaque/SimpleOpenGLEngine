#include "LocalPlayer.h"



LocalPlayer::LocalPlayer(glm::vec3 position, GLfloat movementSpeed, GLfloat mouseSensitivity) :
	Player(position), camera(Camera(glm::vec3(0.0f, 0.0f, 0.0f))), movementSpeed(movementSpeed), mouseSensitivity(mouseSensitivity)
{
}


LocalPlayer::~LocalPlayer()
{
}

void LocalPlayer::key_callback(GLFWwindow * window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void LocalPlayer::mouse_callback(GLFWwindow * window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left

	lastX = xpos;
	lastY = ypos;

	processMouse(xoffset, yoffset);
}

void LocalPlayer::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	//camera.ProcessMouseScroll(yoffset);
}

void LocalPlayer::processMouse(double xoffset, double yoffset) {
	doCameraRotation(xoffset, yoffset);
}

void LocalPlayer::processKeyboard(GLfloat deltaTime) {
	if (keys[GLFW_KEY_W]) doMovement(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S]) doMovement(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A]) doMovement(LEFT, deltaTime);
	if (keys[GLFW_KEY_D]) doMovement(RIGHT, deltaTime);
}

void LocalPlayer::doMovement(Direction direction, GLfloat deltaTime)
{
	GLfloat velocity = deltaTime * movementSpeed;
	switch (direction) {
	case FORWARD:
		translate(getFront() * velocity);
	case BACKWARD:
		translate(-1.0f * getFront() * velocity);
	case LEFT:
		translate(-1.0f * getRight() * velocity);
	case RIGHT:
		translate(getRight() * velocity);
	}
	std::cout << "doing movement, position: " << direction << ", cord: " << position.x << ", " << position.y << ", " << position.z << std::endl;
}

void LocalPlayer::doCameraRotation(double xdelta, double ydelta) {
	/*if (this->Pitch > 89.0f)
		this->Pitch = 89.0f;
	if (this->Pitch < -89.0f)
		this->Pitch = -89.0f; */
	camera.rotate(glm::vec3(ydelta, xdelta, 0.0f));
}

void LocalPlayer::update(GLfloat delta) {
	processKeyboard(delta);
}