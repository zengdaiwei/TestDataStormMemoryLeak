//
// Copyright (c) ZeroC, Inc. All rights reserved.
//
#include <DataStorm/DataStorm.h>

/* ObjectAssembly read from topic GetObject(string)
*  upon each GetObject, create an ObjectClass
*  ObjectClass writes data*/

using namespace std;

#include "ObjectAssembly.h"

int
main(int argc, char* argv[])
{
    try
    {
        DataStorm::Node node(argc, argv);
        ObjectAssembly assembly(node);
        node.waitForShutdown();
    }
    catch(const std::exception& ex)
    {
        cerr << ex.what() << endl;
        return 1;
    }
    return 0;
}
