package Tema1;

import java.util.List;

public abstract class ConsumatorEnergie extends ComponentaRetea implements Comparable<ConsumatorEnergie> {
    //  campuri
    protected double cerereEnergie;
    protected int prioritate;
    protected boolean esteAlimentat;

    //  constructor
    public ConsumatorEnergie(String id, double cerereEnergie, int prioritate) {
        super(id);
        this.cerereEnergie = cerereEnergie;
        this.prioritate = prioritate;
        this.esteAlimentat = true;
    }

    //  getter prioritate
    public int getPrioritate() {
        return prioritate;
    }

    //  getter cerereEnergie
    public double getCerereEnergie() {
        return cerereEnergie;
    }

    //  getter esteALimentat
    public boolean getEsteAlimentat() {
        return esteAlimentat;
    }

    //  setter prioritate
    public void setPrioritate(int prioritate) {
        this.prioritate = prioritate;
    }

    //  setter esteAlimentat
    public void setEsteAlimentat(boolean esteAlimentat) {
        this.esteAlimentat = esteAlimentat;
    }

    //  setter cerereEnergie
    public void setCerereEnergie(double cerereEnergie) {
        this.cerereEnergie = cerereEnergie;
    }

    //  metoda getCerereCurenta()
    public double getCerereCurenta() {
        if ( esteAlimentat== true && getStatusOperational() == true ) {
            return cerereEnergie;
        }
        return 0;
    }

    //  metodele cupleazaLaRetea() si decupleazaDeLaRetea()
    public void cupleazaLaRetea() {
        esteAlimentat = true;
    }
    public void decupleazaDeLaRetea() {
        esteAlimentat = false;
    }

    //  metoda compareTo pentru sortare
    @Override
    public int compareTo(ConsumatorEnergie consumatorEnergie) {
        return consumatorEnergie.getPrioritate() - this.prioritate;
    }

    //  afisare producatori pentru comanda 5
    public abstract void afisConTip();

    public static void afisConsumatori(List<ConsumatorEnergie> consumatori) {
        for ( ConsumatorEnergie consumator: consumatori ) {
            System.out.print("Consumator " + consumator.getId());
            consumator.afisConTip();
            System.out.printf("Cerere: %.2f", consumator.getCerereEnergie());
            System.out.print(" - Prioritate: " + consumator.getPrioritate());
            if ( consumator.getEsteAlimentat() == true ) {
                System.out.println(" - Status: Alimentat");
            } else {
                System.out.println(" - Status: Decuplat");
            }
            System.out.println();
        }
    }
}
