package Tema1;

import java.io.*;
import java.lang.reflect.Array;
import java.util.*;
import java.util.stream.Collectors;
import java.text.*;

public class App {
    private Scanner scanner;

    public App(InputStream input) {
        this.scanner = new Scanner(input);
    }

    //  metoda pentru rezolvarea comenzii 0
    private void comanda0(String tip, String id, double putereSpecifica, GridController grid) {
        //  verificare daca puterea este invalida
        if ( putereSpecifica <= 0 ) {
            System.out.println("EROARE: Putere invalida");
            return;
        }

        //  verificare id
        if ( grid.idValid(id) != null ) {
            System.out.println("EROARE: Exista deja o componenta cu id-ul " + id);
            return;
        }

        //  verificare tip producator
        ProducatorEnergie prod;
        if ( tip.equals("solar") ) {
            prod = new PanouSolar(putereSpecifica, id);
        } else if ( tip.equals("reactor") ) {
            prod = new ReactorNuclear(putereSpecifica, id);
        } else if ( tip.equals("turbina") ) {
            prod = new TurbinaEoliana(putereSpecifica, id);
        } else {
            System.out.println("EROARE: Tip producator invalid");
            return;
        }

        //  adaugare in vectorul de producatori
        grid.addProducatorEnergie(prod);
        System.out.println("S-a adaugat producatorul " + id + " de tip " + tip);
    }

    //  metoda pentru rezolvarea comenzii 1
    private void comanda1(String tip, String id, double putereSpecifica, GridController grid) {
        //  verificare daca puterea este invalida
        if ( putereSpecifica <= 0 ) {
            System.out.println("EROARE: Cerere putere invalida");
            return;
        }

        //  verificare id
        if ( grid.idValid(id) != null ) {
            System.out.println("EROARE: Exista deja o componenta cu id-ul " + id);
            return;
        }

        ConsumatorEnergie con;
        //  verificare tip consumator
        if ( tip.equals("suport_viata") ) {
            con = new SistemSuportViata(id, putereSpecifica);
        } else if ( tip.equals("laborator") ) {
            con = new LaboratorStiintific(id, putereSpecifica);
        } else if ( tip.equals("iluminat") ) {
                con = new SistemIluminat(id, putereSpecifica);
        } else {
            System.out.println("EROARE: Tip consumator invalid");
            return;
        }

        //  adaugare in vectorul de consumatori
        grid.addConsumatorEnergie(con);
        System.out.println("S-a adaugat consumatorul " + id + " de tip " + tip);
    }

    //  metoda pentru rezolvarea comenzii 2
    private void comanda2(String id, double capacitate, GridController grid) {
        //  verificare cazului in care capacitatea este invalida
        if ( capacitate <= 0 ) {
            System.out.println("EROARE: Capacitate invalida");
            return;
        }

        //  verificare id
        if ( grid.idValid(id) != null ) {
            System.out.println("EROARE: Exista deja o componenta cu id-ul " + id);
            return;
        }

        //  adaugare in vectorul de baterii
        Baterie bat = new Baterie(id, capacitate);
        grid.addBaterie(bat);
        System.out.println("S-a adaugat bateria " + id + " cu capacitatea " + capacitate);
    }

    //  metoda pentru rezolvarea comenzii 3
    private void comanda3(double factorSoare, double factorVant, GridController grid) {
        //  verificare daca factorii sunt invalizi
        if ( factorSoare < 0 || factorVant < 0 ) {
            System.out.println("EROARE: Factori invalizi");
            return;
        }

        //  apel simulare
        if ( grid.getEsteInBlackout() == false ) {
            grid.simuleazaTick(factorSoare, factorVant);
        }

        //  verificare daca resteaua este in blackout
        if ( grid.getEsteInBlackout() == true ) {
            System.out.println("EROARE: Reteaua este in BLACKOUT. Simulare oprita.");
        }
    }

    //  metoda pentru rezolvarea comenzii 4
    private void comanda4(String id, boolean statusOperational, GridController grid) {
        //  verificare id
        ComponentaRetea compCautat = grid.idValid(id);
        if ( compCautat == null ) {
            System.out.println("EROARE: Nu exista componenta cu id-ul " + id);
            return;
        }

        //  setare stare componenta
        if ( statusOperational == true ) {
            compCautat.setStatusOperational(true);
            System.out.println("Componenta " + id + " este acum operationala.");
        } else if ( statusOperational == false ) {
            compCautat.setStatusOperational(false);
            System.out.println("Componenta " + id + " este acum defecta.");
        } else {
            System.out.println("EROARE: Status invalid");
        }
    }

    //  metoda pentru rezolvarea comenzii 5
    private void comanda5(GridController grid) {
        //  verificare daca exista componente in liste
        if ( grid.getProdList().size() == 0 && grid.getConsList().size() == 0 && grid.getBaterieList().size() == 0 ) {
            System.out.println("Reteaua este goala.");
            return;
        }

        //  verificare daca reteaua este in blackout
        if ( grid.getEsteInBlackout() == true ) {
            System.out.println("Stare Retea: BLACKOUT");
        } else {
            System.out.println("Stare Retea: STABILA");
        }

        //  afisare componente
        ProducatorEnergie.afisProducatori(grid.getProdList());
        ConsumatorEnergie.afisConsumatori(grid.getConsList());
        Baterie.afisBaterii(grid.getBaterieList());
    }

    //  metoda pentru rezolvarea comenzii 6
    private void comanda6(GridController grid) {
        //  verificare daca istoricul e gol
        if ( grid.getIstoric().isEmpty() ) {
            System.out.println("Istoric evenimente gol.");
        } else {
            for ( String comanda: grid.getIstoric() ) {
                System.out.println(comanda);
            }
        }
    }

    //  metoda pentru rezolvarea comenzii 7
    private void comanda7() {
        System.out.println("Simulatorul se inchide.");
    }

    public void run() {
        // Implementați aici cerințele din enunț
        // Pentru citirea datelor de la tastatura se folosește câmpul scanner.

        //  instantiere GridController
        GridController grid = new GridController();

        while ( scanner.hasNextLine() ) {
            String linie = scanner.nextLine().trim();

            //  verificare daca linia este goala
            if ( linie.isEmpty() ) {
                return;
            }

            //  impartirea sirului in cuvinte
            String[] cuv = linie.split(" ");

            //  comanda 0
            if ( cuv[0].equals("0") ) {
                //  numar nepotrivit de cuvinte in comanda
                if ( cuv.length != 4 ) {
                    System.out.println("EROARE: Format comanda invalid");
                    return;
                }

                // verificare daca puterea e de tip numeric valid
                double putere;
                try {
                    putere = Double.parseDouble(cuv[3]);
                } catch (NumberFormatException e) {
                    System.out.println("EROARE: Putere invalida");
                    return;
                }

                // apel comanda 0
                comanda0(cuv[1], cuv[2], putere, grid);
            }
            //  comanda 1
            else if ( cuv[0].equals("1") ) {
                //  numar nepotrivit de cuvinte in comanda
                if ( cuv.length != 4 ) {
                    System.out.println("EROARE: Format comanda invalid");
                    return;
                }

                // verificare daca puterea e de tip numeric valid
                double putere;
                try {
                    putere = Double.parseDouble(cuv[3]);
                } catch (NumberFormatException e) {
                    System.out.println("EROARE: Putere invalida");
                    return;
                }

                // apel comanda 1
                comanda1(cuv[1], cuv[2], putere, grid);
            }
            //  comanda 2
            else if ( cuv[0].equals("2") ) {
                //  numar nepotrivit de cuvinte in comanda
                if ( cuv.length != 3 ) {
                    System.out.println("EROARE: Format comanda invalid");
                    return;
                }

                // verificare daca puterea e de tip numeric valid
                double capacitate;
                try {
                    capacitate = Double.parseDouble(cuv[2]);
                } catch (NumberFormatException e) {
                    System.out.println("EROARE: Putere invalida");
                    return;
                }

                // apel comanda 2
                comanda2(cuv[1], capacitate, grid);
            }
            //  comanda 3
            else if ( cuv[0].equals("3") ) {
                //  numar nepotrivit de cuvinte in comanda
                if ( cuv.length != 3 ) {
                    System.out.println("EROARE: Format comanda invalid");
                    return;
                }

                // verificare daca factorii sunt de tip numeric valid
                double factorSoare;
                double factorVant;
                try {
                    factorSoare = Double.parseDouble(cuv[1]);
                    factorVant = Double.parseDouble(cuv[2]);
                } catch (NumberFormatException e) {
                    System.out.println("EROARE: Factori invalizi");
                    return;
                }

                //  apel comanda 3
                comanda3(factorSoare, factorVant, grid);
            }
            //  comanda 4
            else if ( cuv[0].equals("4") ) {
                //  numar nepotrivit de cuvinte in comanda
                if ( cuv.length != 3 ) {
                    System.out.println("EROARE: Format comanda invalid");
                    return;
                }

                //  verificare daca statusul e de tip boolean
                boolean statusOperational;
                if ( cuv[2].equals("true") ) {
                    statusOperational = true;
                } else if ( cuv[2].equals("false") ) {
                    statusOperational = false;
                } else {
                    System.out.println("EROARE: Status invalid");
                    return;
                }

                //  apel comanda 4
                comanda4(cuv[1], statusOperational, grid);
            }
            //  comanda 5
            else if ( cuv[0].equals("5") ) {
                //  numar nepotrivit de cuvinte in comanda
                if ( cuv.length != 1 ) {
                    System.out.println("EROARE: Format comanda invalid");
                }

                //  apel comanda 5
                comanda5(grid);
            }
            //  comanda 6
            else if ( cuv[0].equals("6") ) {
                //  numar nepotrivit de cuvinte in comanda
                if ( cuv.length != 1 ) {
                    System.out.println("EROARE: Format comanda invalid");
                    return;
                }

                //  apel comanda 6
                comanda6(grid);
            }
            //  comanda 7
            else if ( cuv[0].equals("7") ) {
                //  numar nepotrivit de cuvinte in comanda
                if ( cuv.length != 1 ) {
                    System.out.println("EROARE: Format comanda invalid");
                }

                //  apel comanda 7
                comanda7();
            //  comanda necunoscuta
            } else {
                System.out.println("EROARE: Comanda necunoscuta.");
            }
        }
    }

    public static void main(String[] args) {
        App app = new App(System.in);
        app.run();
    }
}
