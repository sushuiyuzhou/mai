//
// Created by suhuiyuzhou on 28/05/2020.
//

#ifndef MAI_UTILS_H
#define MAI_UTILS_H

#include <iostream>

namespace mai {

  enum log_level {
    DEBUG = 1,
    INFO = 2,
    WARN = 3,
    ERROR = 4
  };

  static const auto g_log_level = log_level::INFO; // TODO: make configurable

  class Logger {
  public:
      template<typename T = std::string>
      void log(T const& t = std::string{}, std::string const& msg = {})
      {
          if (_lv>=g_log_level) {
              if (!msg.empty()) {
                  _os << msg << " : " << t << std::endl;
              }
              else { // TODO: try constexpr if to check for member functions such as print()
                  _os << t << std::endl;
              }
          }
      }

  private:
      Logger(std::ostream& os, log_level lv)
              :_os{os}, _lv{lv} { }

      friend Logger& getLogger(log_level);

      log_level _lv;
      std::ostream& _os;
  };

  inline Logger& getLogger(log_level lv = log_level::INFO)
  {
      static Logger info_logger(std::cout, log_level::INFO);
      static Logger debug_logger(std::cout, log_level::DEBUG);

      switch (lv) {
      case log_level::INFO: return info_logger;
          break;
      case log_level::DEBUG: return debug_logger;
          break;
      }
  }

}

#endif //MAI_UTILS_H
