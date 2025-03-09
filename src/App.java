import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class App {

    public static void main(String[] args) throws IOException {
        // Path path = Paths.get("C:/MultiUser/JAVA/cbmp/input/zebra24.bmp");
        // byte[] data = Files.readAllBytes(path);
        // for (byte b : data){
        //     String st = String.format("%02X", b);
        //     System.out.print(st+ "\t");
        //     // System.out.print((char)b+ "\t");
        // }

        // File input = new File("C:/MultiUser/JAVA/cbmp/input/zebra24.bmp");

        // byte[] data = Files.readAllBytes(input);

        BMP bmp = new BMP("C:/MultiUser/JAVA/cbmp/Structure.txt");

        System.out.println(bmp.temp());

        File output = new File("C:/MultiUser/JAVA/cbmp/output/zebra24 copy.bmp");
        
        // Path path = Paths.get("C:/MultiUser/JAVA/cbmp/input/zebra24.bmp");
        Path path = Paths.get("C:/MultiUser/JAVA/cbmp/input/bmp_test.bmp");

        byte[] data = Files.readAllBytes(path);

        for (int i= 53;i!=data.length;i++){
            data[i]=(byte)(Math.random()*255);
        }

        System.out.println(data.length);

        Files.write(output.toPath(), data);


    }

}