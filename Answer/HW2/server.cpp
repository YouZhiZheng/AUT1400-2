#include "server.h"
#include "client.h"

std::shared_ptr<Client> Server::add_client(std::string id)
{
    for(const auto &client: clients)
    {
        if(client.first->get_id() == id)
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distrib(1000, 9999);
            
            id += std::to_string(distrib(gen));
            break;
        }
    }

    std::shared_ptr<Client> new_client = std::make_shared<Client>(id, *this);
    clients.insert({new_client, 5.0});
    return new_client;
}

std::shared_ptr<Client> Server::get_client(std::string id) const
{
    for(const auto &client: clients)
    {
        if(client.first->get_id() == id) return client.first;
    }

    return nullptr;
}

double Server::get_wallet(std::string id) const
{
    for(const auto &client: clients)
    {
        if(client.first->get_id() == id) return client.second;
    }

    std::cout << "The user does not exist" << std::endl;

    return -1;
}

bool Server::parse_trx(std::string trx, std::string &sender, std::string &receiver, double &value)
{
    // Regular expression matching pattern
    // NOTE: This regular expression is not robust enough
    std::regex pattern("^([a-zA-Z0-9_*@]+)-([a-zA-Z0-9_*@]+)-([0-9]+(?:\\.[0-9]+)?)$");
    std::smatch match;

    if (std::regex_match(trx, match, pattern) && match.size() == 4) 
    {
        sender = match[1];
        receiver = match[2];
        value = std::stod(match[3]);

        return true;
    } 
    else 
    {
        throw std::runtime_error("Invalid transaction format");
        return false;
    }
}

bool Server::add_pending_trx(std::string trx, std::string signature) const
{
    std::string sender, receiver;
    double value;

    if(!parse_trx(trx, sender, receiver, value)) return false; // Judge the transaction information format

    // Determine whether both parties to the transaction exist
    if(get_client(sender) == nullptr || get_client(receiver) == nullptr) return false; 

    // Determine whether this transaction was initiated by sender
    std::shared_ptr<Client> s_client = get_client(sender);
    bool authentic = crypto::verifySignature(s_client->get_publickey(), trx, signature);
    if(!authentic) return false;

    if(get_wallet(sender) < value) return false;

    pending_trxs.push_back(trx);
    return true;
}

/**
 * @brief The main function of this function is to mine. The steps are: 
 * 1. Connect all orders with transactions and store them in mempool. 
 * 2. Traverse each customer, obtain a nonce for each customer, add the nonce to the end of mempool, and calculate whether its hash value meets the requirements for successful mining (there are 3 consecutive 0s in the first 10 characters). 
 * 3. If someone successfully mines, process the order, output the miner's ID and return the nonce; if no one mines, repeat step 2 until someone mines.
 * 
 * @return size_t 
 */
size_t Server::mine()
{
    std::string mempool, hash;
    for(std::string &pending_trx: pending_trxs) mempool += pending_trx;

    size_t nonce;
    while(true)
    {
        for(auto &client: clients)
        {
            nonce = client.first->generate_nonce();
            hash = crypto::sha256(mempool + std::to_string(nonce));

            if(hash.substr(0, 10).find("000") != std::string::npos)
            {
                client.second += 6.25;
                std::cout << "mine id: " << client.first->get_id() << std::endl;
                
                std::string sender, receiver;
                double value;
                for(std::string &pending_trx: pending_trxs)
                {
                    if(parse_trx(pending_trx, sender, receiver, value) && get_wallet(sender) >= value)
                    {
                        clients[get_client(sender)] -= value;
                        clients[get_client(receiver)] += value;
                    }
                    else
                    {
                        std::cout << "this trx is error: " << pending_trx << std::endl;
                    }
                }

                pending_trxs.clear();
                return nonce;
            }
        }
    }
}