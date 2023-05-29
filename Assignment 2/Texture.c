#include "Texture.h"
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996) // FUCKING COMPILE

#define TOPRIGHT 1, 1
#define TOPLEFT 0, 1
#define BOTTOMLEFT 0, 0
#define BOTTOMRIGHT 1, 0

Texture* load_texture(char* filename, char* shortname)
{
	Texture* this = malloc(sizeof(Texture));

	// copy over the filename
	strncpy(this->filename, filename, MAXNAME);
	strncpy(this->shortname, shortname, MAXNAME);

	// the ID of the image file
	FILE* fileID;

	// maxValue
	int  maxValue;

	// total number of pixels in the image
	int  totalPixels;

	// temporary character
	char tempChar;

	// counter variable for the current pixel in the image
	int i;

	// array for reading in header information
	char headerLine[100];

	// if the original values are larger than 255
	float RGBScaling;

	// temporary variables for reading in the red, green and blue data of each pixel
	int red, green, blue;

	GLubyte* image;

	// open the image file for reading - note this is hardcoded would be better to provide a parameter which
	//is the file name. There are 3 PPM files you can try out mount03, sky08 and sea02.
	fileID = fopen(filename, "r");

	if (!fileID)
	{
		printf("no file\n");
		printf("%s", filename);
	}
	

	// read in the first header line
	//    - "%[^\n]"  matches a string of all characters not equal to the new line character ('\n')
	//    - so we are just reading everything up to the first line break
	fscanf(fileID, "%[^\n] ", headerLine);

	// make sure that the image begins with 'P3', which signifies a PPM file
	if ((headerLine[0] != 'P') || (headerLine[1] != '3'))
	{
		printf("This is not a PPM file!\n");
		exit(0);
	}

	// we have a PPM file
	printf("%s is a PPM3 file.\n", filename);

	// read in the first character of the next line
	fscanf(fileID, "%c", &tempChar);

	// while we still have comment lines (which begin with #)
	while (tempChar == '#')
	{
		// read in the comment
		fscanf(fileID, "%[^\n] ", headerLine);

		// print the comment
		printf("%s\n", headerLine);

		// read in the first character of the next line
		fscanf(fileID, "%c", &tempChar);
	}

	// the last one was not a comment character '#', so we need to put it back into the file stream (undo)
	ungetc(tempChar, fileID);

	// read in the image hieght, width and the maximum value
	fscanf(fileID, "%d %d %d", &(this->width), &(this->height), &maxValue);

	// print out the information about the image file
	printf("%d rows  %d columns  max value= %d\n", this->width, this->height, maxValue);

	// compute the total number of pixels in the image
	totalPixels = this->width * this->height;

	// allocate enough memory for the image  (3*) because of the RGB data
	image = malloc(3 * sizeof(GLuint) * totalPixels);


	// determine the scaling for RGB values
	RGBScaling = 255.0 / maxValue;


	// if the maxValue is 255 then we do not need to scale the 
	//    image data values to be in the range or 0 to 255
	if (maxValue == 255)
	{
		for (i = 0; i < totalPixels; i++)
		{
			// read in the current pixel from the file
			fscanf(fileID, "%d %d %d", &red, &green, &blue);

			// store the red, green and blue data of the current pixel in the data array
			image[3 * totalPixels - 3 * i - 3] = red;
			image[3 * totalPixels - 3 * i - 2] = green;
			image[3 * totalPixels - 3 * i - 1] = blue;
		}
	}
	else  // need to scale up the data values
	{
		for (i = 0; i < totalPixels; i++)
		{
			// read in the current pixel from the file
			fscanf(fileID, "%d %d %d", &red, &green, &blue);

			// store the red, green and blue data of the current pixel in the data array
			image[3 * totalPixels - 3 * i - 3] = red * RGBScaling;
			image[3 * totalPixels - 3 * i - 2] = green * RGBScaling;
			image[3 * totalPixels - 3 * i - 1] = blue * RGBScaling;
		}
	}

	// now we are ready to call the OpenGL functions to generate the texture
	glGenTextures(1, &(this->ID));
	glBindTexture(GL_TEXTURE_2D, this->ID);

	// TODO: set these via members from the struct
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, this->width, this->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	// close the image file
	fclose(fileID);

	free(image);
	return this;
}

void texture_test(Texture* t)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, t->ID);
	glBegin(GL_QUADS);

	// faff about until it works
	glNormal3i(0, 1, 0);
	glTexCoord2i(TOPRIGHT);
	glVertex3i(5, 1, 5);

	glTexCoord2i(TOPLEFT);
	glVertex3i(-5, 1, 5);

	glTexCoord2i(BOTTOMLEFT);
	glVertex3i(-5, 1, -5);

	glTexCoord2i(BOTTOMRIGHT);
	glVertex3i(5, 1, -5);

	glEnd();
	glDisable(GL_TEXTURE_2D);
}