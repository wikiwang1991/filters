/* Copyright © 2016 Wiki Wang <wikiwang@live.com>
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * the COPYING file for more details. */

#include "PcapGraph.h"

int main(int argc, char *argv[])
{
    if (argc < 2) return -1;

    PcapGraph g(argv[1]);

    getchar();

    return 0;
}
