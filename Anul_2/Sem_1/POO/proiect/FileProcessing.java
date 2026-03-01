package org.example;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.List;

public class FileProcessing {
    public static void readFromFile(String typePath, String pathName) {
        String pathInput =  pathName + ".in";
        try (Scanner scanner = new Scanner(new File(pathInput))) {
            List<String> outputMessages = new ArrayList<>();
            scanner.nextLine();
            CommandFactory commandType = new CommandFactory();
            int nrCommands = 1;
            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();
                String[] params = line.split("\\|", -1);
                //  apel metode in functie de comanda
                Command command = commandType.typeCommand(typePath, params, nrCommands);
                if (command != null) {
                    String outputMessage = command.execute();
                    if (outputMessage != null) {
                        outputMessages.add(outputMessage);
                    }
                }
                nrCommands++;
            }
            writeInFile(pathName, outputMessages);
        } catch (FileNotFoundException e) {
            System.out.println("Error when opening file");
        }
    }

    private static void writeInFile(String pathName, List<String> outputMessages) throws FileNotFoundException {
        //  calea catre fisierul de output
        String pathOutput = pathName + ".out";
        try (PrintWriter pw = new PrintWriter(pathOutput)) {
            for (String messages: outputMessages) {
                pw.println(messages);
            }
        } catch (FileNotFoundException e) {
            System.out.println("Error when opening file");
        }
    }
}
