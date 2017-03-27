package rsakeygen.util;

import java.io.FileInputStream;  
import java.io.FileNotFoundException;  
import java.io.FileOutputStream;  
import java.io.IOException;  
import java.io.ObjectInputStream;  
import java.io.ObjectOutputStream;  
import java.security.Key;  
import java.security.KeyPair;  
import java.security.KeyPairGenerator;  
import java.security.NoSuchAlgorithmException;  
import java.security.interfaces.RSAPrivateKey;  
import java.security.interfaces.RSAPublicKey;  
  
import javax.crypto.Cipher;  
import javax.crypto.NoSuchPaddingException;  
/**
 *
 * @author Yuan Yifan
 */

public class RSAUtility implements java.io.Serializable{
    
    public RSAPrivateKey privateKey;
    public RSAPublicKey publicKey;
    
    /**
     *
     * @param keySize 密钥大小，默认为1024
     * @throws NoSuchAlgorithmException
     */
    public void generateKey(int keySize) throws NoSuchAlgorithmException {
        // KeyPairGenerator类用于生成公钥和私钥对，基于RSA算法生成对象  
        KeyPairGenerator keyPairGen = KeyPairGenerator.getInstance("RSA");  
        keyPairGen.initialize(keySize);  // 初始化密钥对生成器，密钥大小为keySize位  
        KeyPair keyPair = keyPairGen.generateKeyPair(); // 生成一个密钥对，保存在keyPair中  
        privateKey = (RSAPrivateKey) keyPair.getPrivate(); // 得到私钥  
        publicKey = (RSAPublicKey) keyPair.getPublic(); // 得到公钥  
    }
  
    /** 
     *  
     * @param k 
     * @param data 
     * @param encrypt 
     *            1 加密 0解密 
     * @return 
     * @throws NoSuchPaddingException 
     * @throws Exception 
     */  
    public static byte[] handleData(Key k, byte[] data, int encrypt)  
            throws Exception {  
        if (k != null) {  
            Cipher cipher = Cipher.getInstance("RSA");  
            switch (encrypt) {
                case 1:
                {
                    cipher.init(Cipher.ENCRYPT_MODE, k);
                    byte[] resultBytes = cipher.doFinal(data);
                    return resultBytes;
                }
                case 0:
                {
                    cipher.init(Cipher.DECRYPT_MODE, k);
                    byte[] resultBytes = cipher.doFinal(data);  
                    return resultBytes;
                }
                default:
                    System.out.println("参数必须为: 1 加密 0解密");
                    break;
            }
        }  
        return null;  
    }  
}
