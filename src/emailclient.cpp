#include "emailclient.h"
#include <chrono>
#include <cstdlib>
#include <ratio>
#include <thread>

EmailClient::EmailClient(const SSL_METHOD *ssl_method, std::string hostname,
                         std::string port) {
  m_imap = new IMAP(ssl_method, hostname, port);
}
void EmailClient::run() {
    std::thread listen_incoming_commands(&IMAP::read_response, m_imap); //
    std::this_thread::sleep_for(std::chrono::seconds(2));
    this->m_imap->capability();
    std::this_thread::sleep_for(std::chrono::seconds(2));
	this->m_imap->starttls();
    std::this_thread::sleep_for(std::chrono::seconds(2));
	this->m_imap->capability();
	listen_incoming_commands.join();
}

EmailClient::~EmailClient() {}

void EmailClient::fetchEmail() {}

