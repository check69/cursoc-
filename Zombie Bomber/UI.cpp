#include "StdAfx.h"
#include "UI.h"

//-------------------------------------------------------------------
TUI::TUI ()
{
	this->m_ok        = false;
	this->m_pWorld    = NULL;
}

//-------------------------------------------------------------------
bool TUI::init (TWorld *pWorld)
{
	if (!this->m_ok)
	{
		if (!pWorld)
			return false;
		
		this->m_pWorld    = pWorld;
		this->m_ok        = true;

		return true;
	}

	return false;
}

//-------------------------------------------------------------------
void TUI::end()
{
	if (this->m_ok)
	{
		this->m_ok        = false;
		this->m_pWorld    = NULL;
	}
}

//-------------------------------------------------------------------
TUI::~TUI ()
{
	this->end();
}

//-------------------------------------------------------------------
void TUI::processInput ()
{
	if (this->m_ok)
	{
		if (_kbhit())
		{
			switch (_getch())
			{
				case 27 : this->m_pWorld->setWantsToExit(); break;
				case '1': this->m_pWorld->toPlantABomb(1);  break;
				case '2': this->m_pWorld->toPlantABomb(2);  break;
				case '3': this->m_pWorld->toPlantABomb(3);  break;
				case '4': this->m_pWorld->toPlantABomb(4);  break;
				case '5': this->m_pWorld->toPlantABomb(5);  break;
				case '6': this->m_pWorld->toPlantABomb(6);  break;
				case '7': this->m_pWorld->toPlantABomb(7);  break;
				case '8': this->m_pWorld->toPlantABomb(8);  break;
				case '9': this->m_pWorld->toPlantABomb(9);  break;
				case '0': this->m_pWorld->toPlantABomb(0);  break;

			}
		}
	}
}