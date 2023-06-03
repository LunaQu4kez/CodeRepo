public class TestClass {
    public static void main(String[] args) {
        QReader sc = new QReader();
        QWriter out = new QWriter();
        int a = sc.nextInt();
        String s = sc.next();
        out.println(a);
        out.println(s);
        out.close();
    }
}
