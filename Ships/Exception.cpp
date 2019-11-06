#include "Exception.h"

Exception::Exception(const string& message) : message(message) {};

const string Exception::what()
{
	return message;
}