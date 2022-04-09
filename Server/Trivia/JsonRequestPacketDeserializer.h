#ifndef JSONDESERIALIZER_H
#define JSONDESERIALIZER_H


#include "json.hpp"
#include <vector>



typedef struct RequestInfo {

	int msgCode;

	std::string timeOf;

	std::vector<char> msgContent;

};




class JsonRequestPacketDeserializer {


public:

	



};









#endif // JSONDESERIALIZER_H
