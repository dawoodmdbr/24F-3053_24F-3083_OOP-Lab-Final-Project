#include "Stronghold.h"
using namespace std;
ResourceManager::ResourceManager(){
    for (int i = 0; i < RESOURCE_TYPE_COUNT; i++) {
        resources[i] = Resource(static_cast<ResourceType>(i), 100.0);
    }
}
void ResourceManager::gather()