#ifndef SERVER_H
#define SERVER_H

#include <memory>
#include <string>
#include <map>
#include <random>
#include <regex>

class Client; // Forward declaration

inline std::vector<std::string> pending_trxs;

class Server
{
public:
	Server(){}

    // INFO: Use the random library to generate random numbers
    // NOTE: each client should be assigned with 5 coins at the begining
	std::shared_ptr<Client> add_client(std::string id);

	std::shared_ptr<Client> get_client(std::string id) const;
	double get_wallet(std::string id) const;
    
	static bool parse_trx(std::string trx, std::string &sender, std::string &receiver, double &value);
    bool add_pending_trx(std::string trx, std::string signature) const;
	size_t mine();

private:
	std::map<std::shared_ptr<Client>, double> clients;
	friend void show_wallets(const  Server& server);
};

#endif //SERVER_H