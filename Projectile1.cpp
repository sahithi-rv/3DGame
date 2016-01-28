#include "Projectile.hpp"
//#include "utility.hpp"

Circle *projectile,*hinge, *borders[BORDERS][4];
Quadrilateral * canon, *base, *obstacles[15], *bar[15], *tar, *button , *button_base;

Quadrilateral * boundary_bottom, *boundary_top, *boundary_left, *boundary_right;
bool game_end = false,game_end_flag = false,unnatural = true,motion_phase_projectile = false, can_roll = false, motion_phase_start_projectile = false, win = false, stop_oscillation = false, bound = true, bound1 = true;
double motion_start_time;
double projectile_init_vx,projectile_init_vy;
Quadrilateral * back_floor, *back_lines[BACK_LINES];
Line * paint[PAINT];
Circle * back_circles[CIRCLE] , * ball_circles[BALL_CIRCLES], *ball_fill_circles[BALL_CIRCLES];
Line * lines[LINES];
Circle * jumper;

int chance_no = 0,points = 60,score = 0;
float pan=0;
int ATTEMPT;

 Circle * attempt[10000];
//float rec_vel = 0;
/* Executed when a regular key is pressed/released/held-down */
/* Prefered for Keyboard events */
void keyboard (GLFWwindow* window, int key, int scancode, int action, int mods)
{
     // Function is called first on GLFW_PRESS.

    if (action == GLFW_RELEASE) {
      switch (key) {
            case GLFW_KEY_SPACE:
            if(!motion_phase_projectile && !motion_phase_start_projectile){
                motion_start_time = glfwGetTime();
                motion_phase_start_projectile = true;
            }
                break;
            case GLFW_KEY_D:
                canon->updatePosition(CANON_STEP,-6.8,-4.8);
                break;
            case GLFW_KEY_A:
                canon->updatePosition(-1*CANON_STEP,-6.8,-4.8);
                break;
            case GLFW_KEY_W:
                canon->updateAngle(CANON_ROTATION,0,-90,1);
                break;
            case GLFW_KEY_S:
                canon->updateAngle(-1*CANON_ROTATION,0,-90,1);
                break;
            case GLFW_KEY_UP:
                if(speed_level<10)
                  speed_level++;
                break;

            case GLFW_KEY_DOWN:
                if(speed_level>0)
                  speed_level--;
                break;

            case GLFW_KEY_LEFT:
                pan-=0.5;
                break;
            case GLFW_KEY_RIGHT:
                pan+=0.5;
                break;
             

          /* case GLFW_KEY_PAGE_UP:
              zoom -= 0.25f;
              if (zoom < 0.f)
                zoom = 0.f;
              pan_left+=zoom;
              pan_right+=zoom;
              pan_down+=zoom;
              pan_up+=zoom;
              break;
          case GLFW_KEY_PAGE_DOWN:
              zoom += 0.25f;
              pan_left+=zoom;
              pan_right+=zoom;
              pan_down+=zoom;
              pan_up+=zoom;
              break;
*/

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

/* Executed for character input (like in text boxes) */
void keyboardChar (GLFWwindow* window, unsigned int key)
{
	switch (key) {
		case 'Q':
		case 'q':
            quit(window);
            break;
		default:
			break;
	}
}

/* Executed when a mouse button is pressed/released */
void mouseButton (GLFWwindow* window, int button, int action, int mods)
{
    switch (button) {
        default:
            break;
    }
}

float camera_rotation_angle = 90;
//float projectile->rectangle_rotation = 0;

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw ()
{

  Matrices.projection = glm::ortho(zoom*(-10.0f + pan),  zoom*(10.0f + pan), zoom*(-10.0f), zoom*(10.0f), 0.1f, 500.0f);
  // clear the color and depth in the frame buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  // use the loaded shader program
  // Don't change unless you know what you are doing
  glUseProgram (programID);

  // Eye - Location of camera. Don't change unless you are sure!!
  glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
  // Target - Where is the camera looking at.  Don't change unless you are sure!!
  glm::vec3 target (0, 0, 0);
  // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
  glm::vec3 up (0, 1, 0);

  
  for(int i=0;i<BALL_CIRCLES;i++){
    ball_circles[i]->renderCircle();
    draw3DObject(ball_circles[i]->circle);
   

  }
  for(int i=chance_no;i<BALL_CIRCLES;i++){
     ball_fill_circles[i]->renderCircle();
    draw3DObject(ball_fill_circles[i]->circle);
  }

   back_floor->renderQuad();
   draw3DObject(back_floor->rectangle);
   obstacles[5]->renderQuad();
    draw3DObject(obstacles[5]->rectangle);
   for(int i=0;i<BACK_LINES;i++){
    back_lines[i]->renderQuad();
    draw3DObject(back_lines[i]->rectangle);
   }

   for(int i=0;i<PAINT;i++){
    paint[i]->renderLine();
    draw3DObject(paint[i]->line);
   }

   for(int i=0;i<CIRCLE;i++){
    back_circles[i]->renderCircle();
    draw3DObject(back_circles[i]->circle);
  }



   for(int i=0;i<STATIC_OBSTACLES - 1;i++){
    obstacles[i]->renderQuad();
    draw3DObject(obstacles[i]->rectangle);
  }
  
  hinge->renderCircle();
  draw3DObject(hinge->circle);
/*for(int j=0;j<BORDERS;j++){
  for(int i=0;i<4;i++){
    borders[j][i]->renderCircle();
    draw3DObject(borders[j][i]->circle);
  }
}*/

  canon->renderQuad();
  draw3DObject(canon->rectangle);
  base->renderQuad();
  draw3DObject(base->rectangle);

  button_base->renderQuad();
  draw3DObject(button_base->rectangle);


  button->renderQuad();
  draw3DObject(button->rectangle);

  tar->renderQuad();
  draw3DObject(tar->rectangle);

  for(int i=0;i<LINES;i++){
    lines[i]->renderLine();
    draw3DObject(lines[i]->line);
  }

  for(int i=0;i<=speed_level;i++){
        
      bar[i]->renderQuad();
      draw3DObject(bar[i]->rectangle);
  }

  jumper->renderCircle();
  draw3DObject(jumper->circle);

  if(motion_phase_projectile || can_roll){
    projectile->renderCircle();
    draw3DObject(projectile->circle);
  }
}

/* Initialise glfw window, I/O callbacks and the renderer to use */
/* Nothing to Edit here */
GLFWwindow* initGLFW (int width, int height)
{
    GLFWwindow* window; // window desciptor/handle

    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, "Sample OpenGL 3.3 Application", NULL, NULL);

    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval( 1 );

    /* --- register callbacks with GLFW --- */

    /* Register function to handle window resizes */
    /* With Retina display on Mac OS X GLFW's FramebufferSize
     is different from WindowSize */
    glfwSetFramebufferSizeCallback(window, reshapeWindow);
    glfwSetWindowSizeCallback(window, reshapeWindow);

    /* Register function to handle window close */
    glfwSetWindowCloseCallback(window, quit);

    /* Register function to handle keyboard input */
    glfwSetKeyCallback(window, keyboard);      // general keyboard input
    glfwSetCharCallback(window, keyboardChar);  // simpler specific character handling

    /* Register function to handle mouse click */
    glfwSetMouseButtonCallback(window, mouseButton);  // mouse button clicks
    glfwSetScrollCallback(window, scroll_callback);
    return window;
}

void setInitials(Quadrilateral *box,float r,float g,float b){

  GLfloat * vertex_buffer_data;
  vertex_buffer_data = box->getInitVertices();
  GLfloat * colors = box->getInitColors(r,g,b);
  box->setInitVertices(vertex_buffer_data);
  box->setInitColors(colors);
  box->createRectangle ();
}

void setInitials(Quadrilateral *box,float r,float g,float b,GLfloat * vertex_buffer_data){


  GLfloat * colors = box->getInitColors(r,g,b);
  box->setInitVertices(vertex_buffer_data);
  box->setInitColors(colors);
  box->createRectangle ();
}

void setInitials(Line *box,float r,float g,float b){

  GLfloat * vertex_buffer_data;
  vertex_buffer_data = box->getInitVertices();
  GLfloat * colors = box->getInitColors(r,g,b);
  box->setInitVertices(vertex_buffer_data);
  box->setInitColors(colors);
  box->createLine();
}


/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL (GLFWwindow* window, int width, int height)
{
  
for(int i=0;i<STATIC_OBSTACLES - 1;i++){
   setInitials(obstacles[i],0.698039, 0.133333, 0.133333);
  }
     setInitials(obstacles[5],0.721569, 0.52549, 0.0431373);


  GLfloat * hinge_vertices = circleVertices(borders[0][0]->num_vertices, borders[0][0]->radius);
  GLfloat * hinge_colors = circleColors(borders[0][0]->num_vertices,0.698039, 0.133333, 0.133333);
for(int j=0;j<BORDERS;j++){
  for(int i=0;i<4;i++){
    borders[j][i]->setInitVertices(hinge_vertices);
    borders[j][i]->setInitColors(hinge_colors);
    borders[j][i]->createCircle();
  }
}
hinge_colors = circleColors(borders[0][0]->num_vertices,0.662745, 0.662745, 0.662745);
 hinge->setInitVertices(hinge_vertices);
  hinge->setInitColors(hinge_colors);
  hinge->createCircle();

hinge_vertices = circleVertices(jumper->num_vertices,jumper->radius);
hinge_colors  = circleColors(jumper->num_vertices,0.466667, 0.533333, 0.6);
jumper->setInitVertices(hinge_vertices);
jumper->setInitColors(hinge_colors);
jumper->createCircle();
/*for (int i = 0; i < ATTEMPT; ++i)
{
  attempt[i]->setInitVertices(hinge_vertices);
    attempt[i]->setInitColors(hinge_colors);
    attempt[i]->createCircle();
}
*/
GLfloat * circle_vertices , * circle_colors;
for(int i=0;i<CIRCLE;i++){
  circle_vertices = circleVertices(back_circles[i]->num_vertices,back_circles[i]->radius);
  circle_colors = circleColors(back_circles[i]->num_vertices,1,1,1);
  back_circles[i]->setInitVertices(circle_vertices);
    back_circles[i]->setInitColors(circle_colors);
    back_circles[i]->createCircle();
}

for(int i=0;i<BALL_CIRCLES;i++){
  circle_vertices = circleVertices(ball_circles[i]->num_vertices,ball_circles[i]->radius);
  circle_colors = circleColors(ball_circles[i]->num_vertices,1, 0.54902, 0);
  ball_circles[i]->setInitVertices(circle_vertices);
    ball_circles[i]->setInitColors(circle_colors);
    ball_circles[i]->createCircle();
    ball_fill_circles[i]->setInitVertices(circle_vertices);
    ball_fill_circles[i]->setInitColors(circle_colors);
    ball_fill_circles[i]->createCircle();
}

setInitials(canon,1, 0.870588, 0.678431);
  setInitials(base,0, 0, 0.501961);

  setInitials(tar,0.8,0.1,0);

  for(int i=0;i<=10;i++){
      setInitials(bar[i],float(i)/10,1-float(i)/10,0);
  }

  GLfloat button_base_vertices[] = {
    0,0,0,
    0,0.8,0,
    1.5,1.25,0,

    1.5,1.25,0,
    1.5,-0.45,0,
    0,0,0

  } ;

  GLfloat * colors = button_base->getInitColors(0.741176, 0.717647, 0.419608);
  button_base->setInitVertices(button_base_vertices);
  button_base->setInitColors(colors);
  button_base->createRectangle();

  GLfloat back_floor_vertices[]={
    -10,-4,0,
    -9,4,0,
    10,4,0,

    10,4,0,
    10,-4,0,
    -10,-4,0,

  };

  colors = back_floor->getInitColors(0.721569, 0.52549, 0.0431373);
  back_floor->setInitVertices(back_floor_vertices);
  back_floor->setInitColors(colors);
  back_floor->createRectangle();

 GLfloat back_line1[]={
   -0.25,-4,0,
    0,4,0,
    0.25,4,0,

    0.25,4,0,
    0,-4,0,
    -0.25,-4,0,
  };
  setInitials(back_lines[0],1, 1, 0.941176,back_line1);

  for(int i = 0 ;i<PAINT;i++){
    setInitials(paint[i],1, 1, 0.941176);
  }
 /* GLfloat back_line2[]={
    -8,-2,0,
    -8.3,-1.7,0,
    -4,-0.7,0,
    
    -4,-0.7,0,
    -3.7,-1,0,
    -8,-2,0,
  };
  setInitials(back_lines[1],1, 1, 0.941176,back_line2);*/


  setInitials(button,0.862745, 0.0784314, 0.235294);

  for(int i=0;i<LINES;i++)
    setInitials(lines[i],1,1,1);

	// Create and compile our GLSL program from the shaders
	programID = LoadShaders( "Sample_GL.vert", "Sample_GL.frag" );
	// Get a handle for our "MVP" uniform
	Matrices.MatrixID = glGetUniformLocation(programID, "MVP");

	
	reshapeWindow (window, width, height);

    // Background color of the scene
	glClearColor ( 1, 0.980392, 0.803922 ,0.f); // R, G, B, A
	glClearDepth (1.0f);

	glEnable (GL_DEPTH_TEST);
	glDepthFunc (GL_LEQUAL);

   
}


void onCollision(Circle * granade,Quadrilateral * obstacle){
  float x1 = granade->getX() , y1 = granade->getY();
  float vx = granade->getVX() , vy = granade->getVY();
  double theta = atan2(vy,vx);

  float displace = 2*granade->getRadius();
 
  if(vx>=0)
    granade->setX(x1-displace);
  else
    granade->setX(x1+displace);
  if(vy>=0)
    granade->setY(y1-displace);
  else
    granade->setY(y1+displace);

  //output1(theta);
  double v = sqrt(vx*vx + vy*vy );
  double finalv = obstacle->cor * v;
  theta += M_PI;

  granade->setVX(finalv*cos(theta));
  granade->setVY(finalv*sin(theta));
  //output2(granade->getVX(),granade->getVY());
  //output2(granade->getX(),granade->getY());
}

bool checkCollision(Circle granade,pair<float,float> pt1 ,pair<float,float> pt2){
  pair<float,float> centre= granade.getCentre();
  pair< pair<float,float> , float > line = getLine(pt1,pt2);
 // output2(centre.F,centre.S);
  //output2(line.F.F,line.F.S);
  //output1(line.S);
  pair<float,float> foot = getFoot(centre , line.F.F,line.F.S , line.S);
  //output2(foot.F,foot.S);
  double dt = distance(foot.F,foot.S, centre.F, centre.S) ;
  //output1(dt);
  if( dt <= 2*granade.getRadius()  ){
    if( isInBW(foot,pt1,pt2) ){
      return true;
    }
    else
      return false;
  }
}


bool checkCollision(Circle granade,Circle obstacle){
  float dt = distance(granade.getX(),granade.getY(),obstacle.getX(),obstacle.getY());
  if(obstacle.getRadius()+granade.getRadius() >= dt){
    return true;
  }
  return false;
}

pair<pair<float,float>,pair<float,float> > getProjectileInitPosition(Quadrilateral canon){
  double theta = canon.getAngle();
 // output1(theta);

  theta*=-1*M_PI/180.0f;
  float x1 = canon.getX() , y1 = canon.getY();
  float rx= canon.getSideX() , ry = canon.getSideY();
  
 // output2(x1,y1);
 // output2(rx,ry);

  float y = y1 + ry*cos(theta);
  float x = x1 + ry*sin(theta);
  y = y + rx/2*cos(M_PI/2 - theta);
  //output1(sin(M_PI/2 - theta));
  x = x + rx/2*sin(M_PI/2 - theta);
 // output2(x,y);
  return MP(MP(x,y),MP(cos(M_PI/2 - theta),sin(M_PI/2 - theta)));
}

void getBorders(Quadrilateral rect, int index){

   vector<pair<float,float> > vert = rect.get4Vertices();
    int ind=0;
    TR(vert,it){
     //output2((*it).F,(*it).S);
      borders[index][ind] = new Circle(360,0,0,0,0,(*it).F,(*it).S,0,0.05,0,0);

      ind++;
    }

}

int main (int argc, char** argv)
{
  float theta=1, ax= MEW*VELOCITY;
	 int width = SCREEN_WIDTH;
	 int height = SCREEN_HEIGHT;
   int projectile_collision_count,flag[]={0,0,0};
   float collide_vel;
   speed_level=0;

  obstacles[0] = new Quadrilateral(1,9.7,0,0,0.3,7,0,0.05,0.3,0,10000,1);

  obstacles[1] = new Quadrilateral(90,9.7,6.3,0,0.5,5,0,0.05,0.3,0,10000,1);
  obstacles[2] = new Quadrilateral(90,7.7,3.3,0,0.5,2,0,0.05,0.3,0,10000,1);
  obstacles[3] = new Quadrilateral(0,7.4,0,0,0.3,3.5,0,0.05,0.3,0,10000,1);
  obstacles[4] = new Quadrilateral(180,5.2,6.5,0,0.3,2.5,0,0.05,0.3,0,10000,1);

  obstacles[5] = new Quadrilateral(90,10,-0.5,0,1,19.5,0,0.05,0.3,0,10000,1);

  for(int i=0;i<6;i++){
    getBorders(*obstacles[i],i);
  }


   
    canon = new Quadrilateral(-50,-6.8,0.8,0,0.5,2.7,0,0.05,0.2,0,10000,1);
    base = new Quadrilateral(0,-6.8,0,0,2.5,0.8,0,0.05,0.2,0,10000,1);

    button_base = new Quadrilateral(0,5.9,1.3,0,1.5,0.8,0,0.05,1,0,10000,1);
    button = new Quadrilateral(0,5.55,1.3,0,0.35,0.8,0,0.05,1,0,10000,1);

    getBorders(*button,6);
    getBorders(*button_base,7);
    borders[7][1]->updatePosition(borders[7][1]->getX(),borders[7][1]->getY()-0.45);
    borders[7][2]->updatePosition(borders[7][2]->getX(),borders[7][2]->getY()+0.45);

    tar = new Quadrilateral(90,9.5,1.3,0,0.4,1.5,0,0.05,0.2,0,10000,1);

    getBorders(*tar,8);

    jumper = new Circle(360,0,-1*VELOCITY/16,0,0,0,5,0,0.5,0,0);

    lines[0] = new Line(9.2,0,0,90,1);
    lines[1] = new Line(8.2,0,0,49,1.45);
    lines[2] = new Line(9.2,0,0,39,1.45);

    lines[3] = new Line(8.9,0,0,49,1.36);
    lines[4] = new Line(9.2,0,0,49,1.36);
    lines[5] = new Line(8.6,0,0,49,1.36);

     lines[6] = new Line(8.4,0,0,39,1.36);
     lines[7] = new Line(8.7,0,0,39,1.36);
     lines[8] = new Line(9.0,0,0,39,1.36);


      for(int i=0;i<=10;i++){
        bar[i] = new Quadrilateral(0,-9+float(i)/8,8,0,0.25,1,0,0,1,0,0,1); 
      }

      hinge = new Circle(360,0,0,0,0,5.05,6.5,0,0.05,0,0);

/***** background elements****/

      back_floor = new Quadrilateral(0,0,0,0,6,5,0,0.05,0.3,0,10000,1);

      back_lines[0] = new Quadrilateral(0,0,0,0,5,5,0,0.05,0.3,0,10000,1);

      paint[0] = new Line(-9.3,2,0,-5,4);
      paint[1] = new Line(-9.7,-2,0,5,4);
      paint[2] = new Line(-5.8,-1.33,0,40,2.7);

      paint[3] = new Line(6.2,1.35,0,185,4);
      paint[4] = new Line(6.2,-1.35,0,175,4);
      paint[5] = new Line(6.2,-1.33,0,45,2.7);

      back_circles[0] = new Circle(360,0,0,0,0,-5.6,0.0,0,1.35,0,0,0);
      back_circles[1] = new Circle(360,0,0,0,0,0,0,0,1.35,0,0,1);
      back_circles[2] = new Circle(360,0,0,0,0,-8,0,0,4,0,0,0);
      back_circles[3] = new Circle(360,0,0,0,0,6.2,0,0,1.35,0,0,0);
      back_circles[4] = new Circle(360,0,0,0,0,8.5,0,0,4,0,0,0);
      int x=-2;
      for(int i=0;i<BALL_CIRCLES;i++){
        ball_circles[i] = new Circle(360,0,0,0,0,x,9,0,0.5,0,0,0);
        ball_fill_circles[i] = new Circle(360,0,0,0,0,x,9,0,0.5,0,0,1);
        x-=1;
      }

    GLFWwindow* window = initGLFW(width, height);
	  initGL (window, width, height);
    double last_update_time = glfwGetTime(), current_time;
    double start_time=last_update_time;
    // Draw in loop
    pair <float,float> centre;float rad;
    vector<pair<float,float> > verti;

    
    while (!glfwWindowShouldClose(window)) {
     // output2(jumper->getY(),jumper->getVY());

        if(motion_phase_projectile){
          if(projectile->getX()>10 || projectile->getX()<-10)
            motion_phase_projectile=false;
          if(projectile->getY()>10 || projectile->getY()< -10)
            motion_phase_projectile = false;
        }
       
       if(chance_no == CHANCES){
        if(!game_end_flag){
            output1(score);
            cout << "****GAME OVER****" << endl;
            game_end_flag = true;
          }
          game_end = true;
        }
        // OpenGL Draw commands
        draw();

        // Swap Frame Buffer in double buffering
        glfwSwapBuffers(window);

        // Poll for Keyboard and mouse events
        
          glfwPollEvents();
        
      if(motion_phase_start_projectile){
          pair<pair<float,float>,pair<float,float> > dis;
          can_roll = true;
          win = false;
          
          if(chance_no<CHANCES){
            points -= 10;
          motion_phase_projectile = true;
          dis=getProjectileInitPosition(*canon);
          float displace = DISPLACEMENT + (float)speed_level/10;
          projectile = new Circle(360,0,-1*VELOCITY,displace*dis.S.F,displace*dis.S.S,dis.F.F,dis.F.S,0,0.25,0,0);
          GLfloat * circle_vertices = circleVertices(projectile->num_vertices, projectile->radius);
          GLfloat * circle_colors = circleColors(projectile->num_vertices,1, 0.54902, 0);

          projectile->setInitVertices(circle_vertices);
          projectile->setInitColors(circle_colors);
          projectile->createCircle();

            flag[0]=flag[1]=flag[2] =0;
            motion_phase_start_projectile = false;
            projectile_collision_count=0;
            chance_no++;
          }
        }
    // collision with floor

        // Control based on time (Time based transformation like 5 degrees rotation every 0.5s)
        current_time = glfwGetTime(); // Time in seconds
        if ((current_time - last_update_time) >= 0.05) { 

        if(motion_phase_projectile){
           if(checkCollision(*projectile,borders[5][1]->getCentre(),borders[5][2]->getCentre()) ){
              //output2("collide","");
              if(!flag[0]){
                collide_vel=projectile->getVX();
              if(collide_vel>0)
                projectile->setAX(-1*ax);
              else if(collide_vel<0)
                projectile->setAX(ax);
                flag[0]=1;
              }
              if(collide_vel*projectile->getVX()<=0){
                projectile->setAX(0);
                projectile->setVX(0);
                motion_phase_projectile = false;
              }
              if(!win){
              projectile->setY(0);
              projectile->setVY(0);
              projectile->setAY(0);
            }
          }  
          // 0 - 4
          if(checkCollision(*projectile,borders[0][3]->getCentre(),borders[0][0]->getCentre()) ){
           // output2(0,4);
            onCollision(projectile,obstacles[0]);
          }
            // 1 - 2
           
          if(checkCollision(*projectile,borders[1][1]->getCentre(),borders[1][2]->getCentre()) ){
              //output2("collide","");
              //output2(1,2);
              if(!flag[1]){
                collide_vel=projectile->getVX();
              if(collide_vel>0)
                projectile->setAX(-1*ax);
              else if(collide_vel<0)
                projectile->setAX(ax);
                flag[1]=1;
              }
              if(collide_vel*projectile->getVX()<=0){
                projectile->setAX(0);
                projectile->setVX(0);
                motion_phase_projectile = false;
              }
             
              projectile->setVY(0);
              projectile->setEFY(VELOCITY);
          }
          // 1 - 3,4
          if(
           checkCollision(*projectile,borders[1][2]->getCentre(),borders[1][3]->getCentre()) ||
           checkCollision(*projectile,borders[1][3]->getCentre(),borders[1][0]->getCentre()) 
           ){
            //output2(1,3);
            onCollision(projectile,obstacles[1]);
            }
          //2 - 3-4
          if(
           checkCollision(*projectile,borders[2][2]->getCentre(),borders[2][3]->getCentre()) ||
           checkCollision(*projectile,borders[2][3]->getCentre(),borders[2][0]->getCentre()) 
           ){
           // output2(2,3);
            onCollision(projectile,obstacles[2]);
        }
          //2 - 2
          if(checkCollision(*projectile,borders[2][1]->getCentre(),borders[2][2]->getCentre()) ){
             // output2(2,2);
              if(!flag[2]){
                collide_vel=projectile->getVX();
              if(collide_vel>0)
                projectile->setAX(-1*ax);
              else if(collide_vel<0)
                projectile->setAX(ax);
                flag[2]=1;
              }
              if(collide_vel*projectile->getVX()<=0){
                projectile->setAX(0);
                projectile->setVX(0);
                motion_phase_projectile = false;
              }
            
              projectile->setVY(0);
              projectile->setEFY(VELOCITY);
            }
          //3 2-4
           if(
           checkCollision(*projectile,borders[3][1]->getCentre(),borders[3][2]->getCentre()) ||
           checkCollision(*projectile,borders[3][3]->getCentre(),borders[3][0]->getCentre()) 
           ){
           // output2(3,2);
            onCollision(projectile,obstacles[3]);
          }

          // button
          if(
          
           checkCollision(*projectile,borders[6][3]->getCentre(),borders[6][0]->getCentre()) 
           ){
           // output2(3,2);
            onCollision(projectile,button);
            stop_oscillation = true;
          }

          //button-base
           if(
           checkCollision(*projectile,borders[7][0]->getCentre(),borders[7][1]->getCentre()) ||
           checkCollision(*projectile,borders[7][2]->getCentre(),borders[7][3]->getCentre()) 
           ){
           // output2(3,2);
            onCollision(projectile,button_base);
          }
           //perfect
             if(
                 checkCollision(*projectile,borders[4][1]->getCentre(),borders[4][2]->getCentre()) ||
                 checkCollision(*projectile,borders[4][2]->getCentre(),borders[4][3]->getCentre()) ||
                 checkCollision(*projectile,borders[4][3]->getCentre(),borders[4][0]->getCentre()) )
               {
                
                  onCollision(projectile,obstacles[4]);
                }
             //target
             if(
            
            checkCollision(*projectile,borders[8][1]->getCentre(),borders[8][2]->getCentre())
            ){
              win = true;
            score += points;
                projectile->setAX(0);
                projectile->setAY(0);
                projectile->setVX(0);
                projectile->setVY(0);
                projectile->setX(8.8);
                projectile->setY(0.7);
                cout << "into the basket" << endl;
             }
             //jumper
             if(checkCollision(*projectile,*jumper)){
              unnatural = false;
              float v1x=projectile->getVX();
              float v1y = projectile->getVY();
              float v2x=jumper->getVX();
              float v2y = jumper->getVY();
              projectile->setVX(v2x);
              projectile->setVY(v2y);
              jumper->setVX(v1x);
              jumper->setVY(v1y);
             }

             if(!unnatural && jumper->getY()<0){
              jumper->setY(0);
             }

             if(!unnatural && checkCollision(*jumper,borders[5][1]->getCentre(),borders[5][2]->getCentre()) ){
              //output2("collide","");
              if(!flag[0]){
                collide_vel=jumper->getVX();
              if(collide_vel>0)
                jumper->setAX(-1*ax);
              else if(collide_vel<0)
               jumper->setAX(ax);
                flag[0]=1;
              }
              if(collide_vel*jumper->getVX()<=0){
                jumper->setAX(0);
                jumper->setVX(0);
              }
              jumper->setY(0);
              jumper->setVY(0);
              jumper->setAY(0);
          }  
          
        }

          if(!stop_oscillation){
            
            obstacles[4]->updateAngle(theta,-25,25);
            if(obstacles[4]->getAngle()>=obstacles[4]->rect_rot + 23 || obstacles[4]->getAngle()<=obstacles[4]->rect_rot -23)
              theta*=-1;
            verti.clear();
            verti = obstacles[4]->get4Vertices();
            int indi=0;
            TR(verti,it){
              borders[4][indi]->updatePosition((*it).F,(*it).S);
              indi++;
            }
           
        } else{
              if(obstacles[4]->getAngle()> obstacles[4]->rect_rot - 90){
                theta = -1;
                obstacles[4]->updateAngle(theta,90,205);
                verti.clear();
                verti = obstacles[4]->get4Vertices();
                int indi=0;
                TR(verti,it){
                  borders[4][indi]->updatePosition((*it).F,(*it).S);
                  indi++;
                }
              }else{
                obstacles[4]->setAngle(90);
               /* bound = false;
                obstacles[4]->boundary_points.clear();
                if(bound1){
                  bound1=false;
                }*/
              }
            }


        if(motion_phase_projectile){
              projectile->updatePosition(current_time-motion_start_time);
              projectile->setEFY(0);
        }
//borders[4][1]->updatePosition(1);            
        // atleast 0.5s elapsed since last frame
            // do something every 0.5 seconds ..
/***
          if(motion_phase_projectile ){
            if(projectile->getY()<=-3.5){
              
              
             // output2(projectile->getAX(),projectile->getVX());
            }
          }

          if(bound && obstacles[4]->getAngle()<=90){
            //output1(SZ(obstacles[4]->boundary_points));
            setBoundaries(obstacles[4]);
          }
          if(motion_phase_projectile && checkCollision(*projectile,*boundary_right,&centre,&rad)){
            onCollision(projectile,boundary_right,centre,rad);
          }

          if(motion_phase_projectile && checkCollision(*projectile,*button_base,&centre,&rad)){
            onCollision(projectile,button_base,centre,rad);
          }

          if(motion_phase_projectile && checkCollision(*projectile,*button,&centre,&rad)){
            onCollision(projectile,button,centre,rad);
            stop_oscillation=true;
          }


            
            for(int i=0;i<STATIC_OBSTACLES;i++){
              if(motion_phase_projectile && checkCollision(*projectile,*obstacles[i],&centre,&rad)){
                onCollision(projectile,obstacles[i],centre,rad);
                //output1(i);
                //output2(centre.F,centre.S);
               }
            }
            
            if(!stop_oscillation){
            if(obstacles[4]->getAngle()>=23 || obstacles[4]->getAngle()<=-23)
              theta*=-1;
            obstacles[4]->updateAngle(theta,-25,25);
            
            }
            else{
              //while(obstacles[4]->getAngle()!=180){
              
            }
            if(motion_phase_projectile)
           // output2(projectile->getX(),projectile->getY());
            if(stop_oscillation){
              float dt = distance(tar->getX()+tar->getSideX()/2,tar->getY()+tar->getSideY()/2,projectile->getX(),projectile->getY());
              if(dt<=projectile->getRadius() + 0.5 && projectile->getX()>=2.8 && projectile->getX()<=3.5){
                projectile->setX(3.2);
                projectile->setY(-2.8);
                projectile->setVX(0);
                projectile->setVY(0);
                projectile->setAX(0);
                projectile->setAY(0);

              }
            }****/
              //jumper
              jumper->updatePosition(current_time-start_time);
              if(unnatural&&jumper->getY()<=0){
                float vy = jumper->getVY();
                jumper->setVY(-1*vy);
                jumper->setY(0);
                start_time = glfwGetTime();
              }else if(unnatural && jumper->getY()>=5){
                start_time=glfwGetTime();
                float vy = jumper->getVY();
                jumper->setVY(-1*vy);
                jumper->setY(5);
              }
            last_update_time = current_time;
        }
    }

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
