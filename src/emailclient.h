#pragma once

#include "imap.h"
#include <openssl/ssl.h>

class EmailClient {

public:

  EmailClient(const SSL_METHOD* ssl_method, std::string hostname, std::string port);
  ~EmailClient();
  void run();
  void fetchEmail();
  void login();
 private:
  IMAP *m_imap;
  
};
