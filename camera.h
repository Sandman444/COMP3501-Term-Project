#ifndef CAMERA_H_
#define CAMERA_H_

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "scene_node.h"
#include "Helicopter.h"

namespace game {

    // Abstraction of a camera
    class Camera : public SceneNode {

        public:
            Camera(void);
            ~Camera();

			glm::mat4 Draw(Camera *camera, glm::mat4 parent_transf) override;
			void Update(void) override;

            // Get relative attributes of camera
            glm::vec3 GetForward(void) const;
            glm::vec3 GetSide(void) const;
            glm::vec3 GetUp(void) const;

            // Perform relative transformations of camera
            void Pitch(float angle);
            void Yaw(float angle);
            void Roll(float angle);

            // Set the view from camera parameters: initial position of camera,
            // point looking at, and up vector
            // Resets the current orientation and position of the camera
            void SetView(glm::vec3 position, glm::vec3 look_at, glm::vec3 up);
            // Set projection from frustum parameters: field-of-view,
            // near and far planes, and width and height of viewport
            void SetProjection(GLfloat fov, GLfloat near, GLfloat far, GLfloat w, GLfloat h);
            // Set all camera-related variables in shader program
            void SetupShader(GLuint program);

			void follow(Helicopter* helicopter);
			void setViewMode(std::string);

        private:
            glm::vec3 forward_; // Initial forward vector
            glm::vec3 side_; // Initial side vector
            glm::mat4 view_matrix_; // View matrix
            glm::mat4 projection_matrix_; // Projection matrix

            // Create view matrix from current camera parameters
            void SetupViewMatrix(void);

			Helicopter *followingHelicopter;
			int viewMode;

    }; // class Camera

} // namespace game

#endif // CAMERA_H_
