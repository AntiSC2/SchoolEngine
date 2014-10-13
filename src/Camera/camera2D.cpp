#include "camera2D.h"

Camera2D::Camera2D(int w, int h) : width(w), height(h), position(0, 0), scale(1.0f), cameraMatrix(1), orthoMatrix(1), needUpdate(0) {
   ;
}

Camera2D::~Camera2D() {
   ;
}

void Camera2D::init(int w, int h) {
   width = w;
   height = h;

   orthoMatrix = glm::ortho(0.0f, (float)width, 0.0f, (float)height);
   needUpdate = 1;
}

void Camera2D::update() {
   if(needUpdate) {
      glm::vec3 translate(-position.x + width / 2, -position.y + height / 2, 0.0f);
      cameraMatrix = glm::translate(orthoMatrix, translate);

      glm::vec3 Scale(scale, scale, 0.0f);
      cameraMatrix = glm::scale(glm::mat4(1.0f), Scale) * cameraMatrix;
      needUpdate = false;
   }
}

void Camera2D::setPosition(glm::vec2 position) {
   this->position = position;
   needUpdate = true;
}

void Camera2D::setScale(GLfloat scale) {
   this->scale = scale;
   needUpdate = true;
}

glm::vec2 Camera2D::getPosition() {
   return position;
}

GLfloat Camera2D::getScale() {
   return scale;
}

glm::mat4 Camera2D::getCameraMatrix() {
   return cameraMatrix;
}
