/* Copyright © 2016 Wiki Wang <wikiwang@live.com>
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * the COPYING file for more details. */

#include "Thread.h"

namespace filters {

long Thread::run() {
    r = true;
    l.unlock();
    if (!t.joinable())
        t = std::thread(Thread::f, this);
    return 0;
}

long Thread::pause() {
    l.lock();
    return 0;
}

long Thread::stop() {
    r = false;
    l.unlock();
    t.join();
    return 0;
}

void Thread::f(Thread *t) {
    while (t->r) {
        t->l.lock();
        long ret = t->proc();
        t->l.unlock();
        if (ret) break;
    }
}

}
