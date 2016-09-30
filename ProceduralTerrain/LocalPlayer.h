#pragma once
#include "Player.h"
#include "Camera.h"
#include "InputReceiverInterface.h"

class LocalPlayer : public Player, public InputReceiverInterface
{
public:
	Camera camera;

	LocalPlayer(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));
	~LocalPlayer();

	virtual void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	virtual void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	virtual void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void doMovement(GLfloat deltaTime);
private:
	bool keys[1024];
	bool firstMouse;
	double lastX, lastY;
};

