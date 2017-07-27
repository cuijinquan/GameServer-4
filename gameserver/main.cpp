#include <iostream>
#include <gateSession.h>
#include <tinyxml.h>

int main(int argc, char* argv[]) {

    khaki::InitLog(khaki::logger, "./gameserver.log", log4cpp::Priority::DEBUG);
    std::string filename = "./config.xml";
    TiXmlDocument config;
    if ( !config.LoadFile(filename.c_str()) ) {
        log4cppDebug(khaki::logger, "Load config xml error");
        return 0;
    }

    TiXmlElement* root = config.RootElement();  
    TiXmlElement *host = root->FirstChildElement();
    TiXmlElement *port = host->NextSiblingElement();

    std::string gateHost = host->FirstChild()->Value();
    std::string gatePort = port->FirstChild()->Value();
    khaki::EventLoop loop;
    gateSession* gSession = new gateSession(&loop, gateHost, uint16_t(atoi(gatePort.c_str())));
    if ( !gSession->ConnectGateway() ) {
        log4cppDebug(khaki::logger, "connect gateway failed !!");
        return 0;
    }

    gSession->Loop();
    ////////////////////
    delete gSession;
    log4cpp::Category::shutdown();
	google::protobuf::ShutdownProtobufLibrary();
    return 0;
}