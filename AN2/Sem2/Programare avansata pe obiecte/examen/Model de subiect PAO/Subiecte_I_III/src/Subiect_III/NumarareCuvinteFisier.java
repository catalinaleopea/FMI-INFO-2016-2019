package Subiect_III;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

class FirNumarareCuvinteFisier extends Thread
{
    private String numeFisier;
    private String cuvantCautat;
    private int nrAparitii;

    public FirNumarareCuvinteFisier(String numeFisier, String cuvantCautat)
    {
        this.numeFisier = numeFisier;
        this.cuvantCautat = cuvantCautat;
        this.nrAparitii = 0;
    }

    public int getNrAparitii()
    {
        return nrAparitii;
    }

    @Override
    public void run()
    {
        try
        {
            Scanner in = new Scanner(new File(numeFisier));
            
            while(in.hasNextLine())
            {
                String linie = in.nextLine();
                String []cuvinte = linie.split("[ .,\n]+");
                for(int i = 0; i < cuvinte.length; i++)
                    if(cuvinte[i].equals(cuvantCautat))
                        nrAparitii++;
            }
            
            in.close();
        }
        catch (FileNotFoundException ex)
        {
            System.out.println("Eroare deschidere fisier!");
        }
    }
}

public class NumarareCuvinteFisier
{
    public static void main(String[] args)
    {
        Scanner in = new Scanner(System.in);
        
        System.out.println("Cuvantul cautat: ");        
        String cuv = in.next();
        
        FirNumarareCuvinteFisier f_1 = new FirNumarareCuvinteFisier("exemplu_1.txt" , cuv);
        FirNumarareCuvinteFisier f_2 = new FirNumarareCuvinteFisier("exemplu_2.txt" , cuv);
        FirNumarareCuvinteFisier f_3 = new FirNumarareCuvinteFisier("exemplu_3.txt" , cuv);

        try
        {
            f_1.start();
            f_1.join();
            f_2.start();
            f_2.join();
            f_3.start();
            f_3.join();
        } 
        catch (InterruptedException ex)
        {
            System.out.println("Eroare fire de executare!");
        }
        
        int t = f_1.getNrAparitii() + f_2.getNrAparitii() + f_3.getNrAparitii();
        
        System.out.println("Cuvantul " + cuv + " apare de " + t + " ori in fisierele date!");
    }
}
