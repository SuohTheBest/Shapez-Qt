#include "ItemGetter.h"
void ItemGetter::get_item(BasicItems *Item) {
    emit item_get(Item);
}