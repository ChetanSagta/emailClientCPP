#include "imap.h"
#include "command.h"
#include "sslclient.h"
#include <fstream>
#include <ios>
#include <unistd.h>

bool IMAP::send_command(Command command) {
  this->m_commands_written[command.get_text()]  = command.get_command_type();
  this->m_client->write_ssl(command.get_text()) ;
  return false;
}

IMAP::IMAP(const SSL_METHOD *method, std::string hostname, std::string port) {
  this->m_client = new SSLClient(method, hostname, port);
  this->m_imapState = IMAP_State::NOT_AUTHENTICATED;
}

void IMAP::noop() {
  Command *command = new Command();
  command->generate_uid();
  command->set_command_type(CommandType::NOOP);
  command->set_text("NOOP\r\n");
  send_command(*command);
}

void IMAP::capability() {
  Command *command = new Command();
  command->generate_uid();
  command->set_command_type(CommandType::CAPABILITY);
  command->set_text("CAPABILITY\r\n");
  this->send_command(*command);
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
    std::cout << "Creating StartTtls Command" << std::endl;
    Command *command = new Command();
    command->generate_uid();
    command->set_text("STARTTLS\r\n");
	command->set_command_type(CommandType::STARTTLS);
	this->send_command(*command);
  } else {
    std::cout << "The Client should be authenticated" << std::endl;
    return;
  }
}

void IMAP::login() {
  std::string login_file = "../resources/creds.txt";
  std::ifstream ifFile(login_file, std::ios::in);
  std::string line;
  int i = 0;
  if (ifFile.is_open()) {
    while (std::getline(ifFile, line)) {
      if (i == 0) {
        username = line.substr(line.find("=")+1, line.length() - 1);
      }
      if (i == 1) {
        password = line.substr(line.find("=")+1, line.length() - 1);
      }
      i++;
    }
  }
  Command *command = new Command();
  command->generate_uid();
  command->set_text("Login " + username + " " + password + "\r\n");
  command->set_command_type(CommandType::LOGIN);
  this->send_command(*command);
}

void IMAP::read_response() { this->m_client->read_ssl(); }
