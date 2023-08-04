#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include "printTable.h"
const std::string filename = "file.map";
struct MapData
{
    std::string mapId;
    struct MapObject
    {
        std::string objectID;
        std::string objectName;
        std::string objectFilePath;
        std::string objectPosition;
        std::string objectScale;
        std::string rotationAngle;
    };
    struct SpecialObject
    {
        std::string sobjectName;
        std::string positionMap;
        std::string positionObject;
        std::string keyMap;
        float distance;
    };
    std::vector<MapObject> mapObject;
    SpecialObject specialObject;
};

struct MapList
{
    std::vector<MapData *> objects; // duyet vector này
    MapData *currentMap = new MapData();
    void readFile()
    {
        std::ifstream file(filename);
        std::string line;

        while (std::getline(file, line))
        {
            if (line.rfind("MAP") == 0)
            {

                if (!currentMap->mapId.empty())
                {
                    append(currentMap);
                }
                currentMap = new MapData();
                currentMap->mapId = line;
            }
            else if (line.rfind("OBJ") == 0)
            {

                MapData::MapObject obj;
                obj.objectID = line;
                std::getline(file, obj.objectName);
                std::getline(file, obj.objectFilePath);
                std::getline(file, obj.objectPosition);
                std::getline(file, obj.objectScale);
                std::getline(file, obj.rotationAngle);
                currentMap->mapObject.push_back(obj);
            }
            else if (line.rfind("GOTO") == 0)
            {
                MapData::SpecialObject sobj;
                sobj.sobjectName = line;
                std::getline(file, sobj.keyMap);
                std::getline(file, sobj.positionMap);
                std::getline(file, sobj.positionObject);
                std::string distanceStr;
                std::getline(file, distanceStr);
                std::istringstream(distanceStr) >> sobj.distance;
                currentMap->specialObject = sobj;
            }
        }
        if (!currentMap->mapId.empty())
        {
            append(currentMap);
        }
    }

    void append(MapData *currentMap)
    {
        objects.push_back(currentMap);
    }
    // print Data
    void printData(std::string nameOfMap, std::string option3)
    {
        for (const auto &map_Data : objects)
        {
            if (map_Data->mapId == nameOfMap)
            {

                if (option3 == "1")
                {
                    std::cout << "\t\t\t\t\t\t\t" << map_Data->mapId << "\n";
                    row();
                    rowWord();
                    row();
                    for (const auto &mapO : map_Data->mapObject)
                    {
                        row(mapO.objectID, mapO.objectName, mapO.objectFilePath, mapO.objectPosition, mapO.objectScale, mapO.rotationAngle);
                        row();
                    }
                }
                else if (option3 == "2")
                {
                    std::cout << "\t\t\t\t\t"
                              << "Special Object of " << map_Data->mapId << "\n";
                    row2();
                    rowWord2();
                    row2();
                    row(map_Data->specialObject.sobjectName, map_Data->specialObject.keyMap, map_Data->specialObject.positionMap, map_Data->specialObject.positionObject, map_Data->specialObject.distance);
                    row2();
                }
            }
        }
    }
    void addAndFix(MapData *generalMap)
    {
        std::cin.ignore();
        MapData::MapObject obj;
        std::cout << "(-)Enter map ID: ";
        std::getline(std::cin, generalMap->mapId);
        int numberOfObject = 0;
        std::cout << "Enter number of Object you want to add: ";
        std::cin >> numberOfObject;
        std::cin.ignore();
        for (int i = 0; i <= numberOfObject - 1; i++)
        {
            std::cout << "Object ID: ";
            std::getline(std::cin, obj.objectID);
            std::cout << "Object Name: ";
            std::getline(std::cin, obj.objectName);
            std::cout << "Object File Path: ";
            std::getline(std::cin, obj.objectFilePath);
            std::cout << "Object Postion: ";
            std::getline(std::cin, obj.objectPosition);
            std::cout << "Object Scale: ";
            std::getline(std::cin, obj.objectScale);
            std::cout << "Object Rotation Angle: ";
            std::getline(std::cin, obj.rotationAngle);
            generalMap->mapObject.push_back(obj);
        }
        std::cout << "Special Object Name: ";
        std::getline(std::cin, generalMap->specialObject.sobjectName);
        std::cout << "Special Key Map: ";
        std::getline(std::cin, generalMap->specialObject.keyMap);
        std::cout << "Special Object Position Map: ";
        std::getline(std::cin, generalMap->specialObject.positionMap);
        std::cout << "Special Object Position Object: ";
        std::getline(std::cin, generalMap->specialObject.positionObject);
        std::cout << "Special Object Distance: ";
        std::cin >> generalMap->specialObject.distance;
    };
    void addMap()
    {
        MapData *newMap = new MapData();
        addAndFix(newMap);
        append(newMap);
        std::cout << "(+)" << currentMap->mapId << " has added \n";
        save();
    };
    // edit map function start
    void edit(std::string nameOfMap)
    {
        std::cin.ignore();

        std::cout << "(!)You are currently editing the " << nameOfMap << std::endl;
        // for (short i = 0; i < objects.size(); i++)
        // {
        //     std::cout << (*objects)[i] << " ";
        // }
        for (short i = 0; i < objects.size(); i++)
        {
            // std::cout << objects[i]->mapId << " ";
            if (nameOfMap == objects[i]->mapId)
            {
                // std::cout << objects[i]->mapId << std::endl;
                for (short j = 0; j < objects[i]->mapObject.size(); j++)
                {
                    // std::cout << objects[i]->mapObject[j];

                    std::cout << "(!)Current Object ID: " << objects[i]->mapObject[j].objectID << std::endl;
                    std::cout << "(!)Current Object Name: " << objects[i]->mapObject[j].objectName << std::endl;
                    std::cout << "(!)Current Object FIle Path: " << objects[i]->mapObject[j].objectFilePath << std::endl;
                    std::cout << "(!)Current Object Position: " << objects[i]->mapObject[j].objectPosition << std::endl;
                    std::cout << "(!)Current Object Scale: " << objects[i]->mapObject[j].objectScale << std::endl;
                    std::cout << "(!)Current Object Rotation Angle: " << objects[i]->mapObject[j].rotationAngle << std::endl;

                    std::cout << "(!)Enter the new Object ID: " << std::endl;
                    std::getline(std::cin, objects[i]->mapObject[j].objectID);
                    std::cout << "(!)Your Object ID has successfully changed with new value: " << objects[i]->mapObject[j].objectID << std::endl;
                    std::cout << "(!)Enter the new Object Name: " << std::endl;
                    std::getline(std::cin, objects[i]->mapObject[j].objectName);
                    std::cout << "(!)Your Object Name has successfully changed with new value: " << objects[i]->mapObject[j].objectName << std::endl;
                    std::cout << "(!)Enter the new Object File Path: " << std::endl;
                    std::getline(std::cin, objects[i]->mapObject[j].objectFilePath);
                    std::cout << "(!)Your Object File Path has successfully changed with new value: " << objects[i]->mapObject[j].objectFilePath << std::endl;
                    std::cout << "(!)Enter the new Object Position: " << std::endl;
                    std::getline(std::cin, objects[i]->mapObject[j].objectPosition);
                    std::cout << "(!)Your Object Position has successfully changed with new value: " << objects[i]->mapObject[j].objectPosition << std::endl;
                    std::cout << "(!)Enter the new Object Scale: " << std::endl;
                    std::getline(std::cin, objects[i]->mapObject[j].objectScale);
                    std::cout << "(!)Your Object Scale has successfully changed with new value: " << objects[i]->mapObject[j].objectScale << std::endl;
                    std::cout << "(!)Enter the new Object Rotation Angle: " << std::endl;
                    std::getline(std::cin, objects[i]->mapObject[j].rotationAngle);
                    std::cout << "(!)Your Object Rotation Angle has successfully changed with new value: " << objects[i]->mapObject[j].rotationAngle << std::endl;
                }
            }
        }
        // std::cout << obj.objectID;
        save();
    };
    // edit map function end
    void save()
    {
        std::ofstream output(filename);
        for (const auto &map_Data : objects)
        {
            output << map_Data->mapId << "\n";
            for (const auto &map_obj : map_Data->mapObject)
            {
                output << map_obj.objectID << "\n"
                       << map_obj.objectName << "\n"
                       << map_obj.objectFilePath << "\n"
                       << map_obj.objectPosition << "\n"
                       << map_obj.objectScale << "\n"
                       << map_obj.rotationAngle << "\n";
            }
            output << map_Data->specialObject.sobjectName << "\n"
                   << map_Data->specialObject.keyMap << "\n"
                   << map_Data->specialObject.positionMap << "\n"
                   << map_Data->specialObject.positionObject << "\n"
                   << map_Data->specialObject.distance << "\n";
        }
    }
};

void modify(){};

void selectMAP(std::string nameOfMap, MapList mapList, std::string option3)
{

    for (const auto &map_Data : mapList.objects)
    {
        if (nameOfMap == map_Data->mapId)
        {
            mapList.printData(nameOfMap, option3);
        }
    }
    // std::string option;
}
void listOfMap(MapList mapList)
{
    int i = 1;
    std::cout << "(-)List of map: ";
    for (const auto &map_Data : mapList.objects)
    {
        std::cout << "(" << i << ")" << map_Data->mapId << "  ";
        i++;
    }
    std::cout << "\n";
};
int main()
{
    MapList mapList;
    mapList.readFile();
    // mapList.print();
    std::string option = "";
    std::string nameOfMap = "MAP01";
    std::string nameOfMap_2 = "";
    std::string option3 = "";
    while (true)
    {
        listOfMap(mapList);
        std::cout << "(+)List of options \n";
        std::cout
            << "\t" << std::left << std::setfill('-') << std::setw(20) << "+"
            << "+"
            << "\n"
            << "\t" << std::left << std::setfill(' ') << std::setw(20) << "|(1) Move"
            << "|"
            << "\n"
            << "\t" << std::left << std::setfill('-') << std::setw(20) << "+"
            << "+"
            << "\n"
            << "\t" << std::left << std::setfill(' ') << std::setw(20) << "|(2) Find"
            << "|"
            << "\n"
            << "\t" << std::left << std::setfill('-') << std::setw(20) << "+"
            << "+"
            << "\n"
            << "\t" << std::left << std::setfill(' ') << std::setw(20) << "|(3) Add"
            << "|"
            << "\n"
            << "\t" << std::left << std::setfill('-') << std::setw(20) << "+"
            << "+"
            << "\n"
            << "\t" << std::left << std::setfill(' ') << std::setw(20) << "|(4) Edit"
            << "|"
            << "\n"
            << "\t" << std::left << std::setfill('-') << std::setw(20) << "+"
            << "+"
            << "\n"
            << "\t" << std::left << std::setfill(' ') << std::setw(20) << "|(5) Modify"
            << "|"
            << "\n"
            << "\t" << std::left << std::setfill('-') << std::setw(20) << "+"
            << "+"
            << "\n"
            << "\t" << std::left << std::setfill(' ') << std::setw(20) << "|(6) Exit"
            << "|"
            << "\n"
            << "\t" << std::left << std::setfill('-') << std::setw(20) << "+"
            << "+"
            << "\n";
        std::cout << "(!)Enter your option: ";
        std::cin >> option;

        if (option == "1")
        {
            system("cls");
            bool declared = true;

            while (true)
            {
                if (declared)
                {
                    option3 = "1";
                    listOfMap(mapList);
                    std::cout << "(+)Select map you want to move: ";
                    std::cin >> nameOfMap;
                    system("cls");
                    selectMAP(nameOfMap, mapList, option3);
                }
                std::cout << "\n";
                std::cout << "(!)Now you are standing at " << nameOfMap << std::endl;
                std::cout << "(*)Do you want move to another map or going to the special map \n"
                          << "(1) Move to another map  (2) Going to the special map (3) Back to Menu\n";
                std::cout << "(!)Enter your option: ";
                std::cin >> option3;
                system("cls");
                if (option3 == "1")
                {
                    declared = true;
                }
                else if (option3 == "2")
                {
                    declared = false;
                    selectMAP(nameOfMap, mapList, option3);
                }
                else if (option3 == "3")
                {
                    break;
                }
            }
        }
        else if (option == "2")
        {
            std::cout << "(!)Now you are standing at " << nameOfMap << std::endl;
            std::cout << "(!)Enter name of map you want to find out the path: ";
            std::cin >> nameOfMap_2;
        }
        else if (option == "3")
        {
            system("cls");
            listOfMap(mapList);
            mapList.addMap();
        }
        else if (option == "4")
        {
            system("cls");
            listOfMap(mapList);
            std::cout << "(!)Enter name of map you want to edit: ";
            std::cin >> nameOfMap_2;
            mapList.edit(nameOfMap_2);
            // bool declared = true;
            // while (true)
            // {

            //     std::cout << "(!)You are currently editing the " << nameOfMap_2;
            // }
        }
        else if (option == "6")
        {
            // system("cls");
            std::string endOption = "";
            std::cout << "(*)Do you want end program? (1) Yes (2) No \n";
            std::cout << "(!)Enter your option: ";
            std::cin >> endOption;
            if (endOption == "1")
            {
                break;
            }
        }
        std::cout << "(*)Press any key to back to menu...";
        std::cin.ignore();
        std::getline(std::cin, option);
        system("cls");
    }
    return 0;
}
