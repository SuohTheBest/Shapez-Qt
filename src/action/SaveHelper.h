#ifndef SAVEHELPER_H
#define SAVEHELPER_H
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <string>
using namespace std;
class SaveHelper
{
public:
    SaveHelper(int layer=0);
    string item_data_path(int layer);
private:
    int layer;
};

#endif // SAVEHELPER_H
