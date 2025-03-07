#include "ws/requests/IRequests.hpp"
#include "ws/requests/RequestsBuilder.hpp"

namespace BNB::WS::Streams
{
    class Subscribe : public IRequest
    {
    public:
        Subscribe();
        std::string dump() const override;
    };

    class Unsubscribe : public IRequest
    {
    public:
        Unsubscribe();
        std::string dump() const override;
    };

    class ListSubscriptions : public IRequest
    {
    public:
        ListSubscriptions();
        std::string dump() const override;
    };

    class SetProperty : public IRequest
    {
    public:
        SetProperty(const std::string& property, const std::string& value);
        std::string dump() const override;
    };

}