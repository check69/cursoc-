#ifndef _UI_H
#define _UI_H

#include "World.h"

class TUI
{
	bool       m_ok;
	TWorld    *m_pWorld;

public:
	//-----------------------Constructor and Destructor------------------------
	TUI       ();
	bool init (TWorld *pWorld);
	void end  ();
	~TUI      ();

	bool isOk () {return this->m_ok;}

	//------------------------------Other Functions-------------------------------
	void processInput ();
};

#endif