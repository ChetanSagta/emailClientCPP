#pragma once
#include <string>
 
enum CommandType {
  CAPABILITY,
  LOGIN,
  FETCH,
  STARTTLS,
  NOOP
};

class Command {

public:
  std::string toString();
  void generate_uid();
  void set_text(std::string);
  void set_command_type(CommandType);
  CommandType get_command_type();
  std::string get_text();
  Command();
  ~Command();
  
private:
  static Command *p_command;
  static int m_uid;
  std::string m_text;
  CommandType m_command_type;
};
