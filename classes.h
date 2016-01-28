#include "resources.h"

class Cuboid{
public:
	VAO * cube;
	double cx,cy,cz;int cube_no;
	double sideX,sideY,sideZ;
	GLfloat * vertex_buffer,*color_buffer;
	Cuboid(double c_x,double c_y,double c_z,double sx,double sy,double sz,int cno ){
		cx = c_x;
		cy = c_y;
		cz = c_z;
		sideX = sx;
		sideY = sy;
		sideZ = sz;
		cube_no = cno;

	}

	void setInitVertices(){
		static const GLfloat vertex_buffer_data [] = {
			0,0,0,//side 1
			sideX,0,0,
			sideX,sideY,0,

			sideX,sideY,0,
			0,sideY,0,
			0,0,0,

			0,sideY,sideZ,//side 2
			sideX,sideY,sideZ,
			sideX,sideY,0,

			sideX,sideY,0,
			0,sideY,0,
			0,sideY,sideZ,

			0,0,sideZ,//side 3
			sideX,0,sideZ,
			sideX,sideY,sideZ,

			sideX,sideY,sideZ,
			0,sideY,sideZ,
			0,0,sideZ,

			0,0,sideZ,//side 4
			sideX,0,sideZ,
			sideX,0,0,

			sideX,0,0,
			0,0,0,
			0,0,sideZ,

			sideX,0,sideZ,//side 5
			sideX,0,0,
			sideX,sideY,0,

			sideX,sideY,0,
			sideX,sideY,sideZ,
			sideX,0,sideZ,

			0,0,sideZ,//side 6
			0,0,0,
			0,sideY,0,

			0,sideY,0,
			0,sideY,sideZ,
			0,0,sideZ,
		};
		vertex_buffer = new GLfloat[3*36];
		for(int i=0;i<36;i++){
			vertex_buffer[3*i]  = vertex_buffer_data[3*i]; 
			vertex_buffer[3*i+1]  = vertex_buffer_data[3*i+1]; 
			vertex_buffer[3*i+2]  = vertex_buffer_data[3*i+2]; 
		}

	}

	void setInitVertices(GLfloat vertex_buffer_data[] ){
		vertex_buffer = new GLfloat[3*36];
		vertex_buffer = vertex_buffer_data;
	}

	

	void setInitColors( GLfloat color_buffer_data[]){
		color_buffer= new GLfloat[3*36];
		color_buffer=color_buffer_data;
	}

	void setInitColors(int side,double r,double g,double b){

		for(int i = side*6;i<6*side + 6;i++){
			color_buffer[3*i]=r;
			color_buffer[3*i+1]=g;
			color_buffer[3*i+2]=b;
		}
	}
	void startSetInitColors(){
		
	}

	void setInitColors(double r, double g, double b){
	color_buffer = new GLfloat[3*36];
		//color_buffer = new GLfloat[3*36];
		/*for(int i=0;i<6;i++){
			color_buffer[3*i]=1;
			color_buffer[3*i+1]=0;
			color_buffer[3*i+2]=0;
		}
		for(int i=6;i<12;i++){
			color_buffer[3*i]=0;
			color_buffer[3*i+1]=1;
			color_buffer[3*i+2]=0;
		}
		for(int i=12;i<18;i++){
			color_buffer[3*i]=1;
			color_buffer[3*i+1]=1;
			color_buffer[3*i+2]=0;
		}
		for(int i=18;i<24;i++){
			color_buffer[3*i]=0;
			color_buffer[3*i+1]=0;
			color_buffer[3*i+2]=1;
		}
		for(int i=24;i<30;i++){
			color_buffer[3*i]=0;
			color_buffer[3*i+1]=1;
			color_buffer[3*i+2]=1;
		}
		for(int i=30;i<36;i++){
			color_buffer[3*i]=1;
			color_buffer[3*i+1]=0;
			color_buffer[3*i+2]=1;
		}*/	
		for(int i=0;i<6;i++){
			//cout << i << endl;
			setInitColors(i,r,g,b);
		}


	}

	void createCube ()
	{
			GLfloat *vertex_buffer_data = new GLfloat[3*36];
			vertex_buffer_data= vertex_buffer;

			GLfloat *color_buffer_data = new GLfloat[3*36];
			color_buffer_data  = color_buffer;
		
		// create3DObject creates and returns a handle to a VAO that can be used later
		cube = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, color_buffer_data, GL_FILL);
	}

	void renderCube(glm::mat4 VP){
		glm::mat4 MVP;
		Matrices.model = glm::mat4(1.0f);
  		glm::mat4 translateCube = glm::translate (glm::vec3(cx,cy,cz));        // glTranslatef
 	   // glm::mat4 rotateRectangle = glm::rotate((float)(rectangle_rotation*M_PI/180.0f), glm::vec3(0,0,1)); // rotate about vector (-1,1,1)
  		Matrices.model *= translateCube;//*((rotateRectangle ));
  		MVP = VP * Matrices.model;
  		glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
  		draw3DObject(cube);
	}
};
