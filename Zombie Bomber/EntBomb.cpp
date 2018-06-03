#include "StdAfx.h"
#include "EntBomb.h"
#include "World.h"


//-------------------------------------------------------------------
TEntBomb::TEntBomb()
{
	this->m_ok      = false;
}

//-------------------------------------------------------------------
bool TEntBomb::init (int iWidth, TWorld *pWorld, int iCoordX, char cSprite)
{
	this->m_iTime      = 0;
	this->m_eState     = Charging;
	this->m_pSptBlast1 = NULL;
	this->m_pSptBlast2 = NULL;

	return TEntity::init(iWidth, pWorld, iCoordX, cSprite, Bomb);
}

//-------------------------------------------------------------------
void TEntBomb::end ()
{
	if (this->m_ok)
	{
		this->m_pWorld->getG_pGfxEngine()->removeSprite(this->m_pSprite);

		this->m_ok     = false;
		this->m_pWorld = NULL;
	}
}

//-------------------------------------------------------------------
TEntBomb::~TEntBomb()
{
	this->end();
}

//-------------------------------------------------------------------
void TEntBomb::run ()
{
	if (this->m_ok)
	{
		if (!this->m_iTime)
			this->m_iTime = clock();

		else if ((clock() - this->m_iTime) >= 500)
		{
			this->m_iTime = clock();

			switch (this->m_eState)
			{
				case Charging:
				{
					this->m_eState = Exploit;
					this->m_pSprite->setCSprite('*');

					break;
				}

				case Exploit:
				{
					this->m_eState = Blast;

					this->m_pSptBlast1 = this->m_pWorld->getG_pGfxEngine()->insertSprite(this->getCoordX()-1,'*',this->m_pSprite->getColor());
					this->m_pSptBlast2 = this->m_pWorld->getG_pGfxEngine()->insertSprite(this->getCoordX()+1,'*',this->m_pSprite->getColor());
					this->m_pSprite->setCSprite(' ');

					break;
				}

				case Blast: 
				{
					this->m_eState  = Charging;

					this->m_pWorld->getG_pGfxEngine()->removeSprite(this->m_pSptBlast1);
					this->m_pWorld->getG_pGfxEngine()->removeSprite(this->m_pSptBlast2);
					this->m_pSptBlast1 = this->m_pSptBlast2 = NULL;

					this->m_pWorld->removeEntity(this);
					this->m_pWorld->setNumBombs();

					break;
				}
			}
		}
	}
}

//-------------------------------------------------------------------
bool TEntBomb::collision (TEntity *pEntity)
{
	if (!this->explosion())
		return false;

	if (this->m_eState == Blast)
	{
		if (pEntity->collisionEntity(this->getType(), this->getCoordX()-1))
			return true;
		if (pEntity->collisionEntity(this->getType(), this->getCoordX()+1))
			return true;

		return false;
	}

	return pEntity->collisionEntity(this->getType(), this->getCoordX());
}

//-------------------------------------------------------------------
bool TEntBomb::collisionEntity (TType eType, int coordX)
{
	if (eType != this->getType() && this->explosion())
	{
		if (this->m_eState == Blast)
		{
			if (this->getCoordX()+1 == coordX || this->getCoordX()-1 == coordX)
				return true;
		}
		else if (this->getCoordX() == coordX)
			return true;
	}

	return false;
}