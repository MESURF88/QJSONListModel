#include "pch.h"

#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <map>

#include "curl_easy.h"
#include "curl_form.h"
#include "curl_ios.h"
#include "curl_exception.h"
#include "ProviderAPI.h"

static constexpr char tmpJSON1[] = "{ \"store\": {\"book\": [ { \"title\": \"Harry Potter and the Goblet of Fire\" }, {\"title\": \"Anders Game\"}, {\"title\": \"Bible\"} ] } }";
static constexpr char tmpJSON2[] = "{ \"store\": {\"book\": [ { \"title\": \"Sherlock Holmes\" }, {\"title\": \"Experiencing God\"}, {\"title\": \"Jurassic Park\"}, {\"title\": \"Willy Wonka and the Chocolate Factory\"} ] } }";

class Provider::ProviderImpl
{
public:
    ProviderImpl();
    const char* GET(std::string entityName);

private:
    std::string mSecretURL;
};

Provider::ProviderImpl::ProviderImpl() : mSecretURL("")
{
    // read url from file
    std::ifstream urlfile("url.txt");
    std::getline(urlfile, mSecretURL);
    
    urlfile.close();
}

const char* Provider::ProviderImpl::GET(std::string entityName)
{
    if ((entityName == "entitya") || (entityName == "entityb"))
    {
        std::string uri = mSecretURL + entityName;
        std::stringstream str;
        curl::curl_ios<std::stringstream> writer(str);

        curl::curl_easy easy(writer);

        easy.add<CURLOPT_URL>(uri.c_str());
        easy.add<CURLOPT_FOLLOWLOCATION>(1L);
        try
        {
            easy.perform();
        }
        catch (curl::curl_easy_exception error)
        {
            auto errors = error.get_traceback();
            error.print_traceback();
        }
        return str.str().c_str();
    }
    else
    {
        return "";
    }
}

// this has to be below
Provider::Provider() : impl_(new ProviderImpl) {

}

Provider::~Provider() = default;

Provider::Provider(const Provider & other) : impl_(new ProviderImpl(*other.impl_)) {};

Provider& Provider::operator=(Provider rhs)
{
    swap(impl_, rhs.impl_);
    return *this;
}

const char* Provider::GET(const char* entityName)
{
    return impl_->GET(std::string(entityName));
}

const char* Provider::stuff(const char* entityName)
{
    return tmpJSON1;
}