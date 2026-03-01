package Tema1;

public class PanouSolar extends ProducatorEnergie {
    //  campul putereMaxima
    private double putereMaxima;

    //  constructor
    public PanouSolar(double putereMaxima, String id) {
        super(id);
        this.putereMaxima = putereMaxima;
    }

    //  getter putereMaxima
    public double getPutereMaxima() {
        return putereMaxima;
    }

    //  setter putereMaxima
    public void setPutereMaxima(double putereMaxima) {
        this.putereMaxima = putereMaxima;
    }

    //  implementarea metodei calculeazaProductie()
    @Override
    public double calculeazaProductie(double factorExtern) {
        if ( getStatusOperational() == false ) {
            return 0;
        }
        return putereMaxima * factorExtern;
    }

    //  afisare pentru comanda 5
    @Override
    public void afisProdTip() {
        System.out.print(" (PanouSolar) - ");
        System.out.printf("PutereBaza: %.2f", getPutereMaxima());
    }
}
