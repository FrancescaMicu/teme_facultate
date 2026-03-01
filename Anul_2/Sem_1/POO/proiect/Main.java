package org.example;

public class Main {
    public static void main(String[] args) {
        String typePath = args[0];
        if (args.length == 2) {
            String pathName = args[1];
            FileProcessing.readFromFile(typePath, pathName);
        }
        else if (args.length == 4) {
            String serverPath  = args[1];
            String groupPath = args[2];
            String listenerPath = args[3];
            FileProcessing.readFromFile(PathTypes.SERVERS.getValue(), serverPath);
            FileProcessing.readFromFile(PathTypes.GROUPS.getValue(), groupPath);
            FileProcessing.readFromFile(PathTypes.LISTENER.getValue(), listenerPath);
        } else {
            System.out.println("Invalid number of arguments");
        }
    }
}
