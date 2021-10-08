#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <ctime>

using namespace std;


enum class mapSi {
	voidy = ' ',
	gamer = 'x',
	apple = '+',
	bar = '#'
};




struct Game {
	const int xsz = 50;
	const int ysz = 25;
	mapSi **map = nullptr;
	int lvl =1;
	int quan = lvl;
	
};


void memory(Game &g) {
	g.map = new mapSi * [g.ysz];
	for (int i = 0; i < g.ysz; ++i) {
		g.map[i] = new mapSi[g.xsz];
	}
}

void deMemory(Game& g) {
	for (int i = 0; i < g.ysz; ++i) {
		delete[] g.map[i];
	}
	delete[] g.map;
	g.map = nullptr;
}

void wasd(int &y, int &x, int dy, int dx, Game &g) {
	
	if (g.map[y + 1 * dy][x + 1 * dx] == mapSi::bar) {
		return;
	}
	g.map[y][x] = mapSi::voidy;
	
	
	if (g.map[y + 1 * dy][x + 1 * dx] == mapSi::apple)
		--g.quan;

	g.map[y +1*dy][x + 1*dx] = mapSi::gamer;
	x += 1 * dx;
	y += 1 * dy;
}


void mapprint(Game g){
	cout << " level: " << g.lvl << '\n' << endl;
	for (int i = 0; i < g.ysz; ++i) {
		for (int j = 0; j < g.xsz; ++j) {
			
			cout << (char)g.map[i][j];
		}
		cout << endl;
	}
	
}

void initS(Game& g, mapSi sim) {
	int yAp, xAp;
	srand(time(0));
	for (int i = 0; i < g.lvl; ++i) {
		do {
			yAp = rand() % g.ysz;
			xAp = rand() % g.xsz;
		} while (g.map[yAp][xAp] != mapSi::voidy);
		g.map[yAp][xAp] = sim;
	}

}

int main() {
	int x = 0;
	int y = 0;
	
	Game g;
	
	char run;
	memory(g);
	g.lvl = 1;
	
	while (true) {
		
		
		for (int i = 0; i < g.ysz; i++) {
			for (int j = 0; j < g.xsz; ++j) {
				g.map[i][j] = mapSi::voidy;
			}
		}
		
		x = 0;
		y = 0;
		g.map[y][x] = mapSi::gamer;
		
		
		g.quan = g.lvl;
		initS(g, mapSi::apple);
		initS(g, mapSi::bar);

	
		mapprint(g);
		while (g.quan != 0) {
			run = _getch();
			if ((run == 'D' || run == 'd')&& x != 49) {
				
					
					wasd(y, x, 0, 1, g);
					system("cls");
					mapprint(g);
				
			}
			else if ((run == 'A' || run == 'a')&& x != 0) {
				
					
					wasd(y, x, 0, -1, g);
					system("cls");
					mapprint(g);
				
			}
			else if ((run == 'W' || run == 'w')&& y != 0) {
				
					
					wasd(y, x, -1, 0, g);
					system("cls");
					mapprint(g);
				
			}
			else if ((run == 'S' || run == 's')&& y != 24) {
				
					
					wasd(y, x, 1, 0, g);
					system("cls");
					mapprint(g);
				
			}
			

			if (run == 'Q' || run == 'q') {
				deMemory(g);
				cout << "end\n";
				return 0;
			}
		}
		system("cls");
		++g.lvl;
	}
	

}
