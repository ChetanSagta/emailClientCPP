#pragma once
#include <string>
 
enum CommandType {
  CAPABILITY,
  LOGIN
};

inline const std::string ToString(CommandType v) {
    switch (v)
    {
        case CAPABILITY:   return "Capability";
        case LOGIN:   return "";
        default:      return "[Unknown CommandType]";
    }
}

class Command {

public:
  void createCommand(CommandType);
  std::string toString();
  std::string generate_uid();
  Command();
  ~Command();
  
private:
  static Command *p_command;
  int m_uid = 0;
  std::string m_text;
  CommandType m_command_type;
};

