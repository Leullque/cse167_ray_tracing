#ifndef GLOBALS_H
#define GLOBALS_H

#include <glm/glm.hpp>
#include <GLUT/glut.h>
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>

#include "Camera.h"
#include "GeometryBase.h"
#include "Scene.h"
#include "ShadingMode.h"
#include <queue> 
#include "RayTracer.h"
#include "Image.h"

// Declare external variables
extern RayTracer rayTracer;

#endif  // GLOBALS_H