package org.example;

public class Operator extends User {
    protected String department;

    public Operator(String name, String role, String email, String department) {
        super(name, role, email);
        this.department = department;
    }
}
