#include "imap.h"
#include "sslclient.h"

bool IMAP::send_command(Command command) {
  this->m_client->write_ssl(command.toString());
  return false;
}

IMAP::IMAP(const SSL_METHOD *method, std::string hostname, std::string port) {
  this->m_client = new SSLClient(method, hostname, port);
}

void IMAP::noop(){
	Command *command = new Command();
	std::string uid = command->generate_uid();
	std::string command_str = "NOOP\r\n";
	this->m_client->write_ssl(uid+" "+command_str);
}

void IMAP::capability(){
	Command *command = new Command();
	std::string uid = command->generate_uid();
	std::string command_str = "CAPABILITY\r\n";
	std::string final_command = uid+" "+command_str;
	std::cout<<"final command: " + final_command<<std::endl;
	this->m_client->write_ssl(final_command);
}

void IMAP::fetch() {
  if (m_imapState != IMAP_State::SELECTED) {
    std::cout << "IMAP State Should be selected: " << std::endl;
    return;
  }
}

void IMAP::starttls() {
  if (m_imapState == IMAP_State::NOT_AUTHENTICATED) {
	// a002 STARTTLS
	std::cout<<"Creating StartTtls Command"<<std::endl;
	Command *command = new Command();
	std::string uid = command->generate_uid();
	std::string command_str = "STARTTLS\r\n";
	this->m_client->write_ssl(uid+" "+command_str);
  } else {
    std::cout << "The Client should be authenticated" << std::endl;
    return;
  }
}


void IMAP::login() {
}

void IMAP::read_response(){
  this->m_client->read_ssl();
}
