#pragma once
#include <common.h>
#include <DynamicStringArray.hpp>


class Server_Client_Base
{
public:
    virtual boost::interprocess::managed_shared_memory *getSharedMemory() = 0;
    virtual boost::interprocess::message_queue *getMessageQueue() = 0;
    virtual bool deleteStringArray(int clientId, std::string input) { return false; }
    virtual std::string *getStringArrayEntry(int clientId, int index) { return nullptr; }
    virtual void setStringArrayEntry(int clientId, std::string input) {}
    virtual void createClientArray(int clientId) {}
    virtual std::map<int, std::shared_ptr<DynamicStringArray>> getClientArray() { return {}; }
    virtual void exitClient(){}
    virtual int getNumberOfClients() {return 0;}
    virtual ~Server_Client_Base() {}
};

class Server : public Server_Client_Base
{
private:
    int m_number_of_clients = 0;
    std::map<int, std::shared_ptr<DynamicStringArray>> m_ClientArray;
    std::unique_ptr<boost::interprocess::message_queue> m_mq;
    std::unique_ptr<boost::interprocess::managed_shared_memory> m_managed_smh;

public:
    Server()
    {
        boost::interprocess::shared_memory_object::remove(SHARED_MEMORY_NAME.c_str());
        boost::interprocess::message_queue::remove(MESSAGE_QUEUE_NAME.c_str());

        m_mq = std::make_unique<boost::interprocess::message_queue>(boost::interprocess::create_only, MESSAGE_QUEUE_NAME.c_str(), MAX_MESSAGE_NUMBER, MAX_MESSAGE_SIZE);
        m_managed_smh = std::make_unique<boost::interprocess::managed_shared_memory>(boost::interprocess::create_only, SHARED_MEMORY_NAME.c_str(), SHARED_MEMORY_SIZE);
    }

    boost::interprocess::managed_shared_memory *getSharedMemory() override
    {
        return m_managed_smh.get();
    }
    boost::interprocess::message_queue *getMessageQueue() override
    {
        return m_mq.get();
    }

    std::map<int, std::shared_ptr<DynamicStringArray>> getClientArray()
    {
        return m_ClientArray;
    }

    void setStringArrayEntry(int clientId, std::string input)
    {
        m_ClientArray[clientId]->addEntry(input);
    }

    std::string *getStringArrayEntry(int clientId, int index)
    {
        return m_ClientArray[clientId]->getEntry(index);
    }

    bool deleteStringArray(int clientId, std::string input)
    {
        return m_ClientArray[clientId]->deleteEntry(input);
    }

    void createClientArray(int clientId)
    {
        if (m_ClientArray.find(clientId) == m_ClientArray.end())
        {
            m_ClientArray.insert(std::make_pair(clientId, std::make_unique<DynamicStringArray>()));
            m_number_of_clients++;
        }
    }

    void exitClient() {
        m_number_of_clients--;
    }
    int getNumberOfClients() {
        return m_number_of_clients;
    }
};

class Client : public Server_Client_Base
{
private:
    std::unique_ptr<boost::interprocess::message_queue> m_message_queue;
    std::unique_ptr<boost::interprocess::managed_shared_memory> m_managed_smh;

public:
    Client()
    {
        m_message_queue = std::make_unique<boost::interprocess::message_queue>(boost::interprocess::open_only, MESSAGE_QUEUE_NAME.c_str());
        m_managed_smh = std::make_unique<boost::interprocess::managed_shared_memory>(boost::interprocess::open_only, SHARED_MEMORY_NAME.c_str());
    }
    boost::interprocess::managed_shared_memory *getSharedMemory() override
    {
        return m_managed_smh.get();
    }
    boost::interprocess::message_queue *getMessageQueue() override
    {
        return m_message_queue.get();
    }
};