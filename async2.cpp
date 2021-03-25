/*
 * @Author: DukeHouse
 * @Date: 2021-03-22 16:43:08
 * @LastEditors: DukeHouse
 * @LastEditTime: 2021-03-22 16:45:20
 * @Description: Do not edit
 * @Sample output: Do not edit
 */
#include <iostream>
#include <future>
#include <thread>

int fun(int x) {
	x++;
	x *= 10;
	std::cout << std::this_thread::get_id() << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(5));
	return x;
}


int main()
{
	std::packaged_task<int(int)> pt(fun);         // 将函数打包起来
	std::future<int> fu = pt.get_future();        // 并将结果返回给future
	std::thread t(std::ref(pt), 1);
	std::cout << fu.get() << std::endl;
	std::cout << std::this_thread::get_id() << std::endl;
	t.join();
    
	return 0;
}