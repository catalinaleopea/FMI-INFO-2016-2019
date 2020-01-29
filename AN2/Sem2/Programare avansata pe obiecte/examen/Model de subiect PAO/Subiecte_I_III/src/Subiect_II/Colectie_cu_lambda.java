package Subiect_II;

import java.util.Comparator;
import java.util.LinkedList;
import java.util.List;
import java.util.Objects;
import java.util.stream.Collectors;
import static java.util.stream.Collectors.groupingBy;

class Automobil
{
    private String marca, model;
    private double capacitate;
    private int pret;

    public Automobil(String marca, String model, double capacitate, int pret)
    {
        this.marca = marca;
        this.model = model;
        this.capacitate = capacitate;
        this.pret = pret;
    }

    public String getMarca()
    {
        return marca;
    }

    public void setMarca(String marca)
    {
        this.marca = marca;
    }

    public String getModel()
    {
        return model;
    }

    public void setModel(String model)
    {
        this.model = model;
    }

    public double getCapacitate()
    {
        return capacitate;
    }

    public void setCapacitate(float capacitate)
    {
        this.capacitate = capacitate;
    }

    public int getPret()
    {
        return pret;
    }

    public void setPret(int pret)
    {
        this.pret = pret;
    }

    @Override
    public int hashCode()
    {
        int hash = 3;
        hash = 23 * hash + Objects.hashCode(this.marca);
        hash = 23 * hash + Objects.hashCode(this.model);
        hash = 23 * hash + (int) (Double.doubleToLongBits(this.capacitate) ^ (Double.doubleToLongBits(this.capacitate) >>> 32));
        hash = 23 * hash + this.pret;
        return hash;
    }

    @Override
    public boolean equals(Object obj)
    {
        if (this == obj)
            return true;
        if (obj == null)
            return false;
        if (getClass() != obj.getClass())
            return false;
        final Automobil other = (Automobil) obj;
        if (Double.doubleToLongBits(this.capacitate) != Double.doubleToLongBits(other.capacitate))
            return false;
        if (this.pret != other.pret)
            return false;
        if (!Objects.equals(this.marca, other.marca))
            return false;
        if (!Objects.equals(this.model, other.model))
            return false;
        return true;
    }
    
    @Override
    public String toString()
    {
        return marca + " " + model + " " + capacitate + " " + pret;
    }
}

public class Colectie_cu_lambda
{
    public static void main(String[] args)
    {
        LinkedList<Automobil> la = new LinkedList<>();
        
        la.add(new Automobil("BMW", "X5", 2000.5, 5000));
        la.add(new Automobil("Mercedes", "E Class", 3500, 6000));
        la.add(new Automobil("BMW", "X6", 2800.75, 4500));
        la.add(new Automobil("BMW", "X1", 1600.5, 5000));
        la.add(new Automobil("Mercedes", "S Class", 2200.25, 15000));
        la.add(new Automobil("Audi", "A6", 2000.5, 4000));
        
        //la.stream().forEach(System.out::println);
        
        //la.stream().filter(a -> a.getPret() >= 5000).sorted(Comparator.comparing(Automobil::getPret).reversed()).forEach(System.out::println);
        
        //la.stream().map(Automobil::getMarca).distinct().forEach(System.out::println);
        
        //List<Automobil> ln = la.stream().filter(a -> a.getCapacitate() >= 2000 && a.getCapacitate() <= 3000).collect(Collectors.toList());
        //ln.stream().forEach(System.out::println);
        
        la.stream().collect(groupingBy(Automobil::getMarca)).forEach((m,lm) -> {
                                                                                    System.out.print(m + ": "); 
                                                                                    lm.stream().map(Automobil::getModel).forEach(x -> System.out.print(x + ", "));
                                                                                    System.out.println();
                                                                                });
    }
}
