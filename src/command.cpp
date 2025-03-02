#include "command.h"


void Command::generate_uid() { this->m_text = "A" + std::to_string(++m_uid) + " "; }

Command* Command::p_command{ nullptr};

Command::Command(){}
Command::~Command(){}

void Command::set_text(std::string text){
  this->m_text.append(text);
}

std::string Command::get_text(){
  return this->m_text;
}

int Command::m_uid = 0;

void Command::set_command_type(CommandType command_type){
  this->m_command_type = command_type;
}

CommandType Command::get_command_type(){
  return this->m_command_type;
}
