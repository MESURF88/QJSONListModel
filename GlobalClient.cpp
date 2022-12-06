#include "GlobalClient.hpp"

GlobalClient::GlobalClient()
{
  mProvider = std::make_shared<Provider>();
}


GlobalClient::~GlobalClient()
{

}

std::shared_ptr<Provider> GlobalClient::getClient()
{
	return mProvider;
}
