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

    if (argc < 2)
    {
        fprintf(stderr, "Error, no port provided!\n");
        exit(1);
    }
}

NetworkReceiver::~NetworkReceiver()
{
    //clean up
    //delete server;
}

void NetworkReceiver::createServerTCPSocket()
{ 
    //create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    //check if the socket creation was successful
    if (sockfd < 0)
    {
        error("ERROR opening port!\n");
    }

    //set up socket settings
    // sets all values in a buffer to zero. bzero function takes two arguments
    // the first is a pointer to the buffer and the second is the size of the buffer.
    bzero((char*)&server_addr, sizeof(server_addr));
    
    //set the address family 
    server_addr.sin_family = AF_INET;
    //port number the server will listen for connections is passed in
    server_addr.sin_port = htons(portnmb);
    //setting the IP address of the host, for the server this is the IP address of the machine
    server_addr.sin_addr.s_addr = INADDR_ANY;

    //bind system call binds the socket to and address, in this case the address of the
    //current host and port number on which the server will run.
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        error("Error binding to socket!\n");
    }

    //listen system call allows the process to listne on the socket for connecteds
    //the first argument is the socket file descriptor and the second is the size of the backlog queue,
    //(the number of connections that can be waiting while the process is a particular connection.)
    if(listen(sockfd,5) == -1)
    {
        error("Failed on listening for socket connection!\n");
    }
    
    //get size of the cli_addr
    clilen = sizeof(cli_addr);
    //accept system call causes the process to block until a clinet connects to the server.
    newSocketfd = accept(sockfd, (struct sockaddr*)&cli_addr, &clilen);
    //check for socket accept
    if (newSocketfd < 0)
    {
        //failed to accept the socket
        error("Error on socket accept!\n");
    }
    
    //read from socket
    char buffer[256];
    bzero(buffer, 256);
    n = read(newSocketfd, buffer, 255);
    if (n < 0)
    {
        error("Error reading from socket!\n");
    }
    printf("Message received: %s", buffer);
    
    //write to socket
    std::string receivedMsg = "I got the message!.";
    n = write(newSocketfd, receivedMsg.c_str(), sizeof(receivedMsg));
    if (n < 0)
    {
        error("Error writing to socket!\n");
    }
        
}

void NetworkReceiver::initParameters()
{
    //initalise variables
    //both the sockfd and newSocketfd are file descriptors, they store the
    //returned values by the socket system call and accept system call.
    sockfd = 0;
    newSocketfd = 0;
	portnmb = 0;
	n = 0;
    clilen = 0;
}

void NetworkReceiver::error(std::string msg)
{
    //error report
    perror(msg.c_str());
    //exit application
    exit(0);
}
