#!/bin/sh
cd vue-source \
&& npm run build \
&& cd .. \
&& cp ./vue-source/dist/js/*.js ./content/built.js \
&& mkdir build > /dev/null
cd lib/Common \
&& mkdir build > /dev/null
meson build
cd build && meson compile
cd ../../../
cd build \
&& cmake .. \
&& make \
&& sudo ./Website
