#include "../../include/lib_base.h"
#include "../../include/ip_address.h"
#include "../../include/tcp_client.h"
#include "../../include/enum_classes.h"

int main(int argc , char *argv[])
{
  int mode  = 0;
  std::string input;
  std::stringstream msg;

  if((argc != 4) || ((strcmp(argv[1],"v4") != 0) && (strcmp(argv[1],"v6") != 0)) )
  {
      std::cout << "[-] usage: " << argv[0] << " <mode> <address> <port>" << "\n";
      _exit (1);
  }

    mode = (strcmp(argv[1],"v4") == 0) ? AF_INET : AF_INET6;
    ip_address server_addr(argv[2] , argv[3] , mode , SOCK_STREAM );
    tcp_client maxTCli(mode);

    maxTCli.connect(server_addr);
    std::cout << "[+] Welcome to maxClient!" << "\n";
    std::cout << "[+] Type 'quit' to close the connection..:" << "\n";

    loop_always()
    {
      try
      {
        std::cout << "> ";
        std::getline(std::cin , input);

        if(std::cin.eof())
        {
          std::cout << "CTRL-D" << "\n";
          break;
        }

        if(input.empty()) continue;

        CLEAR_MSG(msg);
        if(strcmp(input.c_str(),"quit") == 0)
        {
          msg << "CLOSE" << " " << "\n";
        }
        else
        {
          msg << "NUM" << " " << input << "\n";
        }

        maxTCli.send_message(msg.str());

        std::vector<std::string> message;
        message = maxTCli.receive_message();

        if(strcmp(message[0].c_str(),"ACK") == 0)
        {
          if(strcmp(message[1].c_str(),"CLOSE") == 0)
          {
            std::cout << "[-] Connection closed. Bye Bye! " << "\n";
            break;
          }
          else if(strcmp(message[1].c_str(),"MAX") == 0)
          {
            std::cout << "[x] Server response: " << message[2] << "\n";
          }
        }
        else if(strcmp(message[0].c_str(),"ERR") == 0)
        {
          if(strcmp(message[1].c_str(),"NAN") == 0)
          {
            std::cout << "[-] Input is not a number" << "\n";
            continue;
          }
        }

      }
      catch(generic_exception & e)
      {
        switch(e.get_errcode())
        {
          case socket_status_t::BAD_READ:
            std::cout << "[-] Server Shutdown " << "\n";
            _exit (1);
        }
      }
}
 return 0;

}
