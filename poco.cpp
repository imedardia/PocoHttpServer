#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Util/ServerApplication.h>
#include <iostream>
#include <string>
#include <vector>

using namespace Poco::Net;
using namespace Poco::Util;
using namespace std;

class MyRequestHandler : public HTTPRequestHandler
{
public:
  virtual void handleRequest(HTTPServerRequest &req, HTTPServerResponse &resp)
  {
    ostream& out = resp.send();
    if(req.getMethod() == string("POST")) {
        cout << "POST METHOD not supported" << endl;
        resp.setStatus(HTTPResponse::HTTP_METHOD_NOT_ALLOWED);

        return;
    }
    if(req.getMethod() == string("GET")) {
        cout << "GET METHOD is supported" << endl;
    }

    resp.setStatus(HTTPResponse::HTTP_OK);
    resp.setContentType("text/html");

    out << "<h1>Hello world!</h1>"
        << "<p>Host: "   << req.getHost()   << "</p>"
        << "<p>URI: "    << req.getURI()    << "</p>";
    out.flush();
  }
};

class MyRequestHandlerFactory : public HTTPRequestHandlerFactory
{
public:
  virtual HTTPRequestHandler* createRequestHandler(const HTTPServerRequest &)
  {
    return new MyRequestHandler;
  }
};


class MyServerApp : public ServerApplication
{
protected:
  int main(const vector<string> &)
  {
    HTTPServer s(new MyRequestHandlerFactory, ServerSocket(8080), new HTTPServerParams);

    s.start();
    cout << endl << "Server started" << endl;

    waitForTerminationRequest();  // wait for CTRL-C or kill

    cout << endl << "Shutting down..." << endl;
    s.stop();

    return Application::EXIT_OK;
  }
};


int main(int argc, char** argv)
{
  MyServerApp app;
  return app.run(argc, argv);
}
