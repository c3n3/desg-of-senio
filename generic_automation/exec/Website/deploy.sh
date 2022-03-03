#!/bin/sh
cd vue-source \
&& npm run build -- --mode development \
&& cd .. \
&& cp ./vue-source/dist/js/*.js ./content/built.js \
&& mkdir build > /dev/null
cd build \
&& cmake .. \
&& make \
&& sudo ./Website
