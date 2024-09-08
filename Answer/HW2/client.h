#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <random>
#include "crypto.h"

class Server; // Forward declaration

class Client
{
public:
	Client(std::string id, const Server& server): _id(id), _server(&server){
		crypto::generate_key(public_key, private_key);
	}
	std::string get_id() const;
	std::string get_publickey() const;
	double get_wallet() const;
	std::string sign(std::string txt) const;
	bool transfer_money(std::string receiver, double value);
	size_t generate_nonce();
private:
	Server const* const _server;
	const std::string _id;
	std::string public_key;
	std::string private_key;
};

#endif //CLIENT_H
