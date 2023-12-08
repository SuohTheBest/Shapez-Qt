#include "MapCreator.h"
#include "direct.h"
#include "iostream"
#include "unistd.h"

string pic_path(int type) {
	return "./img/" + to_string(type) + ".png";
}

string map_path(int layer) {
	return "./data/map/" + to_string(layer) + ".map";
}

string item_data_path(int layer) {
	return "./data/playerdata/" + to_string(layer) + ".json";
}

void MapCreator::randomPoint(int &x, int &y) {
	x = rand() % 64;
	y = rand() % 64;
}

void MapCreator::spread(int x, int y, int type, int &max_spread) {
	if (x < 0 || y < 0 || x > 63 || y > 63 || max_spread <= 0) return;
	if (rand() % 100 < 50) {
		map[x][y] = type;
		int directions[4][2] = {{0,  1},
								{1,  0},
								{0,  -1},
								{-1, 0}};
		for (int i = 0; i < 4; i++) {
			int x_next = x + directions[i][0];
			int y_next = y + directions[i][1];
			max_spread--;
			if (map[x_next][y_next] == 0) spread(x_next, y_next, type, max_spread);
		}
	}
}

void MapCreator::createMap() {
	if (access("./data/map", F_OK) == -1) {
		mkdir("./data");
		mkdir("./data/map");
	}
	if (access("./data/playerdata", F_OK == -1)) {
		mkdir("./data/playerdata");
	}
	memset(map, 0, sizeof(map));
	for (int j = 1; j < TYPES_OF_BLOCKS; j++) {
		for (int i = 0; i < 10; i++) {//TODO
			int x, y, max_spread = 10;
			randomPoint(x, y);
			map[x][y] = j;
			spread(x, y, j, max_spread);
		}
	}
	ofstream map_out(map_path(layer), ios::out);
	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 64; j++) {
			map_out << map[i][j] << " ";
		}
		map_out << endl;
	}
	map_out.close();
}
