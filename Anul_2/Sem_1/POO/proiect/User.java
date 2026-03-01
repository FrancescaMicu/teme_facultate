package org.example;

public class User {
    protected String name;
    protected String role;
    protected String email;

    public User(String name, String role, String email) {
        this.name = name;
        this.role = role;
        this.email = email;
    }

    public String getName() {
        return name;
    }

    public String getRole() {
        return role;
    }
}
