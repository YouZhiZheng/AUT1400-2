#include "client.h"
#include "server.h"



std::string Client::get_id() const
{
    return _id;
}

std::string Client::get_publickey() const
{
    return public_key;
}

double Client::get_wallet() const
{
    return _server->get_wallet(_id);
}

std::string Client::sign(std::string txt) const
{
     std::string signature = crypto::signMessage(private_key, txt);
     return signature;
}

bool Client::transfer_money(std::string receiver, double value)
{
    std::string trx{_id + "-" + receiver + "-" + std::to_string(value)};
    std::string signature = sign(trx);

    return _server->add_pending_trx(trx, signature);
}

size_t Client::generate_nonce()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> distrib;

    return distrib(gen);
}