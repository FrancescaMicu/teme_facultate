package org.example;

public interface Subject {
    void notifyObservers(Alert alert);
    void addObserver(Observer observer);
    void removeObserver(Observer observer);
    void newAlert(Alert alert);
}
