#include "HttpServer.h"

std::string HttpCodeToString(HttpCode code) {
    switch (code) {
        case HttpCode::Ok:
            return "200 OK";
        case HttpCode::NotFound:
            return "404 Not found";
        case HttpCode::Found:
            return "302 Found";
    }
    return "";
}

std::pair<std::string, std::string> SplitBy(const std::string &what, const std::string &by) {
    size_t pos = what.find(by);
    if (by.size() < what.size() && pos < what.size() - by.size()) {
        return {what.substr(0, pos), what.substr(pos + by.size())};
    } else {
        return {what, {}};
    }
}

std::pair<size_t, std::string> ParseIdAndContent(const std::string &body) {
    auto[id_string, content] = SplitBy(body, " ");
    return {FromString<size_t>(id_string), content};
}

std::ostream &operator<<(std::ostream &output, const HttpHeader &h) {
    return output << h.name << ": " << h.value;
}

bool operator==(const HttpHeader &lhs, const HttpHeader &rhs) {
    return lhs.name == rhs.name && lhs.value == rhs.value;
}


HttpResponse& HttpResponse::AddHeader(std::string name, std::string value) {
    headers_.emplace_back(HttpHeader{std::move(name), std::move(value)});
    return *this;
}

HttpResponse& HttpResponse::SetContent(std::string a_content) {
    content_ = std::move(a_content);
    return *this;
}

HttpResponse& HttpResponse::SetCode(HttpCode a_code) {
    code_ = a_code;
    return *this;
}

std::ostream &operator<<(std::ostream &output, const HttpResponse &resp) {
    output << "HTTP/1.1 ";
    output << HttpCodeToString(resp.code_) << "\n";
    for (const auto &[key, value]: resp.headers_) {
        output << key << ": " << value << "\n";
    }

    if (!resp.content_.empty()) {
        output << "Content-Length: " << resp.content_.size() << "\n";
    }
    output << "\n" << resp.content_;
    return output;
}



HttpResponse CommentServer::ServeRequest(const HttpRequest &req) {
    if (req.method == "POST") {

        if (req.path == "/add_user") {
            return AddUser(req);
        } else if (req.path == "/add_comment") {
            return AddComment(req);
        } else if (req.path == "/checkcaptcha") {
            return CheckCaptcha(req);
        }
    } else if (req.method == "GET") {

        if (req.path == "/user_comments") {
            return UserComments(req);
        } else if (req.path == "/captcha") {
            return Captcha(req);
        }
    }

    return HttpResponse(HttpCode::NotFound);
}

HttpResponse CommentServer::AddUser(const HttpRequest &req) {
    comments_.emplace_back();
    auto response = std::to_string(comments_.size() - 1);
    return HttpResponse(HttpCode::Ok).SetCode(HttpCode::Ok).SetContent(response);
}

HttpResponse CommentServer::AddComment(const HttpRequest &req) {
    auto[user_id, comment] = ParseIdAndContent(req.body);

    if (!last_comment || last_comment->user_id != user_id) {
        last_comment = LastCommentInfo{user_id, 1};
    } else if (++last_comment->consecutive_count > 3) {
        banned_users.insert(user_id);
    }

    if (!banned_users.count(user_id)) {
        comments_[user_id].push_back(std::string(comment));

        return HttpResponse(HttpCode::Ok);
    } else {
        return HttpResponse(HttpCode::Found).AddHeader("Location", "/captcha");
    }
}

HttpResponse CommentServer::CheckCaptcha(const HttpRequest &req) {
    if (auto[id, response] = ParseIdAndContent(req.body); response == "42") {
        banned_users.erase(id);
        if (last_comment && last_comment->user_id == id) {
            last_comment.reset();
        }
        return HttpResponse(HttpCode::Ok);
    } else {
        return HttpResponse(HttpCode::Found).AddHeader("Location", "/captcha");
    }
}

HttpResponse CommentServer::UserComments(const HttpRequest& req) {
    auto user_id = FromString<size_t>(req.get_params.at("user_id"));
    std::string response;
    for (const std::string &c: comments_[user_id]) {
        response += c + '\n';
    }

    return HttpResponse(HttpCode::Ok).SetContent(response);
}

HttpResponse CommentServer::Captcha(const HttpRequest& req){
    std::string response = "What's the answer for The Ultimate Question of Life, the Universe, and Everything?";
    return HttpResponse(HttpCode::Ok).SetContent(response);
}
