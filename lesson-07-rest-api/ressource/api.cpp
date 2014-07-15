#include "api.hpp"

API::API()

{
}
void API::handleRequest (const Wt::Http::Request &request, Wt::Http::Response &response)
{
     response.out() << "{\"name\": \"Super man\", \"age\": 12}";
}
