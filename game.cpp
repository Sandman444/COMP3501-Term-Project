#include <iostream>
#include <time.h>
#include <sstream>

#include "game.h"
#include "bin/path_config.h"

namespace game {

// Some configuration constants
// They are written here as global variables, but ideally they should be loaded from a configuration file

// Main window settings
const std::string window_title_g = "Helicopter Assault Game";
const unsigned int window_width_g = 800;
const unsigned int window_height_g = 600;
const bool window_full_screen_g = false;

// Viewport and camera settings
float camera_near_clip_distance_g = 0.01;
float camera_far_clip_distance_g = 1000.0;
float camera_fov_g = 50.0; // Field-of-view of camera
const glm::vec3 viewport_background_color_g(100.0 / 255.0, 181.0 / 255.0, 246.0 / 255.0);
//const glm::vec3 viewport_background_color_g(1, 1, 1);
glm::vec3 camera_position_g(0.0, 0.0, 0.0);
glm::vec3 camera_look_at_g(0.0, 0.0, 0.0);
glm::vec3 camera_up_g(0.0, 1.0, 0.0);

// Materials 
const std::string material_directory_g = MATERIAL_DIRECTORY;


Game::Game(void){

    // Don't do work in the constructor, leave it for the Init() function
}


void Game::Init(void){

    // Run all initialization steps
    InitWindow();
    InitView();
    InitEventHandlers();

	helicopterProjectileManager.setScene(&scene_);
	enemyManager.setScene(&scene_);
	enemyManager.setPlayerManager(&helicopterProjectileManager);

	// Add updateables
	updateables.push_back((Updateable*)&scene_);
	updateables.push_back((Updateable*)&inputController);
	updateables.push_back((Updateable*)&helicopterProjectileManager);
	updateables.push_back((Updateable*)&enemyManager);

    // Set variables
    animating_ = true;
}

       
void Game::InitWindow(void){

    // Initialize the window management library (GLFW)
    if (!glfwInit()){
        throw(GameException(std::string("Could not initialize the GLFW library")));
    }

    // Create a window and its OpenGL context
    if (window_full_screen_g){
        window_ = glfwCreateWindow(window_width_g, window_height_g, window_title_g.c_str(), glfwGetPrimaryMonitor(), NULL);
    } else {
        window_ = glfwCreateWindow(window_width_g, window_height_g, window_title_g.c_str(), NULL, NULL);
    }
    if (!window_){
        glfwTerminate();
        throw(GameException(std::string("Could not create window")));
    }

    // Make the window's context the current one
    glfwMakeContextCurrent(window_);

    // Initialize the GLEW library to access OpenGL extensions
    // Need to do it after initializing an OpenGL context
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK){
        throw(GameException(std::string("Could not initialize the GLEW library: ")+std::string((const char *) glewGetErrorString(err))));
    }
}


void Game::InitView(void){

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
	// Add camera to scene
	scene_.addNode(&camera_);
}


void Game::InitEventHandlers(void){

    // Set event callbacks
    glfwSetKeyCallback(window_, KeyCallback);
    glfwSetFramebufferSizeCallback(window_, ResizeCallback);

    // Set pointer to game object, so that callbacks can access it
    glfwSetWindowUserPointer(window_, (void *) this);
}


void Game::SetupResources(void){
	ResourceManager::theResourceManager().CreateCylinder("CylinderMesh");
	ResourceManager::theResourceManager().CreateCube("CubeMesh");
	ResourceManager::theResourceManager().CreateSphere("SphereMesh");
	ResourceManager::theResourceManager().CreateWall("WallMesh");
	ResourceManager::theResourceManager().CreateSphereParticles("SphereParticles");
	ResourceManager::theResourceManager().CreateTorusParticles("TorusParticles");


	std::string filename;

    // Load material
    filename = std::string(MATERIAL_DIRECTORY) + std::string("/material");
	ResourceManager::theResourceManager().LoadResource(Material, "ObjectMaterial", filename.c_str());

	filename = std::string(MATERIAL_DIRECTORY) + std::string("/ground_material");
	ResourceManager::theResourceManager().LoadResource(Material, "GroundMaterial", filename.c_str());

	filename = std::string(MATERIAL_DIRECTORY) + std::string("/player");
	ResourceManager::theResourceManager().LoadResource(Material, "PlayerMaterial", filename.c_str());

	filename = std::string(MATERIAL_DIRECTORY) + std::string("/enemy");
	ResourceManager::theResourceManager().LoadResource(Material, "EnemyMaterial", filename.c_str());

	filename = std::string(MATERIAL_DIRECTORY) + std::string("/laser");
	ResourceManager::theResourceManager().LoadResource(Material, "LaserMaterial", filename.c_str());

	// Load ground texture
	filename = std::string(MATERIAL_DIRECTORY) + std::string("/ground.jpg");
	ResourceManager::theResourceManager().LoadResource(Texture, "TronGrid", filename.c_str());
}


void Game::SetupScene(void){

    // Set background color for the scene
    scene_.SetBackgroundColor(viewport_background_color_g);

	ground = new Ground("WallMesh", "GroundMaterial", "TronGrid");
	scene_.addNode(ground);

	helicopter = new Helicopter("PlayerMaterial", &helicopterProjectileManager);
	helicopter->SetPosition(glm::vec3(0.0, 3.0, 0.0));
	inputController.control(helicopter);
	camera_.follow(helicopter);
	camera_.setViewMode("third person");
	scene_.addNode(helicopter);

	enemyManager.setPlayer(helicopter);
	enemyManager.spawnTank(glm::vec2(-10.0, 2.0));
	enemyManager.spawnTank(glm::vec2(-30.0, -0.5));
	enemyManager.spawnTank(glm::vec2(-20.0, 1.0));
	enemyManager.spawnTank(glm::vec2(-15.0, -1.0));
	enemyManager.spawnTurret(glm::vec2(-3.0, 3.0));
	enemyManager.spawnTurret(glm::vec2(-2.0, 1.0));
	enemyManager.spawnTurret(glm::vec2(-4.0, -1.5));
	enemyManager.spawnTurret(glm::vec2(-4.0, 1.5));
	enemyManager.spawnTurret(glm::vec2(0.5, -0.5));

	Helicopter *otherCopter = new Helicopter("EnemyMaterial", &helicopterProjectileManager);
	scene_.addNode(otherCopter);
	otherCopter->SetPosition(helicopter->GetPosition() + helicopter->getForward());

	helicopterProjectileManager.addCollideable(otherCopter);
}


void Game::MainLoop(void){

    // Loop while the user did not close the window
    while (!glfwWindowShouldClose(window_)){
        // Animate the scene
        if (animating_){
            static double last_time = 0;
            double current_time = glfwGetTime();
            if ((current_time - last_time) > 0.01){
				//Update every updateable
				for (std::vector<Updateable*>::iterator it = updateables.begin(); it != updateables.end(); ++it) {
					(*it)->update();
				}

                // Update timer
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


void Game::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){

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

	if (key == GLFW_KEY_1) {
		game->camera_.setViewMode("first person");
	}

	if (key == GLFW_KEY_2) {
		game->camera_.setViewMode("third person");
	}

	InputController::handleInput(key, scancode, action, mods);
}


void Game::ResizeCallback(GLFWwindow* window, int width, int height){

    // Set up viewport and camera projection based on new window size
    glViewport(0, 0, width, height);
    void* ptr = glfwGetWindowUserPointer(window);
    Game *game = (Game *) ptr;
    game->camera_.SetProjection(camera_fov_g, camera_near_clip_distance_g, camera_far_clip_distance_g, width, height);
}


Game::~Game(){

	delete ground;
    glfwTerminate();
}

} // namespace game
