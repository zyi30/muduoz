#!/bin/bash

set -e              #一旦脚本中的任何命令返回非0（即失败）状态，脚本立即终止执行

export PATH=/opt/cmake-3.28.3/bin:$PATH  #把 cmake 路径加到 PATH：


echo "开始构建..."
if [ ! -d `pwd`/build ];then  # 如果 build 目录不存在，就创建它
    mkdir  `pwd`/build
fi

rm -rf `pwd`/build/*   # 清空 build 目录（防止旧的编译产物影响）

cd  `pwd`/build && cmake ..&&  make   # 进入 build 目录，使用 cmake 配置，并编译

#回到项目根目录
cd ..

#把头文件拷贝到 /usr/include/mymuduo   so库拷贝到/usr/lib   PATH
# 处理 /usr/include/mymuduo
if [ -f /usr/include/mymuduo ]; then
    echo "/usr/include/mymuduo 是文件，先删除"
    sudo rm /usr/include/mymuduo
fi

if [ ! -d /usr/include/mymuduo ]; then
    echo "创建目录 /usr/include/mymuduo"
    sudo mkdir /usr/include/mymuduo
else
    echo "/usr/include/mymuduo 目录已存在，跳过创建"
fi

sudo cp *.h /usr/include/mymuduo/

# 拷贝动态库
sudo cp lib/libmymuduo.so /usr/lib/

sudo ldconfig

echo "构建和安装完成！"