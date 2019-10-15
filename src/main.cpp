#include "FontLib.h"

#include <glew.h>
#include <glfw3.h>


//font
FONScontext* fs;
int arabicfont = FONS_INVALID;
int normalfont = FONS_INVALID;
int japanesfont = FONS_INVALID;
int italianfont = FONS_INVALID;
int emotionsfont = FONS_INVALID;
int fancyfont = FONS_INVALID;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "FontRendering", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	glewExperimental = GL_TRUE;
	if (glewInit())
	{
		std::cout << "Failed to initialize Glew" << std::endl;
		return -1;
	}
	// Define the viewport dimensions
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

	// Set OpenGL options
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	
	//wireframe for debug
	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	// Create GL stash for 512x512 texture, our coordinate system has zero at top-left.
	fs = glfonsCreate(SCR_WIDTH, SCR_HEIGHT, FONS_ZERO_TOPLEFT);
	if (fs == NULL)
	{
		printf("Could not create stash.\n");
	}

	// Add font to stash.
	arabicfont = fonsAddFont(fs, "sans", "DroidSansArabic.ttf");
	if (arabicfont == FONS_INVALID) 
	{
		printf("Could not add font arabic.\n");
	}

	normalfont = fonsAddFont(fs, "sans", "DroidSerif-Regular.ttf");
	if (normalfont == FONS_INVALID) 
	{
		printf("Could not add font normal.\n");
	}

	japanesfont = fonsAddFont(fs, "sans", "DroidSansJapanese.ttf");
	if (japanesfont == FONS_INVALID)
	{
		printf("Could not add font japanes.\n");
	}

	italianfont = fonsAddFont(fs, "sans", "DroidSerif-Italic.ttf");
	if (italianfont == FONS_INVALID)
	{
		printf("Could not add font italian.\n");
	}

	emotionsfont = fonsAddFont(fs, "sans", "emoticons.otf");
	if (emotionsfont == FONS_INVALID)
	{
		printf("Could not add font emoj.\n");
	}

	fancyfont = fonsAddFont(fs, "sans", "Alin_Square_Emoji.ttf");
	if (fancyfont == FONS_INVALID)
	{
		printf("Could not add font fancy font.\n");
	}

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		
		// input
		// -----
		processInput(window);

		// render
		// ------

		glClearColor(0.0f, 0.3f, 0.3f, 0.5f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Render some text
		float dx = 0, dy = 100;

		fonsSetFont(fs, arabicfont);
		fonsSetSize(fs, 50.0f);
		fonsDrawText(fs, dx, dy, "ﻢﻴﺣﺮﻟﺍ ﻦﻤﺣﺮﻟﺍ ﻪﻠﻟﺍ ﻢﺴﺑ", NULL);

		dy += 60;
		fonsSetFont(fs, normalfont);
		fonsSetSize(fs, 50.0f);
		dx = fonsDrawText(fs, dx, dy, "The Big Fox Is Here ", NULL);

		fonsSetFont(fs, emotionsfont);
		fonsSetSize(fs, 50.0f);
		fonsDrawText(fs, dx, dy, "D ( #", NULL);
		dx = 0;

		dy += 60;
		fonsSetFont(fs, japanesfont);
		fonsSetSize(fs, 50.0f);
		fonsDrawText(fs, dx, dy, "ビッグフォックスはこちら", NULL);

		dy += 60;
		fonsSetFont(fs, italianfont);
		fonsSetSize(fs, 50.0f);
		fonsDrawText(fs, dx, dy, "La grande volpe è qui", NULL);

		dy += 60;
		fonsSetFont(fs, fancyfont);
		fonsSetSize(fs, 50.0f);
		fonsDrawText(fs, dx, dy, "A B C D E F G H I J K", NULL);


		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}