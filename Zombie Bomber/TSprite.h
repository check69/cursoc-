#ifndef _TSPRITE_H
#define _TSPRITE_H

class TSprite
{
	short int m_iColor;
	int       m_id;
	int       m_iCoordX;
	char      m_cSprite;
	bool      m_ok;

	friend class TGfxEngine;

public:
	//-----------------------Constructor and Destructor------------------------
	TSprite   ();
	bool init (int id, int iCoordX, char cSprite, short int iColor);
	void end  ();
	~TSprite  ();

	bool isOk () {return this->m_ok;}

	//------------------------Get and Set members variables------------------------
	int       getId          ()             {return this->m_id;}
	int       getCoordinateX ()             {return this->m_iCoordX;}
	char      getCSprite     ()             {return this->m_cSprite;}
	void      setCSprite     (char cSprite) {if (this->m_ok) this->m_cSprite = cSprite;}
	short int getColor       ()             {return this->m_iColor;}
};

#endif