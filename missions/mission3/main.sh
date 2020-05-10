#!/bin/bash

grep -Po ">#.*?(?=<)" museomarco.html | sed "s/^>//" | sort | uniq -c