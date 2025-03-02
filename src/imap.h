#pragma once

#include "sslclient.h"
#include <mutex>
#include <string>
#include <vector>
#include <map>
#include "command.h"

enum IMAP_State{
  NOT_AUTHENTICATED,
  AUTHENTICATED,
  SELECTED,
  LOGOUT
};



class IMAP {
public:
  IMAP(const SSL_METHOD* method, std::string hostname, std::string port);
  ~IMAP();

  bool send_command(Command command);
  void fetch();
  void starttls();
  void login();
  void noop();
  void capability();
  void read_response();

private:
  SSLClient *m_client;
  std::string m_response;			
  IMAP_State m_imapState;
  std::string username, password;
  std::map<std::string, CommandType> m_commands_written;
};
