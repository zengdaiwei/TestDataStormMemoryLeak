#include <DataStorm/DataStorm.h>

using namespace std;

int
main(int argc, char* argv[])
{
    try
    {
        DataStorm::Node node(argc, argv);
        DataStorm::Topic<string, string> topicGet(node, "get");
        DataStorm::Topic<string, string> topicData(node, "data");
        auto key = "myKey";
        auto reader = DataStorm::makeSingleKeyReader(topicData, key);
        auto writer = DataStorm::makeSingleKeyWriter(topicGet, key);
        writer.add(key);
        reader.onSamples(
            [](const std::vector<DataStorm::Sample<std::string, std::string>> & samples)
            {
                for (const auto sample : samples)
                {
                    std::cout << sample.getValue() << std::endl;
                }
            }, 
            [](const DataStorm::Sample<std::string, std::string> & sample)
            {
				std::cout << sample.getValue() << std::endl;
            });
        node.waitForShutdown();
        auto sample = reader.getNextUnread();
        cout << sample.getKey() << " says " << sample.getValue() << "!" << endl;
    }
    catch(const std::exception& ex)
    {
        cerr << ex.what() << endl;
        return 1;
    }
    return 0;
}
