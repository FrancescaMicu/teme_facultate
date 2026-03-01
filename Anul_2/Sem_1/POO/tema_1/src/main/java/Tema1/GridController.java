package Tema1;

import java.util.ArrayList;
import java.util.List;
import java.util.Collections;

public class GridController {
    //  campuri
    private List<ProducatorEnergie> prodList;
    private List<ConsumatorEnergie> consList;
    private List<Baterie> baterList;

    //  campuri de stare pentru simulare
    private double productieTotala;
    private double cerereTotala;
    private boolean esteInBlackout;
    private List<String> istoric;
    private int cntTick;

    //  constructor
    public GridController() {
        this.prodList = new ArrayList<>();
        this.consList = new ArrayList<>();
        this.baterList = new ArrayList<>();
        this.esteInBlackout = false;
        this.istoric = new ArrayList<>();
        cntTick = 0;
    }

    //  metoda add pentru producator
    public void addProducatorEnergie(ProducatorEnergie p) {
        this.prodList.add(p);
    }

    //  metoda add pentru consumator
    public void addConsumatorEnergie(ConsumatorEnergie c) {
        this.consList.add(c);
    }

    //  metoda add pentru baterie
    public void addBaterie(Baterie b) {
        this.baterList.add(b);
    }

    //  getter pentru producatori
    public List<ProducatorEnergie> getProdList() {
        return prodList;
    }

    //  getter pentru consumatori
    public List<ConsumatorEnergie> getConsList() {
        return consList;
    }

    //  getter pentru baterie
    public List<Baterie> getBaterieList() {
        return baterList;
    }

    //  getter pentru esteInBlackout
    public boolean getEsteInBlackout() {
        return esteInBlackout;
    }

    //  getter pentru istoric
    public List<String> getIstoric() {
        return istoric;
    }

    //  metoda simuleazaTick()
    public void simuleazaTick(double factorSoare, double factorVant) {
        //  contorizare tick-uri
        cntTick++;

        //  verificare daca este in blackout
        if ( esteInBlackout == true ) {
            return;
        }

        //  resetare campuri pentru tick-ul curent
        productieTotala = 0;
        cerereTotala = 0;

        //  resetare consumatori pentru a fi conectati la retea
        for ( ConsumatorEnergie consumator: consList ) {
            consumator.cupleazaLaRetea();
        }

        //  calculul productiei totale
        for ( ProducatorEnergie producator: prodList ) {
            if ( producator.getStatusOperational() == true ) {
                if ( producator instanceof PanouSolar ) {
                    productieTotala += producator.calculeazaProductie(factorSoare);
                } else if ( producator instanceof TurbinaEoliana ) {
                    productieTotala += producator.calculeazaProductie(factorVant);
                } else if ( producator instanceof ReactorNuclear ) {
                    productieTotala += producator.calculeazaProductie(0);
                }
            }
        }

        //  calculul cererii totale
        cerereTotala = 0;
        for ( ConsumatorEnergie consumator: consList ) {
            if ( consumator.getStatusOperational() == true ) {
                cerereTotala += consumator.getCerereCurenta();
            }
        }
        ArrayList<String> consDecupl = new ArrayList<>();

        //  calculul balansarii
        double delta = productieTotala - cerereTotala;
        double deficit;

        //  scenariul 1
        if ( delta > 0 ) {
            for ( Baterie baterie : baterList ) {
                if ( baterie.getStatusOperational() == true ) {
                    delta = baterie.incarca(delta);
                }
            }
        //  scenariul 2
        } else if ( delta < 0 ) {
            deficit = (-1) * delta;
            for ( Baterie baterie : baterList ) {
                if ( baterie.getStatusOperational() == true ) {
                    double energ = baterie.descarca(deficit);
                    deficit -= energ;
                }
            }
            //  scenariul 3
            if ( deficit > 0 ) {
                //  sortare dupa prioritate
                Collections.sort(consList);
                for ( ConsumatorEnergie consumator : consList ) {
                    if ( consumator.getPrioritate() != 1 && deficit > 0 ) {
                        consumator.decupleazaDeLaRetea();
                        deficit -= consumator.getCerereEnergie();
                        consDecupl.add(consumator.getId());

                        //  adaugare comanda in istoric
                        String comanda = "Tick " + cntTick + ": Deficit - Decuplat " + consumator.getId();
                        istoric.add(comanda);
                    }
                }
                //  scenariul 4
                if ( deficit > 0 ) {
                    esteInBlackout = true;
                    System.out.println("BLACKOUT! SIMULARE OPRITA.");

                    //  adaugare comanda in istoric
                    String comanda = "Tick "+ cntTick + ": BLACKOUT! SIMULARE OPRITA.";
                    istoric.add(comanda);
                    return;
                }
            }
        }
        //  calculul energiei ramase in baterii
        double energBat = 0;
        for ( Baterie bat: baterList ) {
            energBat += bat.getEnergieStocata();
        }

        //  afisare detalii tick
        afisTick(energBat, consDecupl);
    }

    //  metoda pentru afisarea detaliilor unui tick
    public void afisTick(double energBat, ArrayList<String> consDecupl) {
        System.out.print("TICK: Productie ");
        System.out.printf("%.2f", productieTotala);
        System.out.print(", Cerere ");
        System.out.printf("%.2f", cerereTotala);
        System.out.print(". Baterii: ");
        System.out.printf("%.2f", energBat);
        System.out.print(" MW. ");
        System.out.println("Decuplati: " + consDecupl.toString());
    }

    //  metoda pentru validarea id-ului primit
    public ComponentaRetea idValid (String id) {
        for ( ProducatorEnergie prod: getProdList() ) {
            if ( prod.getId().equals(id) ) {
                return prod;
            }
        }
        for ( ConsumatorEnergie con: getConsList() ) {
            if ( con.getId().equals(id) ) {
                return con;
            }
        }
        for ( Baterie bat: getBaterieList() ) {
            if ( bat.getId().equals(id) ) {
                return bat;
            }
        }
        return null;
    }
}
