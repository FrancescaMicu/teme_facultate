package org.example;

public enum AlertType {
    ANOMALY("anomaly"),
    ADVISORY("advisory");

    private final String value;

    AlertType(String value) {
        this.value = value;
    }

    public String getValue() {
        return this.value;
    }
}
