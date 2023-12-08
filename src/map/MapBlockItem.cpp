#include "MapBlockItem.h"

string MapBlockItem::info[]{"stone", "coal"};

void MapBlockItem::set_type(int type) {
	this->item_type = type;
}

string MapBlockItem::detail_info() {
	return info[item_type];
}
