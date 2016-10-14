#pragma once

#include "Renderer.h"
#include "Camera.h"
#include "Scene.h"
#include "LocalPlayer.h"

#include "InputManager.h"

#include "CubeGeometry.h"
#include "PlaneGeometry.h"
#include "Mesh.h"
#include "Texture.h"
#include "MeshBasicMaterial.h"


// Window dimensions

class Game
{
public:
	Game();
	~Game();

	const GLuint WIDTH = 800, HEIGHT = 600;

	void start();
	void loop();

	void addTestMeshes();
private:
	Renderer renderer;
	Camera camera;
	Scene scene;
	LocalPlayer player;

	InputManager inputManager;

	GLfloat currentFrame;
	GLfloat deltaTime;
	GLfloat lastFrame;

	Mesh* testmesh;
};

