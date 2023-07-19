


# ew\_list

Universal linked list


test demo
```shell
gcc -I./src demo.c ./src/ew_list.c  -o demo
./demo
[1] name: (dog)
[2] name: (cat)
[3] name: (pig)
[4] name: (duck)
delete pig
free(0x556615774370)
[1] name: (dog)
[2] name: (cat)
[4] name: (duck)
free(0x556615774290)
free(0x556615774300)
free(0x5566157743e0)
```
