#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase* db) : m_database(db) { }

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler() {
	return &LoginRequestHandler(this->m_database);
}

