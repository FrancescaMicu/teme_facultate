package org.example;

import java.util.ArrayList;
import java.util.List;

public class ResourceGroup implements Observer {
    private List<User> members;
    private String ipAddress;

    public ResourceGroup(String ipAddress) {
        this.ipAddress = ipAddress;
        this.members = new ArrayList<>();
    }

    //  metoda pentru design pattern-ul Observer
    //  metoda este mai mult formala, folosita doar pentru receptionarea alertei
    @Override
    public void update(Alert alert) {}

    public void addMember(User user){
        members.add(user);
    }

    public List<User> getMembers(){
        return members;
    }

    public void removeMember(User user){
        members.remove(user);
    }

    public User getUser(String name, String role) {
        for (User user : members) {
            if (user.getName().equals(name) && user.getRole().equals(role)) {
                return user;
            }
        }
        return null;
    }

    public String getIpAddress() {
        return ipAddress;
    }

    //  suprascrierea metodelor pentru folosirea corecta a hashset-ului
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) {
            return false;
        }
        ResourceGroup resourceGroup = (ResourceGroup) o;
        return ipAddress.equals(resourceGroup.getIpAddress());
    }

    @Override
    public int hashCode() {
        return ipAddress.hashCode();
    }
}
