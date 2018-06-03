#ifndef _WORLD_H
#define _WORLD_H

#include "Entity.h"
#include "GfxEngine.h"

class TWorld
{
	bool                 m_ok;
	bool                 m_bWantsToExit;
	int                  m_iWidth;

	int                  m_iLevel;
	int                  m_iNumEnemies;
	int                  m_iPuntuacion;
	int                  m_iMaxBombs;
	int                  m_iNumBombs;
	short int            m_siLifes;

	TGfxEngine          *m_pGfxEngine;
	std::list<TEntity *> m_lEntity;
	std::list<TEntity *>   m_lDelEntity; //list of entity that i have to del.

public:
	//-------------------------Constructor and Destructor--------------------------
	TWorld    ();
	bool init (int iWidth, short int siLifes, int iMaxBombs, TGfxEngine *pGfxEngine);
	void end  ();
	~TWorld   ();

	bool isOk () {return this->m_ok;}
	
	//------------------------Get and Set members variables------------------------
	TGfxEngine *getG_pGfxEngine ();
	bool getWantsToExit         () {return this->m_bWantsToExit;}
	int  getPuntuacion          () {return this->m_iPuntuacion;}
	void setWantsToExit         () {if (this->m_ok) this->m_bWantsToExit = true;}
	void setNumEnemies          () {if (this->m_ok) --this->m_iNumEnemies;}
	void setNumBombs            () {if (this->m_ok) --this->m_iNumBombs;}
	void lifeDown               () {if (this->m_ok) --this->m_siLifes; if (!this->m_siLifes) this->m_bWantsToExit = true;}

	//------------------------------Other Functions-------------------------------
	bool insertEntity     (TEntity *pEntity);
	bool removeEntity     (TEntity *pEntity);
	bool createBomb       (int iCoordX);
	bool createBombs      ();
	void createEnemy      ();
	void checkCollision   ();
	void toPlantABomb     (int iSector);
	void run              ();
};

#endif