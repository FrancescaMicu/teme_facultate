package org.example;

import java.util.HashSet;
import java.util.Set;

public class Database {
    //  splicare design pattern Singleton
    private static Database instance;
    private Set<Server> servers;
    private Set<ResourceGroup> resourceGroups;
    private Set<Alert> alerts;

    private Database() {
        this.servers = new HashSet<>();
        this.resourceGroups = new HashSet<>();
        this.alerts = new HashSet<>();
    }

    public static Database getInstance() {
        if (instance == null) {
            instance = new Database();
        }
        return instance;
    }

    public void addServer(Server server) {
        servers.add(server);
        ResourceGroup group = findGroup(server.getIpAddress());
        if (group != null) {
            server.addObserver(group);
        }
    }

    public void addServers(Set<Server> servers) {
        for (Server server : servers) {
            addServer(server);
        }
    }

    public void addResourceGroup(ResourceGroup group) {
        resourceGroups.add(group);
        Server server = findServer(group.getIpAddress());
        if (server != null) {
            server.addObserver(group);
        }
    }

    public void addResourceGroups(Set<ResourceGroup> resourceGroups) {
        for (ResourceGroup group : resourceGroups) {
            addResourceGroup(group);
        }
    }

    public void addAlert(Alert alert) {
        alerts.add(alert);
    }

    public ResourceGroup findGroup(String ipAddress) {
        for (ResourceGroup resourceGroup: resourceGroups) {
            if (resourceGroup.getIpAddress().equals(ipAddress)) {
                return resourceGroup;
            }
        }
        return null;
    }

    public Server findServer(String ipAddress) {
        for (Server server: servers) {
            if (server.getIpAddress().equals(ipAddress)) {
                return server;
            }
        }
        return null;
    }

    public void removeGroup(ResourceGroup group) {
        resourceGroups.remove(group);
        for (Server server: servers) {
            server.removeObserver(group);
        }
    }
}
