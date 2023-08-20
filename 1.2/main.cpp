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
    std::vector<MapData *> objects;
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
    void findAndPrintPath(std::string startMap, std::string mapTarget)
    {
        if (startMap == mapTarget)
        {
            std::cout << "(!)There is no path\n";
            return;
        }
        std::vector<std::string> paths;
        int startPosition = 0;
        int endPosition = 0;
        for (int i = 0; i < objects.size(); i++)
        {
            if (objects[i]->mapId == startMap)
            {
                startPosition = i;
            }
            if (objects[i]->mapId == mapTarget)
            {
                bool mapTargetFound = true;
                endPosition = i;
            }
        }
        // std::cout << startPosition << " " << endPosition;
        int bigNumber = 0;
        int smallNumber = 0;
        if (startPosition > endPosition)
        {
            for (int i = startPosition; i >= endPosition; i--)
            {
                paths.push_back(objects[i]->mapId);
            }
        }
        else
        {
            for (int i = startPosition; i <= endPosition; i++)
            {
                paths.push_back(objects[i]->mapId);
            }
        }
        std::cout << "\t\t\t(+)Path from " << startMap << " to " << mapTarget << " is: ";
        for (const auto &path : paths)
        {
            if (path == mapTarget)
                break;
            std::cout << path << "->";
        }
        std::cout << mapTarget << "\n";
        // find and print models occurence
        std::cout << "\t\t\t(+)The models that have encountered\n";
        row();
        rowWord();
        row();
        for (const auto &map_Data : objects)
        {
            for (const auto &path : paths)
            {
                if (path == map_Data->mapId)
                {
                    for (const auto &obj : map_Data->mapObject)
                    {
                        row(obj.objectID, obj.objectName, obj.objectFilePath, obj.objectPosition, obj.objectScale, obj.rotationAngle);
                        row();
                    }
                }
            }
        }
    }
    void addAndFix(MapData *generalMap)
    {
        std::cin.ignore();
        MapData::MapObject obj;
        std::cout << "(!)Enter the new map ID (MAP + name): ";
        std::getline(std::cin, generalMap->mapId);
        int numberOfObject = 0;
        std::cout << "(!)Enter number of Object you want to add: ";
        std::cin >> numberOfObject;
        std::cin.ignore();
        for (int i = 0; i <= numberOfObject - 1; i++)
        {
            std::cout << "(!)Enter the new Object ID (Obj + nameobj): ";
            std::getline(std::cin, obj.objectID);
            std::cout << "(!)Enter the new Object Name: ";
            std::getline(std::cin, obj.objectName);
            std::cout << "(!)Enter the new Object File Path(models/filepath): ";
            std::getline(std::cin, obj.objectFilePath);
            std::cout << "(!)Enter the new Object Postion: ";
            std::getline(std::cin, obj.objectPosition);
            std::cout << "(!)Enter the new Object Scale: ";
            std::getline(std::cin, obj.objectScale);
            std::cout << "(!)Enter the new Object Rotiona Angle: ";
            std::getline(std::cin, obj.rotationAngle);
            generalMap->mapObject.push_back(obj);
        }
        std::cout << "(!)Enter the new Special Object Name(GOTO + name): ";
        std::getline(std::cin, generalMap->specialObject.sobjectName);
        std::cout << "(!)Enter the new Special Key Map: ";
        std::getline(std::cin, generalMap->specialObject.keyMap);
        std::cout << "(!)Enter the new Special Object Position Map: ";
        std::getline(std::cin, generalMap->specialObject.positionMap);
        std::cout << "(!)Enter the new Special Object Position Object: ";
        std::getline(std::cin, generalMap->specialObject.positionObject);
        std::cout << "(!)Enter the new Special Object Distance: ";
        std::cin >> generalMap->specialObject.distance;
    }
    void addMap()
    {
        MapData *newMap = new MapData();
        addAndFix(newMap);
        append(newMap);
        std::cout << "(+)" << newMap->mapId << " has added \n";
        save();
    }
    void edit(std::string nameOfMap)
    {
        std::string option = "";
        std::string option_2 = "";
        std::string option_3 = "";
        std::string IDOfObject = "";
        // std::cout << "(!)You are currently editing the " << nameOfMap << std::endl;
        bool nameOfMap_exist = false;
        for (auto &mapData : objects)
        {
            if (mapData->mapId == nameOfMap)
            {
                nameOfMap_exist = true;
                std::cout
                    << std::left << std::setw(30) << std::setfill('-') << "+"
                    << "+"
                    << "\n"
                    << std::left << std::setw(30) << std::setfill(' ') << "|(1) Edit objects in map"
                    << "|"
                    << "\n"
                    << std::left << std::setw(30) << std::setfill('-') << "+"
                    << "+"
                    << "\n"
                    << std::left << std::setw(30) << std::setfill(' ') << "|(2) Edit entire of map"
                    << "|"
                    << "\n"
                    << std::left << std::setw(30) << std::setfill('-') << "+"
                    << "+"
                    << "\n";
                std::cout << "Enter your option: ";
                std::cin >> option;
                system("cls");
                if (option == "1")
                {
                    std::cout << "(!)You are currently editing the " << nameOfMap << std::endl;
                    std::cout
                        << std::left << std::setw(30) << std::setfill('-') << "+"
                        << "+"
                        << "\n"
                        << std::left << std::setw(30) << std::setfill(' ') << "|(1) Edit map ID"
                        << "|"
                        << "\n"
                        << std::left << std::setw(30) << std::setfill('-') << "+"
                        << "+"
                        << "\n"
                        << std::left << std::setw(30) << std::setfill(' ') << "|(2) Edit objects"
                        << "|"
                        << "\n"
                        << std::left << std::setw(30) << std::setfill('-') << "+"
                        << "+"
                        << "\n"
                        << std::left << std::setw(30) << std::setfill(' ') << "|(3) Edit special objects"
                        << "|"
                        << "\n"
                        << std::left << std::setw(30) << std::setfill('-') << "+"
                        << "+"
                        << "\n";
                    std::cout << "Enter your option: ";
                    std::cin >> option_2;
                    if (option_2 == "1")
                    {
                        std::cin.ignore();
                        std::cout << "(!)Enter map ID: ";
                        std::string name = "";
                        std::getline(std::cin, mapData->mapId);
                        std::cout << "(!)Map ID has changed\n";
                        break;
                    }
                    else if (option_2 == "2")
                    {
                        std::cin.ignore();
                        int numberOfObject = 1;
                        std::cout << "(!)List of Object:";
                        for (auto &obj : mapData->mapObject)
                        {
                            std::cout << "(" << numberOfObject << ")" << obj.objectID << " ";
                            numberOfObject++;
                        }
                        for (auto &obj : mapData->mapObject)
                        {
                            std::cout << "\n(!)Enter ID of Object you want to edit: ";
                            std::cin >> IDOfObject;
                            if (IDOfObject == obj.objectID)
                            {
                                std::cout
                                    << std::left << std::setw(40) << std::setfill('-') << "+"
                                    << "+"
                                    << "\n"
                                    << std::left << std::setw(40) << std::setfill(' ') << "|(1) Edit ID of object"
                                    << "|"
                                    << "\n"
                                    << std::left << std::setw(40) << std::setfill('-') << "+"
                                    << "+"
                                    << "\n"
                                    << std::left << std::setw(40) << std::setfill(' ') << "|(2) Edit name of object"
                                    << "|"
                                    << "\n"
                                    << std::left << std::setw(40) << std::setfill('-') << "+"
                                    << "+"
                                    << "\n"
                                    << std::left << std::setw(40) << std::setfill(' ') << "|(3) Edit file path of object"
                                    << "|"
                                    << "\n"
                                    << std::left << std::setw(40) << std::setfill('-') << "+"
                                    << "+"
                                    << "\n"
                                    << std::left << std::setw(40) << std::setfill(' ') << "|(4) Edit position of object"
                                    << "|"
                                    << "\n"
                                    << std::left << std::setw(40) << std::setfill('-') << "+"
                                    << "+"
                                    << "\n"
                                    << std::left << std::setw(40) << std::setfill(' ') << "|(5) Edit scale of object"
                                    << "|"
                                    << "\n"
                                    << std::left << std::setw(40) << std::setfill('-') << "+"
                                    << "+"
                                    << "\n"
                                    << std::left << std::setw(40) << std::setfill(' ') << "|(6) Edit rotion angle of object"
                                    << "|"
                                    << "\n"
                                    << std::left << std::setw(40) << std::setfill('-') << "+"
                                    << "+"
                                    << "\n";
                                std::cout << "Enter your option: ";
                                std::cin >> option_3;
                                std::cin.ignore();
                                if (option_3 == "1")
                                {
                                    std::cout << "(!)Enter the ID of object: ";
                                    std::getline(std::cin, obj.objectID);
                                    std::cout << "(!)Object ID has changed\n";
                                    break;
                                }
                                else if (option_3 == "2")
                                {
                                    std::cout << "(!)Enter the name of object: ";
                                    std::getline(std::cin, obj.objectName);
                                    std::cout << "(!)Name of object has changed\n";
                                    break;
                                }
                                else if (option_3 == "3")
                                {
                                    std::cout << "(!)Enter the file path of object: ";
                                    std::getline(std::cin, obj.objectFilePath);
                                    std::cout << "(!)File path of object has changed\n";
                                    break;
                                }
                                else if (option_3 == "4")
                                {
                                    std::cout << "(!)Enter the position of object: ";
                                    std::getline(std::cin, obj.objectPosition);
                                    std::cout << "(!)Position of object has changed\n";
                                    break;
                                }
                                else if (option_3 == "5")
                                {
                                    std::cout << "(!)Enter the scale of object: ";
                                    std::getline(std::cin, obj.objectScale);
                                    std::cout << "(!)Scale position of object has changed\n";
                                    break;
                                }
                                else if (option_3 == "6")
                                {
                                    std::cout << "(!)Enter the rotation angle of object: ";
                                    std::getline(std::cin, obj.rotationAngle);
                                    std::cout << "(!)Rotation angle of object has changed\n";
                                    break;
                                }
                                break;
                            }
                        }
                        break;
                    }
                    else if (option_2 == "3")
                    {
                        std::cout
                            << std::left << std::setw(50) << std::setfill('-') << "+"
                            << "+"
                            << "\n"
                            << std::left << std::setw(50) << std::setfill(' ') << "|(1) Edit ID of special object"
                            << "|\n"
                            << std::left << std::setw(50) << std::setfill('-') << "+"
                            << "+"
                            << "\n"
                            << std::left << std::setw(50) << std::setfill(' ') << "|(2) Edit key map of special object"
                            << "|\n"
                            << std::left << std::setw(50) << std::setfill('-') << "+"
                            << "+"
                            << "\n"
                            << std::left << std::setw(50) << std::setfill(' ') << "|(3) Edit position map of special object"
                            << "|\n"
                            << std::left << std::setw(50) << std::setfill('-') << "+"
                            << "+"
                            << "\n"
                            << std::left << std::setw(50) << std::setfill(' ') << "|(4) Edit position object of special object"
                            << "|\n"
                            << std::left << std::setw(50) << std::setfill('-') << "+"
                            << "+"
                            << "\n"
                            << std::left << std::setw(50) << std::setfill(' ') << "|(5) Edit distance to move of special object"
                            << "|\n"
                            << std::left << std::setw(50) << std::setfill('-') << "+"
                            << "+"
                            << "\n";
                        std::cout << "Enter your option: ";
                        std::cin >> option_3;
                        std::cin.ignore();
                        if (option_3 == "1")
                        {
                            std::cout << "(!)Enter the ID of special object: ";
                            std::getline(std::cin, mapData->specialObject.sobjectName);
                            std::cout << "(!)ID of special object has changed\n";
                        }
                        else if (option_3 == "2")
                        {
                            std::cout << "(!)Enter the key map of special object: ";
                            std::getline(std::cin, mapData->specialObject.keyMap);
                            std::cout << "(!)Key map of special object has changed\n";
                        }
                        else if (option_3 == "3")
                        {
                            std::cout << "(!)Enter the position map of special object: ";
                            std::getline(std::cin, mapData->specialObject.positionMap);
                            std::cout << "(!)Position map of special object has changed\n";
                        }
                        else if (option_3 == "4")
                        {
                            std::cout << "(!)Enter the position object of special object: ";
                            std::getline(std::cin, mapData->specialObject.positionObject);
                            std::cout << "(!)Position object of special object has changed\n";
                        }
                        else if (option_3 == "5")
                        {
                            std::cout << "(!)Enter the distance to move of special object: ";
                            std::cin >> mapData->specialObject.distance;
                            std::cout << "(!)Distance to move of special object has changed\n";
                        }
                        break;
                    }
                }
                else if (option == "2")
                {
                    std::cout << "(!)You are currently editing the " << nameOfMap << std::endl;
                    mapData = new MapData();
                    addAndFix(mapData);
                    break;
                }
            }
        }
        if (!nameOfMap_exist)
        {
            std::cout << "(!)You are typing wrong name of Map\n";
        }
        save();
    }
    bool fileExists(const std::string &filePath)
    {
        std::ifstream file(filePath);
        return file.good();
    }
    void modify()
    {
        for (const auto &map_Data : objects)
        {
            for (const auto &map_obj : map_Data->mapObject)
            {
                if (map_obj.objectFilePath.length() == 0)
                {
                    std::cout << "(!)" << map_obj.objectID << " in " << map_Data->mapId << "has no file path\n";
                }
            }
        }
        std::cout << "(*)All of objects have file path\n\n";
        for (const auto &map_Data : objects)
        {
            for (const auto &map_obj : map_Data->mapObject)
            {
                int pos = map_obj.objectFilePath.find("/");
                std::string fileObject = map_obj.objectFilePath.substr(pos + 1);
                std::ifstream input(fileObject);
                std::string line;
                std::getline(input, line);
                std::getline(input, line);
                int size = std::stoi(line);
                input.seekg(0, std::ios::end);
                int kichThuoc = input.tellg();
                std::cout << "Size of " << fileObject << " is: " << kichThuoc << " bytes." << std::endl;
                if (size == kichThuoc)
                {
                    std::cout << "Size of file is valid.\n"
                              << std::endl;
                }
                else
                {
                    std::cout << "Size of file is invalid.\n"
                              << std::endl;
                }
                input.close();
            }
        }
    }
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
std::string mapNextBefore;
std::string mapNextAfter;
std::string mapNow;
void selectMAP(std::string mapMove, MapList mapList, std::string option3, bool *typingWrong)
{
    *typingWrong = true;
    int sizeOfObject = mapList.objects.size();
    // std::cout << mapNow << " " << mapNextAfter << mapNextBefore << "\n";

    if (mapNow == mapList.objects[0]->mapId)
    {
        if (mapMove == mapNextBefore)
        {
            *(typingWrong) = false;
        }
    }
    else if (mapNow == mapList.objects[sizeOfObject - 1]->mapId)
    {
        if (mapMove == mapNextAfter)
        {
            *(typingWrong) = false;
        }
    }
    for (int i = 0; i < sizeOfObject; i++)
    {
        if (i != 0 && i != sizeOfObject - 1)
        {
            if (mapList.objects[i]->mapId == mapNow)
            {
                if (mapMove == mapNextAfter || mapMove == mapNextBefore)
                {
                    *(typingWrong) = false;
                }
            }
        }
    }
    if (*typingWrong)
    {
        std::cout << "You are typing wrong name of map and back to " << mapList.objects[0]->mapId << "\n";
    }
    else
    {
        mapList.printData(mapMove, option3);
        std::cout << "(!)Now you are standing at " << mapMove << std::endl;
    }
}
void printPath(MapList mapList, std::string mapisStanding)
{
    mapNow = mapisStanding;
    std::cout << "(!)You only move to: ";
    int sizeOfObject = mapList.objects.size();
    if (mapList.objects[0]->mapId == mapisStanding)
    {
        mapNextBefore = mapList.objects[1]->mapId;
        std::cout << mapList.objects[1]->mapId << "\n";
    }
    else if (mapList.objects[sizeOfObject - 1]->mapId == mapisStanding)
    {
        mapNextAfter = mapList.objects[sizeOfObject - 1 - 1]->mapId;
        std::cout << mapList.objects[sizeOfObject - 1 - 1]->mapId << "\n";
    }
    for (int i = 0; i < sizeOfObject; i++)
    {
        if (i != 0 && i != sizeOfObject - 1)
        {
            if (mapList.objects[i]->mapId == mapisStanding)
            {
                mapNextAfter = mapList.objects[i - 1]->mapId;
                mapNextBefore = mapList.objects[i + 1]->mapId;
                std::cout << mapList.objects[i - 1]->mapId << " and " << mapList.objects[i + 1]->mapId << "\n";
            }
        }
    }
    // std::cout << "\n";
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
}
void mapisStanding(std::string &mapisStanding)
{
    std::cout << "(!)Now you are standing at " << mapisStanding << "\n";
}
int main()
{
    MapList mapList;
    mapList.readFile();
    std::string option = "";
    std::string nameOfMap = "MAP01";
    std::string nameOfMap_2 = "";
    std::string option3 = "";
    bool typingWrong = true;
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
                    mapisStanding(nameOfMap);
                    printPath(mapList, nameOfMap);
                    std::cout << "(+)Select map you want to move: ";
                    std::cin >> nameOfMap;
                    system("cls");
                    selectMAP(nameOfMap, mapList, option3, &typingWrong);
                    if (typingWrong)
                    {
                        nameOfMap = mapList.objects[0]->mapId;
                        break;
                    }
                }
                std::cout << "\n";
                std::cout
                    << "(*) List of option: \n"
                    << "\t" << std::left << std::setfill('-') << std::setw(30) << "+"
                    << "+"
                    << "\n"
                    << "\t" << std::left << std::setfill(' ') << std::setw(30) << "|(1) Move to another map "
                    << "|"
                    << "\n"
                    << "\t" << std::left << std::setfill('-') << std::setw(30) << "+"
                    << "+"
                    << "\n"
                    << "\t" << std::left << std::setfill(' ') << std::setw(30) << "|(2) Go to the special map"
                    << "|"
                    << "\n"
                    << "\t" << std::left << std::setfill('-') << std::setw(30) << "+"
                    << "+"
                    << "\n"
                    << "\t" << std::left << std::setfill(' ') << std::setw(30) << "|(3) Back to Menu"
                    << "|"
                    << "\n"
                    << "\t" << std::left << std::setfill('-') << std::setw(30) << "+"
                    << "+"
                    << "\n";
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
                    selectMAP(nameOfMap, mapList, option3, &typingWrong);
                }
                else if (option3 == "3")
                {
                    break;
                }
            }
        }
        else if (option == "2")
        {
            system("cls");
            // mapisStanding(nameOfMap);
            std::cout << "(!)Now you are standing at " << nameOfMap << std::endl;
            listOfMap(mapList);
            std::cout << "(!)Enter name of map you want to find out the path: ";
            std::cin >> nameOfMap_2;
            mapList.findAndPrintPath(nameOfMap, nameOfMap_2);
        }
        else if (option == "3")
        {
            system("cls");
            std::cout << "(+)Add map\n";
            mapList.addMap();
        }
        else if (option == "4")
        {
            system("cls");
            listOfMap(mapList);
            std::cout << "(!)Enter name of map you want to edit: ";
            std::cin >> nameOfMap_2;
            mapList.edit(nameOfMap_2);
        }
        else if (option == "5")
        {
            mapList.modify();
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
        std::cout << "(*)Press enter to back to menu...";
        std::cin.ignore();
        std::getline(std::cin, option);
        system("cls");
    }
    return 0;
}
