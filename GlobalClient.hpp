#ifndef _GLOBAL_CLIENT_H
#define _GLOBAL_CLIENT_H
#include <memory>
#include "ProviderAPI.h"

class GlobalClient
{

public:
    GlobalClient();
	~GlobalClient();
    std::shared_ptr<Provider> getClient();
private:
    std::shared_ptr<Provider> mProvider;
};
#endif
