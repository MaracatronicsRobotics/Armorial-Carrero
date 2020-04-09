# Armorial-Carrero
[![Build Status](https://travis-ci.com/maracatronics/Armorial-Carrero.svg?branch=master)](https://travis-ci.com/maracatronics/Armorial-Carrero)

This repository contains the software used by Maracatronics Robotics Team and Research Lab to receive packages from SSL-Vision System used by Small Size League.

## Release 1.0
This release contain a full functional software that can be used by the teams of RoboCup Small Size Soccer League. This software contains a thread to handle with information packages sended by SSLVsion software, four filters to avoid problems with robots blinking in the image. They are listed below:
    - Kalman Filter
    - MultiObject Filter
    - Noise Filter
    - Loss Filter

A brief description about each filter can be found at GithubWiki. 

## Armorial-Project:


## Dependencies:

### Ubuntu Dependencies (You can install using apt)
* Google Protobuf
* qt5-default
* libqt5opengl5-dev
* libprotobuf-dev 
* protobuf-compiler
* build-essential 
* libsfml-dev

### Instaling GearSystem
This Lib was created By Warthog Robotics and was modificated by Maracatronics to attend our necessity.

```bash
git clone https://github.com/maracatronics/GEARSystem.git
cd GEARSystem && cd trunk
sh build/corba_skeletons.sh
qmake install_path=/usr/lib/
make -j4
sudo sh install.sh
```

### Instaling WRBackbone
This Lib was created By Warthog Robotics and was modificated by Maracatronics to attend our necessity. It allows communication between all modules of Armorial-Project. 

```bash
git clone https://github.com/maracatronics/GEARSystem.git
cd GEARSystem && cd trunk
sh build/corba_skeletons.sh
qmake install_path=/usr/lib/
make -j4
sudo sh install.sh
```



## Compiling Armorial-Carrero

- Step 1: Install all dependencies

- Step 2: Compiling 
```bash
git clone https://github.com/maracatronics/Armorial-Carrero.git
sudo sh protobuf.sh

mkdir build
cd build
qmake ..
make
```
- Step 3: Run WRBackbone
```bash
./bin/Armorial-Carrero
```