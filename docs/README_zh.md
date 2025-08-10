# README

## 从源码编译安装

```
sudo apt update -y
sudo apt install -y cmake pkg-config
sudo apt install -y libncurses5-dev libncursesw5-dev
mkdir build && cd build
cmake ..
cmake --build .
sudo ln -s "$(pwd)/headertack" /usr/local/bin/headertack
```
