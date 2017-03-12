sudo mkdir build
cd build
sudo cmake .. -DCMAKE_INSTALL_PREFIX=/usr/bin
sudo make clean
sudo make
sudo make install
sudo chmod 777 /usr/bin/curve_fix/run-TT-MD-live.sh
sudo chmod 777 /usr/bin/curve_fix/run-TT-live.sh
