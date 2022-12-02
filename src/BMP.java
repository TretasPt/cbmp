import java.io.File;
import java.nio.file.Path;
import java.nio.file.Paths;
// import java.io.ByteArrayInputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;

public class BMP {

    private final FileInputStream file;

    private FileHeader fileHeader;
    private DIBHeader dibheader;;
    private ExtraBitMasks extraBitMasks;
    private ColorTable colorTable;
    private Gap gap1;
    private PixelArray pixelArray;
    private Gap gap2;
    private ICCColorProfile colorProfile;

    BMP(File path) throws FileNotFoundException {//MAIN
        file= new FileInputStream(path);
    }

    BMP(Path path) throws FileNotFoundException {//EXTRA
        this(path.toFile());
    }

    BMP(String path) throws FileNotFoundException {//EXTRA
        this(new File(path));
    }

    public int temp(){
        try {
            return file.available();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return -1;
    }
}