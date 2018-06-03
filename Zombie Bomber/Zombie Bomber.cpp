// Zombie Bomber.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include "GfxEngine.h"
#include "World.h"
#include "UI.h"

TGfxEngine *g_pGfxEngine;
TWorld     *g_pWorld;
TUI        *g_pUI;

int _tmain(int argc, _TCHAR* argv[])
{
	argv;
	argc;

	srand (static_cast<unsigned int>(time(0)));

	g_pGfxEngine = new TGfxEngine;
	g_pWorld     = new TWorld;
	g_pUI        = new TUI;

	g_pGfxEngine->init(70);

	if (!g_pWorld->init(70, 3, 3, g_pGfxEngine))
		g_pWorld->setWantsToExit();
	if (!g_pUI->init(g_pWorld))
		g_pWorld->setWantsToExit();

	/*printf("\t\tGame legend\n");
	printf("\t\t1 = Bomb in sector 1\n");
	printf("\t\t2 = Bomb in sector 2\n");
	printf("\t\t3 = Bomb in sector 3\n");
	printf("\t\t4 = Bomb in sector 4\n");
	printf("\t\t5 = Bomb in sector 5\n");
	printf("\t\t6 = Bomb in sector 6\n");
	printf("\t\t7 = Bomb in sector 7\n");
	printf("\t\t8 = Bomb in sector 8\n");
	printf("\t\t9 = Bomb in sector 9\n");
	printf("\t\t0 = Bomb in sector 10\n\n\n");*/

	clock_t ini = 0;

	while (!g_pWorld->getWantsToExit())
	{	
		if ((clock() - ini) >= 50 || !ini)
		{
			g_pGfxEngine->draw();
			g_pWorld->run();
			g_pUI->processInput();

			ini = clock();
			//Sleep(50);
		}
	}

	g_pGfxEngine->setTextColor(FOREGROUND_RED);
	printf("\n Game Over: tu puntuacion es: %i \n\n", g_pWorld->getPuntuacion());
	getchar();

	return 0;
}

