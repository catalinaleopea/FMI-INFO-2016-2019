package Subiect_I;

import java.sql.SQLException;

class A
{
    public int x = 0;
}

public class Test
{
    public static A metoda()
    {
        A a = new A();
        try
        {
            a.x += 1;
            throw new NullPointerException();
        }
        catch(Exception e)
        {
            a.x += 2;
        }
        finally
        {
            a.x += 3;
        }
        
        return a;
    }
    
    public static void main(String[] args)
    {
        A ob = metoda();
        System.out.println(ob.x);
    }
}

/*
class Tablou
{

    static void met(int[] a, int b)
    {
        int aux;
        aux = a[0];
        a[0] = b;
        b = aux;
    }
}

public class Test
{

    public static void main(String[] args)
    {
        int a[] = {1, 2, 3, 4, 5};
        int b = 6;
        
        Tablou.met(a, b);
        
        int s = b;
        for (int i = 0; i < a.length; i++)
            s = s + a[i];
        
        System.out.println(s);
    }
}
*/
/*
class A
{
    public int x = 1;
    void afisare() 
    {
        System.out.println(x);           
    }
}

class B extends A
{
    public int x = 2;
    void afisare() 
    {
        System.out.println(++x);           
    }
}

public class Test
{
    public static void main(String[] args)
    {
        A ob = new B();
        System.out.println(++ob.x);
    }
}
 */

 /*
class C1
{
    int x = 1;

    int f(int x)
    {
        return this.x + x;
    }
    
    int f(int x, int y)
    {
        return this.x + y;
    }
}

class C2 extends C1
{
    int f(int x)
    {
        return this.x;
    }
}

public class Test
{

    public static void main(String[] args)
    {
        C1 ob = new C2();
        System.out.println(ob.f(1) + ob.f(2,2));
    }
}
 */

 /*
public class Test
{

    public static void main(String[] args)
    {
        String s = new String("Examen");
        if (s == "Examen")
            System.out.print("A");
        else
            System.out.print("B");
        if (s.equals("Examen"))
            System.out.print("C");
        else
            System.out.print("D");

    }
}
 */

 /*
public class Test
{

    public static void main(String[] args)
    {
        String s = "Examen", t = "Examen";
        if (s == t)
            System.out.print("A");
        else
            System.out.print("B");
        if (s.equals(t))
            System.out.print("C");
        else
            System.out.print("D");

    }
}
 */
 /*
class A{
    public int x = 1;
    public A() { x++; }
}

class B extends A{
    public B() { x++; }
}

class C extends B{
    public int x = 1;
    public C() {  x++; }
}

public class Test{
    public static void main(String[] args){
        B b = new B();
        C c = new C();
        System.out.println(b.x + " " + c.x);
    }
}
 */

 /*
class Test
{

    String str = "a";

    void A()
    {
        try
        {
            str += "b";
            B();
        } catch (Exception e)
        {
            str += "c";
        }
    }

    void B() throws Exception
    {
        try
        {
            str += "d";
            C();
        } catch (Exception e)
        {
            throw new Exception();
        } 
        finally
        {
            str += "e";
        }

        str += "f";
    }

    void C() throws Exception
    {
        throw new Exception();
    }
  
    public static void main(String[] args) throws Exception
    {
        Test ob = new Test();
        ob.A();
        System.out.println(ob.str);
    }
}
 */
 /*
class Tablou
{
    int[] met(int []a)
    {
        a[0] = -a[0];
                
        a = new int[a.length];
        a[0] = 1;
        
        return a;
    }
}

public class Test
{
    public static void main(String[] args)
    {
        int a[] = {1,2,3,4,5};
        
        int b[] = new Tablou().met(a);
        int s = 0;
        for(int i = 0; i < a.length; i++)
            s = s + a[i]  +b[i];
        System.out.println(s);
        for(int i = 0; i < a.length; i++)
            System.out.println(a[i] + " " + b[i]);
        
        
    }
}
 */

 /*
class ABC
{
    public int x;
    public int y;

    public ABC()
    {
        met();
    }

    public void met()
    {
        x = x + 3;
        y = y + 1;
    }
}

public class Grile
{
    public static void main(String[] args)
    {
        ABC t = new ABC();
        ABC u = new ABC();
        System.out.println(t.x + u.y);
    }
}
 */

 /*
class A
{
    String sir = "";
    public A(String sir)
    {
        this.sir = this.sir + sir + "A";
    }
}

class B extends A
{

    public B(String sir)
    {
        super(sir);
        this.sir = this.sir + sir + "B";
    }
}

class C extends B
{
    public C(String sir)
    {
        super(sir);
        this.sir = this.sir + sir + "C";
    }
}

public class Grile
{

    public static void main(String[] args)
    {
        //C ob = new C("D");
        System.out.println(new C("D").sir);
    }
}
 */

 /*
class A
{
    public static int f(int x)
    {
        return x+1;
    }

    public int g(int x)
    {
        return x+2;
    }
}

class B extends A
{

    public static int f(int x)
    {
        return x+4;
    }

    public int g(int x)
    {
        return x+3;
    }
}

public class Grile
{

    public static void main(String[] args)
    {
        A a = new B();
        System.out.println(a.f(1) + a.g(3));
    }
}
 */

 /*
public class Grile
{
    public static void main(String[] args) 
    {
        String s = "abcbd";
        String t = "Programare";
        int p = t.indexOf(s.charAt(0));
        t = t.substring(0, p) + t.substring(p+1);
        System.out.println(t);
    }
}
 */

 /* 
class C
{
    void metoda()
    {
        throw new IllegalArgumentException();
        //throw new NullPointerException();
    }
    
    void test()
    {
        try
        {
            metoda();
        }
        catch (NullPointerException ex)
        {
            System.out.print("NPE ");
        }
        catch (Exception ex)
        {
            System.out.print("EX ");
        }
        finally
        {
            System.out.print("FIN ");
        }
        System.out.println("END");
    }
}

public class Grile
{
    public static void main(String[] args)
    {
        C ob = new C();
        
        ob.test();
    }
}
 */

 /*
class C
{
    public static int a = 1;
}

public class Grile
{
    public static void main(String[] args)
    {
        C ob1 = new C();
        C ob2 = new C();
        ob1.a++;
        System.out.println(++ob2.a);
    }
}
 */
