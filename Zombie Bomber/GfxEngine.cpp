#include "StdAfx.h"
#include "GfxEngine.h"

//-------------------------------------------------------------------
TGfxEngine::TGfxEngine ()
{
	this->m_ok = false;
}

//-------------------------------------------------------------------
bool TGfxEngine::init (int iWidth)
{
	if (!this->m_ok)
	{
		this->m_ok     = true;
		this->m_iWidth = iWidth;
		this->h        = GetStdHandle(STD_OUTPUT_HANDLE);

		return true;
	}

	return false;
}

//-------------------------------------------------------------------
void TGfxEngine::end ()
{
	if (this->m_ok)
	{
		for (std::list<TSprite *>::iterator it = this->m_lSprite.begin(); it != this->m_lSprite.end(); ++it)
			delete *it;

		this->m_lSprite.clear();
		this->m_ok = false;
	}
}

//-------------------------------------------------------------------
TGfxEngine::~TGfxEngine ()
{
	this->end();
}

/*******************************************************************
return id of the new Sprite
return -1 if the function init of Sprite class is failed.
*******************************************************************/
TSprite *TGfxEngine::insertSprite (int iCoordX, char cSprite, short int iColor)
{
	TSprite *pSpriteAux = new TSprite();

	int id;
	if (!this->m_lSprite.size())
		id = 1;
	else
		id = (*this->m_lSprite.begin())->getId() +1;

	if (!pSpriteAux->init(id, iCoordX, cSprite, iColor))
		return NULL;

	this->m_lSprite.push_front(pSpriteAux);
	
	return pSpriteAux;
}

/*******************************************************************
return false if the function don't found the Sprite
return true  if everything is allright
*******************************************************************/
bool TGfxEngine::removeSprite (TSprite *pSprite)
{
	if (!this->m_ok && !pSprite)
		return false;

	this->m_lSprite.remove(pSprite);
	delete pSprite;

	return true;
}

/*******************************************************************
return false if the function don't found the Sprite
return true  if everything is allright
*******************************************************************/
bool TGfxEngine::moveSprite (int id, int iMove)
{
	for (std::list<TSprite *>::iterator it = this->m_lSprite.begin(); it != this->m_lSprite.end(); ++it)
	{
		if ((*it)->getId() == id)
		{
			(*it)->m_iCoordX = iMove;
			return true;
		}
	}

	return false;
}

//-------------------------------------------------------------------
void TGfxEngine::draw ()
{
	this->ClearScreen();

	printf("\t\tGame legend\n");
	printf("\t\t1 = Bomb in sector 1\n");
	printf("\t\t2 = Bomb in sector 2\n");
	printf("\t\t3 = Bomb in sector 3\n");
	printf("\t\t4 = Bomb in sector 4\n");
	printf("\t\t5 = Bomb in sector 5\n");
	printf("\t\t6 = Bomb in sector 6\n");
	printf("\t\t7 = Bomb in sector 7\n");
	printf("\t\t8 = Bomb in sector 8\n");
	printf("\t\t9 = Bomb in sector 9\n");
	printf("\t\t0 = Bomb in sector 10\n\n\n");
	
	//printf("\r");

	//this function is for maps with one dimension but for this case, i prefer do that
	printf("     ");
	/*for (unsigned int i = 0; i < ((80-this->m_iWidth)/2);++i)
		printf(" ");*/

	char *paSprites = new char[this->m_iWidth];
	short int *paColorSprites = new short int[this->m_iWidth];
	memset(paSprites,0,this->m_iWidth);

	for (std::list<TSprite *>::iterator it = this->m_lSprite.begin(); it != this->m_lSprite.end(); ++it)
	{
		int iCoordX = (*it)->getCoordinateX();
		if (iCoordX < this->m_iWidth && iCoordX >= 0)
		{
			paSprites[iCoordX] = (*it)->getCSprite();
			paColorSprites[iCoordX]  = (*it)->m_iColor;
		}
	}

	for (int i = 0; i < this->m_iWidth; ++i)
	{
		if (!paSprites[i])
			printf("-");
		else
		{
			setTextColor(paColorSprites[i]);
			//Print the Sprite
			printf("%c",paSprites[i]);

			//Restore the original colors
			SetConsoleTextAttribute ( h, wOldColorAttrs);
		}
	}
	delete[] paSprites;
	delete[] paColorSprites;
}

//-------------------------------------------------------------------
const TSprite *TGfxEngine::getSprite (int id)
{
	for (std::list<TSprite *>::iterator it = this->m_lSprite.begin(); it != this->m_lSprite.end(); ++it)
		if ((*it)->getId() == id)
			return (*it);

	return NULL;
}

//-------------------------------------------------------------------
void TGfxEngine::setTextColor (short int iColor)
{
	if (this->m_ok)
	{
		//First save the current color information
		GetConsoleScreenBufferInfo(h, &csbiInfo);
		wOldColorAttrs = csbiInfo.wAttributes;
	
		//Set the new color information
		SetConsoleTextAttribute ( h, iColor | FOREGROUND_INTENSITY );
	}
}

//-------------------------------------------------------------------
void TGfxEngine::ClearScreen ()
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) 
		return;

	// Get the number of cells in the current buffer
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) 
		return;
	
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	// Fill the entire buffer with spaces
	if (!FillConsoleOutputCharacter(hStdOut, (TCHAR)'-', cellCount, homeCoords, &count))
		return;

	// Fill the entire buffer with the current colors and attributes
	if (!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count))
		return;

	// Move the cursor home
	SetConsoleCursorPosition(hStdOut, homeCoords);
}