#!/bin/sh
cd vue-source
npm run build
cd ..
cp ./vue-source/dist/js/*.js ./content/built.js
mkdir build > /dev/null
cd build
cmake ..
make
./Website
