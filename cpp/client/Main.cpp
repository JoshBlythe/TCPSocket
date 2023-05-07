#include "NetworkReceiver.h"

void help();

int main(int argc, char* argv[])
{
	//check if any command line parameter are provided
	if (argc == 1 )
	{
		printf("No command line parameters are provide.\n");
		help();
	}
	else
	{
		//create instance of the NetworkReceiver
		NetworkReceiver* socket = new NetworkReceiver(argc, argv);

		socket->createClientTCP();
		
	}
	
	//NetworkReceiver* socket = new NetworkReceiver();
	return 0;
}

void help()
{
	printf("This application expects the following parameters:\n");
	printf("-h | --help:	Provides parameters.\n");
}