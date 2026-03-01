package org.example;

//  aplicare design pattern Factory si Command
public class CommandFactory {
    public Command typeCommand(String typePath, String[] params, int nrCommands) {
        PathTypes typePathEnum = PathTypes.valueOf(typePath.toUpperCase());
        switch (typePathEnum) {
            case GROUPS:
                return groupTypeCommand(params, nrCommands);
            case LISTENER:
                try {
                    return new AddEvent(params);
                } catch (IllegalArgumentException e) {
                    return null;
                }
            case SERVERS:
                try {
                    return new AddServer(params);
                } catch (MissingIpAddressException|LocationException|UserException e) {
                    return new AddServer(e.getMessage() + " ## line no: " + nrCommands);
                } catch (IllegalArgumentException e) {
                    return null;
                }
            default:
                return null;
        }
    }

    public Command groupTypeCommand(String[] params, int nrCommands) {
        switch (params[0]) {
            case "ADD GROUP":
                try {
                    return new AddGroup(params);
                } catch (MissingIpAddressException e) {
                    return new AddGroup(e.getMessage() + " ## line no: " + nrCommands);
                }
            case "FIND GROUP":
                try {
                    return new FindGroup(params);
                } catch (MissingIpAddressException e) {
                    return new FindGroup(e.getMessage() + " ## line no: " + nrCommands);
                }
            case "REMOVE GROUP":
                try {
                    return new RemoveGroup(params);
                } catch (MissingIpAddressException e) {
                    return new RemoveGroup(e.getMessage() + " ## line no: " + nrCommands);
                }
            case "ADD MEMBER":
                try {
                    return new AddMember(params);
                } catch (MissingIpAddressException e) {
                    return new AddMember(e.getMessage() + " ## line no: " + nrCommands);
                } catch (NumberFormatException e) {
                    return null;
                }
            case "FIND MEMBER":
                try {
                    return new FindMember(params);
                } catch (MissingIpAddressException|UserException e) {
                    return new FindMember(e.getMessage() + " ## line no: " + nrCommands);
                } catch (NumberFormatException e) {
                    return null;
                }
            case "REMOVE MEMBER":
                try {
                    return new RemoveMember(params);
                } catch (MissingIpAddressException|UserException e) {
                    return new RemoveMember(e.getMessage() + " ## line no: " + nrCommands);
                }
            default:
                return null;
        }
    }
}
