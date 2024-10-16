#include "httprequest.h"

HttpRequest::HttpRequest():method_(INVALID),version_(UNKNOWN)
{

}

void HttpRequest::setVersion(HttpRequest::Version v)
{
    version_ = v;
}

HttpRequest::Version HttpRequest::getVersion() const
{
    return version_;
}

bool HttpRequest::setMethod(const char *start, const char *end)
{
    string m(start,end);
    if(m == "GET")
    {
        method_ = GET;
    }
    else if(m == "POST")
    {
        method_ = POST;
    }
    else if(m == "HEAD")
    {
        method_ = HEAD;
    }
    else if(m == "PUT")
    {
        method_ = PUT;
    }
    else if(m == "DELETE")
    {
        method_ = DELETE;
    }
    else
    {
        method_ = INVALID;
    }

    return method_ != INVALID;
}

HttpRequest::Method HttpRequest::method() const
{
    return method_;
}

const char *HttpRequest::methodString() const
{
    const char *result = "UNKNOWN";
    switch(method_)
    {
    case GET:
        result = "GET";
        break;
    case POST:
        result = "POST";
        break;
    case HEAD:
        result = "HEAD";
        break;
    case PUT:
        result = "PUT";
        break;
    case DELETE:
        result = "DELETE";
        break;
    default:
        break;
    }

    return result;
}

void HttpRequest::setPath(const char *start, const char *end)
{
    path_.assign(start,end);
}

const string &HttpRequest::path() const
{
    return path_;
}

void HttpRequest::setQuery(const char *start, const char *end)
{
    query_.assign(start,end);
}

const string &HttpRequest::query() const
{
    return query_;
}

void HttpRequest::setReceiveTime(Timestamp t)
{
    receiveTime_ = t;
}

Timestamp HttpRequest::receiveTime() const
{
    return receiveTime_;
}

void HttpRequest::addHeader(const char *start, const char *colon, const char *end)
{
    string field(start,colon);
    ++colon;
    while(colon < end && isspace(*colon))
        ++colon;

    string value(colon,end);
    while(!value.empty() && isspace(value[value.size()-1]))
        value.resize(value.size()-1);

    headers_[field] = value;
}

string HttpRequest::getHeader(const string &field) const
{
    string result;
    unordered_map<string, string>::const_iterator it = headers_.find(field);
    if(it != headers_.end())
        result = it->second;

    return result;
}

const unordered_map<string, string> &HttpRequest::headers() const
{
    return headers_;
}

void HttpRequest::swap(HttpRequest &that)
{
    std::swap(method_, that.method_);
    path_.swap(that.path_);
    query_.swap(that.query_);
    receiveTime_.swap(that.receiveTime_);
    headers_.swap(that.headers_);
}