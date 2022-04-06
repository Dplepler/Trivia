#include "JsonResponsePacketSerializer.h"

using json = nlohmann::json;

Buffer JsonResponsePacketSerializer::serializeResponse(LoginResponse loginRes) {

	json json;
	Buffer buffer;

	buffer.push_back((char)RESPONSE::LOGIN);
	json["status"] = loginRes.status;

	parseLength(buffer, json.size());

	buffer.insert(buffer.end(), json.dump().begin(), json.dump().end());
}

Buffer JsonResponsePacketSerializer::serializeResponse(SignupResponse signupRes) {

	json json;
	Buffer buffer;

	buffer.push_back((char)RESPONSE::LOGIN);
	json["status"] = signupRes.status;

	parseLength(buffer, json.size());

	buffer.insert(buffer.end(), json.dump().begin(), json.dump().end());
}

Buffer JsonResponsePacketSerializer::serializeResponse(ErrorResponse errorRes) {

	json json;
	Buffer buffer;

	buffer.push_back((char)RESPONSE::LOGIN);
	json["message"] = errorRes.message;

	parseLength(buffer, json.size());

	buffer.insert(buffer.end(), json.dump().begin(), json.dump().end());

}

/*
parseLength parses an integer value into a buffer, each digit becomes an index in the vector buffer
Input: Buffer, length to parse into buffer
*/
void JsonResponsePacketSerializer::parseLength(Buffer& buffer, unsigned int length) {

	for (int8_t i = sizeof(unsigned int) - 1; i >= 0; i--) {
		buffer.push_back(length >> i * sizeof(unsigned int) & BYTE);
	}
}