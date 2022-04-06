#include "JsonResponsePacketSerializer.h"

using json = nlohmann::json;

/*
This instance of serializeResponse takes a login response and parses it into a buffer
Input: Login response
Output: Buffer containing response as a char vector
*/
Buffer JsonResponsePacketSerializer::serializeResponse(LoginResponse loginRes) {

	json json;
	Buffer buffer;

	buffer.push_back((char)RESPONSE::LOGIN);
	json["status"] = loginRes.status;

	parseLength(buffer, json.size());

	buffer.insert(buffer.end(), json.dump().begin(), json.dump().end());
}

/*
This instance of serializeResponse takes a sign up response and parses it into a buffer
Input: Sign up response
Output: Buffer containing response as a char vector
*/
Buffer JsonResponsePacketSerializer::serializeResponse(SignupResponse signupRes) {

	json json;
	Buffer buffer;

	buffer.push_back((char)RESPONSE::LOGIN);
	json["status"] = signupRes.status;

	parseLength(buffer, json.size());

	buffer.insert(buffer.end(), json.dump().begin(), json.dump().end());
}

/*
This instance of serializeResponse takes an error response and parses it into a buffer
Input: Error response
Output: Buffer containing response as a char vector
*/
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