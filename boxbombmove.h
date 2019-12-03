#ifndef BOXBOMBMOVE_H
#define BOXBOMBMOVE_H

#include <sys/types.h>
#include <utility>

struct BoxBombMove
{
    std::pair<size_t,size_t> pos;
    std::pair<size_t,size_t> newpos;
};

#endif // BOXBOMBMOVE_H
