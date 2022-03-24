#ifndef TASK_7_HTTPSERVER_H
#define TASK_7_HTTPSERVER_H

#include <string>
#include <map>
#include <sstream>
#include <optional>
#include <vector>
#include <unordered_set>

struct HttpRequest {
    std::string method, path, body;
    std::map<std::string, std::string> get_params;
};

struct HttpHeader {
    std::string name;
    std::string value;
};

std::ostream &operator<<(std::ostream &output, const HttpHeader &h);
bool operator==(const HttpHeader &lhs, const HttpHeader &rhs);

enum class HttpCode {
    Ok = 200,
    NotFound = 404,
    Found = 302
};

std::string HttpCodeToString(HttpCode code);

class HttpResponse {
public:
    explicit HttpResponse(HttpCode code) : code_(code) {}

    HttpResponse &AddHeader(std::string name, std::string value);
    HttpResponse &SetContent(std::string a_content);
    HttpResponse &SetCode(HttpCode a_code);

    friend std::ostream &operator<<(std::ostream &output, const HttpResponse &resp);

private:
    HttpCode code_;
    std::vector<HttpHeader> headers_;
    std::string content_;
};


struct LastCommentInfo {
    size_t user_id, consecutive_count;
};


template<typename T>
T FromString(const std::string &s);

std::pair<std::string, std::string> SplitBy(const std::string &what, const std::string &by);
std::pair<size_t, std::string> ParseIdAndContent(const std::string &body);

class CommentServer {
private:
    std::vector<std::vector<std::string>> comments_;
    std::optional<LastCommentInfo> last_comment;
    std::unordered_set<size_t> banned_users;

public:
    HttpResponse ServeRequest(const HttpRequest &req);

private:
    HttpResponse AddUser(const HttpRequest &req);
    HttpResponse AddComment(const HttpRequest &req);
    HttpResponse CheckCaptcha(const HttpRequest &req);
    HttpResponse UserComments(const HttpRequest& req);
    HttpResponse Captcha(const HttpRequest& req);

};

template<typename T>
T FromString(const std::string &s) {
    T x;
    std::istringstream is(s);
    is >> x;
    return x;
}


#endif //TASK_7_HTTPSERVER_H
