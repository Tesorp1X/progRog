package main;

import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.servlet.ServletContextHandler;
import org.eclipse.jetty.servlet.ServletHolder;
import servlets.AllRequestsServlet;
import servlets.MirrorRequestServlet;

public class Main {
    public static void main(String[] args) throws Exception {
        AllRequestsServlet allRequestsServlet = new AllRequestsServlet();
        MirrorRequestServlet mirrorRequestServlet = new MirrorRequestServlet();

        ServletContextHandler context = new ServletContextHandler(ServletContextHandler.SESSIONS);


        context.addServlet(new ServletHolder(mirrorRequestServlet), "/mirror");
        context.addServlet(new ServletHolder(allRequestsServlet), "/*");


        Server server = new Server(8080);
        server.setHandler(context);


        java.util.logging.Logger.getGlobal().info("Server started");
        server.start();
        System.out.println("Server started");
        server.join();
    }
}
