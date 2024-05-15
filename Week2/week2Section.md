## Compilation

编译



## Arrays



## Strings



## CLI arguments

`stdlib`

- `atoi`, 将字符串转换为整数

```c
#incldue <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
  	if (argc != 2)
    {
      	printf("Usage: /mario number");
      	return 1;
    }
  	int height = atoi(argv[1]);
  	return 0;
}
```

