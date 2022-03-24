#include "../../Utils/TestRunner.h"
#include "HttpServer.h"

#include <vector>
#include <string>
#include <iostream>
#include <optional>

using namespace std;

struct ParsedResponse {
    int code = {};
    vector<HttpHeader> headers;
    string content;
};

istream &operator>>(istream &input, ParsedResponse &r) {
    string line;
    getline(input, line);

    {
        istringstream code_input(line);
        string dummy;
        code_input >> dummy >> r.code;
    }

    size_t content_length = 0;

    r.headers.clear();
    while (getline(input, line) && !line.empty()) {
        if (auto[name, value] = SplitBy(line, ": "); name == "Content-Length") {
            istringstream length_input(value);
            length_input >> content_length;
        } else {
            r.headers.push_back({std::move(name), std::move(value)});
        }
    }

    r.content.resize(content_length);
    input.read(r.content.data(), r.content.size());
    return input;
}

void Test(CommentServer &srv, const HttpRequest &request, const ParsedResponse &expected) {
    stringstream ss;
    ss << srv.ServeRequest(request);
    ParsedResponse resp;
    ss >> resp;

    ASSERT_EQUAL(resp.code, expected.code);
    ASSERT_EQUAL(resp.headers, expected.headers);
    ASSERT_EQUAL(resp.content, expected.content);
}

template<typename CommentServer>
void TestServer() {
    CommentServer cs;

    const ParsedResponse ok{200};
    const ParsedResponse redirect_to_captcha{302, {{"Location", "/captcha"}}, {}};
    const ParsedResponse not_found{404};

    Test(cs, {"POST", "/add_user"}, {200, {}, "0"});
    Test(cs, {"POST", "/add_user"}, {200, {}, "1"});
    Test(cs, {"POST", "/add_comment", "0 Hello"}, ok);
    Test(cs, {"POST", "/add_comment", "1 Hi"}, ok);
    Test(cs, {"POST", "/add_comment", "1 Buy my goods"}, ok);
    Test(cs, {"POST", "/add_comment", "1 Enlarge"}, ok);
    Test(cs, {"POST", "/add_comment", "1 Buy my goods"}, redirect_to_captcha);
    Test(cs, {"POST", "/add_comment", "0 What are you selling?"}, ok);
    Test(cs, {"POST", "/add_comment", "1 Buy my goods"}, redirect_to_captcha);
    Test(
            cs,
            {"GET", "/user_comments", "", {{"user_id", "0"}}},
            {200, {}, "Hello\nWhat are you selling?\n"});
    Test(
            cs,
            {"GET", "/user_comments", "", {{"user_id", "1"}}},
            {200, {}, "Hi\nBuy my goods\nEnlarge\n"});
    Test(
            cs,
            {"GET", "/captcha"},
            {200, {}, {"What's the answer for The Ultimate Question of Life, the Universe, and Everything?"}});
    Test(cs, {"POST", "/checkcaptcha", "1 24"}, redirect_to_captcha);
    Test(cs, {"POST", "/checkcaptcha", "1 42"}, ok);
    Test(cs, {"POST", "/add_comment", "1 Sorry! No spam any more"}, ok);
    Test(
            cs,
            {"GET", "/user_comments", "", {{"user_id", "1"}}},
            {200, {}, "Hi\nBuy my goods\nEnlarge\nSorry! No spam any more\n"});

    Test(cs, {"GET", "/user_commntes"}, not_found);
    Test(cs, {"POST", "/add_uesr"}, not_found);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestServer<CommentServer>);
}