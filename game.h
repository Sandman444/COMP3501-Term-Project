#ifndef GAME_H_
#define GAME_H_

#include <exception>
#include <string>
#include <vector>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GameException.h"
#include "Updateable.h"
#include "InputController.h"
#include "scene_graph.h"
#include "resource_manager.h"
#include "ProjectileManager.h"
#include "camera.h"
#include "Helicopter.h"
#include "Tank.h"
#include "Turret.h"
#include "Ground.h"

namespace game {

    // Game application
    class Game {

        public:
            // Constructor and destructor
            Game(void);
            ~Game();
            // Call Init() before calling any other method
            void Init(void); 
            // Set up resources for the game
            void SetupResources(void);
            // Set up initial scene
            void SetupScene(void);
            // Run the game: keep the application active
            void MainLoop(void); 

        private:
            // GLFW window
            GLFWwindow* window_;

            // Scene graph containing all nodes to render
            SceneGraph scene_;

			// Input controller
			InputController inputController;

			// Helicopter projectile manager
			ProjectileManager helicopterProjectileManager;

			// Input controller
			InputController inputController;

            // Camera abstraction
            Camera camera_;

			//Game Objects
			Helicopter *helicopter;

			Tank *tank1, *tank2, *tank3, *tank4;
			Turret *turret1, *turret2, *turret3, *turret4, *turret5;
			Ground *ground;

            // Flag to turn animation on/off
            bool animating_;

			std::vector<Updateable*> updateables;

            // Methods to initialize the game
            void InitWindow(void);
            void InitView(void);
            void InitEventHandlers(void);
 
            // Methods to handle events
            static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
            static void ResizeCallback(GLFWwindow* window, int width, int height);

    }; // class Game

} // namespace game

#endif // GAME_H_
