package org.example;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class SubmissionOutsideTimeIntervalException extends Exception {
    //  declarare campuri
    private static final DateTimeFormatter timeFormat = DateTimeFormatter.ofPattern("dd-MM-yyyy-HH-mm");
    private LocalDateTime timestamp;
    private String nameStud;

    //  constructor
    public SubmissionOutsideTimeIntervalException(LocalDateTime timestamp, String nameStud, String message) {
        super(message);
        this.timestamp = timestamp;
        this.nameStud = nameStud;
    }

    //  metoda toString
    @Override
    public String toString() {
        return this.timestamp.format(timeFormat) + " | " + getMessage() + this.nameStud;
    }
}
