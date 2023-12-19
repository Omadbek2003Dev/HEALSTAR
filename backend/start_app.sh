#!/bin/bash

gcc -o http_request http_request.c $(pkg-config --libs --cflags libcurl json-c)