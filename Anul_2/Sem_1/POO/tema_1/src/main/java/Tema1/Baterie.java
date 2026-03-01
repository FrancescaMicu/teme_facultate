package Tema1;

import java.util.List;

public class Baterie extends ComponentaRetea {
    //  campuri
    private double capacitateMaxima;
    private double energieStocata;

    //  constructor
    public Baterie(String id, double capacitateMaxima) {
        super(id);
        this.capacitateMaxima = capacitateMaxima;
        this.energieStocata = 0;
    }

    //  getter capacitateMaxima
    public double getCapacitateMaxima() {
        return capacitateMaxima;
    }

    //  getter energieStocata
    public double getEnergieStocata() {
        return energieStocata;
    }

    //  setter capacitateMaxima
    public void setCapacitateMaxima(double capacitateMaxima) {
        this.capacitateMaxima = capacitateMaxima;
    }

    //  setter energieStocata
    public void setEnergieStocata(double energieStocata) {
        this.energieStocata = energieStocata;
    }

    //  metoda double incarca(double energieDisponibila)
    public double incarca(double energieDisponibila) {
        //  verificare baterie defecta
        if ( getStatusOperational() == false ) {
            return energieDisponibila;
        }
        //  calculare surplus
        double surplus;
        if ( energieDisponibila <= capacitateMaxima - energieStocata ) {
            energieStocata += energieDisponibila ;
            surplus = 0;
        } else {
            double energieStocInitiala = energieStocata;
            energieStocata = capacitateMaxima;
            surplus = energieDisponibila - (capacitateMaxima - energieStocInitiala);
        }
        return surplus;
    }

    //  metoda double descarca(double energieCeruta)
    public double descarca(double energieCeruta) {
        //  verificare baterie defecta
        if ( getStatusOperational() == false ) {
            return 0;
        }
        //  calculare energie care poate furnizata
        double diferenta = energieStocata - energieCeruta;
        double energieFurnizata;
        if ( diferenta >= 0 ) {
            energieStocata = diferenta;
            energieFurnizata = energieCeruta;
        } else {
            energieFurnizata = energieStocata;
            energieStocata = 0;
        }
        return energieFurnizata;
    }

    //  afisare baterii pentru comanda 5
    public static void afisBaterii(List<Baterie> baterii) {
        for ( Baterie baterie: baterii ) {
            System.out.print("Baterie " + baterie.getId());
            System.out.printf(" - Stocare: %.2f/%.2f", baterie.getEnergieStocata(), baterie.getCapacitateMaxima());
            if ( baterie.getStatusOperational() == true ) {
                System.out.println(" - Status: Operational");
            } else {
                System.out.println(" - Status: Defect");
            }
        }
    }
}
