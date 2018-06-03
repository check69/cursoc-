#ifndef _TENTITY_H
#define _TENTITY_H

#include "TSprite.h"
class TWorld;

enum TType
{
	Bomb   = 0,
	Enemy  = 1,
};

class TEntity
{
	TType m_eType;

protected:
	bool     m_ok;
	int      m_iWidth;
	int      m_iSpeed;
	TWorld  *m_pWorld;
	TSprite *m_pSprite;

public:
	//-----------------------Constructor and Destructor------------------------
	TEntity           ();
	bool init         (int iWidth, TWorld *pWorld, int iCoordX, char cSprite, TType eType);
	virtual void end  () = 0;
	~TEntity          ();

	virtual bool isOk () {return this->m_ok;}

	//------------------------Get and Set members variables------------------------
	int   getId     ()           {if (this->m_ok) return this->m_pSprite->getId();}
	int   getCoordX ()           {if (this->m_ok) return this->m_pSprite->getCoordinateX(); else return -1;}
	void  setSpeed  (int iSpeed) {if (this->m_ok) this->m_iSpeed = iSpeed;}
	TType getType   ()           {return this->m_eType;}
	int   getSpeed  ()           {return this->m_iSpeed;}

	//------------------------------Other Functions-------------------------------
	bool outOfMap                ();
	bool move                    (int iMove);
	virtual void bulletDestroy   () {}
	virtual bool collision       (TEntity *pEntity) = 0;
	virtual bool collisionEntity (TType eType, int coordX) = 0;
	virtual void run             () = 0;
};

#endif