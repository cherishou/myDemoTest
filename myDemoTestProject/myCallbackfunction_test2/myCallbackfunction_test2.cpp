// myCallbackfunction_test2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <functional>
#include <set>
#include <memory>

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
		m_pClients.erase(p);
	}

	void start() {
		std::cout << "Before CallBack, Client num: " << m_pClients.size() << std::endl;
		for (auto &p : m_pClients) {
			std::cout << "client id: " << p->getId() << std::endl;
			p->callback();
		}
		std::cout << "After CallBackClient num: " << m_pClients.size() << std::endl;
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

    return 0;
}

