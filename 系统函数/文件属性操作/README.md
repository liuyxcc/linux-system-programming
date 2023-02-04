## access函数

```c
#include <unistd.h>

int access(const char *pathname, int mode);
```

- `pathname`：文件位置
- `mode`:
    - R_OK：判断是否有读权限
    - W_OK：判断是否有写权限
    - X_OK：判断是否有执行权限
    - F_OK：判断文件是否存在

成功返回0，失败返回-1。

## chmod函数

修改文件权限。

```c
#include <sys/stat.h>

int chmod(const char *pathname, mode_t mode);
```

- `pathname`：文件位置
- `mode`：需要修改的权限值，为一个八进制的数。

成功返回0，失败返回-1。

## truncate函数

对文件进行缩减或扩展。

```c
#include <unistd.h>
#include <sys/types.h>

int truncate(const char *path, off_t length);
```

- `pathname`：文件位置
- `length`：将文件修改后的大小