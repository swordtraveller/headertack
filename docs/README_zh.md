# README

## 图示

<img src="assets/demo.gif" style="width: 60dvw; height: auto;" />

## 使用说明

|键位|作用|
|---|---|
|↑|向上滚动|
|↓|向下滚动|
|g|滚动到顶部|
|G|滚动到底部|
|q|退出|

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
