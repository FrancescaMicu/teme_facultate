package org.example;

import java.util.ArrayList;
import java.util.List;

public class Server implements Subject {
    //  campuri obligatorii
    private String ipAddress;
    private Location location;
    private User owner;

    //  campuri optionale
    private String hostname;
    private ServerStatus status;
    private Integer cpuCores;
    private Integer ramGb;
    private Integer storageGb;

    //  lista de observatori pentru design pattern-ul Observer
    private List<Observer> observers;

    private Server(Builder builder) {
        this.ipAddress = builder.ipAddress;
        this.location = builder.location;
        this.owner = builder.owner;
        this.hostname = builder.hostname;
        this.status = builder.status;
        this.cpuCores = builder.cpuCores;
        this.ramGb = builder.ramGb;
        this.storageGb = builder.storageGb;
        this.observers = new ArrayList<>();
    }

    //  metode pentru design pattern-ul Observer
    @Override
    public void notifyObservers(Alert alert) {
        for (Observer group: observers) {
            group.update(alert);
        }
    }

    @Override
    public void addObserver(Observer observer) {
        if (!observers.contains(observer)) {
            observers.add(observer);
        }
    }

    @Override
    public void removeObserver(Observer observer) {
        observers.remove(observer);
    }

    @Override
    public void newAlert(Alert alert) {
        notifyObservers(alert);
    }

    public String getIpAddress() {
        return ipAddress;
    }

    public ServerStatus getStatus() {
        return status;
    }

    //  suprascrierea metodelor pentru folosirea corecta a hashset-ului
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) {
            return false;
        }
        Server server = (Server) o;
        return ipAddress.equals(server.getIpAddress());
    }

    @Override
    public int hashCode() {
        return ipAddress.hashCode();
    }

    //  aplicare design pattern Builder
    public static class Builder {
        //  campuri obligatorii
        private String ipAddress;
        private Location location;
        private User owner;

        //  campuri optionale
        private String hostname;
        private ServerStatus status;
        private Integer cpuCores;
        private Integer ramGb;
        private Integer storageGb;

        public Builder(String ipAddress, Location location, User owner) {
            this.ipAddress = ipAddress;
            this.location = location;
            this.owner = owner;
        }

        public Builder setHostname(String hostname) {
            this.hostname = hostname;
            return this;
        }

        public Builder setStatus(ServerStatus status) {
            this.status = status;
            return this;
        }

        public Builder setCpuCores(Integer cpuCores) {
            this.cpuCores = cpuCores;
            return this;
        }

        public Builder setRamGb(Integer ramGb) {
            this.ramGb = ramGb;
            return this;
        }

        public Builder setStorageGb(Integer storageGb) {
            this.storageGb = storageGb;
            return this;
        }

        public Server build() {
            return new Server(this);
        }
    }
}
