package org.example;

public class AddGroup extends Command {
    private ResourceGroup group;
    private String error;

    public AddGroup(String[] params) throws MissingIpAddressException {
        //  verificare lipsa parametrii
        if (params[1].equals("")) {
            throw new MissingIpAddressException();
        }
        group = new ResourceGroup(params[1]);
    }

    public AddGroup(String error) {
        this.error = error;
    }

    @Override
    public String execute() {
        if (error != null) {
            return "ADD GROUP: " + error;
        }
        Database database = Database.getInstance();
        database.addResourceGroup(group);
        return "ADD GROUP: " + group.getIpAddress();
    }
}
