#ifndef OBJECT_CLASS_HEADER
#define OBJECT_CLASS_HEADER
#include "ObjectAssembly.h"
#include <thread>
#include <chrono>
class ObjectClass
{
public:
    ObjectClass(ObjectAssembly * assembly, const DataStorm::Node& node, const std::string &key)
        : m_assembly(assembly)
        , m_node(node)
        , m_key (key)
        , m_topic(node, "data")
        , m_writer(DataStorm::makeSingleKeyWriter(m_topic, key, "ObjectClassDataWriter", {1, Ice::nullopt, DataStorm::ClearHistoryPolicy::OnAdd}))
        , m_readerCount(0)
        , m_working(true)
        , m_thread(&ObjectClass::write, this)
    {
        m_writer.onConnectedReaders(
            [this](const std::vector<std::string>& readers) 
            {
                m_readerCount = readers.size();
            },
            [this](DataStorm::CallbackReason reason, const std::string&) 
            {
                switch (reason)
                {
                case DataStorm::CallbackReason::Connect:
                    ++m_readerCount;
                    break;
                case DataStorm::CallbackReason::Disconnect:
                    if (--m_readerCount == 0)
                    {
                        m_working = false;
                        m_thread.join();
                        m_assembly->release(m_key);
                    }
                    break;
                default:
                    break;
                }
            });
    }
    void write()
    {
        while (m_working)
        {
            m_writer.add("data" + std::to_string(time(NULL)));
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    void release()
    {

    }
private:
    ObjectAssembly* const m_assembly;
    const DataStorm::Node& m_node;
    const std::string m_key;
	DataStorm::Topic<string, string> m_topic;
    DataStorm::SingleKeyWriter<std::string, std::string> m_writer;
    int m_readerCount;
    bool m_working;
    std::thread m_thread;
};
#endif ! OBJECT_CLASS_HEADER
