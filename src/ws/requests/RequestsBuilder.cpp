#include "ws/requests/RequestsBuilder.hpp"

std::string RequestsBuilder::basicRequest(const std::string& requestId, const std::string& method)
{
    nlohmann::json requestBody = {
        {"id", requestId},
        {"method", method}
    };

    return requestBody.dump();
}

std::string RequestsBuilder::paramsUnsignedRequest(const std::string& requestId, const std::string& method, const nlohmann::json& params)
{
    nlohmann::json requestBody = {
        {"id", requestId},
        {"method", method},
        {"params", params}
    };
    return requestBody.dump();
}

std::string RequestsBuilder::paramsSignedRequest(const std::string& requestId, const std::string& method, const std::map<std::string, std::string>& params)
{
    if (instance == nullptr) {
        LOG_ERROR("[REQUESTS_BUILDER] Singleton is not yet initialized.");
        return "";
    }

    auto signedParams = params;
    signedParams.insert({"apiKey", instance->apiKey_});
    signedParams.insert({"timestamp", getTimestamp()});

    std::string payload = generatePayload(params);
    std::string signature = instance->signatureKey_->sign(payload);
    signedParams.insert({"signature", signature});

    nlohmann::json requestBody = {
        {"id", requestId},
        {"method", method},
        {"params", params},
    };
    return requestBody.dump();
}

std::string RequestsBuilder::generatePayload(const std::map<std::string, std::string>& params) {
    return std::accumulate(
        params.begin(),
        params.end(),
        std::string(),
        [](const std::string& acc, const std::pair<std::string, std::string>& param) {
            return acc.empty()
                ? param.first + "=" + param.second
                : acc + "&" + param.first + "=" + param.second;
        });
}

std::string RequestsBuilder::getTimestamp(){
    auto now = std::chrono::system_clock::now();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    return std::to_string(milliseconds);
}
