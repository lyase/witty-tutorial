#include <Wt/WServer>
#include <Wt/WResource>
#include <Wt/WGlobals>

struct API : public Wt::WResource {
	void handleRequest (const Http::Request &request, Http::Response &response) {
        response.out() << "hello\n";
    }
};

int main (int, char**) {
  try {
    // use argv[0] as the application name to match a suitable entry
    // in the Wt configuration file, and use the default configuration
    // file (which defaults to /etc/wt/wt_config.xml unless the environment
    // variable WT_CONFIG_XML is set)
    WServer server(argv[0]);

    // WTHTTP_CONFIGURATION is e.g. "/etc/wt/wthttpd"
    server.setServerConfiguration(argc, argv, Wt::WTHTTP_CONFIGURATION);

    // add a single entry point, at the default location (as determined
    // by the server configuration's deploy-path)
    server.addResource(new API(), "/");
    if (server.start()) {
      int sig = WServer::waitForShutdown(argv[0]);

      std::cerr << "Shutdown (signal = " << sig << ")" << std::endl;
      server.stop();

      if (sig == SIGHUP)
	WServer::restart(argc, argv, environ);
    }
  } catch (WServer::Exception& e) {
    std::cerr << e.what() << "\n";
    return 1;
  } catch (std::exception& e) {
    std::cerr << "exception: " << e.what() << "\n";
    return 1;
  }

}
