#pragma once
#include <iostream>

#ifndef LOGTARGET
#define LOGTARGET std::cout
#endif // !LOGTARGET


#define TRACE(msg, line) LOGTARGET << "[TRACE]\t" << msg << \
" at: " << line << "\n"

#define ENTER(fkt) TRACE("ENTER " fkt, __LINE__)
#define EXIT(fkt) TRACE("EXIT " fkt, __LINE__)

#define CALL(fktcall) TRACE("CALL " #fktcall, __LINE__)