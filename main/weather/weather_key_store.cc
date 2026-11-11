#include "weather_key_store.h"

#include "settings.h"

#include <algorithm>

std::string WeatherKeyStore::GetKey() const {
    Settings settings("weather", false);
    return settings.GetString("qweather_key");
}

void WeatherKeyStore::SetKey(const std::string& key) {
    Settings settings("weather", true);
    if (key.empty()) {
        settings.EraseKey("qweather_key");
    } else {
        settings.SetString("qweather_key", key);
    }
}

std::string WeatherKeyStore::GetHost() const {
    Settings settings("weather", false);
    return settings.GetString("qweather_host");
}

bool WeatherKeyStore::SetHost(const std::string& host) {
    const std::string suffix = ".qweatherapi.com";
    if (host.size() <= suffix.size() || host.size() > 100 ||
        host.compare(host.size() - suffix.size(), suffix.size(), suffix) != 0 ||
        !std::all_of(host.begin(), host.end(), [](char c) {
            return (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') ||
                   c == '-' || c == '.';
        }) || host.front() == '.' || host.find("..") != std::string::npos) {
        return false;
    }
    Settings settings("weather", true);
    settings.SetString("qweather_host", host);
    return true;
}

void WeatherKeyStore::EnsureCreated() {
    Settings settings("weather", true);
    if (!settings.HasKey("qweather_key")) {
        settings.SetString("qweather_key", "");
    }
}
