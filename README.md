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
        Parameter : argone
            Type : int
        Parameter : argtwo
            Type : int
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
