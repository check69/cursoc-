#include "StdAfx.h"
#include "World.h"
#include "EntBomb.h"
#include "EntEnemy.h"

//-------------------------------------------------------------------
TWorld::TWorld ():m_lEntity()
{
	this->m_ok = false;
}

//-------------------------------------------------------------------
bool TWorld::init (int iWidth, short int siLifes, int iMaxBombs, TGfxEngine *pGfxEngine)
{
	if (!this->m_ok && pGfxEngine && siLifes > 0 && iMaxBombs > 0)
	{
		this->m_ok           = true;
		this->m_bWantsToExit = false;
		this->m_iWidth       = iWidth;
		this->m_iPuntuacion  = 0;
		this->m_iMaxBombs    = iMaxBombs;
		this->m_iNumBombs    = 0;
		this->m_iNumEnemies  = 0;
		this->m_iLevel       = 1;
		this->m_siLifes      = siLifes;

		this->m_pGfxEngine   = pGfxEngine;

		return true;
	}

	return false;
}

//-------------------------------------------------------------------
void TWorld::end ()
{
	if (this->m_ok)
	{
		for (auto it = this->m_lEntity.begin(); it != this->m_lEntity.end(); ++it)
			delete *it;

		this->m_lEntity.clear();
		this->m_lDelEntity.clear();

		this->m_ok = false;
	}
}

//-------------------------------------------------------------------
TWorld::~TWorld ()
{
	this->end();
}

//-------------------------------------------------------------------
TGfxEngine *TWorld::getG_pGfxEngine () 
{
	if (this->m_ok) 
		return this->m_pGfxEngine;

	return NULL;
}

//-------------------------------------------------------------------
void TWorld::run ()
{
	if (this->m_ok)
	{
		if (this->m_iNumEnemies < ((this->m_iLevel/5)+1))
			this->createEnemy();

		for (auto it = this->m_lEntity.begin(); it != this->m_lEntity.end(); ++it)
			(*it)->run();

		this->checkCollision();
		printf (" %i",this->m_iNumBombs);

		TEntity *pEntityAux;
		std::list<TEntity *>::iterator it = this->m_lDelEntity.begin();
		while (it != this->m_lDelEntity.end())
		{				
			pEntityAux = *it;
			++it;

			this->m_lEntity.remove    (pEntityAux);
			this->m_lDelEntity.remove (pEntityAux);

			pEntityAux->end();
			delete pEntityAux;
		}
	}
}

//-------------------------------------------------------------------
bool TWorld::insertEntity (TEntity *pEntity)
{
	if (!this->m_ok)
		return false;

	if (!pEntity)
		return false;

	this->m_lEntity.push_back(pEntity);

	return true;
}

//-------------------------------------------------------------------
bool TWorld::removeEntity (TEntity *pEntity)
{
	if (!this->m_ok || !pEntity)
		return false;

	this->m_lDelEntity.push_back(pEntity);
	
	return true;
}

//-------------------------------------------------------------------
void TWorld::createEnemy ()
{
	if (this->m_ok)
	{
		int iSpeed  = ((rand()%2 != 0) ? 1 : -1);
		int iCoordX = (this->m_iWidth)/2+(rand()%this->m_iLevel)*iSpeed;

		TEntity *pEntity = new TEntEnemy;  
		if (static_cast<TEntEnemy *>(pEntity)->init(this->m_iWidth, this, iCoordX, '|'))
		{
			if (pEntity)
			{
				this->insertEntity(pEntity);
				pEntity->setSpeed(iSpeed);
				++this->m_iNumEnemies;
			}
		}
	}
}

//-------------------------------------------------------------------
void TWorld::checkCollision ()
{
	if (this->m_ok)
	{
		std::list<TEntity *>::iterator iti = this->m_lEntity.begin();
		std::list<TEntity *>::iterator itj;

		while (iti != this->m_lEntity.end())
		{
			itj = iti;
			++itj;
			
			while (itj != this->m_lEntity.end() && !(*iti)->outOfMap())
			{
				if ((*itj)->outOfMap())
					itj = this->m_lEntity.end();
				else
				{
					if ((*iti)->collision(*itj))
					{
						if ((*iti)->getType() != Bomb)
							this->m_lDelEntity.push_back(*iti);
						else
							this->m_lDelEntity.push_back(*itj);
						itj = this->m_lEntity.end();
						
						this->m_iPuntuacion += 10;
						if (this->m_iPuntuacion%100 == 0)
						{
							++this->m_iLevel;
							if (this->m_iLevel%5 == 0)
								++this->m_siLifes;
						}

						--this->m_iNumEnemies;
					}
					else
						++itj;
				}
			}
			++iti;
		}
	}
}

//-------------------------------------------------------------------
bool TWorld::createBomb (int iCoordX)
{
	if (!this->m_ok || this->m_iNumBombs >= this->m_iMaxBombs)
		return false;

	for (auto it = this->m_lEntity.begin(); it != this->m_lEntity.end(); ++it)
		if ((*it)->getType() == Bomb && (*it)->getCoordX() == iCoordX)
			return false;

	TEntity *pEntity = new TEntBomb;
	if (!static_cast<TEntBomb *>(pEntity)->init(this->m_iWidth, this, iCoordX, 'B'))
		return false;

	this->insertEntity(pEntity);

	return true;
}

//-------------------------------------------------------------------
void TWorld::toPlantABomb (int iSector)
{
	if (this->m_ok && iSector < 10 && iSector >= 0)
	{
		if (this->createBomb((iSector *(this->m_iWidth/10))+3))
			++this->m_iNumBombs;
	}
}