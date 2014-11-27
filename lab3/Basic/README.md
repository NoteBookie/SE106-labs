##Tiny BASIC Interpreter

####我所做的对于Demo中bug的修改：

1. 对于1+1将会被demo中认为是储存起来的code（误判断为1），我会输出SYNTAX ERROR。
	```1+1
	SYNTAX ERROR
2. 对于关键字被作为变量名的情况，我做了特殊的判断：
	```let then = 1
	then: ONE OF KEYWORD
3. 对于run，clear，list等指令，我不会误认为其是program的指令
	```10 help
	11 clear
	12 run
	list
	//不会输出任何东西
4. 我能处理表达式带有空格的情况，也能区分printx（输出错误）等没有带空格的情况。
5. 空行输入不会产生syntax error。
6. 变量名中可以带有数字，但不能是第一位。
	```let n3 = 1
	print n3
	1
	let 3n = 1
	variable cannot start with numbers

####一些漏洞，诚实的说：

1. 面向对象的程度不够，代码不易于阅读。
2. 使用了比较多的substr和atoi函数，使代码显得丑陋。
3. 无尽的错误情况，没有一一测试：无法保证和demo的情况完全一致，也无法确定能处理所有的输入错误。
4. 由于完全复用了homework7的表达式树的代码，而其假定了算式的完全正确，我不能处理有关算式非法的错误（当然，除零和变量未定义可以处理）。对于print 3@3,我将会输出3（尽管demo也是这么做的）;然而有一些情况我会产生和demo不一样的错误提示信息，如print 3+-3,demo会输出SYNTAX ERROR，而我的代码会认为这是一个变量未定义。这是我和demo输出不同的最主要的一处地方，并且错误在我：因为Tree类的构建树和计算值均使用递归实现，而我对输出“算式非法”的错误感到无从下手…所幸非法的算式仍然会被报错——只是错误信息不一样了。
