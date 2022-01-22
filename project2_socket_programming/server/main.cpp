//Youssef Behery
//Date:22/1/2022
//Socket Programming (Server)

#include<iostream>
#include<string>
#include<WS2tcpip.h>
#include<vector>
#include <cstdlib>
#include<iomanip>
#pragma comment (lib,"ws2_32.lib")
class Bank_Clients{
    private:
std::string name;
int Amount;
public:
void display(){
    std::cout<<std::left<<std::setw(20)<<name<<"        "<<"Bal : "<<Amount<<std::endl;
}
void Bank_Clients::Set_Amount(int Amount){
    this->Amount=Amount;
}
void Bank_Clients::Set_Name(char* INname){
    name.clear();//reset string to avoid overwrite in temp
    for(int i=0;INname[i]!='\0';i++)
    {
       name.insert(i,1,INname[i]) ;
    }
}
};
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
    SOCKET listening= socket(AF_INET,SOCK_STREAM,0);
    if(listening==INVALID_SOCKET)
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
    server_address.sin_addr.S_un.S_addr=INADDR_ANY;

    /**************************Bind socket and listen **********************/
    int BindResult=bind(listening,(sockaddr *)&server_address,sizeof(server_address));

    if(BindResult==SOCKET_ERROR)
    {
        std::cerr<<"Unable to connect to server Err # "<<WSAGetLastError()<<std::endl;
        WSACleanup();//close winsock properly
        return 0;
    }
    listen(listening,5);//5:clients that can connect to the server any more they will get error
    /*********************wait for connection************************/
    sockaddr_in client;
    int ClientSize=sizeof(client);
    SOCKET ClientSocket=accept(listening,(sockaddr*)&client,&ClientSize);

    //display client info
    char host[NI_MAXHOST];
    char service[NI_MAXSERV];

    ZeroMemory(host,NI_MAXHOST);
    ZeroMemory(service,NI_MAXSERV);

    if(getnameinfo((sockaddr *)&client,sizeof(client),host,NI_MAXHOST,service,NI_MAXSERV,0)==0)
    {
        std::cout<<host<<" connected on port"<<service<<std::endl;
    }
    else
    {
        inet_ntop(AF_INET,&client.sin_addr,host,NI_MAXHOST);
        std::cout<<host<<" connected on port "<<ntohs(client.sin_port)<<std::endl;
    }
    //close listening socket
    closesocket(listening);
    //recieve and echo back
    char buffer[8192];
    std::string Name_Request="Name";
    std::string Money_Request="Amount";
    std::vector<Bank_Clients> BankA;
    Bank_Clients temp;
    int Input_Specifier=0;
    int counter =0;
    while(1)
    {

        //send name request
        if(Input_Specifier==0)
        {
            send(ClientSocket,Name_Request.c_str(),sizeof(Name_Request)+1,0);
           // Input_Specifier=1;
        }
        //send amount request
        else if(Input_Specifier==1)
        {
            send(ClientSocket,Money_Request.c_str(),sizeof(Money_Request)+1,0);
            //Input_Specifier=0;
        }
        //recieve data
        ZeroMemory(buffer,8192);
        int BytesRecieved=recv(ClientSocket,buffer,8192,0);

        if (BytesRecieved==SOCKET_ERROR)
        {
            std::cerr<<"unable to recieve Err#"<<GetLastError()<<std::endl;
            break;
        }
        else if(BytesRecieved==0)
        {
            std::cout<<"Client disconnected"<<std::endl;
            break;
        }
        if(Input_Specifier==0)//saving name
        {
            temp.Set_Name(buffer);
         //   std::cout<<"NAME: "<<std::string(buffer,0,BytesRecieved)<<std::endl;
            Input_Specifier=1;
        }
        else if(Input_Specifier==1)//saving amount
        {
            counter++;
            temp.Set_Amount(atoi(buffer));
           // std::cout<<"Amount: "<<std::string(buffer,0,BytesRecieved)<<std::endl;
            BankA.push_back(temp);
            Input_Specifier=0;
                std::cout<<counter<<")";
                BankA.back().display();

        }
        //echo back
        send(ClientSocket,buffer,BytesRecieved+1,0);

    }
    closesocket(ClientSocket);
    WSACleanup();
    system("pause");
}