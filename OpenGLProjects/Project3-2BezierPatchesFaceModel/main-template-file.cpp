/*
Syed F. Ali
COSC 518 Project 3 Texture Project 
Assignment Due: November 23rd, 2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <fstream>                                                                                                                                      // To read in a text file
#include <sstream>                                                                                                                                      // To read in a text file
#include <GL/glut.h>
#include "ASEParser.h"
#include "ASETextureParser.h"
#include "Image.h"


ASEParser parser[8];
ASETextureParser texParser;

float tcu;
float tcv;
float tcw;
//default state
CVector *defaultStatePoints = NULL;
CFace *defaultStateLines = NULL;

//current state
CVector *currentStatePoints = NULL;
CFace *currentStateLines = NULL;

//targetState
CVector *targetStatePoints = NULL;
CFace *targetStateLines = NULL;

//target State == smile
CVector *smileTargetStatePoints = NULL;
CFace *smileTargetStateLines = NULL;
//targetState == surprise
CVector *surpriseTargetStatePoints = NULL;
CFace *surpriseTargetStateLines = NULL;
//targetState == anger
CVector *angerTargetStatePoints = NULL;
CFace *angerTargetStateLines = NULL;

//targetState == sad
CVector *sadTargetStatePoints = NULL;
CFace *sadTargetStateLines = NULL;

//targetState == disgust
CVector *disgustTargetStatePoints = NULL;
CFace *disgustTargetStateLines = NULL;

//targetState == fear
CVector *fearTargetStatePoints = NULL;
CFace *fearTargetStateLines = NULL;

CVector *texFaceVerts = NULL;
CFace *texFace = NULL;

//Load the texture
CImage textureImage;
GLuint tex;
//rotation angle variable
float GAngle = 45.0f;

// Default to the point rendering mode.
int	renderingMode = 1;
//a variable to be a light switch for lights
bool bLighting = false;

static CVector *tempBuffer;
static int numPoints;
//how fast the animation occurs
float blendSpeed = 0.005;
//holds the value of the number of frames it takes to complete the animation
const float animationFrameSequenceLength = 1/blendSpeed;
//used to tell when to skip to the next target state
const float animationLifetime = animationFrameSequenceLength + 1;
//amount of frames it takes to run the blending animation
int animationFrameCounter = 0;


//Change the Target State that the animation transitions to
//we only need to exchange point info but we'll do both(points,lines) for consistancy
void changeTargetState(CVector *newStatePoints,CFace *newStateLines)
{
	//reset animationFrameCounter to 0
	animationFrameCounter = 0;
	//copy current points into the buffer
	memcpy(tempBuffer,currentStatePoints,sizeof(CVector)*numPoints);
	//transfer the location of the new state points to the new target
	targetStatePoints = newStatePoints;
	targetStateLines = newStateLines;
}

//function to automatically loop through all animations
void chooseAutoRandomTarget()
{
	//light values to associate with different mood switches
	float diffuseGoodMood[] = { 5.0f, 5.0f, 0.0, 1.0f};
	float diffuseBadMood[] = { 2.0f, 0.0f, 0.0f, 1.0f};
	int random;
	
	random = rand() % 9 + 3;
	//keep track of the last used Random number
	static int lastRandomGenerated;
	//if the new random numeber is the same as the last; find another!
	if(random == lastRandomGenerated)
	{
		random = rand() % 9 + 3;
	}
	//store the current of random to ensure it doesn't repeat
	lastRandomGenerated = random;
	//change the target states to update to a new/differnet animation sequence
	switch(random)
	{
		case 1:
		case 2: break;
		case 3:
			{

				changeTargetState(defaultStatePoints, defaultStateLines);
				break;
			}
		case 4:
			{
				glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseBadMood);
				changeTargetState(fearTargetStatePoints, fearTargetStateLines);
				break;
			}
		case 5:
			{
				glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseGoodMood);
				changeTargetState(smileTargetStatePoints, smileTargetStateLines);
				break;
			}
		case 6: 
			{
				glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseGoodMood);
				changeTargetState(surpriseTargetStatePoints, surpriseTargetStateLines);
				break;
			}
		case 7 :
			{
				glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseBadMood);
				changeTargetState(angerTargetStatePoints, angerTargetStateLines);
				break;
			}
		case 8:
			{
				glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseBadMood);
				changeTargetState(sadTargetStatePoints, sadTargetStateLines);
				break;
			}
		case 9:
			{
				glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseBadMood);
				changeTargetState(disgustTargetStatePoints, disgustTargetStateLines);
				break;
			}
		default:
			{
				//could run an animation state here
				break;
			}
	}
	
}

//Interpolation Algorithm

void updateState(float blendSpeed, int pA, int pB, int pC)
{
     // Instruction 11: generate in-between frames here:
                     
}

void enableLights()
{
     
	
		float ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
        float diffuse[] = {1.0f, 1.0f, 0.0f, 1.0f};
		float specular[] = {1.0f, 0.0f, 1.0f, 1.0f};
        float position[] = {-20.0f, 20.0f, 20.0f, 0.0f};
		
		glLightfv(GL_LIGHT0, GL_POSITION, position);
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, specular);       

        glFrontFace(GL_CW);
		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
		glEnable(GL_COLOR_MATERIAL);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_AUTO_NORMAL);
        glEnable(GL_NORMALIZE);
        glEnable(GL_DEPTH_TEST); 
        

}


void initTexture()
{
	
	//Instruction 3: read the texture image data into memory
	tex = textureImage.ReadBitmap("loriface512.img");
	
	/* Get the textures. */
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	//pass the address from ASETextureParser to the global texture variables
	texFaceVerts = texParser.getTexVertices();
	texFace = texParser.getFaceDetails();

	//Instruction 4: enable 2d textures
	
	glEnable(GL_TEXTURE_2D);

	//Instruction 5: specify a texture for the texture object

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureImage.GetImageWidth(), textureImage.GetImageHeight(), 0 , 
		GL_RGB, GL_UNSIGNED_BYTE, textureImage.GetImage());

	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, textureImage.GetImageWidth(),
		textureImage.GetImageHeight(), GL_BGR_EXT, GL_UNSIGNED_BYTE,
		(GLubyte*)textureImage.GetImage());

	//Instruction 7: set min and mag texture filters parameters here:
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//Instruction 8: apply some environmental effects like lighting to the texture
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

				
}

void keyPress(unsigned char key, int x, int y) 
{
	switch(key)
	{
		case '1':
			{
				renderingMode = 1;
				
				
				
				break;
			}

		case '2':
			{
				renderingMode = 2;
				break;
			}

		case '3':
			{
				renderingMode = 3;
				changeTargetState(defaultStatePoints, defaultStateLines);
				break;
			}
		case '4':
			{	
				//fear
				renderingMode = 4;
				changeTargetState(fearTargetStatePoints, fearTargetStateLines);
				break;
			}
		case '5':
			{
				//smile
				renderingMode = 5;
				changeTargetState(smileTargetStatePoints, smileTargetStateLines);
				break;
			}
		case '6':
			{
				//surpise
				renderingMode = 6;
				changeTargetState(surpriseTargetStatePoints, surpriseTargetStateLines);
				break;
			}
		case '7':
			{
				//anger
				renderingMode = 7;
				changeTargetState(angerTargetStatePoints, angerTargetStateLines);
				break;
			}
		case '8':
			{
				//sad
				renderingMode = 8;
				changeTargetState(sadTargetStatePoints, sadTargetStateLines);
				break;
			}
		case '9':
			{
				//disgust
				renderingMode = 9;
				changeTargetState(disgustTargetStatePoints, disgustTargetStateLines);
				break;
			}
		case '0':
			{
				
				renderingMode = 0;
				changeTargetState(defaultStatePoints, defaultStateLines);
				break;
			}
		case 'l':
			{
				//if lighting is off turn it on, if its on turn it off
				if(!bLighting)
				{
					bLighting = true;
					glEnable(GL_LIGHTING);
					
				}else
				{
					glDisable(GL_LIGHTING);
					bLighting = false;
				}
				break;
			}
		//escape key exit
		case 27:
			{
				exit(0);
				break;
			}
	}
   
}

void drawPoints()
{
		CVector up(0.0f, 0.0f, 1.0f);

		glBegin(GL_POINTS);

		//iterate through the total number of faces to display them
		for (int i = 0; i < parser[0].getFaceCount(); i++)
		{
			//save off the three vertices so we can do some math on them
			CVector a = currentStatePoints[currentStateLines[i].m_a];
			CVector b = currentStatePoints[currentStateLines[i].m_b];
			CVector c = currentStatePoints[currentStateLines[i].m_c];

			glVertex3f(c.m_x, c.m_z, c.m_y);
			glVertex3f(b.m_x, b.m_z, b.m_y);
			glVertex3f(a.m_x, a.m_z, a.m_y);

		}

		glEnd();
	
	
}


void drawBezierPatches()
{
	CVector up(0.0f, 0.0f, 1.0f);

	// enable the evaluation capability
	glEnable(GL_MAP2_VERTEX_3);

	//iterate through the total number of faces to display them
	for (int i = 0; i < parser[0].getFaceCount(); i++)
	{
		CVector a = currentStatePoints[currentStateLines[i].m_a];
		CVector b = currentStatePoints[currentStateLines[i].m_b];
		CVector c = currentStatePoints[currentStateLines[i].m_c];

		// initial set - trial points
		/* GLfloat controlPoints[8][4][3] =
		{
			{
				{c.m_x, c.m_z, c.m_y},
				{c.m_x, c.m_z + 0.33, c.m_y + 0.5},
				{c.m_x, c.m_z + 0.67, c.m_y + 0.5},
				{c.m_x, c.m_z + 1.0, c.m_y}
			},
			{
				{b.m_x, b.m_z, b.m_y},
				{b.m_x, b.m_z + 0.33, b.m_y + 0.5},
				{b.m_x, b.m_z + 0.67, b.m_y + 0.5},
				{b.m_x, b.m_z + 1.0, b.m_y}
			},
			{
				{a.m_x, a.m_z, a.m_y},
				{a.m_x, a.m_z + 0.33, a.m_y + 0.5},
				{a.m_x, a.m_z + 0.67, a.m_y + 0.5},
				{a.m_x, a.m_z + 1.0, a.m_y}
			},
			{
				{c.m_x, c.m_z, c.m_y},
				{a.m_x, a.m_z, a.m_y},
				{b.m_x, b.m_z, b.m_y},
				{c.m_x, c.m_z, c.m_y}
			},
			{
				{c.m_x, c.m_z + 1.25, c.m_y - 0.5},
				{c.m_x, c.m_z + 1.33, c.m_y - 0.25},
				{c.m_x, c.m_z + 1.67, c.m_y - 0.25},
				{c.m_x, c.m_z + 1.75, c.m_y - 0.5}
			},
			{
				{b.m_x, b.m_z + 1.25, b.m_y - 0.5},
				{b.m_x, b.m_z + 1.33, b.m_y - 0.25},
				{b.m_x, b.m_z + 1.67, b.m_y - 0.25},
				{b.m_x, b.m_z + 1.75, b.m_y - 0.5}
			},
			{
				{a.m_x, a.m_z + 1.25, a.m_y - 0.5},
				{a.m_x, a.m_z + 1.33, a.m_y - 0.25},
				{a.m_x, a.m_z + 1.67, a.m_y - 0.25},
				{a.m_x, a.m_z + 1.75, a.m_y - 0.5}
			},
			{
				{c.m_x, c.m_z + 1.25, c.m_y - 0.5},
				{c.m_x, c.m_z + 1.33, c.m_y},
				{c.m_x, c.m_z + 1.67, c.m_y},
				{c.m_x, c.m_z + 1.75, c.m_y - 0.5}
			},
		};*/

		// modified set based on trial and error
	/*	GLfloat controlPoints[8][7][3] =
		{
			{
				{c.m_x, c.m_z, c.m_y},
				{c.m_x, c.m_z + 0.165, c.m_y + 0.25},
				{c.m_x, c.m_z + 0.33, c.m_y + 0.5},
				{c.m_x, c.m_z + 0.495, c.m_y + 0.75},
				{c.m_x, c.m_z + 0.67, c.m_y + 0.5},
				{c.m_x, c.m_z + 0.835, c.m_y + 0.25},
				{c.m_x, c.m_z + 1.0, c.m_y}
			},
			{
				{b.m_x, b.m_z, b.m_y},
				{b.m_x, b.m_z + 0.165, b.m_y + 0.25},
				{b.m_x, b.m_z + 0.33, b.m_y + 0.5},
				{b.m_x, b.m_z + 0.495, b.m_y + 0.75},
				{b.m_x, b.m_z + 0.67, b.m_y + 0.5},
				{b.m_x, b.m_z + 0.835, b.m_y + 0.25},
				{b.m_x, b.m_z + 1.0, b.m_y}
			},
			{
				{a.m_x, a.m_z, a.m_y},
				{a.m_x, a.m_z + 0.165, a.m_y + 0.25},
				{a.m_x, a.m_z + 0.33, a.m_y + 0.5},
				{a.m_x, a.m_z + 0.495, a.m_y + 0.75},
				{a.m_x, a.m_z + 0.67, a.m_y + 0.5},
				{a.m_x, a.m_z + 0.835, a.m_y + 0.25},
				{a.m_x, a.m_z + 1.0, a.m_y}
			},
			{
				{c.m_x, c.m_z, c.m_y},
				{c.m_x, c.m_z + 0.165, c.m_y + 0.25},
				{a.m_x, a.m_z, a.m_y},
				{a.m_x, a.m_z + 0.165, a.m_y + 0.25},
				{b.m_x, b.m_z, b.m_y},
				{b.m_x, b.m_z + 0.165, b.m_y + 0.25},
				{c.m_x, c.m_z, c.m_y}
			},
			{
				{c.m_x, c.m_z + 1.25, c.m_y - 0.5},
				{c.m_x, c.m_z + 1.33, c.m_y - 0.25},
				{c.m_x, c.m_z + 1.44, c.m_y - 0.125},
				{c.m_x, c.m_z + 1.5, c.m_y},
				{c.m_x, c.m_z + 1.625, c.m_y + 0.25},
				{c.m_x, c.m_z + 1.67, c.m_y + 0.375},
				{c.m_x, c.m_z + 1.75, c.m_y - 0.5}
			

			},
			{
				{b.m_x, b.m_z + 1.25, b.m_y - 0.5},
				{b.m_x, b.m_z + 1.33, b.m_y - 0.25},
				{b.m_x, b.m_z + 1.44, b.m_y - 0.125},
				{b.m_x, b.m_z + 1.5, b.m_y},
				{b.m_x, b.m_z + 1.625, b.m_y + 0.25},
				{b.m_x, b.m_z + 1.67, b.m_y + 0.375},
				{b.m_x, b.m_z + 1.75, b.m_y - 0.5}
			},
			{
				{a.m_x, a.m_z + 1.25, a.m_y - 0.5},
				{a.m_x, a.m_z + 1.33, a.m_y - 0.25},
				{a.m_x, a.m_z + 1.44, a.m_y - 0.125},
				{a.m_x, a.m_z + 1.5, a.m_y},
				{a.m_x, a.m_z + 1.625, a.m_y + 0.25},
				{a.m_x, a.m_z + 1.67, a.m_y + 0.375},
				{a.m_x, a.m_z + 1.75, a.m_y - 0.5}
			},
			{
				{c.m_x, c.m_z + 1.25, c.m_y - 0.5},
				{c.m_x, c.m_z + 1.33, c.m_y - 0.25},
				{c.m_x, c.m_z + 1.44, c.m_y - 0.125},
				{c.m_x, c.m_z + 1.5, c.m_y},
				{c.m_x, c.m_z + 1.625, c.m_y + 0.25},
				{c.m_x, c.m_z + 1.67, c.m_y + 0.375},
				{c.m_x, c.m_z + 1.75, c.m_y - 0.5}
			},
		};*/
		// modified set based on trial and error - added more controlPoints results seem similar
		GLfloat controlPoints[8][8][3] =
		{
			// draws the basic contour of the face 
			{
				{c.m_x, c.m_z, c.m_y},
				{c.m_x, c.m_z + 0.165, c.m_y + 0.25},
				{c.m_x, c.m_z + 0.33, c.m_y + 0.5},
				{c.m_x, c.m_z + 0.495, c.m_y + 0.75},
				{c.m_x, c.m_z + 0.67, c.m_y + 0.5},
				{c.m_x, c.m_z + 0.835, c.m_y + 0.25},
				{c.m_x, c.m_z + 1.0, c.m_y},
				{c.m_x, c.m_z + 1.25, c.m_y - 0.5}
			},
			{
				{b.m_x, b.m_z, b.m_y},
				{b.m_x, b.m_z + 0.165, b.m_y + 0.25},
				{b.m_x, b.m_z + 0.33, b.m_y + 0.5},
				{b.m_x, b.m_z + 0.495, b.m_y + 0.75},
				{b.m_x, b.m_z + 0.67, b.m_y + 0.5},
				{b.m_x, b.m_z + 0.835, b.m_y + 0.25},
				{b.m_x, b.m_z + 1.0, b.m_y},
				{b.m_x, b.m_z + 1.25, b.m_y - 0.5}
			},
			// creates the basic shape face which includes the eyes, the nose, mouth and hair 
			{
				{a.m_x, a.m_z, a.m_y},
				{a.m_x, a.m_z + 0.165, a.m_y + 0.25},
				{a.m_x, a.m_z + 0.33, a.m_y + 0.5},
				{a.m_x, a.m_z + 0.495, a.m_y + 0.75},
				{a.m_x, a.m_z + 0.67, a.m_y + 0.5},
				{a.m_x, a.m_z + 0.835, a.m_y + 0.25},
				{a.m_x, a.m_z + 1.0, a.m_y},
				{a.m_x, a.m_z + 1.25, a.m_y - 0.5}
			},

			{
				{c.m_x, c.m_z, c.m_y},
				{c.m_x, c.m_z + 0.165, c.m_y + 0.25},
				{a.m_x, a.m_z, a.m_y},
				{a.m_x, a.m_z + 0.165, a.m_y + 0.25},
				{b.m_x, b.m_z, b.m_y},
				{b.m_x, b.m_z + 0.165, b.m_y + 0.25},
				{c.m_x, c.m_z, c.m_y},
				{c.m_x, c.m_z + 0.25, c.m_y - 0.5}
			},

			// from here on out its just further refining the face model to get an exact face shape
			{
				{c.m_x, c.m_z + 1.25, c.m_y - 0.5},
				{c.m_x, c.m_z + 1.33, c.m_y - 0.25},
				{c.m_x, c.m_z + 1.44, c.m_y - 0.125},
				{c.m_x, c.m_z + 1.5, c.m_y},
				{c.m_x, c.m_z + 1.625, c.m_y + 0.25},
				{c.m_x, c.m_z + 1.67, c.m_y + 0.375},
				{c.m_x, c.m_z + 1.75, c.m_y - 0.5},
				{c.m_x, c.m_z + 1.875, c.m_y - 0.75}


			},
			{
				{b.m_x, b.m_z + 1.25, b.m_y - 0.5},
				{b.m_x, b.m_z + 1.33, b.m_y - 0.25},
				{b.m_x, b.m_z + 1.44, b.m_y - 0.125},
				{b.m_x, b.m_z + 1.5, b.m_y},
				{b.m_x, b.m_z + 1.625, b.m_y + 0.25},
				{b.m_x, b.m_z + 1.67, b.m_y + 0.375},
				{b.m_x, b.m_z + 1.75, b.m_y - 0.5},
				{b.m_x, b.m_z + 1.875, b.m_y - 0.75}
			},
			{
				{a.m_x, a.m_z + 1.25, a.m_y - 0.5},
				{a.m_x, a.m_z + 1.33, a.m_y - 0.25},
				{a.m_x, a.m_z + 1.44, a.m_y - 0.125},
				{a.m_x, a.m_z + 1.5, a.m_y},
				{a.m_x, a.m_z + 1.625, a.m_y + 0.25},
				{a.m_x, a.m_z + 1.67, a.m_y + 0.375},
				{a.m_x, a.m_z + 1.75, a.m_y - 0.5},
				{a.m_x, a.m_z + 1.875, a.m_y - 0.75}
			},
			{
				{c.m_x, c.m_z + 1.25, c.m_y - 0.5},
				{c.m_x, c.m_z + 1.33, c.m_y - 0.25},
				{c.m_x, c.m_z + 1.44, c.m_y - 0.125},
				{c.m_x, c.m_z + 1.5, c.m_y},
				{c.m_x, c.m_z + 1.625, c.m_y + 0.25},
				{c.m_x, c.m_z + 1.67, c.m_y + 0.375},
				{c.m_x, c.m_z + 1.75, c.m_y - 0.5},
				{c.m_x, c.m_z + 1.875, c.m_y - 0.75}
			},
		};



		
		// set the evaluation mode to generate vertices using GL_MAP2_VERTEX_3
		glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 4, 0.0, 1.0, 12, 4, &controlPoints[0][0][0]);

		// evaluate the surface to generate vertices for the wireframe
		glMapGrid2f(50, 0.0, 1.0, 50, 0.0, 1.0);
		glEvalMesh2(GL_LINE, 0, 8, 0, 30);
	}

	// disable the evaluation capability
	glDisable(GL_MAP2_VERTEX_3);
}


void drawWireFrame()
{
	{
		CVector up(0.0f, 0.0f, 1.0f);

		glBegin(GL_LINE_LOOP);


		//iterate through the total number of faces to display them

		for (int i = 0; i < parser[0].getFaceCount(); i++)
		{
			//save off the three vertices so we can do some math on them
			CVector a = currentStatePoints[currentStateLines[i].m_a];
			CVector b = currentStatePoints[currentStateLines[i].m_b];
			CVector c = currentStatePoints[currentStateLines[i].m_c];
			glVertex3f(c.m_x, c.m_z, c.m_y);
			glVertex3f(b.m_x, b.m_z, b.m_y);
			glVertex3f(a.m_x, a.m_z, a.m_y);


		}



		glEnd();
	}

}

void drawFlatShaded()
{ 
	CVector up(0.0f, 0.0f, 1.0f);
	
	glBegin(GL_TRIANGLES);

	//iterate through the total number of faces to display them

	for (int i = 0; i < parser[0].getFaceCount(); i++)
	{
		//save off the three vertices so we can do some math on them
		CVector a = currentStatePoints[ currentStateLines[i].m_a ];
		CVector b = currentStatePoints[ currentStateLines[i].m_b ];
		CVector c = currentStatePoints[ currentStateLines[i].m_c ];
		
		glVertex3f( c.m_x, c.m_z, c.m_y );
		glVertex3f( b.m_x, b.m_z, b.m_y );
		glVertex3f( a.m_x, a.m_z, a.m_y );
		
	}

	glEnd();
}
void drawTextured()
{
	{
		CVector up(1.0f, 1.0f, 1.0f);

		// Instruction 9: bind the texture to the id so it can be placed on the model
		

		glBindTexture(GL_TEXTURE_2D, tex);

		//Instruction 10: iterate through the total number of faces to display them

		glBegin(GL_TRIANGLES);
		for (int i = 0; i < parser[0].getFaceCount(); i++)
		{
			//save off the three vertices so we can do some math on them
			CVector a = currentStatePoints[currentStateLines[i].m_a];
			CVector b = currentStatePoints[currentStateLines[i].m_b];
			CVector c = currentStatePoints[currentStateLines[i].m_c];

			// the U and V coordinates are the same
			float tau, tav;
			tau = texFaceVerts[texFace[i].m_a].m_x;
			tav = texFaceVerts[texFace[i].m_a].m_y;

			float tbu, tbv;
			tbu = texFaceVerts[texFace[i].m_b].m_x;
			tbv = texFaceVerts[texFace[i].m_b].m_y;

			float tcu, tcv;
			tcu = texFaceVerts[texFace[i].m_c].m_x;
			tcv = texFaceVerts[texFace[i].m_c].m_y;
			/*
			tbu = tuv = texFaceVerts [ texFace[i].m_b ].m_y;

			float tcu, tcv;
			tcu = tcv = texFaceVerts[ texFace[i].m_c ].m_z;*/

			//display the faces on the screen
			glTexCoord2d(tcu, tcv);
			glVertex3f(c.m_x, c.m_z, c.m_y);
			glTexCoord2d(tbu, tbv);
			glVertex3f(b.m_x, b.m_z, b.m_y);
			glTexCoord2d(tau, tav);
			glVertex3f(a.m_x, a.m_z, a.m_y);
		}
		glEnd();
		

	}

}

		



void drawTexturedAnimation()
{ 

	CVector up(0.0f, 0.0f, 1.0f);

	//bind the texture to the id so it can be placed on the model
	glBindTexture(GL_TEXTURE_2D, tex);


	glBegin(GL_TRIANGLES);
	
		//Instruction 12: iterate through the total number of faces to display them

	for (int i = 0; i < parser[0].getFaceCount(); i++)
	{
		CVector a = smileTargetStatePoints[smileTargetStateLines[i].m_a];
		CVector b = smileTargetStatePoints[smileTargetStateLines[i].m_b];
		CVector c = smileTargetStatePoints[smileTargetStateLines[i].m_c];

		glVertex3f(c.m_x, c.m_z, c.m_y);
		glVertex3f(b.m_x, b.m_z, b.m_y);
		glVertex3f(a.m_x, a.m_z, a.m_y);
	}

	glEnd();
		
		
	
}

//callback function to draw the model in either wireframe or full model
void drawModel(void(*drawFunction)())
{
	drawFunction();

}

void Display(void)
{
	// Clear Depth Buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	//Goodies -> Rotation
	//glRotated(GAngle,0,1,0);

	//scale the points so they can be seen
	//glScalef(0.005f, 0.005f, 0.005f);
	glScalef(0.007f, 0.007f, 0.007f);
	//default color of all rendered objects is white
	glColor3f(1.0, 1.0, 1.0);



	switch (renderingMode)
	{

	case 1:
	{
		drawModel(drawPoints);
		break;
	}
	case 2:
	{
		drawModel(drawWireFrame);
		break;
	}

	case 3:
	{
		drawModel(drawTextured);
		break;
	}

	case 4:
	{
		drawModel(drawBezierPatches);
		break;
		//default
		//changeTargetState(defaultStatePoints,defaultStateLines);
		//changed 4 to 3

	}

	case 5:
	{
		//smile
		//changeTargetState(smileTargetStatePoints, smileTargetStateLines);
		//drawModel(drawTexturedAnimation);
		//break;
	}
	case 6:
	{
		//surprise
		//changeTargetState(surpriseTargetStatePoints, surpriseTargetStatePoints);
		//drawModel(drawTexturedAnimation);
		//break;
	}
	case 7:
	{
		//anger
		//changeTargetState(angerTargetStatePoints, angerTargetStatePoints);

	}
	case 8:
	{
	}
	case 9:
	{
		drawModel(drawTexturedAnimation);
		break;
	}
	case 0:
	{
		//this has to appear so that updateScene can be called
		drawModel(drawTexturedAnimation);
		//ensure that the animation has run and has some pause time at the end
		//on startup animation counter will be zero so it needs to choose a random target
		//or this could've been implemented with an ifStatement
		if (animationFrameCounter > animationLifetime || !animationFrameCounter)
		{
			//choose random target here
			chooseAutoRandomTarget();
		}

		break;
	}

	}

	//reset the angle to 0 when 360 hits
	if (GAngle > 360)
	{
		GAngle -= 360;
	}
	else
	{
		GAngle = GAngle + 1;
	}


	glFlush();

	glutSwapBuffers();
}

void Timer(int extra)
{
	glutPostRedisplay();
	glutTimerFunc(15, Timer, 0);
}

int main(void)
{
	//initialize GLUT
	// Init to double buffering
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 480);
	//enableLights();
	glutCreateWindow("FaceProject");
	glutKeyboardFunc(keyPress);



	//make sure model loading occurs before dispalyFunc or suffer longer load times
	parser[0].loadFile("faceverts.txt");
	defaultStatePoints = parser[0].getFacePoints();
	defaultStateLines = parser[0].getFaceLines();
	numPoints = parser[0].getFaceCount();
	//fill our temp buffer
	tempBuffer = new CVector[numPoints];

	//load the model into memory
	parser[1].loadFile("faceverts.txt");
	//pass the addresses from the ASEPaser to our global variables
	//store our default face vertex positions, and the current state positions
	currentStatePoints = parser[1].getFacePoints();
	currentStateLines = parser[1].getFaceLines();

	//Load the animation states
	//first load the vertex information for the face that smiles
	parser[2].loadFile("smile1.txt");
	smileTargetStatePoints = parser[2].getFacePoints();
	smileTargetStateLines = parser[2].getFaceLines();

	//load the surprised state
	parser[3].loadFile("surprise1.txt");
	surpriseTargetStatePoints = parser[3].getFacePoints();
	surpriseTargetStateLines = parser[3].getFaceLines();

	//load the anger face state
	parser[4].loadFile("angry1.txt");
	angerTargetStatePoints = parser[4].getFacePoints();
	angerTargetStateLines = parser[4].getFaceLines();

	//load the sad face state
	parser[5].loadFile("sad1.txt");
	sadTargetStatePoints = parser[5].getFacePoints();
	sadTargetStateLines = parser[5].getFaceLines();

	//load disgust state
	parser[6].loadFile("disgust1.txt");
	disgustTargetStatePoints = parser[6].getFacePoints();
	disgustTargetStateLines = parser[6].getFaceLines();

	//load fear state
	parser[7].loadFile("fear1.txt");
	fearTargetStatePoints = parser[7].getFacePoints();
	fearTargetStateLines = parser[7].getFaceLines();


	//load the texture parser into memory if it fails say something
	texParser.loadFile("texturedatafile.txt");

	//initialize the texture routine
	initTexture();




	glutDisplayFunc(Display);
	glutTimerFunc(0, Timer, 0);

	glShadeModel(GL_SMOOTH);		// Default

	// Uncomment this to hide back-facing polygons.
	//glEnable(GL_CULL_FACE);

	glEnable(GL_DEPTH_TEST);

	glutMainLoop();

	//clean up the memory by freeing the mem for the texture
	textureImage.Cleanup();
	return 0;
}
