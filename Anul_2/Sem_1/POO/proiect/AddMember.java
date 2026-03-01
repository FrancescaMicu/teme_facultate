package org.example;

public class AddMember extends Command {
    private User user;
    private ResourceGroup group;
    private String error;

    public AddMember(String[] params) throws MissingIpAddressException {
        //  verificare lipsa parametrii
        if (params[1].equals("")) {
            throw new MissingIpAddressException();
        }
        int level;
        switch (params[3]) {
            case "Admin":
                try {
                    level = Integer.parseInt(params[6]);
                } catch (NumberFormatException e) {
                    throw new NumberFormatException();
                }
                user = new Admin(params[2], params[3], params[4], params[5], level);
                break;
            case "Operator":
                user = new Operator(params[2], params[3], params[4], params[5]);
                break;
            default:
                user = null;
                break;
        }
        Database database = Database.getInstance();
        group = database.findGroup(params[1]);
    }

    public AddMember(String error) {
        this.error = error;
    }

    @Override
    public String execute() {
        if (error != null) {
            return "ADD MEMBER: " + error;
        }
        if (group != null && user != null) {
            group.addMember(user);
            return "ADD MEMBER: " + group.getIpAddress() + ": name = " + user.getName() + " && role = " + user.getRole();
        }
        return "ERROR";
    }
}
