#ifndef _GFXENGINE_H
#define _GFXENGINE_H

#include "TSprite.h"

class TGfxEngine
{
	HANDLE h;
	WORD wOldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

	bool                 m_ok;
	int                  m_iWidth;
	std::list<TSprite *> m_lSprite;

	void ClearScreen ();

public:
	//-----------------------Constructor and Destructor------------------------
	TGfxEngine  ();
	bool init   (int iWidth);
	void end    ();
	~TGfxEngine ();

	bool isOk   () {return this->m_ok;}
	
	//------------------------Get and Set members variables------------------------
	const TSprite *getSprite (int id);

	//------------------------------Other Functions-------------------------------
	TSprite *insertSprite (int iCoordX, char c, short int iColor);
	bool removeSprite     (TSprite *pSprite);
	bool moveSprite       (int id, int iMove);
	void draw             ();
	void setTextColor     (short int iColor);
};

#endif