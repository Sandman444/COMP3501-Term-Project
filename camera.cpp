#include <stdexcept>
#define GLM_FORCE_RADIANS
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "camera.h"

namespace game {

Camera::Camera(void) : SceneNode("camera") {
}


Camera::~Camera(){
}

void Camera::follow(Helicopter* helicopter) {
	followingHelicopter = helicopter;
}

glm::mat4 Camera::Draw(Camera *camera, glm::mat4 parent_transf) {

	return glm::mat4(1.0);
}


void Camera::Update(void) {
	// update camera position
	glm::vec3 flatenedForward = glm::vec3(followingHelicopter->getForward().x, 0, followingHelicopter->getForward().z);
	if (viewMode == 1) {
		SetView(followingHelicopter->GetPosition() - flatenedForward * 2.0f + glm::vec3(0, 1, 0) * 0.5f, flatenedForward, glm::vec3(0, 1, 0));
	}
	else if (viewMode == 0) {
		SetView(followingHelicopter->GetPosition() + followingHelicopter->getForward() * 0.3f, flatenedForward, glm::vec3(0, 1, 0));
	}
}

void Camera::setViewMode(std::string mode) {
	if (mode == "third person") {
		viewMode = 1;
	}
	else {
		viewMode = 0;
	}
}

glm::vec3 Camera::GetForward(void) const {

    glm::vec3 current_forward = orientation_ * forward_;
    return -current_forward; // Return -forward since the camera coordinate system points in the opposite direction
}


glm::vec3 Camera::GetSide(void) const {

    glm::vec3 current_side = orientation_ * side_;
    return current_side;
}


glm::vec3 Camera::GetUp(void) const {

    glm::vec3 current_forward = orientation_ * forward_;
    glm::vec3 current_side = orientation_ * side_;
    glm::vec3 current_up = glm::cross(current_forward, current_side);
    current_up = glm::normalize(current_up);
    return current_up;
}


void Camera::Pitch(float angle){

    glm::quat rotation = glm::angleAxis(angle, GetSide());
    orientation_ = rotation * orientation_;
}


void Camera::Yaw(float angle){

    glm::quat rotation = glm::angleAxis(angle, GetUp());
    orientation_ = rotation * orientation_;
}


void Camera::Roll(float angle){

    glm::quat rotation = glm::angleAxis(angle, GetForward());
    orientation_ = rotation * orientation_;
}


void Camera::SetView(glm::vec3 position, glm::vec3 look_at, glm::vec3 up){

    // Store initial forward and side vectors
    // See slide in "Camera control" for details
    forward_ = look_at;
    forward_ = -glm::normalize(forward_);
    side_ = glm::cross(up, forward_);
    side_ = glm::normalize(side_);

    // Reset orientation and position of camera
    position_ = position;
    orientation_ = glm::quat();
}


void Camera::SetProjection(GLfloat fov, GLfloat near, GLfloat far, GLfloat w, GLfloat h){

    // Set projection based on field-of-view
    float top = tan((fov/2.0)*(glm::pi<float>()/180.0))*near;
    float right = top * w/h;
    projection_matrix_ = glm::frustum(-right, right, -top, top, near, far);
}


void Camera::SetupShader(GLuint program){

    // Update view matrix
    SetupViewMatrix();

    // Set view matrix in shader
    GLint view_mat = glGetUniformLocation(program, "view_mat");
    glUniformMatrix4fv(view_mat, 1, GL_FALSE, glm::value_ptr(view_matrix_));
    
    // Set projection matrix in shader
    GLint projection_mat = glGetUniformLocation(program, "projection_mat");
    glUniformMatrix4fv(projection_mat, 1, GL_FALSE, glm::value_ptr(projection_matrix_));
}


void Camera::SetupViewMatrix(void){

    //view_matrix_ = glm::lookAt(position, look_at, up);

    // Get current vectors of coordinate system
    // [side, up, forward]
    // See slide in "Camera control" for details
    glm::vec3 current_forward = orientation_ * forward_;
    glm::vec3 current_side = orientation_ * side_;
    glm::vec3 current_up = glm::cross(current_forward, current_side);
    current_up = glm::normalize(current_up);

    // Initialize the view matrix as an identity matrix
    view_matrix_ = glm::mat4(1.0); 

    // Copy vectors to matrix
    // Add vectors to rows, not columns of the matrix, so that we get
    // the inverse transformation
    // Note that in glm, the reference for matrix entries is of the form
    // matrix[column][row]
    view_matrix_[0][0] = current_side[0]; // First row
    view_matrix_[1][0] = current_side[1];
    view_matrix_[2][0] = current_side[2];
    view_matrix_[0][1] = current_up[0]; // Second row
    view_matrix_[1][1] = current_up[1];
    view_matrix_[2][1] = current_up[2];
    view_matrix_[0][2] = current_forward[0]; // Third row
    view_matrix_[1][2] = current_forward[1];
    view_matrix_[2][2] = current_forward[2];

    // Create translation to camera position
    glm::mat4 trans = glm::translate(glm::mat4(1.0), -position_);

    // Combine translation and view matrix in proper order
    view_matrix_ *= trans;
}

} // namespace game
