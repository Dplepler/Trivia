#include "LoginRequestHandler.h"

bool LoginRequestHandler::isRequestRelevant(RequestInfo info) const { return true; }

RequestResult LoginRequestHandler::handleRequest(RequestInfo info) { return RequestResult(); }

RequestResult LoginRequestHandler::login(RequestInfo info) { return RequestResult(); }
RequestResult LoginRequestHandler::signup(RequestInfo info) { return RequestResult(); }