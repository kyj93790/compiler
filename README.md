# compiler
2022-2 Compiler : make TINY compiler for the C- language

##  Lexical Analyzer (Scanner)
- [x] recognize all tokens in C- language
- [x] handle comments (/* ... */) and white space
- [x] handle lexical errors
- [x] scanner should capture the line number of each lexeme correctly

---
##  Parser
- [x] generate the AST if there is no syntatic error in source code
- [x] should be able to handle syntatic errors correctly


Result of Tests

### Test 1)
#### Given test case
```
int a;

void main(int arg){
	a = a + 1;
}
```

```
Syntax tree:
    Variable Declare : a
        Type : int
    Function Declare : main
        Type : void
        Parameter : arg
            Type : int
        Compound Statement
            Assign : =
                Variable : a
                Additive Expression
                    Variable : a
                    Operator : +			
                    Constant : 1
```

### Test 2)
#### Array declaration, assignment, expression

```
int a;

void main(int arg){
	int b[10];

	b[0] = 7;
	b[1] = 2;
	b[2] = b[0] + b[1];
}
```

```
Syntax tree:
    Variable Declare : a
        Type : int
    Function Declare : main
        Type : void
        Parameter : arg
            Type : int
        Compound Statement
            Array Variable Declare (Name, size): (b, 10)
                Type : int
            Assign : =
                Array Variable : b
                    Constant : 0
                Constant : 7
            Assign : =
                Array Variable : b
                    Constant : 1
                Constant : 2
            Assign : =
                Array Variable : b
                    Constant : 2
                Additive Expression
                    Array Variable : b
                        Constant : 0
                    Operator : +			
                    Array Variable : b
                        Constant : 1
```

### Test 3)
#### Given test case
```
void main(void)
{
	int a;
	int b;
	int c;
	int d;
	int e;

	if(a != 1)
		if(b != 2)
			if(c != 3)
				if(d == 4)
					e = 5;
				else
					e = 4;
}
```

```
Syntax tree:
    Function Declare : main
        Type : void
        Compound Statement
            Variable Declare : a
                Type : int
            Variable Declare : b
                Type : int
            Variable Declare : c
                Type : int
            Variable Declare : d
                Type : int
            Variable Declare : e
                Type : int
            If
                Simple Expression
                    Variable : a
                    Operator : !=			
                    Constant : 1
                If
                    Simple Expression
                        Variable : b
                        Operator : !=			
                        Constant : 2
                    If
                        Simple Expression
                            Variable : c
                            Operator : !=			
                            Constant : 3
                        If
                            Simple Expression
                                Variable : d
                                Operator : ==			
                                Constant : 4
                            Assign : =
                                Variable : e
                                Constant : 5
                            Assign : =
                                Variable : e
                                Constant : 4

```


### Test 4)
#### Given test case

```
void main(void)
{
	int a;
	for(;){
		break;
	}
}
```

```
Syntax error at line 4: syntax error
Current token: ;			;

Syntax tree:
```

### Test 5)
#### Multi arguments

```
void main(int a, int b)
{
	int c;
	int d;
	int e;

	if(a != 1)
		if(b != 2)
			if(c != 3)
				if(d == 4)
					e = 5;
				else
					e = 4;
}
```

```
Syntax tree:
    Function Declare : main
        Type : void
        Parameter : a
            Type : int
        Parameter : b
            Type : int
        Compound Statement
            Variable Declare : c
                Type : int
            Variable Declare : d
                Type : int
            Variable Declare : e
                Type : int
            If
                Simple Expression
                    Variable : a
                    Operator : !=			
                    Constant : 1
                If
                    Simple Expression
                        Variable : b
                        Operator : !=			
                        Constant : 2
                    If
                        Simple Expression
                            Variable : c
                            Operator : !=			
                            Constant : 3
                        If
                            Simple Expression
                                Variable : d
                                Operator : ==			
                                Constant : 4
                            Assign : =
                                Variable : e
                                Constant : 5
                            Assign : =
                                Variable : e
                                Constant : 4

```

### Test 6)
#### Multi else

```
void main(int a, int b)
{
	int c;
	int d;
	int e;

	if(a != 1)
		if(b != 2)
			if(c != 3)
				if(d == 4)
					e = 5;
				else
					e = 4;
			else
				e = 7;
}
```

```
Syntax tree:
    Function Declare : main
        Type : void
        Parameter : a
            Type : int
        Parameter : b
            Type : int
        Compound Statement
            Variable Declare : c
                Type : int
            Variable Declare : d
                Type : int
            Variable Declare : e
                Type : int
            If
                Simple Expression
                    Variable : a
                    Operator : !=			
                    Constant : 1
                If
                    Simple Expression
                        Variable : b
                        Operator : !=			
                        Constant : 2
                    If
                        Simple Expression
                            Variable : c
                            Operator : !=			
                            Constant : 3
                        If
                            Simple Expression
                                Variable : d
                                Operator : ==			
                                Constant : 4
                            Assign : =
                                Variable : e
                                Constant : 5
                            Assign : =
                                Variable : e
                                Constant : 4
                        Assign : =
                            Variable : e
                            Constant : 7

```

### Test 7)
#### Declaration with assignment

```
void main(int a, int b)
{
	int c = 0;
	int d;
	int e;

	if(a != 1)
		if(b != 2)
			if(c != 3)
				if(d == 4)
					e = 5;
				else
					e = 4;
			else
				e = 7;
}
```

```
Syntax error at line 3: syntax error
Current token: =			=

Syntax tree:
```

### Test 8)
#### Function call

```
int a;

void func(int x){
	int test;
}

void main(int arg){
	a = a + 1;
	func(a);
}
```

```
Syntax tree:
    Variable Declare : a
        Type : int
    Function Declare : func
        Type : void
        Parameter : x
            Type : int
        Compound Statement
            Variable Declare : test
                Type : int
    Function Declare : main
        Type : void
        Parameter : arg
            Type : int
        Compound Statement
            Assign : =
                Variable : a
                Additive Expression
                    Variable : a
                    Operator : +			
                    Constant : 1
            Call : func
                Variable : a
```

### Test 9)
#### Function call argument with expression

```
int a;

void func(int x){
	int test;
}

void main(int arg){
	a = a + 1;
	func(a + 3);
}
```

```
Syntax tree:
    Variable Declare : a
        Type : int
    Function Declare : func
        Type : void
        Parameter : x
            Type : int
        Compound Statement
            Variable Declare : test
                Type : int
    Function Declare : main
        Type : void
        Parameter : arg
            Type : int
        Compound Statement
            Assign : =
                Variable : a
                Additive Expression
                    Variable : a
                    Operator : +			
                    Constant : 1
            Call : func
                Additive Expression
                    Variable : a
                    Operator : +			
                    Constant : 3

```

### Test 10)
#### Function call argument with assignment

```
int a;

void func(int x){
	int test;
}

void main(int arg){
	a = a + 1;
	func(a = 3);
}
```

```
Syntax tree:
    Variable Declare : a
        Type : int
    Function Declare : func
        Type : void
        Parameter : x
            Type : int
        Compound Statement
            Variable Declare : test
                Type : int
    Function Declare : main
        Type : void
        Parameter : arg
            Type : int
        Compound Statement
            Assign : =
                Variable : a
                Additive Expression
                    Variable : a
                    Operator : +			
                    Constant : 1
            Call : func
                Assign : =
                    Variable : a
                    Constant : 3
```

### Test 11)
#### Iteration(while)

```
int a;

void func(int x){
	int test;
}

void main(int arg){
	a = 1;
	while (a < 5) {
		a = a + 1;
	}
	return ;
}
```

```
Syntax tree:
    Variable Declare : a
        Type : int
    Function Declare : func
        Type : void
        Parameter : x
            Type : int
        Compound Statement
            Variable Declare : test
                Type : int
    Function Declare : main
        Type : void
        Parameter : arg
            Type : int
        Compound Statement
            Assign : =
                Variable : a
                Constant : 1
            Iteration Statement
                Simple Expression
                    Variable : a
                    Operator : <			
                    Constant : 5
                Compound Statement
                    Assign : =
                        Variable : a
                        Additive Expression
                            Variable : a
                            Operator : +			
                            Constant : 1
            Return Statement

```

### Test 12)
#### Return value

```
int a;

void func(int x){
	int test;
}

int main(int arg){
	a = 1;
	while (a < 5) {
		a = a + 1;
	}
	return 0;
}
```

```
Syntax tree:
    Variable Declare : a
        Type : int
    Function Declare : func
        Type : void
        Parameter : x
            Type : int
        Compound Statement
            Variable Declare : test
                Type : int
    Function Declare : main
        Type : int
        Parameter : arg
            Type : int
        Compound Statement
            Assign : =
                Variable : a
                Constant : 1
            Iteration Statement
                Simple Expression
                    Variable : a
                    Operator : <			
                    Constant : 5
                Compound Statement
                    Assign : =
                        Variable : a
                        Additive Expression
                            Variable : a
                            Operator : +			
                            Constant : 1
            Return Statement
                Constant : 0
```
