#include "Renderer.h"

Renderer::Renderer()
{
	createWindow(800, 800);
	screenHeight = 800;
	screenWidth = 800;
}


Renderer::~Renderer()
{
}

int Renderer::createWindow(int width, int height)
{
	std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	// Create a GLFWwindow object that we can use for GLFW's functions
	this->window = glfwCreateWindow(width, height, "Procedural Terrain", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	// Define the viewport dimensions
	int vwidth, vheight;
	glfwGetFramebufferSize(window, &vwidth, &vheight);
	glViewport(0, 0, vwidth, vheight);

	return 0;
}

void Renderer::render(Camera* camera, Scene* scene)
{
	glm::mat4 view;
	view = camera->GetViewMatrix();
	glm::mat4 projection;
	projection = glm::perspective(1.0f, (float)screenWidth / (float)screenHeight, 0.1f, 1000.0f);

	for (int i = 0; i < scene->meshes.size(); i++) {
		Mesh* mesh = scene->meshes.at(i);

		if (mesh->geometry->needsUpdate) {
			std::cout << "uploading geometry" << mesh->material->program << std::endl;
			uploadGeometry(mesh->geometry);
		}

		mesh->material->use(); /* use the shader of the mesh */

		GLint modelLoc = glGetUniformLocation(mesh->material->program, "model");
		GLint viewLoc = glGetUniformLocation(mesh->material->program, "view");
		GLint projLoc = glGetUniformLocation(mesh->material->program, "projection");

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mesh->getModelMatrix()));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(mesh->geometry->VAO); /* bind to the geometry of the mesh */
		glDrawElements(GL_TRIANGLES, mesh->geometry->indices.size(), GL_UNSIGNED_INT, 0);

	}
	glBindVertexArray(0); /* unbind any geometry */

	// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
	glfwPollEvents();
	// Swap the screen buffers
	glfwSwapBuffers(window);
}

void Renderer::terminate() {
	glfwTerminate();
}

bool Renderer::shouldClose()
{
	return glfwWindowShouldClose(window);
}

void Renderer::uploadGeometry(Geometry* g) {
	glGenVertexArrays(1, &g->VAO);
	glGenBuffers(1, &g->VBO);
	glGenBuffers(1, &g->EBO);

	glBindVertexArray(g->VAO);
		// 2. Copy our vertices array in a buffer for OpenGL to use
		glBindBuffer(GL_ARRAY_BUFFER, g->VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g->vertices), &g->vertices, GL_STATIC_DRAW);
		// 2.5 upload indices
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g->indices), &g->indices, GL_STATIC_DRAW);

		// 3. Then set our vertex attributes pointers
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		//4. Unbind the VAO
	glBindVertexArray(0);
	g->needsUpdate = false;
}