#include "command.h"


std::string Command::generate_uid() { return "A" + std::to_string(++m_uid); }

void Command::createCommand(CommandType commandType) {
  m_text = ToString(commandType);
 }

Command* Command::p_command{ nullptr};

Command::Command(){}
Command::~Command(){}

std::string Command::toString() {
  return std::to_string(this->m_uid); + " " + ToString(this->m_command_type) + " " + this->m_text;
}
