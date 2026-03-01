package Tema1;

public class ReactorNuclear extends ProducatorEnergie {
    //  campul putereConstanta
    private double putereConstanta;

    //  constructor
    public ReactorNuclear(double putereConstanta, String id) {
        super(id);
        this.putereConstanta = putereConstanta;
    }

    //  getter putereConstanta
    public double getPutereConstanta() {
        return putereConstanta;
    }

    //  setter putereConstanta
    public void setPutereConstanta(double putereConstanta) {
        this.putereConstanta = putereConstanta;
    }

    //  metoda factorExtern()
    @Override
    public double calculeazaProductie(double factorExtern) {
        if ( getStatusOperational() == true ) {
            return putereConstanta;
        }
        return 0;
    }

    //  afisare pentru comanda 5
    @Override
    public void afisProdTip() {
        System.out.print(" (ReactorNuclear) - ");
        System.out.printf("PutereBaza: %.2f", getPutereConstanta());
    }
}
