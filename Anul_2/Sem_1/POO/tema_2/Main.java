package org.example;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        String pathTest = "src/main/resources/" + args[0] + "/";
        String pathTestInp = pathTest + "input.in";

        //  deschidere fisier
        Scanner readFile = null;
        try {
            readFile = new Scanner(new File(pathTestInp));
        } catch (FileNotFoundException e) {
            System.out.println("Fisierul nu a fost gasit");
            return;
        }
        if (readFile == null) {
            return;
        }

        //  citire linie cu linie din fisier
        Platform plat = new Platform();
        while(readFile.hasNext()) {
            String command = readFile.nextLine();
            //  apel interpretare comanda
            plat.interpretCommands(command, pathTest);
        }
        readFile.close();
    }
}