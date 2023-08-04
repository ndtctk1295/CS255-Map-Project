#ifndef __printTable_H__
#define	__printTable_H__	
const char multiplychr = '+';
const char subtractchr = '-';
const char verticlechr = '|';
std::string objectId = "|Object ID";
std::string objectName = "|Object Name";
std::string objectFilePath = "|Object File Path";
std::string objectPosition = "|Object Position";
std::string objectScale = "|Object Scale";
std::string objectRotationAngle = "|Rotation Angle";
std::string soName = "S0 Name";
std::string soKey = "S0 Key Map";
std::string soPosMap = "SO Position Map";
std::string soPosOb = "SO Position Object";
std::string soDistance = "Distance to move";
void row(std::string objectID, std::string objectName, std::string objectFilePath, std::string objectPosition, std::string objectScale, std::string rotationAngle) {
	std::cout << verticlechr << std::left << std::setfill(' ') << std::setw(14) << objectID
		<< verticlechr << std::setw(14) << objectName
		<< verticlechr << std::setw(29) << objectFilePath
		<< verticlechr << std::setw(19) << objectPosition
		<< verticlechr << std::setw(19) << objectScale
		<< verticlechr << std::setw(18) << rotationAngle << verticlechr;
}
void row(std::string sobjectName, std::string keyMap, std::string positionMap, std::string positionObject, float distance) {
	std::cout << "|" << std::left << std::setfill(' ') << std::setw(19) << sobjectName
		<< "|" << std::setw(19) << keyMap
		<< "|" << std::setw(19) << positionMap
		<< "|" << std::setw(19) << positionObject
		<< "|" << std::setw(19) << distance << verticlechr << "\n";

}
void row2() {
	std::cout << std::left << std::setfill(subtractchr) << std::setw(20) << multiplychr
		<< std::setw(20) << multiplychr
		<< std::setw(20) << multiplychr
		<< std::setw(20) << multiplychr
		<< std::setw(20) << multiplychr << multiplychr << "\n";
}
void row() {
	std::cout<< std::left << std::setfill(subtractchr) << std::setw(15) << multiplychr
		<< std::setw(15) << multiplychr 
		<< std::setw(30) << multiplychr
		<< std::setw(20) << multiplychr
		<< std::setw(20) << multiplychr 
		<< std::setw(19) << multiplychr << multiplychr << "\n";
	
}
void rowWord() {
	std::cout << std::left << std::setfill(' ') << std::setw(15) << objectId
		<< std::setw(15) << objectName
		<< std::setw(30) << objectFilePath
		<< std::setw(20) << objectPosition
		<< std::setw(20) << objectScale
		<< std::setw(19) << objectRotationAngle << '|' << "\n";
}
void rowWord2() {
	std::cout << "|" << std::left << std::setfill(' ') << std::setw(19) << soName
		<< "|" << std::setw(19) << soKey
		<< "|" << std::setw(19) << soPosMap
		<< "|" << std::setw(19) << soPosOb
		<< "|" << std::setw(19) << soDistance << verticlechr << "\n";
}

#endif __printTable_H__

