import java.math.BigInteger;
import java.util.Scanner;

public class Demo {
    public String add(String s1, String s2) {
        BigInteger b1 = new BigInteger(s1);
        BigInteger b2 = new BigInteger(s2);
        return b1.add(b2).toString();
    }

    public String sub(String s1, String s2) {
        BigInteger b1 = new BigInteger(s1);
        BigInteger b2 = new BigInteger(s2);
        return b1.subtract(b2).toString();
    }

    public String mul(String s1, String s2) {
        BigInteger b1 = new BigInteger(s1);
        BigInteger b2 = new BigInteger(s2);
        return b1.multiply(b2).toString();
    }

    String quotient, residue;
    public void div(String s1, String s2) {
        BigInteger b1 = new BigInteger(s1);
        BigInteger b2 = new BigInteger(s2);
        BigInteger[] res = b1.divideAndRemainder(b2);
        quotient = res[0].toString();
        residue = res[1].toString();
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String s1 = sc.next();
        String s2 = sc.next();
        Demo d = new Demo();
        System.out.println(d.add(s1, s2));
        System.out.println(d.sub(s1, s2));
        System.out.println(d.mul(s1, s2));
        d.div(s1, s2);
        System.out.println(d.quotient + " " + d.residue);
    }
}
