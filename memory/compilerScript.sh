#!/bin/bash
g++ -O0 latency.cpp -o latency
g++ -O0 bandwidth.cpp -o bandwidth
g++ -O0 pagefault.cpp -o pagefault
sudo nice --19 ./latency
sudo nice --19 ./bandwidth
sudo nice --19 ./pagefault
