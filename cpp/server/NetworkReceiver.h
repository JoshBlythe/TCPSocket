//includes required for linux network socket
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
//needed for write()
#include <unistd.h>
//include strings
#include <string.h>
#include <stdio.h>
#include <iostream>

class NetworkReceiver
{
public:
	/// @brief default constructor
	NetworkReceiver();
	/// @brief Contructor that passes the command line parameters
	/// @param argc 
	/// @param argv 
	NetworkReceiver(int argc, char**argv);
	/// @brief deconstructor
	~NetworkReceiver();
	//copy constuctor
	//NetworkReceiver(NetworkReceiver N);

	/// @brief creates a TCP client socket.
	void createServerTCPSocket();

private:
	/// @brief will initials the class variables
	void initParameters();
	/// @brief error function prints a message to the console and exits the application
	/// @param msg 
	void error(std::string msg);
	//socket variable
	int sockfd;
	//port variable
	int newSocketfd;
	int portnmb;
	int n;
	socklen_t clilen;
	//server name
	std::string serverName;

	//sockets
	struct sockaddr_in server_addr;
	struct sockaddr_in cli_addr;
	//hostend is defined within netdb.h. Contains server details
	struct hostent* server;	
	
};