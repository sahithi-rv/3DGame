#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "utility.hpp"

class Quadrilateral{

public:

	GLfloat* vertex_buffer;
	GLfloat* color_buffer;


	VAO  *rectangle;
	double rect_rot;
	float rectangle_rotation;
	float vx,vy,vz;
	float sideX,sideY,sideZ;
	float boundary_radius,cor,force;
	vector<pair<float,float> > boundary_points;
	vector<pair<float,float> > vertices;
	double mass;int fill;
	Quadrilateral(float rot,float v_x,float v_y,float v_z,float sdX,float sdY,float sdZ,float rad,float COR,float NF,double m,int filled ){
		rectangle_rotation=rot;
		vx=v_x;
		vy=v_y;
		vz=v_z;
		sideX=sdX;
		sideY=sdY;
		sideZ=sdZ;
		boundary_radius = rad;
		cor = COR;
		force = NF;
		mass = m;
		fill = filled;
		rect_rot=rot;
	}

	float getX(){ return vx ;}

	float getY(){ return vy ;}
	float getZ(){ return vz ;}

	void setX(float dx){  vx = dx ;}

	void setY(float dy){  vy = dy;}
	void setZ(float dz){ vz =dz ;}

	float getSideZ(){
		return sideZ;
	}


	float getSideX(){
		return sideX;
	}

	float getSideY(){
		return sideY;
	}

	float getAngle(){
		return rectangle_rotation;
	}

	void setAngle(double theta){
		 rectangle_rotation = theta;
	}

	float getNF(){
		return force;
	}
	void setNF(float NF){
		force = NF;
	}
	GLfloat * getInitVertices(){
		//output2(vx,vy);
		//output2(sideX,sideY);
		/**GLfloat  vertex_buffer_data[] = {
			0,0,0,
			0,0+sideY,0,
			0+sideX,0+sideY,0,

			0+sideX,0+sideY,0,
			0+sideX,0,0,
			0,0,0
		};**/
		GLfloat * vertex_buffer_data = new GLfloat[100];
		vertex_buffer_data[0]=0;
		vertex_buffer_data[1]=0;
		vertex_buffer_data[2]=0;
		vertex_buffer_data[3]=0;
		vertex_buffer_data[4]=0+sideY;
		vertex_buffer_data[5]=0;
		vertex_buffer_data[6]=0+sideX;
		vertex_buffer_data[7]=0+sideY;
		vertex_buffer_data[8]=0;
		vertex_buffer_data[9]=0+sideX;
		vertex_buffer_data[10]=0+sideY;
		vertex_buffer_data[11]=0;
		vertex_buffer_data[12]=0+sideX;
		vertex_buffer_data[13]=0;
		vertex_buffer_data[14]=0;
		vertex_buffer_data[15]=0;
		vertex_buffer_data[16]=0;
		vertex_buffer_data[17]=0;		
		vertex_buffer = new GLfloat[100];
		return vertex_buffer = vertex_buffer_data;
	}
	GLfloat * getInitColors(float r,float g,float b){
		
		GLfloat * color_buffer_data = new GLfloat[100];
		for (int i=0; i<6; i++) {
        	color_buffer_data [3*i] = r;
        	color_buffer_data [3*i + 1] = g;
        	color_buffer_data [3*i + 2] = b;
   	    }
		color_buffer = new GLfloat[100];
		return color_buffer = color_buffer_data;
	}

	void setInitVertices(GLfloat vertex_buffer_data[] ){
		//vertex_buffer = new GLfloat[100];
		vertex_buffer = vertex_buffer_data;
	}

	

	void setInitColors( GLfloat color_buffer_data[]){
		//color_buffer== new GLfloat[100];
		color_buffer=color_buffer_data;
	}

	vector<pair<float,float> >  get4Vertices(){
		vertices.clear();
		double theta = rectangle_rotation - 90;
  		
  		float sx = abs(sideX) , sy = abs(sideY) ;
  		float x1 = vx, y1 = vy; 
  		float sxc = sx*cos(theta*M_PI/180.0f) , sxs = sx*sin(theta*M_PI/180.0f);
  		float syc  = sy*cos(theta*M_PI/180.0f), sys = sy*sin(theta*M_PI/180.0f);

  		vertices.PB( MP(x1,y1) );
  		//output1(theta);
  		
  		
  		theta+=90;
  		//output1(theta);
  		 sxc = sx*cos(theta*M_PI/180.0f) , sxs = sx*sin(theta*M_PI/180.0f);
  		 syc  = sy*cos(theta*M_PI/180.0f), sys = sy*sin(theta*M_PI/180.0f);
  		 x1+=sxc;y1+=sxs;
  		vertices.PB( MP(x1,y1) );

  		
  		theta+=90;  		//output1(theta);

  		 sxc = sx*cos(theta*M_PI/180.0f) , sxs = sx*sin(theta*M_PI/180.0f);
  		 syc  = sy*cos(theta*M_PI/180.0f), sys = sy*sin(theta*M_PI/180.0f);
  		 x1+=syc;y1+=sys;
  		vertices.PB( MP(x1,y1) );

  		
  		theta+=90;  		//output1(theta);

  		 sxc = sx*cos(theta*M_PI/180.0f) , sxs = sx*sin(theta*M_PI/180.0f);
  		 syc  = sy*cos(theta*M_PI/180.0f), sys = sy*sin(theta*M_PI/180.0f);
  		 		x1+=sxc;y1+=sxs;
  		vertices.PB( MP(x1,y1) );
  		return vertices;

	}

	void createRectangle ()
	{
			// GL3 accepts only Triangles. Quads are not supported
			
			GLfloat *vertex_buffer_data = new GLfloat[100];
			vertex_buffer_data= vertex_buffer;

			GLfloat *color_buffer_data = new GLfloat[100];
			color_buffer_data  = color_buffer;
			//if(fill)
				rectangle = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color_buffer_data, GL_FILL);
			//else
			//	rectangle = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color_buffer_data, GL_LINE);
	}

	void renderQuad(){
		glm::mat4 MVP;	// MVP = Projection * View * Model
		Matrices.view = glm::lookAt(glm::vec3(0,0,3), glm::vec3(0,0,0), glm::vec3(0,1,0)); // Fixed camera for 2D (ortho) in XY plane

  		glm::mat4 VP = Matrices.projection * Matrices.view;
  			/* Render your scene */

  		Matrices.model = glm::mat4(1.0f);



  		glm::mat4 translateRectangle = glm::translate (glm::vec3(vx,vy,vz));        // glTranslatef
 	    glm::mat4 rotateRectangle = glm::rotate((float)(rectangle_rotation*M_PI/180.0f), glm::vec3(0,0,1)); // rotate about vector (-1,1,1)
  		Matrices.model *= translateRectangle*((rotateRectangle ));
  		MVP = VP * Matrices.model;
  		glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

  	}

  	vector<pair<float,float> >  setBoundaryPoints(float x1,float y1, float x2,float y2){
  		float x,y;
  		double angle = atan2( (y2-y1),(x2-x1) );
  		float r = boundary_radius;
  		float dt = distance(x1,y1,x2,y2);
  		
  		while (r <= dt+0.2){
  			x = x1 + r * cos(angle);
  			y = y1 + r * sin(angle);
  			boundary_points.PB(MP(x,y));
  			r += boundary_radius;
  		}
  		return boundary_points;
  	}

	void updateAngle(float theta,float mini,float maxi){
		rectangle_rotation += theta;
	}

	void updateAngle(float theta,float mini,float maxi,int flag){
		rectangle_rotation += theta;

		if(rectangle_rotation>0)
			rectangle_rotation=0;
		else if(rectangle_rotation < -90)
			rectangle_rotation=-90;
	}

	void updatePosition(float dx,float mini,float maxi){
		vx+=dx;
		if(getX()>maxi || getX()<mini)
			vx-=dx;
		
	}



};

class Circle{

public:
	GLfloat* vertex_buffer;
	GLfloat* color_buffer;
	VAO * circle;
	int num_vertices,flag;
	float cx,cy,cz,radius;
	float gravity ;
	float ax;
	float v_x;
	float v_y;
	float s_x;
	float s_y;
	float ext_force_x,ext_force_y;
    Circle(int num,float vx,float vy,float dx,float dy,float c_x,float c_y,float c_z,float r,float EFX,float EFY,int fl=1){
			gravity = vy;
			ax=vx;
			v_x = dx;
			v_y = dy;
			num_vertices = num;
			radius = r;
			cx = c_x;
			cy = c_y;
			cz = c_z;
			ext_force_x= EFX;
			ext_force_y = EFY;
			flag=fl;
	}

		float getX(){ return cx ;}

		float getY(){ return cy ;}

		pair<float,float> getCentre(){
			return MP(cx,cy);
		}

		void setX(float dx){
			cx=dx;
		}
		void setY(float dy){
			cy=dy;
		}

		float getRadius(){
			return radius;
		}

		float getVX(){
			return v_x;
		}
		float getVY(){
			return v_y;
		}

		void setVX(float dx){
			v_x=dx;
		}
		void setVY(float dy){
			v_y=dy;
		}
		float getAX(){
			return ax;
		}
		float getAY(){
			return gravity;
		}

		void setAX(float dx){
			ax=dx;
		}
		void setAY(float dy){
			gravity=dy;
		}

		float getEFX(){
			return ext_force_x;
		}

		void setEFX(float EF){
			ext_force_x = EF;
		}

		float getEFY(){
			return ext_force_y;
		}

		void setEFY(float EFY){
			ext_force_y = EFY;
		}
	void setInitVertices( GLfloat vertex_buffer_data[]){
		vertex_buffer = new GLfloat[num_vertices];
		vertex_buffer = vertex_buffer_data;
	}

	

	void setInitColors( GLfloat color_buffer_data[]){
		color_buffer== new GLfloat[num_vertices];
		color_buffer=color_buffer_data;
	}

	void createCircle(){
		if(flag)
			circle = create3DObject(GL_TRIANGLE_FAN,num_vertices,vertex_buffer,color_buffer,GL_FILL);
		else 
			circle = create3DObject(GL_LINES,num_vertices,vertex_buffer,color_buffer,GL_LINE);

	}

	void renderCircle(){
		glm::mat4 MVP;	// MVP = Projection * View * Model
		Matrices.view = glm::lookAt(glm::vec3(0,0,3), glm::vec3(0,0,0), glm::vec3(0,1,0)); // Fixed camera for 2D (ortho) in XY plane

  		glm::mat4 VP = Matrices.projection * Matrices.view;
  			/* Render your scene */

  		Matrices.model = glm::mat4(1.0f);



  		
  		glm::mat4 translateCircle = glm::translate (glm::vec3(cx,cy,cz));        // glTranslatef
 	   // glm::mat4 rotateRectangle = glm::rotate((float)(rectangle_rotation*M_PI/180.0f*-1), glm::vec3(0,0,1)); // rotate about vector (-1,1,1)
  		Matrices.model *= translateCircle;//*((rotateRectangle ));
  		MVP = VP * Matrices.model;
  		glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

  	}

  	void updatePosition(double time){
  		//output1(ax);
  			cx+=v_x + ax*time;
  			cy+= v_y + gravity*time + ext_force_y*time;
  			v_y+=gravity*time + ext_force_y*time;
  			v_x+=ax*time;
  	}

  	void updatePosition(float c_x,float c_y){
  		cx=c_x;
  		cy=c_y;
  	}

};

class Line{
	public:
		VAO * line;
		GLfloat* vertex_buffer;
		GLfloat* color_buffer;
		float x1,y1,z1;
		float x2,y2,z2;
		float rotation,length;
		Line(float x,float y,float z,float rot,float l){
			x1=x;y1=y;z1=z;
			//x2=z0;y=y0;z2=z0;
			rotation=rot;length=l;
		}

		GLfloat * getInitVertices(){
			GLfloat * vertex_buffer_data = new GLfloat[6];
			vertex_buffer_data[0]=vertex_buffer_data[1]=vertex_buffer_data[2]=0;
			vertex_buffer_data[3]=length*cos(rotation*M_PI/180.0f);
			vertex_buffer_data[4]=length*sin(rotation*M_PI/180.0f);
			vertex_buffer_data[5]=0;
			//output2(length*cos(rotation*M_PI/180.0f),length*sin(rotation*M_PI/180.0f));
			return vertex_buffer_data;
		}

		GLfloat * getInitColors(float r,float g,float b){
			GLfloat * color_buffer_data = new GLfloat[6];
			color_buffer_data[0]=color_buffer_data[3]=r;
			color_buffer_data[1]=color_buffer_data[4]=g;
			color_buffer_data[2]=color_buffer_data[5]=b;

			return color_buffer_data;

		}

		GLfloat * setInitVertices(GLfloat ver[]){
			  vertex_buffer = new GLfloat[6];
			vertex_buffer = ver;
		}

		GLfloat * setInitColors(GLfloat  col[]){
			 color_buffer = new GLfloat[6];
			color_buffer=col;
		}

		void createLine(){
			GLfloat * vertex_buffer_data = new GLfloat[6];
			vertex_buffer_data = vertex_buffer;
			GLfloat * color_buffer_data = new GLfloat[6];
			 color_buffer_data = color_buffer;
			 
			line = create3DObject(GL_LINES,2,vertex_buffer_data,color_buffer_data,GL_FILL);
		}

		void renderLine(){
		glm::mat4 MVP;	// MVP = Projection * View * Model
		Matrices.view = glm::lookAt(glm::vec3(0,0,3), glm::vec3(0,0,0), glm::vec3(0,1,0)); // Fixed camera for 2D (ortho) in XY plane

  		glm::mat4 VP = Matrices.projection * Matrices.view;
  			/* Render your scene */

  		Matrices.model = glm::mat4(1.0f);



  		glm::mat4 translateLine = glm::translate (glm::vec3(x1,y1,z1));        // glTranslatef
 	    glm::mat4 rotateLine = glm::rotate((float)(rotation*M_PI/180.0f), glm::vec3(0,0,1)); // rotate about vector (-1,1,1)
  		Matrices.model *= translateLine*((rotateLine ));
  		MVP = VP * Matrices.model;
  		glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

  	}



};

#endif
