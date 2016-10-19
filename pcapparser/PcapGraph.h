/* Copyright © 2016 Wiki Wang <wikiwang@live.com>
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * the COPYING file for more details. */

#pragma once

#include <FileSource/FileSource.h>
#include <PcapParser/PcapParser.h>
#include <LinuxSllParser/LinuxSllParser.h>
#include <IpParser/IpParser.h>

#include <list>
#include <unordered_map>

class PcapGraph : public filters::Notify {
public:
    PcapGraph(const char *file);
    ~PcapGraph();

    long onNotify(filters::Filter *sender, long msg, void *param);

private:
    filters::Filter *f;
    filters::PcapParser *p;
    filters::LinuxSllParser *lsp;
    filters::IpParser *ip;

    std::list<filters::Object *> g;

};
