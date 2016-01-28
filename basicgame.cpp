#include "classes.h"

platform * cube[HC][VC];

void draw ()
{
  // clear the color and depth in the frame buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUseProgram (programID);

  // Eye - Location of camera. Don't change unless you are sure!!
  glm::vec3 eye(-1,3,1);
  //glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
  // Target - Where is the camera looking at.  Don't change unless you are sure!!
  glm::vec3 target (0,0 ,0);
  // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
  glm::vec3 up (0, 1, 0);

  // Compute Camera matrix (view)
   Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
  //Matrices.view = glm::lookAt(glm::vec3(0,0,3), glm::vec3(0,0,0), glm::vec3(0,1,0)); // Fixed camera for 2D (ortho) in XY plane

  glm::mat4 VP = Matrices.projection * Matrices.view;

	// MVP = Projection * View * Model

  rep(i,0,HC-1){
    rep(j,0,VC-1){
      cube[i][j]->renderCube(VP);
    }
  }
  // Increment angles
  float increments = 1;

  camera_rotation_angle++; // Simulating camera rotation
  //triangle_rotation = triangle_rotation + increments*triangle_rot_dir*triangle_rot_status;
  //rectangle_rotation = rectangle_rotation + increments;//*rectangle_rot_dir;//*rectangle_rot_status;
}

void initGL (GLFWwindow* window, int width, int height)
{
  rep(i,0,HC-1){
    rep(j,0,VC-1){
      cube[i][j]->setInitVertices();
      cube[i][j]->setInitColors(1,1,1);
      cube[i][j]->setInitColors(5,1,0,1);
      cube[i][j]->setInitColors(2,1,1,0);
      cube[i][j]->setInitColors(1,0,1,0);
      cube[i][j]->createCube();
    }
  }
	// Create and compile our GLSL program from the shaders
	programID = LoadShaders( "Sample_GL.vert", "Sample_GL.frag" );
	// Get a handle for our "MVP" uniform
	Matrices.MatrixID = glGetUniformLocation(programID, "MVP");

	
	reshapeWindow (window, width, height);

    // Background color of the scene
	glClearColor (0.3f, 0.3f, 0.3f, 0.0f); // R, G, B, A
	glClearDepth (1.0f);

	glEnable (GL_DEPTH_TEST);
	glDepthFunc (GL_LEQUAL);

}

int main (int argc, char** argv)
{
	int width = SCREEN_WIDTH;
	int height = SCREEN_HEIGHT;

  GLFWwindow* window = initGLFW(width, height);

  rep(i,0,HC-1){
    rep(j,0,VC-1){
      cube[i][j] = new platform(0+j,0,0-i,1,1,1,i*VC+j);
    }
  }

	initGL (window, width, height);

  double last_update_time = glfwGetTime(), current_time;

    // Draw in loop
  while (!glfwWindowShouldClose(window)) {

        // OpenGL Draw commands
    draw();

        // Swap Frame Buffer in double buffering
    glfwSwapBuffers(window);

        // Poll for Keyboard and mouse events
    glfwPollEvents();

        // Control based on time (Time based transformation like 5 degrees rotation every 0.5s)
        //current_time = glfwGetTime(); // Time in seconds
    if ((current_time - last_update_time) >= 0.5) { // atleast 0.5s elapsed since last frame
            // do something every 0.5 seconds ..
      last_update_time = current_time;
    }
  }

  glfwTerminate();
  exit(EXIT_SUCCESS);
}
