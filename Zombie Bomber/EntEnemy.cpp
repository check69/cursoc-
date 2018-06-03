#include "StdAfx.h"
#include "EntEnemy.h"
#include "World.h"

//-------------------------------------------------------------------
TEntEnemy::TEntEnemy()
{
	this->m_ok = false;
}

//-------------------------------------------------------------------
bool TEntEnemy::init (int iWidth, TWorld *pWorld, int iCoordX, char cSprite)
{
	return TEntity::init(iWidth, pWorld, iCoordX, cSprite, Enemy);
}

//-------------------------------------------------------------------
void TEntEnemy::end ()
{
	if (this->m_ok)
	{
		this->m_pWorld->getG_pGfxEngine()->removeSprite(this->m_pSprite);

		this->m_ok     = false;
		this->m_pWorld = NULL;
	}
}

//-------------------------------------------------------------------
TEntEnemy::~TEntEnemy()
{
	this->end();
}

//-------------------------------------------------------------------
void TEntEnemy::run ()
{
	if (this->m_ok)
	{
		int iCoordX = this->m_pSprite->getCoordinateX()+this->m_iSpeed;

		if (iCoordX < 0 || iCoordX >= this->m_iWidth)
		{
			this->m_pWorld->lifeDown();
			this->m_pWorld->removeEntity(this);
			this->m_pWorld->setNumEnemies();
		}
		else if (!this->move(this->m_iSpeed))
			this->m_pWorld->removeEntity(this);
	}
}

//-------------------------------------------------------------------
bool TEntEnemy::collision (TEntity *pEntity)
{
	return pEntity->collisionEntity(this->getType(), this->getCoordX());
}

//-------------------------------------------------------------------
bool TEntEnemy::collisionEntity (TType eType, int coordX)
{
	if (eType != this->getType())
	{
		if (this->getCoordX() == coordX)
			return true;
	}
	return false;
}