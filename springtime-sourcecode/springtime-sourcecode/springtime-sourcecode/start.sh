#!/bin/bash
docker build -t springtime .
docker run -p 8080:8080 -t springtime
