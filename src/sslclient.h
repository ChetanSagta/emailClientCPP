#pragma once

#include "openssl/ssl.h"
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

class SSLClient {

 public:
  SSLClient(const SSL_METHOD*, std::string hostname, std::string port);

  ~SSLClient();
  int write_ssl(std::string request);
  void parse_response();
  void start_reading();
  void join_thread();
  void read_ssl();

 private:
  const SSL_METHOD *m_method;
  SSL_CTX *m_context;
  SSL *m_ssl;
  BIO* m_bio;
  int m_ret;
  std::string m_hostname, m_port;
  std::string m_response;
  std::mutex m_mtx;
  bool done, client_close;
  std::condition_variable m_cv;
  std::thread reading_thread;

};
