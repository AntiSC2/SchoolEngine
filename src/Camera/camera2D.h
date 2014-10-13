#ifndef CAMERA2D_H_INCLUDED
#define CAMERA2D_H_INCLUDED
#ifndef GLEW_BUILD
#define GLEW_BUILD
#endif // GLEW_BUILD
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera2D {
public:
   Camera2D(int w, int h);
   ~Camera2D();

   void init(int w, int h);

   void update();

   void setScale(GLfloat scale);
   void setPosition(glm::vec2 position);

   GLfloat getScale();
   glm::vec2 getPosition();
   glm::mat4 getCameraMatrix();

private:
   int width, height;
   glm::vec2 position;
   GLfloat scale;
   glm::mat4 cameraMatrix;
   glm::mat4 orthoMatrix;
   bool needUpdate;
};

#endif // CAMERA2D_H_INCLUDED
