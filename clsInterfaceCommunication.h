#pragma once

#include <iostream>
#include <string>

using namespace std;

class clsInterfaceCommunication
{
public:

	virtual void SendEmail(string Title, string Body) = 0;
	virtual void SendFAX(string Title, string Body) = 0;
	virtual void SendSMS(string Title, string Body) = 0;

};

