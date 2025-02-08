#include "emailclient.h"
#include <iostream>
#include <thread>

int main() {
  std::string hostname = "imap.gmail.com";
  std::string port = "993";

  const SSL_METHOD* ssl_method = TLS_client_method();
  EmailClient *emailClient  = new EmailClient(ssl_method, hostname, port);

  emailClient->run();
  return 0;
} 
