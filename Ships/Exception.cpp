#include "Exception.h"
#include <utility>

Exception::Exception(string message) : message(std::move(message)) {};

string Exception::what()
{
	return message;
}
