package org.example;

public class AddServer extends Command {
    private Server server;
    private String error;

    public AddServer(String[] params) throws MissingIpAddressException, LocationException, UserException {
        //  verificare lipsa parametrii
        if (params[2].equals("")) {
            throw new MissingIpAddressException();
        }
        if (params[4].equals("")) {
            throw new LocationException();
        }
        if (params[9].equals("")) {
            throw new UserException();
        }
        if (params[10].equals("")) {
            throw new UserException();
        }

        //  creare Location
        Location.Builder locationBuilder = new Location.Builder(params[4]);
        if (!params[5].equals("")) {
            locationBuilder.setCity(params[5]);
        }
        if (!params[6].equals("")) {
            locationBuilder.setAddress(params[6]);
        }
        if (!params[7].equals("")) {
            try {
                locationBuilder.setLatitude(Double.parseDouble(params[7]));
            } catch (NumberFormatException e) {
                throw new NumberFormatException();
            }
        }
        if (!params[8].equals("")) {
            try {
                locationBuilder.setLongitude(Double.parseDouble(params[8]));
            } catch (NumberFormatException e) {
                throw new NumberFormatException();
            }
        }
        Location location = locationBuilder.build();

        //  creare User
        User user = new User(params[9], params[10], params[11]);

        //  crearea Server
        Server.Builder serverBuilder = new Server.Builder(params[2], location, user);
        if (!params[1].equals("")) {
            serverBuilder.setHostname(params[1]);
        }
        if (!params[3].equals("")) {
            try {
                serverBuilder.setStatus(ServerStatus.valueOf(params[3].toUpperCase()));
            } catch (IllegalArgumentException e) {
                throw new IllegalArgumentException();
            }
        }
        if (!params[14].equals("")) {
            try {
                serverBuilder.setCpuCores(Integer.parseInt(params[14]));
            } catch (NumberFormatException e) {
                throw new NumberFormatException();
            }
        }
        if (!params[15].equals("")) {
            try {
                serverBuilder.setRamGb(Integer.parseInt(params[15]));
            } catch (NumberFormatException e) {
                throw new NumberFormatException();
            }
        }
        if (!params[16].equals("")) {
            try {
                serverBuilder.setStorageGb(Integer.parseInt(params[16]));
            } catch (NumberFormatException e) {
                throw new NumberFormatException();
            }
        }
        server = serverBuilder.build();
    }

    public AddServer(String error) {
        this.error = error;
    }

    @Override
    public String execute() {
        if (error != null) {
            return "ADD SERVER: " + error;
        }
        Database database = Database.getInstance();
        database.addServer(server);
        return "ADD SERVER: " + server.getIpAddress() + ": " + server.getStatus();
    }
}
