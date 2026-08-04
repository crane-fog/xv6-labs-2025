# 0. 环境搭建

实验使用一台独立的 Linux 系统主机

> OS: Debian GNU/Linux 13 (trixie) x86_64  
> Kernel: Linux 6.12.94+deb13-amd64  
> CPU: Intel(R) N150 (4) @ 3.60 GHz  
> GPU: Intel Graphics @ 1.00 GHz [Integrated]  
> Memory: 7.55 GiB  
> Disk (/): 225.07 GiB - ext4

安装依赖

```bash
sudo apt-get install git build-essential gdb-multiarch \
    qemu-system-misc gcc-riscv64-linux-gnu binutils-riscv64-linux-gnu
```

拉取源码仓库

```bash
git clone git://g.csail.mit.edu/xv6-labs-2025
```

> 个人代码仓库
> https://github.com/crane-fog/xv6-labs-2025
