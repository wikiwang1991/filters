/* Copyright © 2016 Wiki Wang <wikiwang@live.com>
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * the COPYING file for more details. */

#include "IpParser.h"
#include <netinet/ip.h>

namespace filters {

size_t IpParser::Notify::hash::operator()(const IpParser::Notify &n) const {
    switch (n.version) {
    case IPVERSION: {
        size_t res = 17;
        res = res * 31 + n.protocol;
        res = res * 31 + n.saddr;
        res = res * 31 + n.daddr;
        return res;
    }
    default: return 0;
    }
}

bool IpParser::Notify::operator==(const IpParser::Notify &n) const {
    switch (n.version) {
    case 4:
        return n.protocol == n.protocol &&
                n.saddr == n.saddr && n.daddr == n.daddr;
    default: return false;
    }
}

long IpParser::onReceive(long id, Buffer *data) {
    if (id) return -1;
    iphdr *h = reinterpret_cast<iphdr *>(data->data());
    if (h->version != IPVERSION) return 0;
    long hl = sizeof(iphdr); // TODO: handle options.
    data->setPrefix(data->prefix() + hl);
    data->setLength(data->length() - hl);
    Notify n;
    n.version = IPVERSION;
    n.protocol = h->protocol;
    n.saddr = h->saddr;
    n.daddr = h->daddr;
    auto it = set.find(n);
    if (it == set.end()) {
        if (listener) {
            n.id = i;
            if (listener->onNotify(this, NOTIFY_ID, &n)) return 0;
            it = set.emplace(n).first;
            ++i;
        } else return 0;
    }
    long i = it->id;
    const auto &it1 = sinks.find(i);
    if (it1 == sinks.end()) return 0;
    const auto &pin = it1->second;
    return pin.f->onReceive(pin.i, data);
}

}
