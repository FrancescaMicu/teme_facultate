package Tema1;

public class SistemSuportViata extends ConsumatorEnergie {
    //  constructor care seteaza prioritatea la 1
    public SistemSuportViata(String id, double cerereEnergie) {
        super(id, cerereEnergie, 1);
    }

    //  afisare pentru comanda 5
    @Override
    public void afisConTip() {
        System.out.print(" (SistemSuportViata) - ");
    }
}
