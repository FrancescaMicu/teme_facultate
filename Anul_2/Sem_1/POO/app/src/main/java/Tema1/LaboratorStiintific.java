package Tema1;

public class LaboratorStiintific extends ConsumatorEnergie{
    //  constructor care seteaza prioritatea la 2
    public LaboratorStiintific(String id, double cerereEnergie) {
        super(id, cerereEnergie, 2);
    }

    //  afisare pentru comanda 5
    @Override
    public void afisConTip() {
        System.out.print(" (LaboratorStiintific) - ");
    }
}
