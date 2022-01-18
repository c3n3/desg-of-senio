# Setup
sudo apt install npm

sudo apt install cmake

sudo npm install -g @vue/cli

sudo apt install git
sudo apt install gcc
sudo apt install g++
sudo apt install cmake
sudo apt install libjsoncpp-dev
sudo apt install uuid-dev
sudo apt install openssl
sudo apt install libssl-dev
sudo apt install zlib1g-dev

git clone https://github.com/drogonframework/drogon.git

cd drogon
git submodule update --init
mkdir build
cd build
cmake ..
make && sudo make install

cd ..

cd ..../generic_automation/exec/Website/vue-source
npm install 
cd ..

# Run
./deploy.sh