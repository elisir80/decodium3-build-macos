#ifndef WSJTX_LOGGING_HPP__
#define WSJTX_LOGGING_HPP__

#include <QtGlobal>

//
// Class WSJTXLogging - wraps application specific logging
//
class WSJTXLogging final
{
public:
  explicit WSJTXLogging ();
  ~WSJTXLogging ();

  WSJTXLogging (WSJTXLogging const&) = delete;
  WSJTXLogging& operator= (WSJTXLogging const&) = delete;

private:
  QtMessageHandler previous_qt_message_handler_ {nullptr};
};

#endif
