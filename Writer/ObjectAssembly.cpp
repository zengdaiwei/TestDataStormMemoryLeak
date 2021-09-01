#include "ObjectAssembly.h"
#include "ObjectClass.h"
ObjectAssembly::ObjectAssembly(const DataStorm::Node& node)
	: m_node(node)
	, m_topic(node, "get")
	, m_reader(DataStorm::makeAnyKeyReader(m_topic))
{
	m_reader.onSamples(
		[this](const std::vector<DataStorm::Sample<std::string, std::string>>& samples)
		{
			for (const auto sample : samples)
			{
				auto key = sample.getKey();
				if (m_objects.count(key) == 0)
				{
					auto obj = std::make_shared<ObjectClass>(this, m_node, key);
					m_objects[key] = obj;
				}
			}
		},
		[this](const DataStorm::Sample<std::string, std::string>& sample)
		{
			auto key = sample.getKey();
			if (m_objects.count(key) == 0)
			{
				auto obj = std::make_shared<ObjectClass>(this, m_node, key);
				m_objects[key] = obj;
			}
		});
}
void ObjectAssembly::release(const std::string& key)
{
	m_objects.erase(key);
}
