#ifndef RESOURCE_MANAGER_H_
#define RESOURCE_MANAGER_H_

#include <string>
#include <unordered_map>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>

#include "resource.h"

// Default extensions for different shader source files
#define VERTEX_PROGRAM_EXTENSION "_vp.glsl"
#define FRAGMENT_PROGRAM_EXTENSION "_fp.glsl"

namespace game {

    // Class that manages all resources
    class ResourceManager {

        public:

			// Singleton Manager
			inline static ResourceManager & theResourceManager() {
				static ResourceManager resourceManager;
				return resourceManager;
			}
			ResourceManager(ResourceManager const&) = delete;
			void operator=(ResourceManager const&) = delete;

            // Add a resource that was already loaded and allocated to memory
            void AddResource(ResourceType type, const std::string name, GLuint resource, GLsizei size);
            void AddResource(ResourceType type, const std::string name, GLuint array_buffer, GLuint element_array_buffer, GLsizei size);
            // Load a resource from a file, according to the specified type
            void LoadResource(ResourceType type, const std::string name, const char *filename);
            // Get the resource with the specified name
            Resource *GetResource(const std::string name) const;

            // Methods to create specific resources
            // Create the geometry for a torus and add it to the list of resources
            void CreateTorus(std::string object_name, float loop_radius = 0.6, float circle_radius = 0.2, int num_loop_samples = 90, int num_circle_samples = 30);
            // Create a sphere
            void CreateSphere(std::string object_name, float radius = 0.6, int num_samples_theta = 90, int num_samples_phi = 45);
            // Create cube centered at (0, 0, 0) with sides of length 1
            void CreateCube(std::string object_name);
			// Create Cylinder
			void CreateCylinder(std::string object_name, float cylinder_radius = 0.5, float cylinder_height = 1.0, int num_cylinder_samples = 90);
			void CreateWall(std::string object_name);

        private:
			ResourceManager() {};

            // List storing all resources
            std::unordered_map<std::string, Resource*> resource_; 
 
            // Methods to load specific types of resources
            // Load shaders programs
            void LoadMaterial(const std::string name, const char *prefix);
            // Load a text file into memory (could be source code)
            std::string LoadTextFile(const char *filename);
			void LoadTexture(const std::string name, const char *filename);

    }; // class ResourceManager

} // namespace game

#endif // RESOURCE_MANAGER_H_
