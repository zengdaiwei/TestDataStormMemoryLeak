#ifndef OBJECT_ASSEMBLY_HEADER
#define OBJECT_ASSEMBLY_HEADER

#include <DataStorm/DataStorm.h>

/* ObjectAssembly read from topic GetObject(string)
*  upon each GetObject, create an ObjectClass
*  ObjectClass writes data*/

using namespace std;

#include <unordered_map>
#include <memory>

class ObjectClass;
class ObjectAssembly
{
public:
	ObjectAssembly(const DataStorm::Node& node);
	void release(const std::string& key);
private:
    const DataStorm::Node& m_node;
	DataStorm::Topic<string, string> m_topic;
    DataStorm::MultiKeyReader<std::string, std::string> m_reader;
    std::unordered_map<std::string, std::shared_ptr<ObjectClass>> m_objects;
};
#endif // !OBJECT_ASSEMBLY_HEADER
