#ifndef _ENTBOMB_H
#define _ENTBOMB_H

#include "Entity.h"

class TEntBomb : public TEntity
{
	enum TState 
	{
		Charging    = 0, 
		Exploit = 1, 
		Blast = 2,
	};
	TState   m_eState;
	clock_t  m_iTime;
	TSprite *m_pSptBlast1;
	TSprite *m_pSptBlast2;

public:
	//-----------------------Constructor and Destructor------------------------
	TEntBomb         ();
	bool init        (int iWidth, TWorld *pWorld, int iCoordX, char cSprite);
	virtual void end ();
	~TEntBomb        ();

	//------------------------Get and Set members variables------------------------
	bool explosion   () {if (!this->m_ok || this->m_eState == Charging) return false; else return true;}
	TState getState  () {return this->m_eState;}

	//------------------------------Other Functions-------------------------------
	virtual bool collision (TEntity *pEntity);
	virtual void run       ();
	virtual bool collisionEntity (TType eType, int coordX);
};

#endif