#include <glad/glad.h>
#include <GLFW\glfw3.h>
#include "shaders.h"
#include <iostream>
using namespace std;

/*
*	Callback function to resize the GLFW window.
*	Prototype for the function is here:
*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//add body  for the function
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
/*
* Function for Input Control
* Getkey will take window along witha key as input.
* Function will be named processInput to handle all such code and keep code organzied.
* This function should be near the top of the loop as it should be the first task carried out by the program.
* If we it is below in the order then, the function will run after carrying out all other tasks above it.
*/
void processInput(GLFWwindow* window)
{
	/*
	* we are checking if user has used escape key.
	* if pressed we will close the window.
	*/

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

}

//main code file
int main()
{
	//Initaite GLFW and configure it
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	//Window Object and check if its working.
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	//
	//Initialize GLAD and check if its working. 
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	////////////*******END OF SAFTEY CHECKS****************///////////////

	/*
	Rendering Window size
	X0,Y0,X1,Y1
	First two are the parameters of lower left corner
	and the last two are the width and height of window in pixels
	*/
	glViewport(0, 0, 800, 600);
	//calling the resize function
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//build and compile shader
	Shader ourShader("vertex.s", "fragment.s");
	/*
	*If we want to see the verticesw only then we can use wirefram to see how the objects are connected
	* We can use polygon mode to see that
	* Parameters:
	* if we want to apply it to front and back
	* if we want to fill or draw lines
	* Comment it out to go back to normal mode
	*/
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	//----------------------------------- Vertex and config data here 

	//Comments removed for ease of use in excercise

	float vertice1[] = {
		// positions=x,y,z colors=rgb
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
		0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f // top
	};

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	//---Config for First triangle
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertice1), vertice1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);//position attribute 
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));//color attribute
	glEnableVertexAttribArray(1);


	/*
	* Code to only allow explict closing.
	* It is also the render loop
	*/
	/*
	* Offsets are here
	*/
	float X_offset = 0.8f;
	float Y_offset = -0.8f;

	while (!glfwWindowShouldClose(window))
	{
		/*
		*input
		*/
		processInput(window);

		/*
		* render
		* MAke sure that clearcolor is before anything else as it will be creating the background
		*/

		//glclear will clear the buffer with the collor given in glclearColor. It is also coloring the background piels
		//The parameters are RGBA meaning Red,Green,Blue and Alpha
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//Draw Vertix

		ourShader.use();

		ourShader.setFloat("xOffset", X_offset);
		ourShader.setFloat("yOffset", Y_offset);

		//Update Shader input
		/*
		float timeValue1 = glfwGetTime();//get time
		float timeValue2 = glfwGetTime();//get time
		float timeValue3 = glfwGetTime();//get time

		float greenValue = (sin(timeValue1) / 2.0f) + 0.5f; //calculate value for the Green Color
		float redValue = (sin(timeValue2) / 2.0f) + 0.5f; //calculate for red
		float blueValue = (sin(timeValue3) / 2.0f) + 0.5f; //calculate for red
		int vertexColorLocation = glGetUniformLocation(shaderProgram1, "ourColor"); // get location ofuniform object called ourColor
		glUseProgram(shaderProgram1); //tell program which shader to use
		glUniform4f(vertexColorLocation, redValue, greenValue, blueValue, 1.0f); //set the uniform  value.
		*/



		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		/*
		* GL Draw Array has been commented out as we are going to use EBO which will
		remove the overhead of having same vertices for many triangles.
		*/

		/*
		*check call events
		*/
		//swapbuffers will swap the color buffer
		glfwSwapBuffers(window);
		//Pollevents check if window has been closed or not.
		glfwPollEvents();
	}
	//terminate GLFW at end of program
	glfwTerminate();
	return 0;
}
