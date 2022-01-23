//Youssef Behery
//Date:22/1/2022
//Socket Programming (Client)

#include<iostream>
#include<string>
#include<WS2tcpip.h>
#pragma comment (lib,"ws2_32.lib")
int main()
{
    /***************************initializa winsock*********************/
    WSAData data;
    WORD ver=MAKEWORD(2,2);//defining version 2.2
    int WsResult=WSAStartup(ver, &data);//initiate use of winsock dll file by giving version and pointer to wsadata struct to recieve socket info
    //return 0 in case of error in startup
    if(WsResult!=0)
    {
        std::cerr<<"Unable to start winsock Err #"<<WsResult<<std::endl;
        return 0;
    }
    /***************************create socket**************************/
    //AF_INET:IPV4 | SOCK_STREAM:TCP 
    SOCKET sock= socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(sock==INVALID_SOCKET)
    {
        std::cerr<<"Unable to create socket Err #"<<WSAGetLastError()<<std::endl;
        WSACleanup();//close winsock properly
        return 0;
    }
    
    /**************************server address info**********************/
    sockaddr_in server_address;
    //IPV4
    server_address.sin_family=AF_INET;
    //PORT NUMBER
    server_address.sin_port=htons(45000);
    //IP address of socket INADDR_ANY:it is replaced with the ipaddress of the machine
    //server_address.sin_addr.S_un.S_addr=INADDR_ANY;
    std::string ipAddress = "127.0.0.1";	
inet_pton(AF_INET,ipAddress.c_str(), &server_address.sin_addr);

    /**************************Connect to server**********************/
    int ConnectResult=connect(sock,(sockaddr *)&server_address,sizeof(server_address));

    if(ConnectResult==SOCKET_ERROR)
    {
        std::cerr<<"Unable to connect to server Err # "<<WSAGetLastError()<<std::endl;
        WSACleanup();//close winsock properly
        return 0;
    }
    /*********************Send and recieve data************************/
    std::string  user_input;
    char buffer[8192];

    do
    {
        //recieve requests
        ZeroMemory(buffer,sizeof(buffer));
        int BytesRecieved=recv(sock,buffer,sizeof(buffer),0);
        if (BytesRecieved>0)
            {
                std::cout<<std::string(buffer,0,BytesRecieved)<<">";
            }
            else if (BytesRecieved==SOCKET_ERROR)
            {
                std::cerr<<"unable to recieve Err#"<<WSAGetLastError()<<std::endl;
                return 0;
            }
        getline(std::cin,user_input);
       if(user_input.size()>0)
        {
            //send data
           int SendResult= send(sock, user_input.c_str(),sizeof(user_input)+1,0);//+1 for null char
            if(SendResult==SOCKET_ERROR)
            {
                std::cerr<<"unable to send Err#"<<WSAGetLastError()<<std::endl;
               WSACleanup();//close winsock properly
                return 0;
            }
            //recieve echo
            ZeroMemory(buffer,sizeof(buffer));//clear the buffer
             BytesRecieved=recv(sock,buffer,sizeof(buffer),0);
            if (BytesRecieved>0)
            {
                //string(string that will be shown ,starting from index i,number of characters shown)
                std::cout<<"Echo:"<<std::string(buffer,0,BytesRecieved)<<std::endl;
            }
            else if (BytesRecieved==SOCKET_ERROR)
            {
                std::cerr<<"unable to recieve Err#"<<WSAGetLastError()<<std::endl;
                return 0;
            }
        }
    } while (user_input.size()>0);
closesocket(sock);
  WSACleanup();//close winsock properly  
}