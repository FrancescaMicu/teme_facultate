package org.example;

public class FindGroup extends Command {
    private ResourceGroup group;
    private String error;

    public FindGroup(String[] params) throws MissingIpAddressException {
        //  verificare lipsa parametrii
        if (params[1].equals("")) {
            throw new MissingIpAddressException();
        }
        Database database = Database.getInstance();
        group = database.findGroup(params[1]);
        if (group == null) {
            error = "Group not found: ipAddress = " + params[1];
        }
    }

    public FindGroup(String error) {
        this.error = error;
    }

    @Override
    public String execute() {
        if (error != null) {
            return "FIND GROUP: " + error;
        }
        return "FIND GROUP: " + group.getIpAddress();
    }
}
