#include "classes.h"

Cuboid * platform[HC][VC] , *obstacles[OBSTACLES];
Player * player;
double start_time;bool start_flag= false;

void keyboard (GLFWwindow* window, int key, int scancode, int action, int mods)
{
     // Function is called first on GLFW_PRESS.

    if (action == GLFW_RELEASE) {
        switch (key) {
           case GLFW_KEY_UP:
            player->updatePosition(0,0,-1);
            break;
           case GLFW_KEY_DOWN:
            player->updatePosition(0,0,+1);
            break;
           case GLFW_KEY_LEFT:
            player->updatePosition(-1,0,0);
            break;
           case GLFW_KEY_RIGHT:            
            player->updatePosition(+1,0,0);
            break;
           case GLFW_KEY_RIGHT_SHIFT:
           case GLFW_KEY_LEFT_SHIFT: 
              //output1("shift");
              if(glfwGetKey(window,GLFW_KEY_1)){
              //  output1("1");
               eyex=STARTX-1;eyey=5,eyez=STARTZ+1; 
              }
              else if(glfwGetKey(window,GLFW_KEY_2)){
              //  output1("2");
               eyex=STARTX-1;eyey=5,eyez=STARTZ-VC; 
              }
              else if(glfwGetKey(window,GLFW_KEY_3)){
              //  output1("3");
               eyex=STARTX+HC;eyey=5,eyez=STARTZ-VC; 
              }
              else if(glfwGetKey(window,GLFW_KEY_4)){
              //  output1("4");
               eyex=STARTX+HC;eyey=5,eyez=STARTZ+1; 
              }
              break;
           default:
            break;
        }
    }
    else if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_ESCAPE:
                quit(window);
                break;
            default:
                break;
        }
    }
}

void draw ()
{
  // clear the color and depth in the frame buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUseProgram (programID);

  // Eye - Location of camera. Don't change unless you are sure!!
  //glm::vec3 eye(4.5,5,-4.5);
  glm::vec3 eye(eyex,eyey,eyez);
  //glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
  // Target - Where is the camera looking at.  Don't change unless you are sure!!
  glm::vec3 target (5,0 ,-5);
  // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
  glm::vec3 up (0, 1, 0);

  // Compute Camera matrix (view)
   Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
  //Matrices.view = glm::lookAt(glm::vec3(0,0,3), glm::vec3(0,0,0), glm::vec3(0,1,0)); // Fixed camera for 2D (ortho) in XY plane

  glm::mat4 VP = Matrices.projection * Matrices.view;

	// MVP = Projection * View * Model

  rep(i,0,HC-1){
    rep(j,0,VC-1){
      if( dit.find(MP(i,j)) ==dit.end())
        platform[i][j]->renderCube(VP);
    }
  }
  int ind=0;
  TR(obs,it){
    obstacles[ind]->renderCube(VP);
    ind++;
  }

  if(player->getY() > -5 )
    player->renderCube(VP);
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
      platform[i][j]->setInitVertices();
      platform[i][j]->setInitColors(1,1,1);
      platform[i][j]->setInitColors(5,1,0,1);
      platform[i][j]->setInitColors(2,1,1,0);
      platform[i][j]->setInitColors(1,0,1,0);
      platform[i][j]->createCube();
    }
  }

  rep(i,0,SZ(obs)-1){
      obstacles[i]->setInitVertices();
      obstacles[i]->setInitColors(1,1,1);
      obstacles[i]->setInitColors(5,1,0,1);
      obstacles[i]->setInitColors(2,1,1,0);
      obstacles[i]->setInitColors(1,0,1,0);
      obstacles[i]->createCube();
  }

  player->setInitVertices();
  player->setInitColors(1,1,1);
  player->setInitColors(5,0.392157, 0.584314, 0.929412);
  player->setInitColors(2,1, 0.498039, 0.313725);
  player->setInitColors(1,0.545098, 0, 0.545098);
  player->createCube();
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

bool checkCollision(double dx,double dy,double dz){
  double x1 = player->getX(), y1 = player->getY() , z1 = player->getZ();
  x1+=dx;y1+=dy;z1+=dz;
  if( obs.find(MP(MP(x1,y1),z1)) == obs.end() )
    return false;
  return true;
}

bool checkDitch(){
  double x1 = player->getX(), y1 = player->getY() , z1 = player->getZ();
  int j = x1 - STARTX , i = STARTZ - z1;

  if( dit.find(MP(i,j)) ==dit.end()){
    start_flag = false;
    return false;
  }
  //output2(i,j);
  if(!start_flag){
    start_time = glfwGetTime();
    start_flag = true;
  }
  return true;

}

int main (int argc, char** argv)
{
	int width = SCREEN_WIDTH;
	int height = SCREEN_HEIGHT;

  GLFWwindow* window = initGLFW(width, height);

  getObstaclePositions();
  getDitchPositions();
  rep(i,0,HC-1){
    rep(j,0,VC-1){
      platform[i][j] = new Cuboid(STARTX+j,STARTY,STARTZ-i,1,1,1,i*VC+j);
    }
  }

  int ind=0;
  TR(obs,it){
    
    obstacles[ind] = new Cuboid((*it).F.F,(*it).F.S,(*it).S,1,1,1,ind);
    ind++;
  }

  player = new Player(5,1,0,1/2,1,1/2,VELOCITY);

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
    current_time = glfwGetTime(); // Time in seconds
    if ((current_time - last_update_time) >= 0.05) { // atleast 0.5s elapsed since last frame
            // do something every 0.5 seconds ..
      if(checkDitch()){
        player->setEFY(0);
        player->updatePosition(  current_time - start_time  );
      }
      player->setEFY(-1*player->getAY());
      last_update_time = current_time;
    }
  }

  glfwTerminate();
  exit(EXIT_SUCCESS);
}
