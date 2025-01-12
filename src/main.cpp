#include "openssl/ssl.h"
#include <iostream>
#include <thread>

#include "sslclient.h"

int main() {
  std::string hostname = "imap.gmail.com";
  std::string port = "993";

  const SSL_METHOD* ssl_method = TLS_client_method();
  SSLClient *ssl_client = new SSLClient(ssl_method,hostname, port);

  std::cout<<"Connected to the hostname: " <<hostname<<std::endl;
  // Send data
  std::string request = "A001 CAPABILITY\r\n";
  ssl_client->write_ssl(request);
  ssl_client->read_ssl();

  return 0;
}
