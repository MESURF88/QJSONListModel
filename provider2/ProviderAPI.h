#include "Provider_Export.h"
#include <memory>

extern "C" {

    class Provider
    {
    public:
        explicit Provider(void);
        ~Provider();
        Provider(const Provider& other);
        Provider &operator=(Provider rhs);

        DLIB_EXPORT static const char* GET(const char*);
    private:

        class ProviderImpl;
        std::unique_ptr<ProviderImpl> impl_;
    };

}


