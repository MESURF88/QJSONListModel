#include "pch.h"

#include <iostream>
#include "ProviderAPI.h"

static constexpr char tmpJSON1[] = "{ \"store\": {\"book\": [ { \"title\": \"Harry Potter and the Goblet of Fire\" }, {\"title\": \"Anders Game\"}, {\"title\": \"Bible\"} ] } }";


class Provider::ProviderImpl
{
public:
    ProviderImpl();
    const char* hello();

private:

};

Provider::ProviderImpl::ProviderImpl()
{

}

const char* Provider::ProviderImpl::hello()
{
    return tmpJSON1;
}

// this has to be below
static Provider instance;
Provider::Provider() : impl_(new ProviderImpl) {

}

Provider::~Provider() = default;

Provider::Provider(const Provider & other) : impl_(new ProviderImpl(*other.impl_)) {};

Provider& Provider::operator=(Provider rhs)
{
    swap(impl_, rhs.impl_);
    return *this;
}

const char* Provider::hello()
{
    return instance.impl_->hello();
}