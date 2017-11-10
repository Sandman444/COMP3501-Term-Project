#include <iostream>
#include <time.h>
#include <sstream>

#include "game.h"
#include "bin/path_config.h"

namespace game {

	// Some configuration constants
	// They are written here as global variables, but ideally they should be loaded from a configuration file

	// Main window settings
	const std::string window_title_g = "Demo";
	const unsigned int window_width_g = 800;
	const unsigned int window_height_g = 600;
	const bool window_full_screen_g = false;

	// Viewport and camera settings
	float camera_near_clip_distance_g = 0.01;
	float camera_far_clip_distance_g = 1000.0;
	float camera_fov_g = 20.0; // Field-of-view of camera
	const glm::vec3 viewport_background_color_g(0.0, 0.0, 0.0);
	glm::vec3 camera_position_g(0.0, 0.0, 50.0);
	glm::vec3 camera_look_at_g(0.0, 0.0, 0.0);
	glm::vec3 camera_up_g(0.0, 1.0, 0.0);

	//space ship properties
	glm::vec3 velocity(0.0, 0.0, 0.0);
	const float acceleration = 0.1;

	// Materials 
	const std::string material_directory_g = MATERIAL_DIRECTORY;


	Game::Game(void) {

		// Don't do work in the constructor, leave it for the Init() function
	}


	void Game::Init(void) {

		// Run all initialization steps
		std::cout << "Press tab to fire weapon" << std::endl;
		InitWindow();
		InitView();
		InitEventHandlers();

		// Set variables
		animating_ = true;
	}


	void Game::InitWindow(void) {

		// Initialize the window management library (GLFW)
		if (!glfwInit()) {
			throw(GameException(std::string("Could not initialize the GLFW library")));
		}

		// Create a window and its OpenGL context
		if (window_full_screen_g) {
			window_ = glfwCreateWindow(window_width_g, window_height_g, window_title_g.c_str(), glfwGetPrimaryMonitor(), NULL);
		}
		else {
			window_ = glfwCreateWindow(window_width_g, window_height_g, window_title_g.c_str(), NULL, NULL);
		}
		if (!window_) {
			glfwTerminate();
			throw(GameException(std::string("Could not create window")));
		}

		// Make the window's context the current one
		glfwMakeContextCurrent(window_);

		// Initialize the GLEW library to access OpenGL extensions
		// Need to do it after initializing an OpenGL context
		glewExperimental = GL_TRUE;
		GLenum err = glewInit();
		if (err != GLEW_OK) {
			throw(GameException(std::string("Could not initialize the GLEW library: ") + std::string((const char *)glewGetErrorString(err))));
		}
	}


	void Game::InitView(void) {

		// Set up z-buffer
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		// Set viewport
		int width, height;
		glfwGetFramebufferSize(window_, &width, &height);
		glViewport(0, 0, width, height);

		// Set up camera
		// Set current view
		camera_.SetView(camera_position_g, camera_look_at_g, camera_up_g);
		// Set projection
		camera_.SetProjection(camera_fov_g, camera_near_clip_distance_g, camera_far_clip_distance_g, width, height);
	}


	void Game::InitEventHandlers(void) {

		// Set event callbacks
		glfwSetKeyCallback(window_, KeyCallback);
		glfwSetFramebufferSizeCallback(window_, ResizeCallback);

		// Set pointer to game object, so that callbacks can access it
		glfwSetWindowUserPointer(window_, (void *) this);
	}


	void Game::SetupResources(void) {

		// Create a simple sphere to represent the asteroids
		resman_.CreateSphere("SimpleSphereMesh", 1.0, 10, 10);

		//Create a simple cube to be formed into a laser
		resman_.CreateCube("SimpleCubeMesh");

		//Create a simple cylinder
		resman_.CreateCylinder("SimpleCylinderMesh", 0.5, 0.5, 90, 30);

		//Create a simple torus
		resman_.CreateTorus("SimpleTorusMesh");

		// Load material to be applied to asteroids
		std::string filename = std::string(MATERIAL_DIRECTORY) + std::string("/material");
		resman_.LoadResource(Material, "ObjectMaterial", filename.c_str());
	}


	void Game::SetupScene(void) {
		SceneNode* helicopter = scene_.CreateNode("helicopter", resman_.GetResource("SimpleCylinderMesh"), resman_.GetResource("ObjectMaterial"));
		// Set background color for the scene
		scene_.SetBackgroundColor(viewport_background_color_g);
	}


	void Game::MainLoop(void) {

		// Loop while the user did not close the window
		while (!glfwWindowShouldClose(window_)) {
			// Animate the scene
			if (animating_) {
				static double last_time = 0;
				double current_time = glfwGetTime();
				if ((current_time - last_time) > 0.05) {
					scene_.Update();
					camera_.Translate(velocity);
					last_time = current_time;
				}
			}

			// Draw the scene
			scene_.Draw(&camera_);

			// Push buffer drawn in the background onto the display
			glfwSwapBuffers(window_);

			// Update other events like input handling
			glfwPollEvents();
		}
	}


	void Game::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

		// Get user data with a pointer to the game class
		void* ptr = glfwGetWindowUserPointer(window);
		Game *game = (Game *)ptr;

		// Quit game if 'q' is pressed
		if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}

		// Stop animation if space bar is pressed
		if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
			game->animating_ = (game->animating_ == true) ? false : true;
		}


		// View control
		float rot_factor(glm::pi<float>() / 180);

		if (key == GLFW_KEY_UP) {
			game->camera_.Pitch(rot_factor);
		}
		if (key == GLFW_KEY_DOWN) {
			game->camera_.Pitch(-rot_factor);
		}
		if (key == GLFW_KEY_LEFT) {
			game->camera_.Yaw(rot_factor);
		}
		if (key == GLFW_KEY_RIGHT) {
			game->camera_.Yaw(-rot_factor);
		}
		if (key == GLFW_KEY_S) {
			game->camera_.Roll(-rot_factor);
		}
		if (key == GLFW_KEY_X) {
			game->camera_.Roll(rot_factor);
		}
		if (key == GLFW_KEY_A) {//forward thrusters
			velocity += game->camera_.GetForward() * acceleration;
		}
		if (key == GLFW_KEY_Z) { //braking thrusters
			velocity -= game->camera_.GetForward() * acceleration;
		}
		if (key == GLFW_KEY_J){//left thrusters
			velocity -= game->camera_.GetSide() * acceleration;
		}
		if (key == GLFW_KEY_L){//right thrusters
			velocity += game->camera_.GetSide() * acceleration;
		}
		if (key == GLFW_KEY_I){//up thrusters
			velocity += game->camera_.GetUp() * acceleration;
		}
		if (key == GLFW_KEY_K){//down thrusters
			velocity -= game->camera_.GetUp() * acceleration;
		}
	}


	void Game::ResizeCallback(GLFWwindow* window, int width, int height) {

		// Set up viewport and camera projection based on new window size
		glViewport(0, 0, width, height);
		void* ptr = glfwGetWindowUserPointer(window);
		Game *game = (Game *)ptr;
		game->camera_.SetProjection(camera_fov_g, camera_near_clip_distance_g, camera_far_clip_distance_g, width, height);
	}


	Game::~Game() {

		glfwTerminate();
	}

} // namespace game
