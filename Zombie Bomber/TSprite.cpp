#include "StdAfx.h"
#include "TSprite.h"

//-------------------------------------------------------------------
TSprite::TSprite ()
{
	this->m_ok           = false;
	this->m_id           = -1;
	this->m_iCoordX = -1;
	this->m_cSprite      = 0;
}

//-------------------------------------------------------------------
bool TSprite::init (int id, int iCoordX, char cSprite, short int iColor)
{
	if (!this->m_ok)
	{
		this->m_ok      = true;
		this->m_id      = id;
		this->m_iCoordX = iCoordX;
		this->m_cSprite = cSprite;
		this->m_iColor  = iColor;

		return true;
	}

	return false;
}

//-------------------------------------------------------------------
void TSprite::end ()
{
	if (this->m_ok)
		this->m_ok = false;
}

TSprite::~TSprite ()
{
	this->end();
}