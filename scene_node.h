#ifndef SCENE_NODE_H_
#define SCENE_NODE_H_

#include <string>
#include <vector>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtc/quaternion.hpp>
#include <algorithm>

#include "GameException.h"
#include "resource_manager.h"
#include "resource.h"

namespace game {

	class Camera;

    // Class that manages one object in a scene 
    class SceneNode {

        public:
            // Create scene node from given resources
			SceneNode(const std::string name);
            SceneNode(const std::string name, std::string object_name, std::string material_name, std::string texture_name);

            // Destructor
            ~SceneNode();
            
            // Get name of node
            const std::string GetName(void) const;

            // Get node attributes
            glm::vec3 GetPosition(void) const;
            glm::quat GetOrientation(void) const;
            glm::vec3 GetScale(void) const;
			virtual float getBoundingSphereRadius(void) const;


            // Set node attributes
            void SetPosition(glm::vec3 position);
            void SetOrientation(glm::quat orientation);
            void SetScale(glm::vec3 scale);
            
            // Perform transformations on node
            void Translate(glm::vec3 trans);
            void Rotate(glm::quat rot);
            void Scale(glm::vec3 scale);

            // Draw the node according to scene parameters in 'camera'
            // variable
            virtual glm::mat4 Draw(Camera *camera, glm::mat4 parent_transf);

            // Update the node
            virtual void Update(void);
			virtual void Update(glm::vec3 position);

            // OpenGL variables
            GLenum GetMode(void) const;
            GLuint GetArrayBuffer(void) const;
            GLuint GetElementArrayBuffer(void) const;
            GLsizei GetSize(void) const;
            GLuint GetMaterial(void) const;


            // Hierarchy-related methods
            void addChild(SceneNode *node);
			void removeChild(std::string nodeName);
            std::vector<SceneNode *>::const_iterator children_begin() const;
            std::vector<SceneNode *>::const_iterator children_end() const;

			inline SceneNode *getParent() {
				return parent_;
			}

		protected:
			glm::vec3 position_; // Position of node
			glm::quat orientation_; // Orientation of node
			glm::vec3 scale_; // Scale of node

        private:
            std::string name_; // Name of the scene node
            GLuint array_buffer_; // References to geometry: vertex and array buffers
            GLuint element_array_buffer_;
            GLenum mode_; // Type of geometry
            GLsizei size_; // Number of primitives in geometry
            GLuint material_; // Reference to shader program
			GLuint texture_; //Reference to texture resource
 
            // Hierarchy
            SceneNode *parent_;
            std::vector<SceneNode *> children_;

            // Set matrices that transform the node in a shader program
            // Return transformation of current node combined with
            // parent transformation, without including scaling
            glm::mat4 SetupShader(GLuint program, glm::mat4 parent_transf);

    }; // class SceneNode

} // namespace game

#endif // SCENE_NODE_H_
