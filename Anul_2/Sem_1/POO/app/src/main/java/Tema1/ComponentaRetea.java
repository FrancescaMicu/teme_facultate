package Tema1;

public abstract class ComponentaRetea {
    //  campuri
    private String id;
    private boolean statusOperational;

    //  constructor
    public ComponentaRetea(String id) {
        this.id = id;
        this.statusOperational = true;
    }

    //  getter id
    public String getId() {
        return id;
    }

    //  getter statusOperational
    public boolean getStatusOperational() {
        return statusOperational;
    }

    //  setter statusOperational
    public void setStatusOperational(boolean statusOperational) {
        this.statusOperational = statusOperational;
    }
}
