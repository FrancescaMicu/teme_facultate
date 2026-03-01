package org.example;

public class AddEvent extends Command {
    private Alert alert;
    private Server server;
    private Database database;

    public AddEvent(String[] params) {
        AlertType alertType;
        Severity severity;
        try {
            alertType = AlertType.valueOf(params[1].toUpperCase());
            severity = Severity.valueOf(params[2].toUpperCase());
        } catch (IllegalArgumentException e) {
            throw new IllegalArgumentException();
        }
        alert = new Alert(alertType, severity, params[4], params[3]);
        database = Database.getInstance();
        server = database.findServer(params[3]);
    }

    @Override
    public String execute() {
        if (alert != null) {
            database.addAlert(alert);
            if (server != null) {
                server.newAlert(alert);
            }
            return "ADD EVENT: " + alert.getIpAddress() + ": type = " + alert.getType() + " && severity = " + alert.getSeverity() + " && message = " + alert.getMessage();
        }
        return "ERROR";
    }
}
