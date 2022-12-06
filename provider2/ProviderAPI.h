#include "Provider_Export.h"
#include <memory>

extern "C" {

    class DLIB_EXPORT Provider
    {
    public:
        explicit Provider(void);
        ~Provider();
        Provider(const Provider& other);
        Provider &operator=(Provider rhs);

        const char* GET(const char*);
        const char* stuff(const char*);
    private:

        class ProviderImpl;
        std::unique_ptr<ProviderImpl> impl_;
    };

}


