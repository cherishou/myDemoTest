// myCallbackfunction_test2.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <functional>
#include <set>
#include <memory>


/*�ص������ر��ʺ�ʵ����֮���ͨ��. ��֮���ͨ��, ��ͬ��ƽ̨�и��ԵĽ������, ����windows��MFC, ������Ͱ��������Ļص���������, ��֤��֮���ͨ��. ����, ʵ��һ���Զ���Ļص���������, ���л�����ͨ��.

���ⱳ��:
��һ������������, ��������һϵ�еĿͻ��˵ļ���. �Ƿ�Ͽ���������������ɿͻ��˾���. 
����ͻ�������Ͽ�����, ��ô��������Ҫ����Ҫ�Ͽ����ӵĿͻ��˴Ӽ����н�������. ���������һ������, 
����Ͽ����ǿͻ���, ��ִ��������Ƿ�����, ���ǿͻ����޷�ֱ��ִ�з�������������. Ψһ��������, ֪ͨ��������������.

˼·:
��������������һ��������������ָ���Ŀͻ���, Ȼ������������Ϊ�ص��������ݸ��ͻ���, ����Ϊ�������������. �ͻ�������Ͽ�����ʱ, ִ�з�����������������󼴿�.

ע��, ����˵�Ŀͻ�����RPC�����ϵĿͻ���, ��ô������Ϊ�˷���������, ��Ҳ��C\S�ܹ����õ�һ������.

������ע��һ���ط�, ������Ҫ��֤�ص���ʱ��, ��ɾ���ĶϿ����ӵĺ���, �����Client�ڲ����رȽϺ���. ��Ϊʹ������ָ��, �ڶ��ڴ��Ͽ���, ����ʹ���ڴ��ַ�ıȽ�, ����Ψһ�Ķ�λ��.*/




class Client {
public:
	void set_cbfunc(std::function<void()> f) {
		m_cbFunc = std::move(f);
	}

	void callback() {
		std::cout << "client callback id: " << id << std::endl;
		m_cbFunc();
	}

	// �ȽϺ���, ������Ϊ������ȷ���Ŀͻ���, �����������бȽ�
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

