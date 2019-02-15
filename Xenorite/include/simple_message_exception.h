#ifndef __SIMPLE_MESSAGE_EXCEPTION__
#define __SIMPLE_MESSAGE_EXCEPTION__

#include <exception>
#include <string>

// simple struct for handling exceptions with a plain text message
struct Simple_Message_Exception : public std::exception
{
	const std::string m_error_message;


public:
	// constructor for creating a simple exception with a given string message
	Simple_Message_Exception(const std::string p_message)
		:
		m_error_message(p_message)
	{}
};

#endif