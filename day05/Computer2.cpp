/*************************************************************************
	> File Name: Computer.cpp
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: Sun 09 Jan 2022 07:19:27 PM CST
 ************************************************************************/
#include <stdio.h>
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;


class Computer
{
public:
	Computer(const char * brand, double price)
	: _brand(new char[strlen(brand) + 1]())
	, _price(price)
	{
		cout << "Computer(const char *, float)" << endl;
		strcpy(_brand, brand);
		_totalPrice += _price;
	}

	Computer(const Computer & rhs)  //Computer & rhs = func1()
	: _brand(new char[strlen(rhs._brand) + 1]())
	, _price(rhs._price)
	{
		strcpy(_brand, rhs._brand);
		cout << "Computer(const Computer&)" << endl;
	}
	
	//赋值运算符函数 --> 三部曲
	Computer & operator=(const Computer & rhs)
	{
		if(this != &rhs)//自复制问题
		{
			delete [] _brand;//回收左操作数的申请的空间
			_brand = new char[strlen(rhs._brand) + 1]();//再进行深拷贝
			strcpy(_brand, rhs._brand);

			_price  = rhs._price;
		}
		return *this;
	}

	static void print(const Computer & rhs) {
		printf("_brand = %p\n", rhs._brand);	
		cout << "brand:" << rhs._brand << endl;
		cout << "price:" << rhs._price << endl;
	}
#if 1
	//const成员函数内部只能调用const成员
	void print(/*   Computer const * const this   */) const
	{
		cout << "void print() const" << endl;
		//this = 0x1000;//error
		//_price = 1000;//error
		printf("_brand = %p\n", _brand);	
		cout << "brand:" << _brand << endl;
		cout << "price:" << _price << endl;
	}
#endif


#if 0
	void print(/*  Computer * const this   */) 
	{
		cout << "void print()" << endl;
		//this = 0x1000;//error
		_price = 1000;
		printf("_brand = %p\n", _brand);	
		cout << "brand:" << _brand << endl;
		cout << "price:" << _price << endl;
	}
#endif

	//静态成员函数的参数列表之中不包含this指针
	//静态成员函数不能访问非静态数据成员，非静态成员函数
	//
	//只能访问静态数据成员和静态成员函数
	static void printTotalPrice()
	{
		cout << "总价:" << _totalPrice << endl;
	}

	~Computer()
	{
		delete [] _brand;
		_brand = NULL;
		cout << "~Computer()" << endl;
	}

private:
	char * _brand;
	double _price;

	static double _totalPrice;//全局/静态区，不会成为对象的一部分
};

//静态数据成员的初始化是在类之外进行的
double Computer::_totalPrice = 0;


void func(const Computer & rhs)
{
	rhs.print();
}
 

void test0(void)
{
	cout << "sizeof(Computer) = " << sizeof(Computer) << endl;
	Computer com1("Dell", 6666);//栈对象
	cout << ">> com1:";
	com1.print(com1);
	Computer::print(com1);//静态成员函数可以直接通过类名进行调用
	com1.printTotalPrice();
	Computer::printTotalPrice();
	cout <<endl;
	
	Computer com2("ASUS", 7777);
	cout << " >> com2:";
	com2.print(com2);
	Computer::print(com2);
	Computer::printTotalPrice();
	com2.printTotalPrice();


	Computer com3("Mac", 8888);
	cout << " >> com3:";
	com3.print(com3);
	Computer::print(com3);
	Computer::printTotalPrice();
	com3.printTotalPrice();
}


void test1(void)
{
	Computer com1("Dell", 6666);//如果只有const成员函数，非const对象是可以调用const成员函数的
	com1.print();	//当const版本和非const版本的成员函数同时出现时，非const对象调用非const成员函数
	cout << endl;

	const Computer com2("Mac", 9999);
	com2.print();//const对象只能调用const成员函数

}


int main(void)
{
	test1();

	return 0;
}


