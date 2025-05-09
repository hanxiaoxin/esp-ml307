#ifndef ESP_HTTP_H
#define ESP_HTTP_H

#include "http.h"
#include <esp_http_client.h>

#include <string>
#include <map>

class EspHttp : public Http {
public:
    EspHttp();
    virtual ~EspHttp();

    void SetHeader(const std::string& key, const std::string& value) override;
    bool Open(const std::string& method, const std::string& url, const std::string& content = "") override;
    void Close() override;

    int GetStatusCode() const override;
    std::string GetResponseHeader(const std::string& key) const override;
    size_t GetBodyLength() const override;
    const std::string& GetBody() override;
    int Read(char* buffer, size_t buffer_size) override;
    void SetTimeout(int timeout_ms) override;

private:
    esp_http_client_handle_t client_;
    std::map<std::string, std::string> headers_;
    std::string response_body_;
    int status_code_;
    int64_t content_length_;
    int timeout_ms_ = 30000;

    static esp_err_t HttpEventHandler(esp_http_client_event_t *evt);
};

#endif // ESP_HTTP_H
