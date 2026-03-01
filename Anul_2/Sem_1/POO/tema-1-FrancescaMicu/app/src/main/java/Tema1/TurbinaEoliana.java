package Tema1;

public class TurbinaEoliana extends ProducatorEnergie {
    //  campul putereBaza
    private double putereBaza;

    //  constructor
    public TurbinaEoliana(double putereBaza, String id) {
        super(id);
        this.putereBaza = putereBaza;
    }

    //  getter putereBaza
    public double getPutereBaza() {
        return putereBaza;
    }

    //  setter putereBaza
    public void setPutereBaza(double putereBaza) {
        this.putereBaza = putereBaza;
    }

    //  metoda calculeazaProductie()
    @Override
    public double calculeazaProductie(double factorExtern) {
        if ( getStatusOperational() == false ) {
            return 0;
        }
        return putereBaza * factorExtern;
    }

    //  afisare pentru comanda 5
    @Override
    public void afisProdTip() {
        System.out.print(" (TurbinaEoliana) - ");
        System.out.printf("PutereBaza: %.2f", getPutereBaza());
    }
}
