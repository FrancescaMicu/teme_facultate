package Tema1;

public class SistemIluminat extends ConsumatorEnergie {
    //  constructor care seteaza prioritatea la 3
    public SistemIluminat(String id, double cerereEnergie) {
        super(id, cerereEnergie, 3);
    }

    //  afisare pentru comanda 5
    @Override
    public void afisConTip() {
        System.out.print(" (SistemIluminat) - ");
    }
}
