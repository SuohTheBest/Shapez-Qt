#include "SaveHelper.h"
SaveHelper::SaveHelper(int layer):layer(layer)
{
    //TODO
}
string SaveHelper::item_data_path(int layer)
{
    return "./data/playerdata/"+to_string(layer)+".json";
}
