## 利用stat函数实现 ls -l 命令

```shell
# 编译源文件
gcc ll.c -o ll

# 使用
./ll README.md

#其等价于
ll README.md 
ls -l README.md
```