// myCallbackfunction_test2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <functional>
#include <set>
#include <memory>


/*回调函数特别适合实现类之间的通信. 类之间的通信, 不同的平台有各自的解决方案, 比如windows有MFC, 这里面就包含大量的回调函数机制, 保证类之间的通信. 这里, 实现一个自定义的回调函数机制, 进行基础的通信.

问题背景:
有一个服务器的类, 服务器有一系列的客户端的集合. 是否断开与服务器的连接由客户端决定. 
如果客户端申请断开连接, 那么服务器就要把需要断开链接的客户端从集合中进行清理. 这里就面临一个问题, 
申请断开的是客户端, 而执行清理的是服务器, 但是客户端无法直接执行服务器的清理工作. 唯一能做的是, 通知服务器进行清理.

思路:
服务器单独定义一个函数用于清理指定的客户端, 然后把这个函数作为回调函数传递个客户端, 保存为函数对象的类型. 客户端请求断开连接时, 执行服务器的这个函数对象即可.

注意, 这里说的客户端是RPC意义上的客户端, 这么抽象是为了方便程序设计, 这也是C\S架构常用的一个方法.

代码中注意一个地方, 我们需要保证回调的时候, 是删除的断开连接的函数, 因此在Client内部重载比较函数. 因为使用智能指针, 在堆内存上开辟, 所以使用内存地址的比较, 这是唯一的定位符.*/




class Client {
public:
	void set_cbfunc(std::function<void()> f) {
		m_cbFunc = std::move(f);
	}

	void callback() {
		std::cout << "client callback id: " << id << std::endl;
		m_cbFunc();
	}

	// 比较函数, 仅仅是为了区分确定的客户端, 方便在容器中比较
	inline bool operator<(const Client &client) {
		return bool(this < &client);
	}

	inline int getId() const {
		return id;
	}

	inline void setId(int id_) {
		id = id_;
	}

private:
	int id;
	std::function<void()> m_cbFunc;
};

class Server {
public:
	void callback(std::shared_ptr<Client> &p) {
		std::cout << "Server callback, id: " << p->getId() << std::endl;
	}

	void start() {
		std::cout << "Before CallBack, Client num: " << m_pClients.size() << std::endl;
		for (auto &p : m_pClients) {
			std::cout << "client id: " << p->getId() << std::endl;
			p->callback();
		}
		std::cout << "After CallBackClient num: " << m_pClients.size() << std::endl;
	}

	void destroyCB(std::shared_ptr<Client> &p)
	{
		m_pClients.erase(p);
	}
	

	std::set<std::shared_ptr<Client>> m_pClients;
};

int main()
{
	Server server;
	for (int i = 0; i < 5; ++i) {
		auto it = std::make_shared<Client>();
		it->setId(i);
		it->set_cbfunc(std::bind(&Server::callback, &server, it));
		server.m_pClients.insert(it);
	}
	server.start();

	server.destroyCB(std::make_shared<Client>());

	system("pause");

    return 0;
}

