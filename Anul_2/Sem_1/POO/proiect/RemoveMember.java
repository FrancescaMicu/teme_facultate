package org.example;

public class RemoveMember extends Command {
    private User user;
    private ResourceGroup group;
    private String error;

    public RemoveMember(String[] params) throws MissingIpAddressException, UserException {
        //  verificare lipsa parametrii
        if (params[1].equals("")) {
            throw new MissingIpAddressException();
        }
        if (params[2].equals("")) {
            throw new UserException();
        }
        if (params[3].equals("")) {
            throw new UserException();
        }
        Database database = Database.getInstance();
        group = database.findGroup(params[1]);
        if (group == null) {
            error = "Group not found: ipAddress = " + params[1];
            return;
        }
        user = group.getUser(params[2], params[3]);
        if (user == null) {
            error = "Member not found: ipAddress = " + params[1] + ": name = " + params[2] + " && role = " + params[3];
        }
    }

    public RemoveMember(String error) {
        this.error = error;
    }

    @Override
    public String execute() {
        if (error != null) {
            return "REMOVE MEMBER: " + error;
        }
        group.removeMember(user);
        return "REMOVE MEMBER: " + group.getIpAddress() + ": name = " + user.getName() + " && role = " + user.getRole();
    }
}
