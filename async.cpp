/*
 * @Author: DukeHouse
 * @Date: 2021-03-22 16:51:08
 * @LastEditors: haodu_win7
 * @LastEditTime: 2021-03-23 15:25:26
 */
#include <iostream>
#include <future>
#include <chrono>
//声明一个std::promise对象pr1，其保存的值类型为int
std::promise<int> pr1;
//声明一个std::future对象fu1，并通过std::promise的get_future()函数与pr1绑定
std::future<int> fu1 = pr1.get_future();
 
void Thread_Fun1(std::promise<int> &p)
{
	//为了突出效果，可以使线程休眠5s
	std::this_thread::sleep_for(std::chrono::seconds(3));
 
	int iVal = 233;
	std::cout << "1__int:" << iVal << std::endl;
	//传入数据iVal
	p.set_value(iVal);
	
	// char * iStr = "asd";
	// std::cout << "2(char*)：" << iStr << std::endl;
	
	// p.set_value(iStr);

}
 
void Thread_Fun2(std::future<int> &f)
{
	//阻塞函数，直到收到相关联的std::promise对象传入的数据
	//std::this_thread::sleep_for(std::chrono::seconds(5));

	auto iVal = f.get();		//iVal = 233
	std::cout << "2__int:" << iVal << std::endl;

	// auto iStr = f.get();		//iVal = 233
	// std::cout << "收到数据(char*)：" << iStr << std::endl;
}
 
//创建一个线程t1，将函数Thread_Fun1及对象pr1放在线程里面执行
std::thread t1(Thread_Fun1, std::ref(pr1));
//创建一个线程t2，将函数Thread_Fun2及对象fu1放在线程里面执行
std::thread t2(Thread_Fun2, std::ref(fu1));

void initDevice(){
	//阻塞至线程结束
	t1.join();
}

void searchDevice(){
	t2.detach();
}

int main()
{
	initDevice();
	searchDevice();
	return 1;
}

