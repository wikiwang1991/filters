/* Copyright © 2016 Wiki Wang <wikiwang@live.com>
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * the COPYING file for more details. */

#include "PcapParser.h"
#include <pcap/pcap.h>
#include <arpa/inet.h>

namespace filters {

struct timeval {
    bpf_int32 tv_sec;	/* Seconds.  */
    bpf_int32 tv_usec;	/* Microseconds.  */
};

struct pcap_pkthdr {
	struct timeval ts;	/* time stamp */
	bpf_u_int32 caplen;	/* length of portion present */
	bpf_u_int32 len;	/* length this packet (off wire) */
};

long PcapParser::setSink(long io, Filter *f, long ii) {
    if (io) return -1;
    sink = f;
    sinkI = ii;
    return 0;
}

long PcapParser::setListener(Notify *)
{ return -1; }

long PcapParser::run() {
    b->setSize(sizeof(pcap_file_header));
    b->setLength(sizeof(pcap_file_header));
    src->onReceive(srcI, b);
    const pcap_file_header *h = reinterpret_cast<const pcap_file_header *>(b->buffer());
    if (h->magic != 0xa1b2c3d4 || h->linktype != DLT_LINUX_SLL) return -1;
    b->setSize(h->snaplen);
    src->setSink(srcI, this, 0);
    return Thread::run();
}

long PcapParser::onReceive(long id, Buffer *data) {
    // TODO: support async operation.
    return 0;
}

PcapParser::~PcapParser()
{ b->release(); }

long PcapParser::proc() {
    b->setLength(sizeof(pcap_pkthdr));
    src->onReceive(srcI, b);
    const pcap_pkthdr *h = reinterpret_cast<const pcap_pkthdr *>(b->buffer());
    b->setLength(h->caplen);
    b->setTimestamp(h->ts.tv_sec * 1000000 + h->ts.tv_usec);
    if (src->onReceive(srcI, b)) return -1;
    sink->onReceive(sinkI, b);
    return 0;
}

}
