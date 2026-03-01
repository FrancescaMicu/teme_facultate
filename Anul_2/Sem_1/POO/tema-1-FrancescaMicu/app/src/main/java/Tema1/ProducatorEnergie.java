package Tema1;

import java.util.ArrayList;
import java.util.List;

public abstract class ProducatorEnergie extends ComponentaRetea {
    //  constructor
    public ProducatorEnergie(String id) {
        super(id);
    }

    //  metoda abstracta calculeazaProductie
    public abstract double calculeazaProductie(double factorExtern);

    //  afisare producatori pentru comanda 5
    public abstract void afisProdTip();

    public static void afisProducatori(List<ProducatorEnergie> producatori) {
        for ( ProducatorEnergie producator : producatori) {
            System.out.print("Producator " + producator.getId());
            producator.afisProdTip();
            if ( producator.getStatusOperational() == true ) {
                System.out.println(" - Status: Operational");
            } else {
                System.out.println(" - Status: Defect");
            }
            System.out.println();
        }
    }
}
