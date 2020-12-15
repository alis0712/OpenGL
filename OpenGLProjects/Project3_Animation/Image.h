#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <glut.h>
#include <fstream>                                                                                                                                      // To read in a text file
#include <sstream>                                                                                                                                      // To read in a text file

using namespace std;



class CImage  
{
public:
	CImage();
	virtual ~CImage();
public:

	bool ReadBitmap(const char *fname);
	void Cleanup(void);
	char *GetImage();
	int GetImageWidth();
	int GetImageHeight();
	char * m_lpImage;

private:
    int m_ImageWidth;
	int m_ImageHeight;

};

#endif
