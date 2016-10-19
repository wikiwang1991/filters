/* Copyright © 2016 Wiki Wang <wikiwang@live.com>
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * the COPYING file for more details. */

#include "PcapGraph.h"
#include <UdpParser/UdpParser.h>
#include <RtpParser/RtpParser.h>
#include <FecReceiver/FecReceiver.h>
#include <RtpH264/RtpH264.h>
#include <FileSink/FileSink.h>

PcapGraph::PcapGraph(const char *file) {
    f = new filters::FileSource(file);
    p = new filters::PcapParser;
    lsp = new filters::LinuxSllParser;
    ip = new filters::IpParser;
    ip->setListener(this);

    p->setSource(f, 0);
    p->setSink(0, lsp, 0);
    lsp->setSink(0, ip, 0);

    p->run();
}

PcapGraph::~PcapGraph() {
    p->stop();

    for (auto o : g)
        o->release();
    ip->release();
    lsp->release();
    p->release();
    f->release();
}

long PcapGraph::onNotify(filters::Filter *sender, long msg, void *param) {
    switch (msg) {
    case filters::IpParser::NOTIFY_ID: {
        auto n = reinterpret_cast<filters::IpParser::Notify *>(param);
        if (n->protocol != 17) return -1;
        auto udp = new filters::UdpParser;
        udp->setListener(this);
        ip->setSink(n->id, udp, 0);
        g.push_back(udp);
        return 0;
    } case filters::UdpParser::NOTIFY_ID: {
        auto n = reinterpret_cast<filters::UdpParser::Notify *>(param);
        auto f = new filters::RtpParser;
        f->setListener(this);
        sender->setSink(n->id, f, 0);
        g.push_back(f);
        return 0;
    } case filters::RtpParser::NOTIFY_ID: {
        auto n = reinterpret_cast<filters::RtpParser::Notify *>(param);
        switch (n->type) {
        case 0: {
            return 1;
        }
        case 96: {
            return 1;
        }
        case 98: {
            auto f = new filters::FecReceiver;
            auto f1 = new filters::RtpH264;
            auto f2 = new filters::FileSink("dump.h264");
            sender->setSink(n->id, f, 0);
            f->setSink(0, f1, 0);
            f1->setSink(0, f2, 0);
            g.push_back(f);
            g.push_back(f1);
            g.push_back(f2);
            return 0;
        }
        default: return -1;
        }
    }
    default: return -1;
    }
}
