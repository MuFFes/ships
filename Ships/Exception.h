#pragma once
#include <exception>
#include <string>

using namespace std;

class Exception: public exception
{
	private:
		string message;
	public:
		Exception(const string& message);
		virtual const string what();
};