#ifndef _TENEMY_H
#define _TENEMY_H

#include "Entity.h"

class TEntEnemy : public TEntity
{

public:
	//-----------------------Constructor and Destructor------------------------
	TEntEnemy        ();
	bool init        (int iWidth, TWorld *pWorld, int iCoordX, char cSprite);
	virtual void end ();
	~TEntEnemy       ();

	//------------------------------Other Functions-------------------------------
	virtual bool collision (TEntity *pEntity);
	virtual void run       ();
	virtual bool collisionEntity (TType eType, int coordX);
};

#endif