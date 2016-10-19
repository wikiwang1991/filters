/* Copyright © 2016 Wiki Wang <wikiwang@live.com>
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * the COPYING file for more details. */

#pragma once

#include "Filter.h"
#include <thread>
#include <mutex>

namespace filters {

class Thread : public Controller {
public:
    long run();
    long pause();
    long stop();

    static void f(Thread *t);

protected:
    virtual long proc() = 0;

private:
    std::thread t;
    std::mutex l;
    bool r;
};

}
