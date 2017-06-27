#ifndef TEXTURES_H_
#define TEXTURES_H_

#include "rgbImage.h"

namespace textures
{
    GLuint names[10];

   void loadTextureFromFile(const char *filename)
   {
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	RgbImage theTexMap( filename );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB,
					 theTexMap.GetNumCols(), theTexMap.GetNumRows(),
					 GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData() );
	/*				 */
}


void initTextures(const char* filenames[],int txtNum)
{
	glGenTextures( txtNum, names);
	for ( unsigned i=0; i< txtNum; i++ )
    {
		glBindTexture(GL_TEXTURE_2D, names[i]);
		loadTextureFromFile(filenames[i]);
	}
}
}

#endif // TEXTURES_H_
