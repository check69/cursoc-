#include "StdAfx.h"
#include "Entity.h"
#include "World.h"

//-------------------------------------------------------------------
TEntity::TEntity()
{
	this->m_ok     = false;
	this->m_pWorld = NULL;
}

//-------------------------------------------------------------------
bool TEntity::init (int iWidth, TWorld *pWorld, int iCoordX, char cSprite, TType eType)
{
	if (!this->m_ok)
	{
		if (!pWorld)
			return false;

		this->m_pWorld   = pWorld;
		short int iColor = 0;

		switch (eType)
		{
			case Bomb:   iColor = FOREGROUND_GREEN; break;
			case Enemy:  iColor = FOREGROUND_RED;   break;
		}
		this->m_pSprite = this->m_pWorld->getG_pGfxEngine()->insertSprite(iCoordX, cSprite, iColor);

		if (!this->m_pSprite)
			return false;

		this->m_iWidth = iWidth;
		this->m_eType  = eType;
		this->m_iSpeed = 0;
		this->m_ok     = true;

		return true;
	}

	return false;
}

//-------------------------------------------------------------------
TEntity::~TEntity ()
{
}

//-------------------------------------------------------------------
bool TEntity::outOfMap ()
{
	if (this->getCoordX() <= 0 || this->getCoordX() >= this->m_iWidth-1)
		return true;

	return false;
}

//-------------------------------------------------------------------
bool TEntity::move (int iMove)
{
	return this->m_pWorld->getG_pGfxEngine()->moveSprite(this->m_pSprite->getId(), this->m_pSprite->getCoordinateX()+iMove);
}