/*
 * Copyright (c) 2018 CCS/UPM - GMRV/URJC.
 *
 * Authors: Juan Pedro Brito Méndez <juanpedro.brito@upm.es>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#ifndef _LOGGER_
#define _LOGGER_

#include <iostream>
#include <sstream>
#include <memory>

//Must be done thread safe in the future!
namespace remo
{
  enum LOG_LEVEL
  {
    INFO,
    WARNING,
    DEBUG,
    ERROR
  };

  template < typename osT = std::ostream >
  class Logger
  {
      template < class T >
      void _log ( const T& x )
      {
        _stream << x;
      }

      template < class T, class... Ts >
      void _log ( const T& x, Ts... args )
      {
        _log ( x );
        _log ( args... );
      }
    public:
      Logger ( LOG_LEVEL logLevel_ = INFO, osT& stream_ = std::cout ):
        _logLevel ( logLevel_ ), _stream ( stream_ ) {};

      template < class... Ts >
      Logger& operator() ( LOG_LEVEL level_, Ts... args )
      {
        std::string msg = "";

        switch (( int ) level_ )
        {
          case LOG_LEVEL::INFO:msg = "--> [INFO]: ";
            break;
          case LOG_LEVEL::WARNING:msg = "  --> [WARNING]: ";
            break;
          case LOG_LEVEL::DEBUG:msg = "    --> [DEBUG]: ";
            break;
          case LOG_LEVEL::ERROR:msg = "      --> [ERROR]: ";
            break;
        }

        _log ( msg, args..., "\n" );
        _stream.flush ( );
        return *this;
      }

      void setLogLevel ( const LOG_LEVEL logLevel_ ) { _logLevel = logLevel_; };
      LOG_LEVEL getLogLevel ( ) { return _logLevel; };

      void setStream ( std::ostream& stream_ ) { _stream = &stream_; };
      std::ostream& getStream ( ) { return _stream; };

    protected:
      LOG_LEVEL _logLevel;
      std::ostream& _stream;
  };
  using log = Logger <>;
}

#endif
