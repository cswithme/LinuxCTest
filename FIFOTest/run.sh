#!/bin/bash

./pipe_read &
usleep 500000
./pipe_write
