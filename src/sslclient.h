#pragma once

#include "openssl/ssl.h"
#include <iostream>

class SSLClient {

 public:
  SSLClient(const SSL_METHOD*, std::string hostname, std::string port);

  ~SSLClient();
  void read_ssl();
  int write_ssl(std::string request);

 private:
  const SSL_METHOD *m_method;
  SSL_CTX *m_context;
  SSL *m_ssl;
  BIO* m_bio;
  int m_ret;
  std::string m_hostname, m_port;
};
