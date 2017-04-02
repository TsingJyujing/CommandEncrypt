package rsakeygen.util;


/**
 *
 * @author Yuan Yifan
*/
public class Run {  
    public static void main(String[] args) throws Exception { 
        String savingPath = "../RSACrypt/key/";
        long tick;
        RSAUtility ru = new RSAUtility();
        System.out.println("密钥生成中...");
        ru.generateKey(1024);
        System.out.println("密钥生成完了.");
        

        System.out.println("公钥:");
        PrintData.printByteArray(ru.publicKey.getPublicExponent().toByteArray(), 16);
        PrintData.saveFlipByteArray(ru.publicKey.getPublicExponent().toByteArray(), savingPath + "public_key.flip.hex");
        PrintData.saveByteArray(ru.publicKey.getPublicExponent().toByteArray(),  savingPath + "public_key.hex");
        
        System.out.println("私钥:");
        PrintData.printByteArray(ru.privateKey.getPrivateExponent().toByteArray(), 16);
        PrintData.saveFlipByteArray(ru.privateKey.getPrivateExponent().toByteArray(),  savingPath + "private_key.flip.hex");
        PrintData.saveByteArray(ru.privateKey.getPrivateExponent().toByteArray(),  savingPath + "private_key.hex");
        
        System.out.println("模数 M:");
        PrintData.printByteArray(ru.privateKey.getModulus().toByteArray(), 16);
        PrintData.saveFlipByteArray(ru.privateKey.getModulus().toByteArray(),  savingPath + "modulus.flip.hex");
        PrintData.saveByteArray(ru.privateKey.getModulus().toByteArray(),  savingPath + "modulus.hex");
        
        for (int i = 0;i<10;++i){
        // 使用公钥加密  
        String msg = "It's an interesting algorithm.";  
        String enc = "UTF-8";  
  
        // 使用公钥加密私钥解密  
        System.out.println("原文: ");  
        //PrintData.printByteArray(msg.getBytes(enc), 16);
        tick = System.currentTimeMillis();
        byte[] result = RSAUtility.handleData(ru.publicKey, msg.getBytes(enc), 1);  
        System.out.printf("Public encrypt time:%dms\n",System.currentTimeMillis() - tick);
        System.out.println("加密: ");
        
        //PrintData.printByteArray(result, 16);
        tick = System.currentTimeMillis();
        byte[] deresult = RSAUtility.handleData(ru.privateKey, result, 0);  
        System.out.printf("Private decrypt time:%dms\n",System.currentTimeMillis() - tick);
        System.out.println("解密: " + new String(deresult, enc));  
  
        msg = "It is not an interesting algorithm.";  
        // 使用私钥加密公钥解密  
        System.out.println("原文: ");  
        //PrintData.printByteArray(msg.getBytes(enc), 16);
        tick = System.currentTimeMillis();
        byte[] result2 = RSAUtility.handleData(ru.privateKey, msg.getBytes(enc), 1);  
        System.out.printf("Private encrypt time:%dms\n",System.currentTimeMillis() - tick);
        System.out.println("加密: ");
        //PrintData.printByteArray(result2, 16);
        tick = System.currentTimeMillis();
        byte[] deresult2 = RSAUtility.handleData(ru.publicKey, result2, 0);  
        System.out.printf("Public encrypt time:%dms\n",System.currentTimeMillis() - tick);
        System.out.println("解密: " + new String(deresult2, enc)); 
        //PrintData.printByteArray(deresult2, 16);
        }
    }  
}  
