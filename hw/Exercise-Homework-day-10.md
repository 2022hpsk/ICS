# Exercise-Homework-day-10

##  17.2 

​	NO. At second and subsequent calls they are same,because the address of the function itself is same, we should return that address if we want to recurse. But they are different from last call because we should retain main function at first call's ending.

##  17.8 

```c
int fibo(int n)
{
	int a = 1;
	int b = 1;
	int c = 0;
	if (n == 0) return a;
	else if (n == 1)
	return b;
	else{
		for (int i = 1; i < n; i++){
			c = a + b;
			a = b;
			b = c;
		}
		return c;
	}
}
```

In the cases that n is small, the running time is similar. When the n is very big, the recursion is
slower.
Two reasons:

1. If you call n times recursively,you need to allocate n local variables, n formal parameters, n call function addresses, and n return values, which is bound to affect efficiency.

2. the time complexity of recursion is exponential, but the complexity of iteration is n,which is linear.

##  17.12 

a. No such ```arg```

b. 6 times

c. output: 4

##  17.14

```
9
7
5
3
1
2
4
6
8
10
```

