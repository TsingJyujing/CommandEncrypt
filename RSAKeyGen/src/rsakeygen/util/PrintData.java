package rsakeygen.util;

import java.io.FileWriter;
import java.io.IOException;

/**
 *
 * @author Yuan Yifan
 */
public class PrintData {
    public static void printByteArray(byte[] byteArray, int width) {
        System.out.printf("    ");
        if (byteArray.length < width) {
            for(int i = 0; i<byteArray.length; ++i) {
                System.out.printf("%02X ", i);
            }
        }else{
            for(int i = 0; i<width; ++i) {
                System.out.printf("%02X ", i);
            }
        }
        System.out.printf("\n");
        int printLines = (int)Math.ceil(((double)byteArray.length)/((double)width));
        for (int i = 0; i<printLines; ++i){
            System.out.printf("%03X ", i);
            int indexStart = i*width;
            int indexEnd = Math.min((i+1)*width, byteArray.length);
            for (int j = indexStart; j<indexEnd; j++) {
                System.out.printf("%02X ", byteArray[j]);
            }
            System.out.printf("\n");
        }
    }
    
    public static void saveByteArray(byte[] byteArray, String fileName) throws IOException{
        try (FileWriter fr = new FileWriter(fileName)) {
            for (int i = 0; i<byteArray.length; i++){
                fr.write(String.format("%02X ", byteArray[i]));
            }
            fr.flush();
            fr.close();
        }
    }

    public static void saveFlipByteArray(byte[] byteArray, String fileName) throws IOException{
        try (FileWriter fr = new FileWriter(fileName)) {
            for (int i = 0; i<byteArray.length; i++){
                fr.write(String.format("%02X ", byteArray[byteArray.length - 1 - i]));
            }
            fr.flush();
            fr.close();
        }
    }
}
