package org.example;

public enum ServerStatus {
    UP("up"),
    DOWN("down"),
    DEGRADED("degraded");

    private final String value;

    ServerStatus(String value) {
        this.value = value;
    }

    public String getValue() {
        return this.value;
    }
}
