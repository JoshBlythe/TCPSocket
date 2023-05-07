#include "NetworkReceiver.h"

NetworkReceiver::NetworkReceiver()
{
    initParameters();
}

NetworkReceiver::NetworkReceiver(int argc, char **argv)
{
    initParameters();
    //loop through the command line parameters
    for (int argno = 1; argno < argc; argno++)
    {
        //check for the -portnumber parameter
        if (0 == strcmp(argv[argno], "-portNumber"))
        {
            //parse the parameter
            portnmb = atoi(argv[argno+ 1]);
        }
        else if (0 == strcmp(argv[argno], "-serverName"))
        {
            serverName = argv[argno + 1];
        }
    }

    if (argc < 3)
    {
        fprintf(stderr, "usage %s hostname port: ", argv[0]);
        exit(0);
    }
}

NetworkReceiver::~NetworkReceiver()
{
    //clean up
    //delete server;
}

void NetworkReceiver::createClientTCP()
{ 
    //create the port
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        error("Failed to open port!\n");
    }

    //get host by name takes a char * name
    server = gethostbyname(serverName.c_str());
    if (server == NULL)
    {
        fprintf(stderr, "Error, no such host!\n");
        exit(0);
    }
    //set the fields within serv_addr parameter
    bzero((char*) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    bcopy((char*)server->h_addr, (char*)&server_addr.sin_addr.s_addr, server->h_length);
    server_addr.sin_port = htons(portnmb);

    //connect
    //need to cast the server_addr to a stuct sockeraddr*, or parameter not accepted
    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        error("Error Connecting to socket!\n");
    }
    else
    {
        printf("Client Connection Successful!");
    }

    //needed for write
    //char buffer[256];
    std::string buffer = "Hello i'm the client socket\n";
    //write to socket
    n = write(sockfd, buffer.c_str(), strlen(buffer.c_str()));
}

void NetworkReceiver::initParameters()
{
    //initalise variables
    sockfd = 0;
	portnmb = 0;
	n = 0;
    //server = NULL;
}

void NetworkReceiver::error(std::string msg)
{
    //error report
    perror(msg.c_str());
    //exit application
    exit(0);
}
