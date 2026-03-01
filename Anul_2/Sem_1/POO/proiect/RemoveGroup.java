package org.example;

public class RemoveGroup extends Command {
    private ResourceGroup group;
    private String error;
    private Database database;

    public RemoveGroup(String[] params) throws MissingIpAddressException {
        //  verificare lipsa parametrii
        if (params[1].equals("")) {
            throw new MissingIpAddressException();
        }
        database = Database.getInstance();
        group = database.findGroup(params[1]);
        if (group == null) {
            error = "Group not found: ipAddress = " + params[1];
        }
    }

    public RemoveGroup(String error) {
        this.error = error;
    }

    @Override
    public String execute() {
        if (error != null) {
            return "REMOVE GROUP: " + error;
        }
        database.removeGroup(group);
        return "REMOVE GROUP: " + group.getIpAddress();
    }
}
