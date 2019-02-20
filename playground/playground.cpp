// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
using namespace glm;

#include <common/shader.hpp>
#include "load_bmp.hpp"

void calcMatrix() {
    glm::mat4 myTranslationMatrix = glm::translate(glm::mat4(), glm::vec3(10.0f, 0.0f, 0.0f));
    glm::vec4 myVector(10.0f, 10.0f, 10.0f, 0.0f);
    glm::vec4 transforedVector = myTranslationMatrix * myVector;

    glm::mat4 myScaleMatrix = glm::scale(glm::vec3(2.0f, 2.0f, 2.0f));

    glm::vec3 myRotationAxis(1, 0, 0);
    glm::mat4 myRotationMatrix = glm::rotate(45.0f, myRotationAxis);

    glm::mat4 modelMatrix = myTranslationMatrix * myScaleMatrix * myRotationMatrix;

    glm::mat4 viewMatrix = glm::translate(glm::mat4(), glm::vec3(-3.0f, 0.0f, 0.0f));

    float FoV = M_PI * 45.0f / 180.0f;
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);

    glm::mat4 MVPmatrix = projectionMatrix * viewMatrix * modelMatrix;
}


int main( void )
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

    // calcMatrix();

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( 1024, 768, "Tutorial 02 - Red triangle", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
    std::string dir = "/home/kitamura/work/opengl_sample/ogl/playground/";
    std::string vert_shader = "texture.vert";
    std::string frag_shader = "texture.frag";
	GLuint programID = LoadShaders((dir + vert_shader).c_str(), (dir + frag_shader).c_str());

    GLuint image = loadBMP_custom("/home/kitamura/Downloads/bmp_file_99151/Bmp_file_Icon_256.png");

    // 立方体
	static const GLfloat g_vertex_buffer_data[] = {
        -1.0f,-1.0f,-1.0f, 
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, 
        1.0f, 1.0f,-1.0f, 
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f
	};

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    // 各頂点に2つの値、これらはBlenderで作りました。どうやって作るかはこれから説明します。
    static const GLfloat g_uv_buffer_data[] = {
        0.000059f, 1.0f-0.000004f,
        0.000103f, 1.0f-0.336048f,
        0.335973f, 1.0f-0.335903f,
        1.000023f, 1.0f-0.000013f,
        0.667979f, 1.0f-0.335851f,
        0.999958f, 1.0f-0.336064f,
        0.667979f, 1.0f-0.335851f,
        0.336024f, 1.0f-0.671877f,
        0.667969f, 1.0f-0.671889f,
        1.000023f, 1.0f-0.000013f,
        0.668104f, 1.0f-0.000013f,
        0.667979f, 1.0f-0.335851f,
        0.000059f, 1.0f-0.000004f,
        0.335973f, 1.0f-0.335903f,
        0.336098f, 1.0f-0.000071f,
        0.667979f, 1.0f-0.335851f,
        0.335973f, 1.0f-0.335903f,
        0.336024f, 1.0f-0.671877f,
        1.000004f, 1.0f-0.671847f,
        0.999958f, 1.0f-0.336064f,
        0.667979f, 1.0f-0.335851f,
        0.668104f, 1.0f-0.000013f,
        0.335973f, 1.0f-0.335903f,
        0.667979f, 1.0f-0.335851f,
        0.335973f, 1.0f-0.335903f,
        0.668104f, 1.0f-0.000013f,
        0.336098f, 1.0f-0.000071f,
        0.000103f, 1.0f-0.336048f,
        0.000004f, 1.0f-0.671870f,
        0.336024f, 1.0f-0.671877f,
        0.000103f, 1.0f-0.336048f,
        0.336024f, 1.0f-0.671877f,
        0.335973f, 1.0f-0.335903f,
        0.667969f, 1.0f-0.671889f,
        1.000004f, 1.0f-0.671847f,
        0.667979f, 1.0f-0.335851f
    };

    GLuint uvbuffer;
    glGenBuffers(1, &uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);
    
    // static GLfloat g_color_buffer_data[12 * 3 * 3];
    // for (int i = 0; i < 12 * 3; i++) {
    //     g_color_buffer_data[3 * i + 0] = (g_vertex_buffer_data[3 * i + 0] + 1) * 0.5;
    //     g_color_buffer_data[3 * i + 1] = (g_vertex_buffer_data[3 * i + 1] + 1) * 0.5;
    //     g_color_buffer_data[3 * i + 2] = (g_vertex_buffer_data[3 * i + 2] + 1) * 0.5;
    // }

    // GLuint colorbuffer;
    // glGenBuffers(1, &colorbuffer);
    // glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

    // create MVP matrix
    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    glm::mat4 View = glm::lookAt(glm::vec3(4, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 Model = glm::mat4(1.0f);
    glm::mat4 Model2 = glm::translate(glm::mat4(), glm::vec3(1.0f, 1.0f, 1.0f));
    glm::mat4 MVP = Projection * View * Model;
    glm::mat4 MVP2 = Projection * View * Model2;
    // MVP = glm::mat4(1.0f);

    GLuint MVPMatrixID = glGetUniformLocation(programID, "MVP");

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    float loop = 0.01;

	do{
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);
        glUniformMatrix4fv(MVPMatrixID, 1, GL_FALSE, &MVP[0][0]);
        
		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);

        
        // glEnableVertexAttribArray(1);
        // // color buffer
        // for (int i = 0; i < 12 * 3; i++) {
        //     g_color_buffer_data[3 * i + 0] = (g_vertex_buffer_data[3 * i + 0] + 1) * 0.5 * loop;
        //     g_color_buffer_data[3 * i + 1] = (g_vertex_buffer_data[3 * i + 1] + 1) * 0.5 * loop;
        //     g_color_buffer_data[3 * i + 2] = (g_vertex_buffer_data[3 * i + 2] + 1) * 0.5 * loop;
        // }
        // glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        // glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
        // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

		// glDisableVertexAttribArray(1);

        // glEnableVertexAttribArray(0);
        // glUniformMatrix4fv(MVPMatrixID, 1, GL_FALSE, &MVP2[0][0]);
        // glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        // glDisableVertexAttribArray(0);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

        loop += 0.01;
        if (loop > 1.0) {
            loop = 0.0;
        }
	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO
  	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
