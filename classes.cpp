#include "classes.h"

platform::createCube ()
{
  // GL3 accepts only Triangles. Quads are not supported
  static const GLfloat vertex_buffer_data [] = {
    0,0,0,//side 1
    1,0,0,
    1,1,0,

    1,1,0,
    0,1,0,
    0,0,0,

    0,1,1,//side 2
    1,1,1,
    1,1,0,

    1,1,0,
    0,1,0,
    0,1,1,

    0,0,1,//side 3
    1,0,1,
    1,1,1,

    1,1,1,
    0,1,1,
    0,0,1,

    0,0,1,//side 4
    1,0,1,
    1,0,0,

    1,0,0,
    0,0,0,
    0,0,1,

    1,0,1,//side 5
    1,0,0,
    1,1,0,

    1,1,0,
    1,1,1,
    1,0,1,

    0,0,1,//side 6
    0,0,0,
    0,1,0,

    0,1,0,
    0,1,1,
    0,0,1,
  };

  GLfloat color_buffer_data [3*40];
  for(int i=0;i<6;i++){
    color_buffer_data[3*i]=1;
    color_buffer_data[3*i+1]=0;
    color_buffer_data[3*i+2]=0;
  }
  for(int i=6;i<12;i++){
    color_buffer_data[3*i]=0;
    color_buffer_data[3*i+1]=1;
    color_buffer_data[3*i+2]=0;
  }
  for(int i=12;i<18;i++){
    color_buffer_data[3*i]=1;
    color_buffer_data[3*i+1]=1;
    color_buffer_data[3*i+2]=0;
  }
  for(int i=18;i<24;i++){
    color_buffer_data[3*i]=0;
    color_buffer_data[3*i+1]=0;
    color_buffer_data[3*i+2]=1;
  }
  for(int i=24;i<30;i++){
    color_buffer_data[3*i]=0;
    color_buffer_data[3*i+1]=1;
    color_buffer_data[3*i+2]=1;
  }
  for(int i=30;i<36;i++){
    color_buffer_data[3*i]=1;
    color_buffer_data[3*i+1]=0;
    color_buffer_data[3*i+2]=1;
  }

  // create3DObject creates and returns a handle to a VAO that can be used later
  rectangle = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, color_buffer_data, GL_FILL);
}
