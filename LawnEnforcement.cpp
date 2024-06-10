#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <iostream>
#include <Windows.h>

#include "Game.h"
#include "SettingsLoader.h"

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

GLFWwindow* window;
double lastFrameTime;
int viewportWidth = 1920, viewportHeight = 1080;

std::shared_ptr<Game> game;

void update();
void draw();
void resizeWindow(GLFWwindow* window, int width, int height);

int main()
{
	if (!glfwInit())
		throw std::runtime_error("Could not initialize glfw");

	window = glfwCreateWindow(viewportWidth, viewportHeight, "Lawn Enforcement", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		throw std::runtime_error("Could not initialize glfw");
	}

	glfwMakeContextCurrent(window);
	glfwSetWindowSizeCallback(window, resizeWindow);
	glfwSetScrollCallback(window, [](GLFWwindow*, double, double)
		{
			game->swapTools();
		});
	glfwSetKeyCallback(window, [](GLFWwindow* window, const int key, int, int, int)
		{
			if (key == GLFW_KEY_ESCAPE)
				glfwSetWindowShouldClose(window, true);
		});

	// Used as VSync to prevent 100% GPU usage
	glfwSwapInterval(1);

	glEnable(GL_DEPTH_TEST);

	tigl::init();

	srand(static_cast<unsigned int>(GetTickCount()));
	lastFrameTime = glfwGetTime();

	const SettingsLoader sl("config/game_settings.txt");
	game = std::make_shared<Game>(window, sl.get());

	while (!glfwWindowShouldClose(window))
	{
		update();
		draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

void update()
{
	const double currentFrameTime = glfwGetTime();
	const float deltaTime = static_cast<float>(currentFrameTime - lastFrameTime);
	lastFrameTime = currentFrameTime;

	game->update(deltaTime);
}

void draw()
{
	glViewport(0, 0, viewportWidth, viewportHeight);
	glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	game->draw();
}

void resizeWindow(GLFWwindow*, const int width, const int height)
{
	viewportWidth = width;
	viewportHeight = height;
}
