#pragma once
#include <GLEW/glew.h>
#include <iostream>


// no fucking clue what this stuff does
// its macro magic
#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))	


// this function simply clears all the errors
// we need to do this to clear all the errors
// in the queue before we execute out function call
// so we know which errors are associated with that call

static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR)  // clear all the errors
	{

	}
}


// this just gets the error from glGetError and lets us know the
// function, filename, and line that the error occured in

static bool GLLogCall(const char* function, const char* filename, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << ") " << function
			<< " " << filename << ": " << line << std::endl;
		return false;
	}
	return true;
}

