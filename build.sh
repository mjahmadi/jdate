#!/bin/bash

gcc main.c -o jdate
strip ./jdate

help2man ./jdate

